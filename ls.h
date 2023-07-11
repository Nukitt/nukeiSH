#ifndef __LS_H
#define __LS_H

void ls(char **tokenarr, int numtokens);
int compare(const void *a, const void *b);
int ls_file(char *path,char *fakepath,int flag_a,int flag_l);
void ls_print(char *path,int flag_a, int flag_l);
#endif