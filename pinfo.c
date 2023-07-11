#include "headers.h"
#include "prompt.h"
void pinfo(int numTokens, char **tokenarr)
{
    pid_t pid;
    if (numTokens > 2)
    {
        printf("pinfo can have only 1 argument at max\n");
        return;
    }
    char pidString[20];
    char procPath[30] = "/proc/";
    char exePath[30];
    if (numTokens == 1)
    {
        pid = getpid();
        sprintf(pidString, "%d", pid);
    }
    else
    {
        strcpy(pidString, tokenarr[1]);
        pid = atoi(pidString);
    }
    strcat(procPath, pidString);
    strcpy(exePath, procPath);
    strcat(exePath, "/exe");
    strcat(procPath, "/stat");
    char *line;
    long size = 0;
    FILE *procFile = fopen(procPath, "r");
    if (procFile == NULL)
    {
        printf("process does not exist\n");
        return;
    }
    getline(&line, &size, procFile);

    char *statTokens[60];
    char *stattok;
    statTokens[0] = strtok_r(line, " \n", &stattok);
    int index = 0;
    while (statTokens[index] != NULL)
    {
        index++;
        statTokens[index] = strtok_r(NULL, " \n", &stattok);
    }

    printf("pid -- %s\n", pidString);
    printf("process status -- %s", statTokens[2]);
    if (strcmp(statTokens[4], statTokens[7]) == 0)
        printf("+");
    printf("\nmemory -- %s\n", statTokens[22]);

    char exe[1000] = "";
    readlink(exePath, exe, 1000);
    exe[strlen(exe)] = '\0';
    if (!strncmp(exe, HOME, strlen(HOME)))
    {
        char path[1000] = "~";
        strcat(path, exe + strlen(HOME));
        printf("Executable Path -- %s\n", path);
    }
    else
    {
        printf("Executable Path -- %s\n", exe);
    }
    fclose(procFile);
}