#ifndef __VAR123__
#define __VAR123__
	typedef struct jobs{
		char name[1000];
		long int pid;
		struct jobs *nxt;
		int type;

	}Jobs;
#endif
