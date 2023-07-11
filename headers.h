#include <stdio.h>    
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <dirent.h> 
#include <time.h>
#include <grp.h>
#include <sys/wait.h>
#include <signal.h>
#include <termios.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <errno.h>


#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"
#define WHITE "\033[0;37m"

extern time_t last_time;
extern time_t starttime;
extern time_t endtime;
extern int fgpid;
extern int shellpid;
extern int flagfg;
extern int jobnum;