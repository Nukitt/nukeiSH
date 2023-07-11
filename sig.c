#include "headers.h"
#include "proc_list.h"

void sig(char **tokenarr,int numtokens)
{
    if(numtokens != 3)
    {
        printf("Invalid number of arguments\n");
        return;
    }
    int jobnumber=atoi(tokenarr[1]);
    int sig=atoi(tokenarr[2]);
    int flag=1;
    proc_list *temp=head;
    while(temp!=NULL)
    {
        if(temp->jobnum==jobnumber)
        {
            kill(temp->pid,sig);
            flag=0;
            return;
        }
        temp=temp->next;
    }
    if (flag)
    {
        printf("No such job exists\n");
    }
}