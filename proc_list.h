#ifndef __PROC_LIST_H__
#define __PROC_LIST_H__

typedef struct proc_list
{
    int pid;
    char *name;
    int jobnum;
    char *status;
    struct proc_list *next;
} proc_list;

void init_proc_list();
void display_proc_list();
void add_proc(int pid, char *name,int jobnum);
void remove_proc(int pid);
char* get_proc_name(int pid);

extern proc_list* head;

#endif