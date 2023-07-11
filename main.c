#include "prompt.h"
#include "headers.h"
#include "cummands.h"
#include "proc_list.h"
#include "history.h"
#include "sighand.h"

char *hissarr[20];
int flagfg = 0;
int fgpid = 0;
pid_t shellpid = 0;
int jobnum = 1;

char **tokenization(char *line, int *numtokens, char *delimiter)
{
    if (strcmp(delimiter, ">>") == 0)
    {
        char **tokenarr = (char **)malloc(1000 * sizeof(char *));
        int flag = 1;
        for (int i = 0; i < strlen(line); i++)
        {
            if (line[i] == '>')
            {
                if (line[i + 1] == '>')
                {
                    line[i] = ' ';
                    line[i + 1] = '*';
                    flag = 0;
                }
            }
        }
        if (flag == 1)
        {
            // char **tokenarr = (char **)malloc(1000 * sizeof(char *));
            char *token = strtok(line, "&");
            int i = 0;
            while (token != NULL)
            {
                tokenarr[i] = (char *)malloc(sizeof(char) * strlen(token));
                strcpy(tokenarr[i], token);
                token = strtok(NULL, "&");
                i++;
            }
            tokenarr[i] = NULL;
            *numtokens = i;
            return tokenarr;
        }
        else
        {
            // char **tokenarr = (char **)malloc(1000 * sizeof(char *));
            char *token = strtok(line, "*");
            int i = 0;
            while (token != NULL)
            {
                tokenarr[i] = (char *)malloc(sizeof(char) * strlen(token));
                strcpy(tokenarr[i], token);
                token = strtok(NULL, "*");
                i++;
            }
            tokenarr[i] = NULL;
            *numtokens = i;
            return tokenarr;
        }
    }
    else
    {
        char **tokenarr = (char **)malloc(1000 * sizeof(char *));
        char *token = strtok(line, delimiter);
        int i = 0;
        while (token != NULL)
        {
            tokenarr[i] = (char *)malloc(sizeof(char) * strlen(token));
            strcpy(tokenarr[i], token);
            token = strtok(NULL, delimiter);
            i++;
        }
        tokenarr[i] = NULL;
        *numtokens = i;
        return tokenarr;
    }
}
char *removeSpacesFromStr(char *string)
{
    int non_space_count = 0;
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] != ' ')
        {
            string[non_space_count] = string[i];
            non_space_count++;
        }
    }
    string[non_space_count] = '\0';
    return string;
}
void redirecthandler(char *token, int flagfg)
{
    int backupin = dup(fileno(stdin));
    int backupout = dup(fileno(stdout));
    int appendcount = 0;
    char **tokenarrappend = tokenization(token, &appendcount, ">>");
    if (appendcount > 1)
    {
        char *filename = (char *)malloc(1000 * sizeof(char));
        strcpy(filename, tokenarrappend[1]);
        removeSpacesFromStr(filename);
        int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, fileno(stdout));
        close(fd);
    }

    int writecount = 0;
    char **writetokenarr = tokenization(tokenarrappend[0], &writecount, ">");
    if (writecount > 1)
    {
        char *filename = (char *)malloc(1000 * sizeof(char));
        strcpy(filename, writetokenarr[1]);
        removeSpacesFromStr(filename);
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        // int fd = open(filename, O_WRONLY | O_CREAT , 0644);
        dup2(fd, fileno(stdout));
        close(fd);
    }

    int inputcount = 0;
    char **tokenarrinput = tokenization(writetokenarr[0], &inputcount, "<");
    if (inputcount > 1)
    {
        char *filename = (char *)malloc(1000 * sizeof(char));
        strcpy(filename, tokenarrinput[1]);
        removeSpacesFromStr(filename);
        int fd = open(filename, O_RDONLY);
        if (fd < 0)
        {
            perror("Error: File not found");
            return;
        }
        dup2(fd, fileno(stdin));
        close(fd);
    }

    int numtokens = 0;
    char **tokenarr = tokenization(tokenarrinput[0], &numtokens, " \t\r");

    run_cummand(tokenarr, numtokens, flagfg);
    free(tokenarr);
    free(tokenarrinput);
    free(writetokenarr);
    free(tokenarrappend);
    dup2(backupin, fileno(stdin));
    dup2(backupout, fileno(stdout));
    close(backupin);
    close(backupout);
}

void handlepiping(char *token, int flagfg)
{
    int numtokens = 0;
    char **tokenarr = tokenization(token, &numtokens, "|");
    if (numtokens == 1)
    {
        redirecthandler(tokenarr[0], flagfg);
        return;
    }
    int backupinput = dup(fileno(stdin));
    int backupoutput = dup(fileno(stdout));

    for (int i = 0; i < numtokens - 1; i++)
    {
        int fd[2];
        pipe(fd);
        int pid = fork();
        if (pid == 0)
        {
            dup2(fd[1], fileno(stdout));
            close(fd[0]);
            close(fd[1]);
            redirecthandler(tokenarr[i], flagfg);
            dup2(backupoutput, fileno(stdout));
            dup2(backupinput, fileno(stdin));
            exit(0);
        }
        else
        {
            dup2(fd[0], fileno(stdin));
            close(fd[0]);
            close(fd[1]);
            waitpid(pid, NULL, 0);
        }
    }
    dup2(backupoutput, fileno(stdout));
    redirecthandler(tokenarr[numtokens - 1], flagfg);
    dup2(backupinput, fileno(stdin));

}

void child_handler()
{
    int code;
    pid_t pid;
    while ((pid = waitpid(-1, &code, WNOHANG | WUNTRACED)) > 0)
    {
        char *status =
            (WIFEXITED(code) || WIFSTOPPED(code)) ? "normally" : "abnormally";
        char *process = get_proc_name(pid);
        if (process == NULL)
        {
            endtime=time(NULL);
            last_time = endtime-starttime;
        }
        else
        {
            printf("\n%s with pid %d exited %s\n", process, pid, status);
            prompt();
            fflush(stdout);
            fflush(stderr);
        }
    }
}

void die(const char *s)
{
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

/**
 * Enable row mode for the terminal
 * The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing.
 * Terminal attributes can be read into a termios struct by tcgetattr().
 * After modifying them, you can then apply them to the terminal using tcsetattr().
 * The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.
 * The c_lflag field is for “local flags”
 */
void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

int cmpmain(const void *a, const void *b)
{
    // return strcmp(*(char **)a, *(char **)b);
    struct dirent *entry1 = *(struct dirent **)a;
    struct dirent *entry2 = *(struct dirent **)b;
    return (strcasecmp(entry1->d_name, entry2->d_name));
}
int main()
{
    init_proc_list();
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    signal(SIGCHLD, child_handler);
    HOME = getcwd(NULL, 0);
    char *temp = (char *)malloc(sizeof(char) * (strlen(HOME) + 30));
    sprintf(temp, "%s/history.txt", HOME);
    readfile(temp);

    char *inp = malloc(sizeof(char) * 1000);
    char c;
    while (1)
    {
        CURRDIR = HOME;
        // prompt();
        // last_time = 0;
        char a[1024];

        // if (fgets(a, 1024, stdin) == NULL)
        //     exit(0);

        setbuf(stdout, NULL);
        enableRawMode();
        prompt();
        memset(inp, '\0', 1000);
        int pt = 0;
        while (read(STDIN_FILENO, &c, 1) == 1)
        {
            if (iscntrl(c))
            {
                if (c == 10)
                    break;
                else if (c == 27)
                {
                    char buf[3];
                    buf[2] = 0;
                    if (read(STDIN_FILENO, buf, 2) == 2)
                    { // length of escape code
                      // printf("\rarrow key: %s", buf);
                    }
                }
                else if (c == 127)
                { // backspace
                    if (pt > 0)
                    {
                        if (inp[pt - 1] == 9)
                        {
                            for (int i = 0; i < 7; i++)
                            {
                                printf("\b");
                            }
                        }
                        inp[--pt] = '\0';
                        printf("\b \b");
                    }
                }
                else if (c == 9)
                { // TAB character
                    char *start = strrchr(inp, ' ');
                    char *path = getcwd(NULL, 0);
                    if (start == NULL)
                    {
                        start = inp;
                    }
                    else
                    {
                        start++;
                    }
                    struct dirent **namelist;
                    int n;
                    n = scandir(path, &namelist, NULL, NULL);
                    qsort(namelist, n, sizeof(struct dirent *), cmpmain);
                    int matching = 0;
                    char *match = NULL;
                    for (int i = 0; i < n; i++)
                    {
                        if (strncmp(namelist[i]->d_name, start, strlen(start)) == 0)
                        {
                            matching++;
                            match = namelist[i]->d_name;
                        }
                        
                    }
                    
                    if (n < 0)
                    {
                        perror("scandir");
                        return 0;
                    }
                    if (matching == 1)
                    {
                        printf("\r");
                        prompt();
                        char *newinp = (char *)malloc(sizeof(char) * (strlen(inp) + strlen(match) + 2));
                        strcpy(newinp, inp);
                        newinp[strlen(inp) - strlen(start)] = '\0';
                        strcat(newinp, match);
                        strcpy(inp, newinp);
                        pt = strlen(inp);
                        printf("%s", inp);
                    }
                    else
                    {
                        printf("\n");
                        for (int i = 0; i < n; i++)
                        {

                            struct stat fileStat;

                            char newpath[1000];
                            sprintf(newpath, "%s/%s", path, namelist[i]->d_name);
                            stat(newpath, &fileStat);

                            if (strncmp(namelist[i]->d_name, start, strlen(start)) == 0)
                            {
                                if (S_ISDIR(fileStat.st_mode))
                                {
                                    printf("\033[1;34m%s\033[0m/\t", namelist[i]->d_name);
                                }
                                else
                                {
                                    printf("\033[1;32m%s\033[0m\t", namelist[i]->d_name);
                                }
                            }
                        }
                        printf("\n");
                        prompt();
                        printf("%s", inp);
                    }
                }

                else if (c == 4)
                {
                    exit(0);
                }
                else
                {
                    printf("%d\n", c);
                }
            }
            else
            {
                inp[pt++] = c;
                printf("%c", c);
            }
        }
        disableRawMode();
        strcat(inp, "\n");
        strcpy(a, inp);
        printf("\n");

        if (a[0] == '\n')
        {
            continue;
        }

        if (a != NULL)
        {
            addhistory(a);
        }

        a[strlen(a) - 1] = '\0';
        strcat(a, " ;");

        int numtokenscolon = 0;
        char **tokenarrcolon = tokenization(a, &numtokenscolon, ";");

        for (int i = 0; i < numtokenscolon; i++)
        {
            int numtokensand = 0;
            char **tokenarrand = tokenization(tokenarrcolon[i], &numtokensand, "&");

            for (int j = 0; j < numtokensand; j++)
            {
                if (numtokensand == 1)
                {
                    // int numtokens = 0;
                    // char **tokenarr = tokenization(tokenarrand[j], &numtokens, " \t\r");
                    handlepiping(tokenarrand[j], 1);
                }
                else if (numtokensand > 1)
                {
                    if (j == (numtokensand - 1))
                    {
                        // int numtokens = 0;
                        // char **tokenarr = tokenization(tokenarrand[j], &numtokens, " \t\r");
                        handlepiping(tokenarrand[j], 1);
                    }
                    else
                    {
                        // int numtokens = 0;
                        // char **tokenarr = tokenization(tokenarrand[j], &numtokens, " \t\r");
                        handlepiping(tokenarrand[j], 0);
                    }
                }
            }
        }

        // char *token;
        // char *tokenarr[100];
        // int numtokens = 0;
        // int numcommands = 0;

        // token = strtok(a, " ");
        // while (token != NULL)
        // {
        //     tokenarr[numtokens] = token;
        //     token = strtok(NULL, " ");
        //     numtokens++;
        // }

        // if (strcmp(tokenarr[0], "pwd") == 0)
        // {
        //     pwd();
        // }
        // else if (strcmp(tokenarr[0], "cd") == 0)
        // {
        //     cd(numtokens, tokenarr);
        // }
        // else if (strcmp(tokenarr[0], "echo") == 0)
        // {
        //     echo(numtokens, tokenarr);
        // }
        // else if (strcmp(tokenarr[0], "ls") == 0)
        // {
        //     ls(tokenarr,numtokens);
        // }
        // else if (strcmp(tokenarr[0], "exit") == 0)
        // {
        //     exit(0);
        // }
        // else if (strcmp(tokenarr[0], "history") == 0)
        // {
        //     history(hissarr,totalcomms);
        // }
        // else if(strcmp(tokenarr[0], "discover") == 0)
        // {
        //     discover(tokenarr,numtokens);
        // }
        // else if(strcmp(tokenarr[0], "pinfo") == 0)
        // {
        //     pinfo(numtokens,tokenarr);
        // }
        // else
        // {
        //     printf("%s: Invalid command\n", tokenarr[0]);
        // }
    }
}
