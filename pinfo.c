#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>

void pinfo(char startdir[1024],char *array[1000])
{
    FILE *poi;
    char list1[1000],list2[1000],path[1000],status;
    long unsigned int space;
    int id;
    if(array[1]==NULL)
    {
        sprintf(list1,"/proc/%d/stat",getpid());
        sprintf(list2,"/proc/%d/exe",getpid());
    }
    else
    {
        sprintf(list1,"/proc/%s/stat",array[1]);
        sprintf(list2,"/proc/%s/exe",array[1]);
    }
    if((poi=fopen(list1,"r"))!=NULL)
    {
        fscanf(poi,"%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",&id,&status,&space);

        fclose(poi);
        printf("PID --> %d\n",id);
        printf("Process Status --> %c\n",status);
        printf("Memory --> %lu\n",space);
        readlink(list2,path,500);
        if(strstr(path,startdir))
        {
            char var[1000]="~";
            strcat(var,path+strlen(startdir));
            printf("Executable path --> %s\n",var);

        }
        else
            printf("Executable path --> %s\n",path);

    }
    else
        fprintf(stderr,"process doesn't exist\n");

}

