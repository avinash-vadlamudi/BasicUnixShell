#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pwd.h>
#include<unistd.h>


void exec_echo(char *s2,int count,char *array[1000],char startdir[1024],int flag)
{
    char *arr2[1000],*sep,*arr3[1000];
    int flag2=0,flag3;
    flag3=0;
    int i,cou,cou2,k,poi;
    int uid,st;
    char dir[1024];
    struct passwd *pw;
    uid=getuid();
    pw=getpwuid(uid);
    getcwd(dir,sizeof(dir));
    i=strlen(s2);
    st=0;
    for(k=0;k<i;k++)
    {
        if(s2[k]=='\'')
        {
            s2[k]='\"';
        }
    }
    k=0;
    i=0;
    sep=strtok(s2,"\"");
    while(sep!=NULL)
    {
        arr2[i]=sep;
        i++;
        sep=strtok(NULL,"\"");
    }
    cou=i;
    if(cou>1)
    {
        for(i=0;i<cou;i++)
        {  
            if(i%2==0)
            {
                poi=0;
                if(i==0)
                {
                    sep=strtok(arr2[i]," ");
                    while(sep!=NULL)
                    {
                        arr3[poi]=sep;
                        poi++;
                        sep=strtok(NULL," ");
                    }
                    if(poi>1)
                    {
                        if(strcmp(arr3[1],"-n")==0)
                        {
                            flag3=1;
                            for(k=2;k<poi;k++)
                            {
                                if(strcmp(arr3[k],"~")==0)
                                    printf("%s ",startdir);
                                else if(strcmp(arr3[k],"&")==0)
                                    continue;
                                else if(strcmp(arr3[k],"$USER")==0)
                                    printf("%s ",pw->pw_name);
                                else if(strcmp(arr3[k],"$PWD")==0)
                                    printf("%s ",dir);
                                else
                                    printf("%s ",arr3[k]);
                            }        
                        }
                        else
                        {
                            for(k=1;k<poi;k++)
                            {
                                if(strcmp(arr3[k],"~")==0)
                                    printf("%s ",startdir);
                                else if(strcmp(arr3[k],"&")==0)
                                    continue;
                                else if(strcmp(arr3[k],"$USER")==0)
                                    printf("%s ",pw->pw_name);
                                else if(strcmp(arr3[k],"$PWD")==0)
                                    printf("%s ",dir);
                                else
                                    printf("%s ",arr3[k]);
                            }
                        }
                    }
                }
                else
                {
                    poi=0;
                    sep=strtok(arr2[i]," ");
                    while(sep!=NULL)
                    {
                        arr3[poi]=sep;
                        poi++;
                        sep=strtok(NULL," ");

                    }   
                    for(k=0;k<poi;k++)
                    {
                        if(strcmp(arr3[k],"~")==0)
                            printf("%s ",startdir);
                        else if(strcmp(arr3[k],"&")==0)
                            continue;
                        else if(strcmp(arr3[k],"$USER")==0)
                            printf("%s ",pw->pw_name);
                        else if(strcmp(arr3[k],"$PWD")==0)
                            printf("%s ",dir);
                        else
                            printf("%s ",arr3[k]);
                    }
                }
            }
            else
            {
                printf("%s ",arr2[i]);
            }

        }
        if(flag3==0)
            printf("\n");
    }
    else
    {
        if(strcmp(array[1],"-n")==0)
        {
            for(i=2;i<count;i++)
            {
                if(strcmp(array[i],"~")==0)
                    printf("%s ",startdir);
                else if(strcmp(array[i],"&")==0)
                    continue;
                else if(strcmp(array[i],"$USER")==0)
                    printf("%s ",pw->pw_name);
                else if(strcmp(array[i],"$PWD")==0)
                    printf("%s ",dir);
                else
                    printf("%s ",array[i]);
            }
        }
        else
        {
            for(i=1;i<count;i++)
            {
                if(strcmp(array[i],"~")==0)
                    printf("%s ",startdir);
                else if(strcmp(array[i],"&")==0)
                    continue;
                else if(strcmp(array[i],"$USER")==0)
                    printf("%s ",pw->pw_name);
                else if(strcmp(array[i],"$PWD")==0)
                    printf("%s ",dir);
                else
                    printf("%s ",array[i]);
            }
            printf("\n");
        }
    }
    return;

}

