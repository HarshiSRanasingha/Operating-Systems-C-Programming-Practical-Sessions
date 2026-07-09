===================================Q1========================================
 vi fourth.c
 
     A
	/ \
   B   C
   
#include<stdio.h>
#include<unistd.h>
int main(){
        printf("A (PID: %d)\n",getpid());
        if(fork() == 0)
        {
                printf("B (PID:%d), (PPID: %d)\n",getpid(),getppid());
        }
		else if(fork() == 0)
        {
          printf("C (PID:%d), (PPID: %d)\n",getpid(),getppid());
        }
return 0;
}

  


gcc fourth.c -o fourth
./fourth

		A (PID: 9495)
		B (PID:9496, Parent PID: 9495)
		C (PID:9497, Parent PID: 9496)
		
====================================Q2=========================================================
vi fourth.c
 
		 A
		/ \
	   B   C
	  /\   /\
	 D  E F G
	 
#include<stdio.h>
#include<unistd.h>

int main(){
    printf("A (PID: %d)\n",getpid());

    if(fork() == 0)
    {
        printf("B (PID:%d), (PPID: %d)\n",getpid(),getppid());

        if(fork() == 0)
        {
            printf("D (PID:%d), (PPID: %d)\n",getpid(),getppid());
        }
        else
        {
            if(fork() == 0)
            {
                printf("E (PID:%d), (PPID: %d)\n",getpid(),getppid());
            }
        }
    }
    else
    {
        if(fork() == 0)
        {
            printf("C (PID:%d), (PPID: %d)\n",getpid(),getppid());

            if(fork() == 0)
            {
                printf("F (PID:%d), (PPID: %d)\n",getpid(),getppid());
            }
            else
            {
                if(fork() == 0)
                {
                    printf("G (PID:%d), (PPID: %d)\n",getpid(),getppid());
                }
            }
        }
    }

    return 0;
}
  
########################################################################

#include<stdio.h>
#include<unistd.h>

int main(){
    printf("A (PID: %d)\n",getpid());

    if(fork() == 0)
    {
        printf("B (PID:%d), (PPID: %d)\n",getpid(),getppid());

        if(fork() == 0)
        {
            printf("D (PID:%d), (PPID: %d)\n",getpid(),getppid());
        }
        else if(fork() == 0)
        {
             printf("E (PID:%d), (PPID: %d)\n",getpid(),getppid());
        }
        
    }
    else if(fork() == 0)
    {
            printf("C (PID:%d), (PPID: %d)\n",getpid(),getppid());

            if(fork() == 0)
            {
                printf("F (PID:%d), (PPID: %d)\n",getpid(),getppid());
            }
            else if(fork() == 0)
            {
                printf("G (PID:%d), (PPID: %d)\n",getpid(),getppid());
            }
            
        
    }

    return 0;
}

gcc fourth.c -o fourth
./fourth

		
A (PID: 16343)
B (PID:16344), (PPID: 16343)
C (PID:16345), (PPID: 16343)
D (PID:16346), (PPID: 16344)
F (PID:16347), (PPID: 16345)
E (PID:16348), (PPID: 16344)
G (PID:16349), (PPID: 16345)




==================================Q3=============================================
         A
		/ \
	   B   C
	   |   |
	   D   E
	  
#include<stdio.h>
#include<unistd.h>

int main(){
    printf("A (PID: %d)\n",getpid());

    if(fork() == 0)
    {
        printf("B (PID:%d), (PPID: %d)\n",getpid(),getppid());

        if(fork() == 0)
        {
            printf("D (PID:%d), (PPID: %d)\n",getpid(),getppid());
        }  
    }
	
    else if(fork() == 0)
    {
            printf("C (PID:%d), (PPID: %d)\n",getpid(),getppid());

            if(fork() == 0)
            {
                printf("F (PID:%d), (PPID: %d)\n",getpid(),getppid());
            }
  
    }

    return 0;
}

A (PID: 18135)
B (PID:18136), (PPID: 18135)
C (PID:18137), (PPID: 18135)
D (PID:18138), (PPID: 18136)
F (PID:18139), (PPID: 18137)


====================================q4======================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int num;
    pid_t pid;

    printf("Enter a number: ");
    scanf("%d", &num);

    pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0) {
        int i;
        long long fact = 1;

        for (i = 1; i <= num; i++) {
            fact *= i;
        }

        printf("Child Process:\n");
        printf("Factorial of %d = %lld\n", num, fact);
    }
    else {
        printf("Parent Process:\n");
        printf("Child created with PID: %d\n", pid);
    }

    return 0;
}



Enter a number: 23
Parent Process:
Child created with PID: 19584
Child Process:
Factorial of 23 = 8128291617894825984



================================q5======================================
#include <stdio.h>
#include <unistd.h>

int main(){

	int child1, child2;
	int n,i,j,k;
	printf("enter a num:");
	scanf("%d",&n );	
	child1=fork();
	if(child1==0){
		int fact=1;
			for(i=1;i<=n;i++){
				fact=fact*i;
			}
	
	    printf("the factorial of %d is %d\n",n,fact);

   
		int child5=fork();
		if(child5==0){
			int a=0, b=1, c=0;
			for(j=1;j<=n;j++){
				a=b+c;
				b=c;
				c=a;
			}
			printf("the fibonacci is %d\n",a);
	    }
	    
	
	}
	

	else{

		child2=fork();
		if(child2==0){
			int s=1;
			if(n==0){
				s=1;
			}
			else{
				for(k=0; k<n; k++){
					s*=2;
				}
			}
			printf("2 to the power is %d\n",s);
		}
	}
	
	
	int child3=fork();
	if(child3==0){
		int r= n*n;
		printf("square of %d is %d\n",n,r);
	}
	return 0;
}


enter a num:4
the factorial of 4 is 24
2 to the power is 16
square of 4 is 16
the fibonacci is 3
square of 4 is 16
square of 4 is 16
square of 4 is 16
