#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>





void exec_cd(char *array[1000],int count,char startdir[1024],char lastdir[1024],int flag)
{
        char name[1025],temp[1024];
        int k,lt,lt1,val;

        if(count==1||(strcmp(array[1],"&")==0))
        {
            lt=strlen(startdir);
            for(k=0;k<=lt;k++)
                name[k]=startdir[k];
            getcwd(temp,sizeof(temp));
            val=chdir(name);
            if(val==-1)
                fprintf(stderr,"cd: %s: No such directory\n",name);
            else
                strcpy(lastdir,temp);
        }
        else if(strcmp(array[1],"~")==0)
        {
            lt=strlen(startdir);
            for(k=0;k<=lt;k++)
                name[k]=startdir[k];
            getcwd(temp,sizeof(temp));
            val=chdir(name);
            if(val==-1)
                fprintf(stderr,"cd: %s: No such directory\n",name);
            else
                strcpy(lastdir,temp);
        }
        else if(array[1][0]=='~')
        {
            lt=strlen(startdir);
            for(k=0;k<lt;k++)
                name[k]=startdir[k];
            lt1=strlen(array[1]);
            for(k=lt+1;k<=lt+lt1;k++)
                name[k-1]=array[1][k-lt];
            getcwd(temp,sizeof(temp));
            val=chdir(name);
            if(val==-1)
                fprintf(stderr,"cd: %s: No such directory\n",name);
            else
                strcpy(lastdir,temp);
        }
        else if(strcmp(array[1],"-")==0)
        {

            getcwd(temp,sizeof(temp));
            chdir(lastdir);
            strcpy(lastdir,temp);
        }
        else
        {
            getcwd(temp,sizeof(temp));
            val= chdir(array[1]);
            if(val==-1)
                fprintf(stderr,"cd: %s: No such directory\n",array[1]);
            else
                strcpy(lastdir,temp);
        }
	return;
}
