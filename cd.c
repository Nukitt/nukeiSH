#include "headers.h"
#include "prompt.h"
void cd (int numtokens, char** token)
{
	char* prev = getcwd(NULL, 0);
    if(numtokens > 2)
    {
        printf("Too many arguments.\n");
        return;
    }
	else if (numtokens == 1 || strcmp(token[1], "~") == 0){
		int err = chdir(HOME);
		if (err < 0){
			perror("Error");
		}
	}
	else if(strcmp(token[1], "-") == 0)
		chdir(PREVDIR);
	else
    {
		int err = chdir(token[1]);
		if (err < 0){
			perror("Error");
		}
	}
    strcpy(PREVDIR, prev);
}