//-----------------q1------------------------
vi second.c

	#include <stdio.h>
	#include <unistd.h>
	int main()
	{
	int p=getpid();
	printf("\nProcess id %d\n", p);
	return 0;	
	}

gcc second.c -o second
./second

	Process id 34275


//-------------------q2---------------------

vi second.c

	#include <stdio.h>
	#include <unistd.h>
	int main()
	{
		fork();
		int p=getpid();
		printf("\nProcess id %d\n", p);
		return 0;	
	}
	
gcc second.c -o second
./second
	
	Process id 35690

	Process id 35691


//-------------------q3---------------------

vi second.c

	#include <stdio.h>
	#include <unistd.h>
	int main()
	{
		fork();
		int p=getpid();
		printf("\nHello World\n");
		printf("The process id is %d \n", p);
		return 0;
	}
	
gcc second.c -o second
./second
	
	Hello World
	The process id is 37861

	Hello World
	The process id is 37862
	

//-------------------q4---------------------

vi second.c

	#include <stdio.h>
	#include <unistd.h>
	int main()
	{
		int f= fork();
		printf("Hello World\n");
		printf("Fork returns %d \n", f);
		return 0;
	}
		
gcc second.c -o second
./second
	
Hello World
Fork returns 39852
Hello World
Fork returns 0


//-------------------q5---------------------

vi second.c

#include <stdio.h>
	#include <unistd.h>
	int main()
	{
		printf("Hi\n");
		int f= fork();
		printf("Hello World\n", f);
		return 0;
	}
	
		
gcc second.c -o second
./second
	
	Hi
	Hello World
	Hello World


//-------------------q6---------------------

vi second.c

	#include <stdio.h>
	#include <unistd.h>
	int main()
	{
		fork();
		fork();
		printf("Iam %d my pid is %d ppid is %d\n", getpid(),getpid(),getppid());
		return 0;
	}
	
		
gcc second.c -o second
./second
	
	Iam 43883 my pid is 43883 ppid is 6294
	Iam 43885 my pid is 43885 ppid is 43883
	Iam 43884 my pid is 43884 ppid is 43883
	Iam 43886 my pid is 43886 ppid is 43884



