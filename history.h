#ifndef __HISTORY_H
#define __HISTORY_H

void writefile(char *filename, char **hissarr);
void addhistory(char *command);
void readfile(char *filename);
void history();

extern char* hissarr[20];

#endif