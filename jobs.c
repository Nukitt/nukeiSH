#include "headers.h"
#include "jobs.h"
#include "proc_list.h"

void display_jobs(int flagrun)
{
    proc_list* temp=head;
    temp=temp->next;
    if (flagrun==0)
    {
        while(temp!=NULL)
        {
            if(kill(temp->pid,0)==0)
            {
                printf("[%d] Running %s [%d]\n",temp->jobnum,temp->name,temp->pid);
            }
            else
            {
                printf("[%d] Stopped %s [%d]\n",temp->jobnum,temp->name,temp->pid);
            }
            temp=temp->next;
        }
    }
    else if(flagrun==1)
    {
        while(temp!=NULL)
        {
            if(kill(temp->pid,0)==0)
            {
                printf("[%d] Running %s [%d]\n",temp->jobnum,temp->name,temp->pid);
            }
            temp=temp->next;
        }
    }
    else if(flagrun==-1)
    {
        while(temp!=NULL)
        {
            if(kill(temp->pid,0)!=0)
            {
                printf("[%d] Stopped %s [%d]\n",temp->jobnum,temp->name,temp->pid);
            }
            temp=temp->next;
        }
    }
}

void jobs (char **tokenarr, int numtokens)
{
    int flagrun=0; //0 for all, -1 for stopped , 1 for running
    if(numtokens==1)
    {
        display_jobs(flagrun);
        return;
    }
    else if(numtokens==2)
    {
        if(strcmp(tokenarr[1],"-r")==0)
        {
            flagrun=1;
        }
        else if(strcmp(tokenarr[1],"-s")==0)
        {
            flagrun=-1;
        }
        else
        {
            printf("Invalid argument\n");
            return;
        }
        display_jobs(flagrun);
        return;
    }
    else
    {
        printf("Invalid number of arguments\n");
        return;
    }
}