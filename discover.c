#include "headers.h"

void discover_util(char *dir, char *filename, int search, int flagf, int flagd)
{
    DIR *dp;
    struct dirent **entry;
    struct stat statbuf;
    if ((dp = opendir(dir)) != NULL)
    {

        int n = scandir(dir, &entry, NULL, alphasort);
        for (int i = 0; i < n; i++)
        {
            if (strcmp(entry[i]->d_name, ".") == 0 || strcmp(entry[i]->d_name, "..") == 0)
                continue;
            char *filepath = (char *)malloc(1024);
            strcpy(filepath, dir);
            strcat(filepath, "/");
            strcat(filepath, entry[i]->d_name);
            if (search && strcmp(entry[i]->d_name, filename) == 0)
            {
                printf("%s\n", filepath);
                return;
            }
            if (!search && flagf)
            {
                if (entry[i]->d_type != DT_DIR)
                {
                    printf("%s\n", filepath);
                }
            }
            if (!search && flagd)
            {
                if (entry[i]->d_type == DT_DIR)
                {
                    printf("%s\n", filepath);
                }
            }
            if (entry[i]->d_type == DT_DIR)
            {
                char *path = malloc(strlen(dir) + strlen(entry[i]->d_name) + 2);
                strcpy(path, dir);
                strcat(path, "/");
                strcat(path, entry[i]->d_name);
                discover_util(path, filename, search, flagf, flagd);
            }
        }
    }
}

void discover(char **tokenarr, int numtokens)
{
    int flagf = 0, flagd = 0;
    char *path = (char *)malloc(1000);
    char *filename = (char *)malloc(1000);
    strcpy(filename, "");
    char **token_wo_flags = (char **)malloc(numtokens * sizeof(char *));
    int num_wo_flags = 0;
    int search = 0;

    for (int i = 0; i < numtokens; i++)
    {
        if (tokenarr[i][0] == '-')
        {
            if (strcmp(tokenarr[i], "-f") == 0)
            {
                flagf = 1;
            }
            else if (strcmp(tokenarr[i], "-d") == 0)
            {
                flagd = 1;
            }
        }
        else
        {
            token_wo_flags[num_wo_flags] = (char *)malloc(sizeof(char) * strlen(tokenarr[i]));
            strcpy(token_wo_flags[num_wo_flags], tokenarr[i]);
            num_wo_flags++;
        }
    }

    if (numtokens == 1)
    {
        flagd = 1;
        flagf = 1;
        path = ".";
    }

    else if (num_wo_flags == 1)
    {
        path = ".";
    }
    if (num_wo_flags == 2)
    {
        if(flagf==0 && flagd==0)
        {
            flagf=1;
            flagd=1;
        }
        // printf("%c",token_wo_flags[1][0]);
        // printf("%c",token_wo_flags[1][]);
        if (token_wo_flags[1][0] == '"' && token_wo_flags[1][strlen(token_wo_flags[1]) - 1] == '"')
        {
            // token_wo_flags[2][strlen(token_wo_flags[2]) - 1] = '\0';
            strncpy(filename, token_wo_flags[1] + 1, strlen(token_wo_flags[1]) - 2);
            search = 1;
            strcpy(path,".");
        }
        else
        {
            strcpy(path, token_wo_flags[1]);
        }         
        
        // strcpy(path,'.');
        // strcpy(filename, token_wo_flags[2]);

    }

    if (num_wo_flags == 3)
    {
        strcpy(path, token_wo_flags[1]);
        // strcpy(filename, token_wo_flags[2]);
        strncpy(filename, token_wo_flags[2]+1, strlen(token_wo_flags[2]) - 2);
        search = 1;
    }
    discover_util(path, filename, search, flagf, flagd);
}