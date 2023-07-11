#include "headers.h"
#include "history.h"
// every time a command is called, the history file is updated
// Create the file if not created initially
// Read the lines in the file into an array of size 20
// See the command that was just entered
// If number of commands in the history file are less than 20, then lite
// Otherwise, you basically create a new array where you take only the last 19 from the file, and make the new command the 1st command
// Write the array back to the file

void writefile(char *filename, char **hissarr)
{
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    int i = 0;
    while (hissarr[i] != NULL)
    {
        fprintf(fp, "%s", hissarr[i]);
        i++;
    }
    fclose(fp);
}

void addhistory(char *command)
{
    int i = 0;
    while (hissarr[i] != NULL)
    {
        i++;
    }
    if (i < 10)
    {
        hissarr[i] = (char *)malloc(1000 * sizeof(char));
        strcpy(hissarr[i], command);
        hissarr[i + 1] = NULL;
    }
    else
    {
        for (int j = 0; j < 9; j++)
        {
            hissarr[j] = hissarr[j + 1];
        }
        hissarr[9] = (char *)malloc(1000 * sizeof(char));
        strcpy(hissarr[9], command);
    }
}

void readfile(char *filename)
{
    // hissarr=(char**)malloc(20*sizeof(char*));
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    int i = 0;
    // hissarr[i] = (char *)malloc(1000 * sizeof(char));
    size_t sz;
    while(getline(&hissarr[i], &sz, fp) != -1)
    {
        i++;
    }
    // while (getline(hissarr[i], 1000, fp) != NULL)
    // {
    //     i++;
    // }
    fclose(fp);
}

void history()
{
    int count=1;
    int i = 0;
    while (hissarr[i+1] != NULL)
    {
        if (strcmp(hissarr[i],hissarr[i+1])!=0)
        {
            printf("\n %d\t%s",count, hissarr[i]);
            count++;
        }
        i++;
    }
    printf("\n");
}