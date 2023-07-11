#include "headers.h"
#include "cummands.h"
#include "pwd.h"
#include "cd.h"
#include "echo.h"
#include "history.h"
#include "ls.h"
#include "discover.h"
#include "pinfo.h"
#include "proc_list.h"
#include "prompt.h"
#include "jobs.h"
#include "sig.h"
#include "fg.h"
#include "bg.h"

void run_cummand(char **tokenarr, int numtokens,int flagfg)
{
    if (numtokens==0 || strcmp(tokenarr[0], "") == 0)
    {
        return;
    }
    if (strcmp(tokenarr[0], "cd") == 0)
    {
        cd(numtokens, tokenarr);
    }
    else if (strcmp(tokenarr[0], "pwd") == 0)
    {
        pwd(numtokens);
    }
    else if (strcmp(tokenarr[0], "echo") == 0)
    {
        echo(numtokens,tokenarr);
    }
    else if (strcmp(tokenarr[0], "ls") == 0)
    {
        ls(tokenarr, numtokens);
    }
    else if (strcmp(tokenarr[0], "pinfo") == 0)
    {
        pinfo(numtokens,tokenarr);
    }
    else if (strcmp(tokenarr[0], "history") == 0)
    {
        history();
    }
    else if (strcmp(tokenarr[0], "discover") == 0)
    {
        discover(tokenarr, numtokens);
    }
    else if (strcmp(tokenarr[0], "jobs") == 0)
    {
        jobs(tokenarr, numtokens);
    }
    else if (strcmp(tokenarr[0], "sig") == 0)
    {
        sig(tokenarr,numtokens);
    }
    else if (strcmp(tokenarr[0], "fg") == 0)
    {
        fg(tokenarr,numtokens);
    }
    else if (strcmp(tokenarr[0], "bg") == 0)
    {
        bg(tokenarr,numtokens);
    }
    else if (strcmp(tokenarr[0], "exit") == 0)
    {
        char * temp = (char *)malloc(sizeof(char)*(strlen(HOME)+30));
        sprintf(temp, "%s/history.txt", HOME);
        writefile(temp,hissarr);
        exit(0);
    }
    else
    {
        int status=0;
        starttime=time(NULL);
        int pid = fork();
        if (pid == 0)
        {
            if (flagfg==0)
            {
                setpgid(0,0);
            }
            if (execvp(tokenarr[0], tokenarr) < 0)
            {
                printf("%s: No such command exists\n", tokenarr[0]);
                exit(0);
                return;
            }
            exit(0);
        }
        else if (pid<0)
        {
            kill(pid, SIGCONT);
        }
        
        else
        {
            if(flagfg==1)
            {
                fgpid=pid;
                // waitpid(pid, &status, 2);
                pause();
            }
            else
            {
                add_proc(pid,tokenarr[0],jobnum);
                jobnum++;
                printf("Process with pid %d started in background\n",pid);

            }
        }
    }
}