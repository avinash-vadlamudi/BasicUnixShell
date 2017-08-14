#ifndef __REDIR__
#define __REDIR__
#include "pipe.h"
int redir(char *s2,char startdir[1024],char lastdir[1024],int type,int fd_input,int cond);
#endif
