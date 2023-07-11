#include "headers.h"
#include "proc_list.h"

void bg(char** tokenarr,int numTokens)
{
    if(numTokens != 2)
    {
        printf("Invalid number of arguments\n");
        return;
    }
    int jobnumber = atoi(tokenarr[1]);
    int flag=1;
    proc_list *temp = head;
    while(temp != NULL)
    {
        if(temp->jobnum == jobnumber)
        {
            kill(temp->pid,SIGCONT);
            flag=0;
            return;
        }
        temp = temp->next;
    }
    
    if (flag)
    {
        printf("No such job exists\n");
    }
}