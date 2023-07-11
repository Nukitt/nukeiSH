#include "proc_list.h"
#include "headers.h"


proc_list* head=NULL;

void init_proc_list()
{
    head=(proc_list*)malloc(sizeof(proc_list));
    head->pid=0;
    head->next=NULL;
}

void add_proc(int pid,char *name,int jobnum)
{
    proc_list *temp=head;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    proc_list *new_proc=(proc_list*)malloc(sizeof(proc_list));
    new_proc->pid=pid;
    new_proc->name=(char*)malloc(strlen(name)+1);
    strcpy(new_proc->name,name);
    new_proc->jobnum=jobnum;
    new_proc->next=NULL;
    temp->next=new_proc;
}

void remove_proc(int pid)
{
    proc_list *temp=head;
    proc_list *prev=NULL;
    while(temp!=NULL)
    {
        if(temp->pid==pid)
        {
            if(prev==NULL)
            {
                head=temp->next;
                free(temp->name);
                free(temp);
                return;
            }
            prev->next=temp->next;
            free(temp->name);
            free(temp);
            return;
        }
        prev=temp;
        temp=temp->next;
        free(temp->name);
        free(temp);
        free(prev);
    }
}

char* get_proc_name(int pid)
{
    proc_list *temp=head;
    while(temp!=NULL)
    {
        if(temp->pid==pid)
        {
            return temp->name;
        }
        temp=temp->next;
    }
    return NULL;
}
