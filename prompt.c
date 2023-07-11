#include "headers.h"

char *HOME;
char PREVDIR[1000];
char *CURRDIR;

time_t last_time = 0;
time_t starttime=0;
time_t endtime=0;
void prompt()
{
    struct utsname u;
    struct passwd *pwd;
    uname(&u);
    CURRDIR = getcwd(NULL, 0);

    pwd = getpwuid(getuid());
    printf(RED"<%s@%s:"RESET, pwd->pw_name, u.nodename);

    int lenhome = strlen(HOME);
    int lencurr = strlen(CURRDIR);
    int flag = 1;

    if (lencurr < lenhome){
        if (last_time>=1)
        {
            printf(RED"%s took %dsecs>$"RESET, CURRDIR,last_time);
            last_time = 0;
        }
        else printf(RED"%s>$ "RESET, CURRDIR);
    }
    else
    {
        for (int i = 0; i < lenhome; i++)
        {
            if (CURRDIR[i] == HOME[i])
                continue;
            else
            {
                flag = 0;
                break;
            }
        }
        if (last_time < 1)
        {
            if (flag == 1)
            {
                printf(RED"~%s>$ "RESET, lenhome + CURRDIR);
            }
            else
            {
                printf(RED"%s >$ "RESET, CURRDIR);
            }
        }
        else
        {
            if (flag == 1)
            {
                printf(RED"~%s took %dsecs>$ "RESET, lenhome + CURRDIR, last_time);
                last_time = 0;
            }
            else
            {
                printf(RED"%s took %dsecs>$ "RESET, CURRDIR, last_time);
                last_time = 0;
            }
        }
    }
}