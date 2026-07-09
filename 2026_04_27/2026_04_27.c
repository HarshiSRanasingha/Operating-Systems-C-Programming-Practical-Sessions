/*
Develop a C program to convert tempreature from celsius (C) to farenheight (F),
farenheight to celsius, kelvin to celsius. the program should utilise a parent process, 
three child process, and unnamed pipes. Tempreature units such as C, F, and K should be case sensitive.

( meaning that inputs such as 'c', 'C', 'f','F', 'k', 'K' should be correctly interpreted).
the parent process should send each tempreature to a corresponding child process through pipes.

child1 ==>  C -> F
child2 ==>  F -> C
child3 ==>  K -> C

F= 9/5(C)+32
C=K-273.15
*/




#include<stdio.h>
#include<unistd.h>

int main(){
	
	    int pipeAB[2];
        int pipeAC[2];
		int pipeAD[2];

        pipe(pipeAB);
        pipe(pipeAC);
		pipe(pipeAD);

        int num;
        printf("Enter tempreature : ");
		scanf("%d", &temp);
		printf(" Enter tempreature type (with one letter celsius-c,kelvin-k,fahrenheight-f) : ");
        scanf("%s", type);
		
	// process A 
    //printf("A (PID: %d)\n",getpid());
	
	if(type = 'c' or type = 'C')
	{  
       if(fork() == 0)
       {
		  // process B
           printf("B (PID:%d), (PPID: %d)\n",getpid(),getppid());
		
			int temp;
                close(pipeAB[1]);
                read(pipeAB[0], &temp, sizeof(temp));
                close(pipeAB[0]);

                double tempF = ((9/5)*temp)+32
                
                printf("tempreature in celsius : %d", temp);
                printf("tempreature in 	fahrenheight : %d", tempF);
                exit(0);
	   }
    }
	
	else if(type = 'f' or type = 'F')
	{
		if(fork() == 0)
        {
		   // process C   
           printf("C (PID:%d), (PPID: %d)\n",getpid(),getppid());
			
			int temp;
                close(pipeAC[1]);
                read(pipeAC[0], &temp, sizeof(temp));
                close(pipeAC[0]);

                double tempC = (temp-32)*(5/9)
                
                printf("tempreature in Fahrenheight : %d", temp);
                printf("tempreature in celsius : %d", tempC);
                exit(0);

		
        }
	}
    
	else if(type = 'k' or type = 'K')
	
       if(fork() == 0)
       {
		 // process D   
         printf("D (PID:%d), (PPID: %d)\n",getpid(),getppid());
			
			int temp;
                close(pipeAD[1]);
                read(pipeAD[0], &temp, sizeof(temp));
                close(pipeAD[0]);

                double tempC = temp-273.15;
                
                printf("tempreature in kelvin : %d", temp);
                printf("tempreature in celsius : %d", tempC);
                exit(0);
		
        }

     }
	
        close(pipeAB[0]);
        write(pipeAB[1], &temp, sizeof(num));
        close(pipeAB[1]);
		
        close(pipeAC[0]);
        write(pipeAC[1], &temp, sizeof(num));
        close(pipeAC[1]);
		
		close(pipeAD[0]);
        write(pipeAD[1], &temp, sizeof(num));              
        close(pipeAD[1]);
		

        wait(NULL); 
        wait(NULL);
		wait(NULL);

        return 0;
		  
}						 

==========================================================================================

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
        int pipeAB[2];
        int pipeAC[2];
        int pipeAD[2];

        pipe(pipeAB);
        pipe(pipeAC);
        pipe(pipeAD);

        if (fork() == 0)
        {
                int n;
                close(pipeAB[1]);
                read(pipeAB[0], &n, sizeof(n));
                close(pipeAB[0]);

                printf("Fahrenheit : %.2f\n", ((9.0/5)*n+32));

                exit(0);
        }

        if (fork() == 0)
        {
                int n;
                close(pipeAC[1]);
                read(pipeAC[0], &n, sizeof(n));
                close(pipeAC[0]);

                printf("Celcius : %.2f\n", (((n-32)*5)/9));

                exit(0);
        }

        if (fork() == 0)
        {
                int n;
                close(pipeAD[1]);
                read(pipeAD[0], &n, sizeof(n));
                close(pipeAD[0]);

                printf("Celcius : %d\n", (n - 273));

                exit(0);
        }


        printf("enter values C, F, K : \n");
        int cval, fval, kval;
        scanf("%d", &cval);
        scanf("%d", &fval);
        scanf("%d", &kval);

        close(pipeAB[0]);
        write(pipeAB[1], &cval, sizeof(cval));
        close(pipeAB[1]);

        wait(NULL);

        close(pipeAC[0]);
        write(pipeAC[1], &fval, sizeof(fval));
        close(pipeAC[1]);

        wait(NULL);

        close(pipeAD[0]);
        write(pipeAD[1], &kval, sizeof(kval));
        close(pipeAD[1]);

        wait(NULL);

        return 0;
}
