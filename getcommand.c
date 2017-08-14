#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "execute.h"
#include "var.h"

void getcommand(char *s,char startdir[1024],char lastdir[1024])
{
    int i,count;
    char *token;
    char command[1000][1000];
    s[strlen(s)-1]='\0';
    token=strtok(s,";");
    i=0;
    while(token!=NULL)
    {
        strcpy(command[i],token);
        i++;
        token=strtok(NULL,";");
    }
    count=i;
    for(i=0;i<count;i++)
    {
        execute(command[i],startdir,lastdir);
    }
    return;
}
