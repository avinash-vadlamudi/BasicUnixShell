#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<pwd.h>
#include<signal.h>
#include<setjmp.h>
#include<errno.h>
#include<sys/wait.h>
#include "getcommand.h"
#include "execute.h"
#include "cd.h"
#include "pwd.h"
#include "echo.h"
#include "var.h"

int flag2;
int m,i,bytes,len,flag,pos,poi,status;
int ef;
char *s;
Jobs *tmp,*tmp2;
char startdir[1024],lastdir[1024];
char currdir[1025];
size_t tot=10000;
char h[2]="~";
char hostname[1024];
char *token;
struct passwd *pw;
uid_t uid;


int counter=0;
int getname(char *name,char *hostname,char *dir)
{
    printf("<%s@%s:%s>",name,hostname,dir);
    return 1;
}
void sig_br(int sig)
{
    signal(SIGTSTP,SIG_IGN);
    return;
}
void sighand(int sig);
int main()
{
    flag2=0;
    hostname[1023] = '\0';
    gethostname(hostname, 1023);
    uid=geteuid();
    pw=getpwuid(uid);
    s=(char *)malloc(tot+1);
    getcwd(startdir,sizeof(startdir));
    strcpy(lastdir,startdir);
    while(1)
    {
        flag=0;
        getcwd(currdir,sizeof(currdir));
        if(strlen(currdir)>=strlen(startdir))
        {
            len=strlen(startdir);
            for(i=0;i<len;i++)
            {
                if(startdir[i]==currdir[i])
                    continue;
                else
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            {
                len=strlen(currdir);
                pos=i;
                currdir[0]='~';
                for(i=pos;i<=len;i++)
                {
                    currdir[i-pos+1]=currdir[i];
                }
            }
        }
        bytes=-2;
        getname(pw->pw_name,hostname,currdir);
        signal(SIGTSTP,sig_br);
        signal(SIGINT,sighand);
        bytes=getline(&s,&tot,stdin);
        if(bytes==-1)
        {
            printf("\n");
            break;
        }
        bytes=-23;
        getcommand(s,startdir,lastdir);
    }
    return 0;
}


void sighand(int sig)
{
    flag2=1;
    switch(sig)
    {
        case SIGINT:
            printf("\n");
            if(bytes!=-23)
                getname(pw->pw_name,hostname,currdir);
            fflush(stdout);
            break;
    }
    return;
}
