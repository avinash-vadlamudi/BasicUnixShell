#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

void exec_pwd(char *array[1000],int count,int flag)
{
    int i=0;
    char cwd[1025];
    getcwd(cwd,sizeof(cwd));
    printf("%s\n",cwd);
	return;
}
