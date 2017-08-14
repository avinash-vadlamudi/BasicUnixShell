shell: main.o pwd.o echo.o cd.o getcommand.o pinfo.o execute.o redirection.o pipe.o
	gcc main.o pwd.o echo.o cd.o getcommand.o pinfo.o redirection.o pipe.o execute.o -o shell
main.o: echo.h pwd.h cd.h getcommand.h execute.h var.h main.c
	gcc main.c -c -o main.o
getcommand.o: var.h getcommand.c 
	gcc getcommand.c -c -o getcommand.o
execute.o: var.h var2.h pinfo.h redirection.h pipe.h execute.c 
	gcc execute.c -c -o execute.o
pwd.o: pwd.c
	gcc pwd.c -c -o pwd.o
cd.o: cd.c
	gcc cd.c -c -o cd.o
echo.o: echo.c
	gcc echo.c -c -o echo.o
pinfo.o: pinfo.c
	gcc pinfo.c -c -o pinfo.o
redirection.o: pipe.h execute.h redirection.c
	gcc redirection.c -c -o redirection.o
pipe.o: redirection.h execute.h pipe.c
	gcc pipe.c -c -o pipe.o
