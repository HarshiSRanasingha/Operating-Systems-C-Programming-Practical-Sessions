#include<stdio.h>
#include<unistd.h>
int main()
{
	int child_pid;
	child_pid=fork();
	if (child_pid == 0){
	printf("Child process\n");
	}else if(child_pid > 0){
	printf("parent process\n");
	}else
	perror("Fork faild");
	return 1;
}


[2022ict73@fedora ~]$ gcc second.c -o second
[2022ict73@fedora ~]$ ./second
parent process
Child process
__________________________________________________________________________________________________________________

#include<stdio.h>
#include<unistd.h>
int main()
{
	pid_t child_pid;
	child_pid=fork();
	if (child_pid == 0){
	printf("Child process\n");
	}else if(child_pid > 0){
	printf("parent process\n");
	}else
	perror("Fork faild");
	return 1;
}

[2022ict73@fedora ~]$ gcc second.c -o second
[2022ict73@fedora ~]$ ./second
parent process
Child process
__________________________________________________________________________________________________________________

#include<stdio.h>
#include<unistd.h>
int main()
{
	printf("A (PID: %d)\n",getpid());
	if(fork() == 0)//create a child process of A
	{
		printf("B (PID: %d, Parent PID: %d)\n",getpid()getppid());
		
		if(fork() == 0){  //child process of B
		
		printf("C (PID: %d, Parent PID: %d)\n",getpid()getppid());
	}
	}
	
	return 0;	
}

[2022ict73@fedora ~]$ gcc second.c -o second
[2022ict73@fedora ~]$ ./second
A (PID: 16213)
B (PID: 16214, Parent PID: 16213)
C (PID: 16215, Parent PID: 16214)
		A
		|
		B
		|
		C
__________________________________________________________________________________________________________________
#include<stdio.h>
#include<unistd.h>
int main(){
	printf("A (PID: %d)\n",getpid());
	if(fork() == 0)
	{
		printf("B (PID:%d, Parent PID: %d)\n",getpid(),getppid());
		
		if(fork() == 0)
	{
		printf("C (PID:%d, Parent PID: %d)\n",getpid(),getppid());
	}
	
	}
	return 0;
}

[2022ict73@fedora ~]$ gcc second.c -o second
[2022ict73@fedora ~]$ ./second
A (PID: 21788)
B (PID:21790, Parent PID: 21788)
C (PID:21791, Parent PID: 21790)

===============================================================================
-----------------------------------
(1)

vi third.c

#include <stdio.h>
#include <unistd.h>
int main()
{
pid_t child_pid;			-----> pid_t = datatype (parent ID )
child_pid=fork();
if (child_pid == 0){
printf("Child Process\n");
}else if(child_pid > 0){
printf("Parent Process\n");
}else
perror("Fork Failed");
return 1;
}

gcc third.c -o third   
./third

	Parent Process
	Child Process

------------------------------------
(2)

vi third.c

#include <stdio.h>
#include <unistd.h>
int main()
{
printf("A (PID: %d)\n", getpid());
if(fork() == 0 )														-------> create a child process of A
{
printf("B (PID: %d, Parent PID: %d)\n",getpid(),getppid());             -------> ppid= parent process id
if(fork() == 0)
{
printf("C (PID: %d, Parent PID: %d)\n", getpid(),getppid());
}
}
return 0;
}

gcc third.c -o third
./third

	A (PID: 15483)
	B (PID: 15484, Parent PID: 15483)
	C (PID: 15485, Parent PID: 15484)

============================
	A
	|
	B
	|
	C

-------------------------------------
(3)

	A
   / \
   B  C
   

#include<stdio.h>
#include<unistd.h>
int main(){
        printf("A (PID: %d)\n",getpid());
        if(fork() == 0)
        {
                printf("B (PID:%d), (PPID: %d)/n",getpid(),getppid());
        }
		else if(fork() == 0)
        {
          printf("C (PID:%d), (PPID: %d)/n",getpid(),getppid());
        }
return 0;
}

  