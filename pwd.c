#include "headers.h"

void pwd(int numtokens)
{
    if (numtokens > 1)
    {
        printf("Too many arguments.\n");
        return;
    }
    printf ("%s\n", getcwd(NULL, 0));
}