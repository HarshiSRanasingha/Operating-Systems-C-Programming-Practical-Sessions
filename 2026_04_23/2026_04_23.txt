/* write a c program to create a process tree as shown below

                              A
						    /   \
                           B     C
                          / \  	/ \
                         D   E  F  G
						 
Each process should display its process id and its parent process id.
 The program should satisfy the following:
 
(a) The parent process (A) reads a decimal number x from user input.
(b) The child process (B) finds and displays the largest odd number which is less
than x.
(c)The child process (C) finds and displays the largest even number which is less
than x.
(d) the grandchild process (D) converts that largest odd number into binary number and display it
(e) the grandchild process (E) converts that largest odd number into octal number and display it
*/

#include<stdio.h>
#include<unistd.h>

int main(){
	
	int pipeAB[2];
        int pipeAC[2];

        pipe(pipeAB);
        pipe(pipeAC);

        int num;
        printf("Enter number : ");
        scanf("%d", &num);
		
	// process A 
    printf("A (PID: %d)\n",getpid());
	
	

    if(fork() == 0)
    {
		// process B
        printf("B (PID:%d), (PPID: %d)\n",getpid(),getppid());
		
			int n;
                close(pipeAB[1]);
                read(pipeAB[0], &n, sizeof(n));
                close(pipeAB[0]);

                int res = 0;
                if (n % 2 == 0)
                {
                        res = n - 1;
                }
                else
                {
                        res = n - 2;
                }
                
                printf("%d is the largest odd number\n", res);

                exit(0);
			}

        if(fork() == 0)
        {
             printf("D (PID:%d), (PPID: %d)\n",getpid(),getppid());
        } 
        else if (fork() == 0)
		{
			 printf("E (PID:%d), (PPID: %d)\n",getpid(),getppid());
		}		
    }
	
    else if(fork() == 0)
    {
		 // process C   
         printf("C (PID:%d), (PPID: %d)\n",getpid(),getppid());
			
			int n;
                close(pipeAC[1]);
                read(pipeAC[0], &n, sizeof(n));
                close(pipeAC[0]);

                int res = 0;
                if (n % 2 == 0)
                {
                        res = n - 2;
                }
                else
                {
                        res = n - 1;
                }
               
                printf("%d is the largest even number\n", res);

                exit(0);

		if(fork() == 0)
		{
			printf("F (PID:%d), (PPID: %d)\n",getpid(),getppid());
		}
		else if (fork() == 0)
		{
			printf("g (PID:%d), (PPID: %d)\n",getpid(),getppid());
		}
  
    }

     close(pipeAB[0]);
        write(pipeAB[1], &num, sizeof(num));
        close(pipeAB[1]);

        close(pipeAC[0]);
        write(pipeAC[1], &num, sizeof(num));
        close(pipeAC[1]);

        wait(NULL);
        wait(NULL);

        return 0;
		  
}						 

// -----------------------------------------------------------------------------------------

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>


void toBinary(int n) {
    int b[32], i=0;
    while(n>0){
        b[i++] = n%2;
        n/=2;
    }
    for(int j=i-1;j>=0;j--)
        printf("%d", b[j]);
}


void toOctal(int n){
    printf("%o", n);
}

int main(){

    int pipeAB[2];
    int pipeAC[2];

    pipe(pipeAB);
    pipe(pipeAC);

    int num;
    printf("Enter number : ");
    scanf("%d", &num);

    // process A
    printf("A (PID: %d)\n",getpid());

    if(fork() == 0)
    {
        // -------- B --------
        printf("B (PID:%d), (PPID: %d)\n",getpid(),getppid());

        int n;
        close(pipeAB[1]);
        read(pipeAB[0], &n, sizeof(n));
        close(pipeAB[0]);

        int res;
        if (n % 2 == 0)
            res = n - 1;
        else
            res = n - 2;

        printf("Largest odd: %d\n", res);

        // ---- D ----
        if(fork() == 0)
        {
            printf("D (PID:%d), (PPID: %d)\n",getpid(),getppid());
            printf("Binary: ");
            toBinary(res);
            printf("\n");
            exit(0);
        }

        // ---- E ----
        if(fork() == 0)
        {
            printf("E (PID:%d), (PPID: %d)\n",getpid(),getppid());
            printf("Octal: ");
            toOctal(res);
            printf("\n");
            exit(0);
        }

        wait(NULL);
        wait(NULL);
        exit(0);
    }

    else if(fork() == 0)
    {
        // -------- C --------
        printf("C (PID:%d), (PPID: %d)\n",getpid(),getppid());

        int n;
        close(pipeAC[1]);
        read(pipeAC[0], &n, sizeof(n));
        close(pipeAC[0]);

        int res;
        if (n % 2 == 0)
            res = n - 2;
        else
            res = n - 1;

        printf("Largest even: %d\n", res);

        // ---- F ----
        if(fork() == 0)
        {
            printf("F (PID:%d), (PPID: %d)\n",getpid(),getppid());
            exit(0);
        }

        // ---- G ----
        if(fork() == 0)
        {
            printf("G (PID:%d), (PPID: %d)\n",getpid(),getppid());
            exit(0);
        }

        wait(NULL);
        wait(NULL);
        exit(0);
    }

    // send data from A
    close(pipeAB[0]);
    write(pipeAB[1], &num, sizeof(num));
    close(pipeAB[1]);

    close(pipeAC[0]);
    write(pipeAC[1], &num, sizeof(num));
    close(pipeAC[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}