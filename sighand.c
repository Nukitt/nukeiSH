#include "headers.h"
#include "prompt.h"
#include "sighand.h"
#include "proc_list.h"


void sigtstp_handler(int signum) {
    if (fgpid == shellpid) {
        return;
    }
    kill(fgpid, SIGTSTP);
    add_proc(fgpid, "ctrl+z" , jobnum);
    jobnum++;
    printf("\n");
}
void sigint_handler(int signum){
    if(fgpid!=0){
        kill(fgpid,SIGINT);
        printf("\n");
        fflush(stdout);
        fgpid=0;
    }
    else{
        printf("\n");
        prompt();
        fflush(stdout);
    }
}