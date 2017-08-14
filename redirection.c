#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
#include<signal.h>
#include "execute.h" 
#include "pipe.h"

int redir(char *s2,char startdir[1024],char lastdir[1024],int type,int fd_input,int cond)
{
    int i,fdo,fdc,fiopen,ficlose,i2,len2;
    int count,len,flag,pos,status,flag2,flag3;
    int id;
    int stdin_copy = dup(0);
    int stdout_copy = dup(1);
    char openfi[1000],closefi[1000];
    fiopen=0;
    ficlose=0;
    flag3=0;
    len=strlen(s2);
    flag2=0;
    for(i=0;i<len;i++)
    {
        if(s2[i]=='<')
        {
            fiopen=1;
            s2[i]='\0';

            for(id=i+1;id<len;id++)
            {
                if(s2[id]==' ')
                    continue;
                else
                {
                    i=id;
                    break;
                }
            }
            for(id=i;id<len;id++)
            {
                if(s2[id]=='>'||s2[id]=='<')
                {
                    openfi[id-(i)]='\0';
                    i=id-1;
                    break;
                }
                else
                {
                    openfi[id-(i)]=s2[id];
                }
            }
            if(id==len)
                openfi[id-(i)]='\0';
            len2=strlen(openfi);
            for(i2=len2-1;i2>=0;i2--)
            {
                if(openfi[i2]==' ')
                    openfi[i2]='\0';
                else
                    break;
            }
            fdo=open(openfi,O_RDONLY,0644);
            if(fdo==-1)
            {
                flag3=1;
                fprintf(stderr,"failed to open file '%s' ",openfi);
                perror(" ");
            }
            else
                close(fdo);
        }
        else if(s2[i]=='>')
        {
            ficlose=1;
            s2[i]='\0';
            if(s2[i+1]=='>')
            {
                flag2=1;
            }
            if(flag2==1)
            {
                for(id=i+2;id<len;id++)
                {
                    if(s2[id]==' ')
                        continue;
                    else
                    {
                        i=id;
                        break;
                    }
                }
                for(id=i;id<len;id++)
                {
                    if(s2[id]=='<'||s2[id]=='>')
                    {
                        closefi[id-(i)]='\0';
                        i=id-1;
                        break;
                    }
                    else
                    {
                        closefi[id-(i)]=s2[id];
                    }
                }
                if(id==len)
                    closefi[id-(i)]='\0';

                len2=strlen(closefi);
                for(i2=len2-1;i2>=0;i2--)
                {
                    if(closefi[i2]==' ')
                        closefi[i2]='\0';
                    else
                        break;
                }
                if(flag2==1)
                {
                    fdc=open(closefi,O_APPEND|O_WRONLY|O_CREAT, 0644);
                }
                else
                {
                    fdc=open(closefi,O_WRONLY|O_CREAT|O_TRUNC,0644);
                }
                if(fdc==-1)
                {
                    flag3=1;
                    fprintf(stderr,"failed to open file %s ",closefi);
                    perror(" ");
                }
                else
                    close(fdc);
            }
            else
            {
                for(id=i+1;id<len;id++)
                {
                    if(s2[id]==' ')
                        continue;
                    else
                    {
                        i=id;
                        break;
                    }
                }
                for(id=i;id<len;id++)
                {
                    if(s2[id]=='<'||s2[id]=='>')
                    {
                        closefi[id-(i)]='\0';
                        i=id-1;
                        break;
                    }
                    else
                    {
                        closefi[id-(i)]=s2[id];
                    }
                }
                if(id==len)
                    closefi[id-(i)]='\0';
                len2=strlen(closefi);
                for(i2=len2-1;i2>=0;i2--)
                {
                    if(closefi[i2]==' ')
                        closefi[i2]='\0';
                    else
                        break;
                }
                if(flag2==1)
                {
                    fdc=open(closefi,O_APPEND|O_WRONLY|O_CREAT, 0644);
                }
                else
                {
                    fdc=open(closefi,O_WRONLY|O_CREAT|O_TRUNC,0644);
                }
                if(fdc==-1)
                {
                    flag3=1;
                    fprintf(stderr,"failed to open file %s ",closefi);
                    perror(" ");
                }
                else
                    close(fdc);
            }

        }

    }
    len=strlen(closefi);
    for(i=len-1;i>=0;i--)
    {
        if(closefi[i]==' ')
            closefi[i]='\0';
        else
            break;
    }
    len=strlen(openfi);
    for(i=len-1;i>=0;i--)
    {
        if(openfi[i]==' ')
            openfi[i]='\0';
        else
            break;
    }
    if(flag3==1)
        return 0;
    if(fiopen==1)
    {
        fdo=open(openfi,O_RDONLY,0644);
        if(fdo==-1)
        {
            fprintf(stderr,"failed to open file %s ",openfi);
            perror(" ");
        }
        close(0);
        if(dup2(fdo,0)!=0)
            perror("dup2 fail");
        close(fdo);

    }
    if(ficlose==1)
    {
        if(flag2==1)
        {
            fdc=open(closefi,O_APPEND|O_WRONLY|O_CREAT, 0644);
        }
        else
        {
            fdc=open(closefi,O_WRONLY|O_CREAT|O_TRUNC,0644);
        }
        if(fdc==-1)
        {
            fprintf(stderr,"failed to open file %s ",closefi);
            perror(" ");
        }
        close(1);
        if(dup2(fdc,1)!=1)
            perror("Dup2 failed");
        if(flag==1)
            lseek(fdc,0,SEEK_END);
        close(fdc);
    }
    if(type==0)
        execute(s2,startdir,lastdir);
    else if(type==1)
        fd_input=execute2(s2,startdir,lastdir,fiopen,ficlose,fd_input,cond);

    dup2(stdin_copy, 0);
    dup2(stdout_copy, 1);
    close(stdin_copy);
    close(stdout_copy);
    return fd_input;

}

