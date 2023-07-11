#include "headers.h"
#include "prompt.h"
#include "ls.h"
int compare(const void *a, const void *b) 
{ 
    const char **str_a = (const char **)a;
    const char **str_b = (const char **)b;
    return strcasecmp(*str_a, *str_b);
}

void ls(char **tokenarr,int numtokens)
{
    int flaga = 0, flagl = 0;

    char *path = (char *)malloc(1000);
    // char *filename = (char *)malloc(1000);
    // strcpy(filename, "");
    char **token_wo_flags = (char **)malloc(numtokens * sizeof(char *));
    int num_wo_flags = 0;
    // int search = 0;

    for (int i = 0; i < numtokens; i++)
    {
        if (tokenarr[i][0] == '-')
        {
            for(int j=1;j<strlen(tokenarr[i]);j++)
            {
                if(tokenarr[i][j]=='a')
                {
                    flaga=1;
                }
                else if(tokenarr[i][j]=='l')
                {
                    flagl=1;
                }
            }
        }
        else
        {
            token_wo_flags[num_wo_flags] = (char *)malloc(sizeof(char) * strlen(tokenarr[i]));
            strcpy(token_wo_flags[num_wo_flags], tokenarr[i]);
            num_wo_flags++;
        }
    }
    // char *path = (char *)malloc(1000);
    char **path_arr = (char **)malloc(num_wo_flags * sizeof(char *));
    if (num_wo_flags == 1)
    {
        strcpy(path,getcwd(NULL, 0));
        // ls_print(path, filename, search, flaga, flagl);
        ls_print(path,flaga,flagl);
        // path_arr[0] = (char *)malloc(sizeof(char) * strlen(path)+1);
        // strcpy(path_arr[0], path);
    }
    else
    {
        for (int i = 1; i < num_wo_flags; i++)
        {
            if(token_wo_flags[i][0]=='~' &&  (token_wo_flags[i][1] == '/' || token_wo_flags[i][1] == '\0'))
            {
                strcpy(path,HOME);
                strcat(path,token_wo_flags[i]+1);
            }
            else
            {
                strcpy(path,token_wo_flags[i]);
            }
            path_arr[i-1] = (char *)malloc(sizeof(char) * strlen(path)+1);
            strcpy(path_arr[i-1], path);

        }
        int done[num_wo_flags-1];
        
        for (int i = 0; i < num_wo_flags - 1; i++)
        {
            done[i] = ls_file(path_arr[i],token_wo_flags[i+1], flaga, flagl);
        }
        for (int i = 0; i < num_wo_flags - 1; i++)
        {
            if(done[i]){
                continue;
            }
            if(num_wo_flags>2)
            {
                printf(GREEN"%s:\n"RESET,path_arr[i]);                                                                                                                                                                                                                                                                                                                                                                                                        
            }
            ls_print(path_arr[i], flaga, flagl);
            // free(path[i]);
        }

        for(int i=0;i<num_wo_flags-1;i++)
        {
            free(path_arr[i]);
        }
        free(path_arr);
       
        
    }
    

    // else if (numtokens == 3)
    // {
    //     if (strcmp(tokenarr[1], "-a") == 0)
    //     {
    //         flaga = 1;
    //         strcpy(path,tokenarr[2]);
    //     }
    //     else if (strcmp(tokenarr[1], "-l") == 0)
    //     {
    //         flagl = 1;
    //         strcpy(path,tokenarr[2]);
    //     }
    //     else if (strcmp(tokenarr[2], "-a") == 0)
    //     {
    //         flaga = 1;
    //         strcpy(path,tokenarr[2]);
    //     }
    //     else if (strcmp(tokenarr[2], "-l") == 0)
    //     {
    //         flagl = 1;
    //         strcpy(path,tokenarr[2]);
    //     }
    //     else
    //     {
    //         strcpy(path,tokenarr[2]);
    //     }
    // }
    // else
    // {
    //     printf ("Invalid command\n");
    //     return;
    // }
    // DIR *dir;
    // struct dirent *entry;
    // struct stat fileStat;
    // char *lslist[100];
    // char *lslistlmode[100];
    // char *lslistlnlink[100];
    // char *lslistluid[100];
    // char *lslistlgid[100];
    // char *lslistlsize[100];
    // char *lslistltime[100];
    // int count=0;
    // int count2=0;
    // if ((dir = opendir(path)) == NULL)
    // {
    //     printf ("Cannot open directory '%s' \n", path);
    //     return;
    // }
    // while ((entry = readdir(dir)) != NULL)
    // {
    //     if (flaga == 0 && entry->d_name[0] == '.')
    //     {
    //         continue;
    //     }
    //     if (flagl == 0)
    //     {
    //         lslist[count]=entry->d_name;
    //         count++;
    //     }
    //     else
    //     {
    //         stat(entry->d_name, &fileStat);
    //         // lslistlmode[count2]=fileStat->st_mode;
    //         // count2++;
    //         printf ((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    //         printf ((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    //         printf ((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    //         printf ((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    //         printf ((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    //         printf ((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    //         printf ((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    //         printf ((fileStat.st_mode & S_IROTH) ? "r" : "-");
    //         printf ((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    //         printf ((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    //         printf (" %ld ", fileStat.st_nlink);
    //         struct passwd *pw = getpwuid(fileStat.st_uid);
    //         struct group  *gr = getgrgid(fileStat.st_gid);
    //         printf ("%s %s ", pw->pw_name, gr->gr_name);
    //         printf ("%ld ", fileStat.st_size);
    //         char *time = ctime(&fileStat.st_mtime);
    //         time[strlen(time) - 1] = '\0';
    //         printf ("%s ", time);
    //         printf ("%s \n", entry->d_name);
    //     }
    // }
    // qsort(lslist, count, sizeof(char*), compare);
    // for (int i = 0; i < count; i++)
    // {
    //     printf ("%s\t ", lslist[i]);
    // }
    // printf ("\n");
    free(path);
}
int ls_file(char *path,char *fakepath,int flag_a,int flag_l)
{
    struct stat fileStat;
    // stat(path, &fileStat);
    if(stat(path,&fileStat) < 0)    
    {
        perror("stat");
        return 0;
    }
    if(fileStat.st_mode & S_IXUSR){
        printf(GREEN);
    }
    else
    {
        printf(WHITE);
    }

    if(!S_ISDIR(fileStat.st_mode))
    {
        if(flag_l){
            printf ((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            printf ((fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf ((fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf ((fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf ((fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf ((fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf ((fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf ((fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf ((fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf ((fileStat.st_mode & S_IXOTH) ? "x" : "-");
            printf (" %ld ", fileStat.st_nlink);
            struct passwd *pw = getpwuid(fileStat.st_uid);
            struct group  *gr = getgrgid(fileStat.st_gid);
            printf ("%s %s ", pw->pw_name, gr->gr_name);
            printf ("%ld ", fileStat.st_size);
            char *time = ctime(&fileStat.st_mtime);
            time[strlen(time) - 1] = '\0';
            printf ("%s ", time);
            printf ("%s \n", fakepath);
        }
        else
        {
            printf("%s\n",fakepath);
        }
        printf(RESET);
        return 1;
    }

    return 0;

    
}
int cmp(const void *a, const void *b)
{
    // return strcmp(*(char **)a, *(char **)b);
    struct dirent *entry1 = *(struct dirent **)a;
    struct dirent *entry2 = *(struct dirent **)b;
    return(strcasecmp(entry1->d_name,entry2->d_name));
}

void ls_print(char *path,int flag_a, int flag_l)
{
    struct dirent **namelist;
    int n;
    n = scandir(path, &namelist, NULL, NULL);
    qsort(namelist, n, sizeof(struct dirent *), cmp);
    if (n < 0){
        perror("scandir");
        return;
    }
    for(int i = 0;i<n;i++){
        if(flag_a==0 && namelist[i]->d_name[0]=='.'){
            continue;
        }
        if(flag_l==0){
            struct stat fileStat;

            

            char newpath[1000];
            sprintf(newpath,"%s/%s",path,namelist[i]->d_name);
            stat(newpath, &fileStat);

            if(S_ISDIR(fileStat.st_mode)){
                printf(BLUE);
            }
            else if (fileStat.st_mode & S_IXUSR)
            {
                printf(GREEN);
            }
            else{
                printf(WHITE);
            }
            printf("%s\t",namelist[i]->d_name);
            printf(RESET);
        }
        else{
            struct stat fileStat;

            

            char newpath[1000];
            sprintf(newpath,"%s/%s",path,namelist[i]->d_name);
            stat(newpath, &fileStat);

            if(S_ISDIR(fileStat.st_mode)){
                printf(BLUE);
            }
            else if (fileStat.st_mode & S_IXUSR)
            {
                printf(GREEN);
            }
            else{
                printf(WHITE);
            }
            printf ((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            printf ((fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf ((fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf ((fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf ((fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf ((fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf ((fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf ((fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf ((fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf ((fileStat.st_mode & S_IXOTH) ? "x" : "-");
            printf (" %ld ", fileStat.st_nlink);
            struct passwd *pw = getpwuid(fileStat.st_uid);
            struct group  *gr = getgrgid(fileStat.st_gid);
            printf ("%s %s ", pw->pw_name, gr->gr_name);
            printf ("%ld ", fileStat.st_size);
            char *time = ctime(&fileStat.st_mtime);
            time[strlen(time) - 1] = '\0';
            printf ("%s ", time);
            printf ("%s \n", namelist[i]->d_name);

            printf(RESET);
        }
    }
    printf("\n");
     
}


            