/*
write a c program to create a process tree as shown below

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
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){

       int pipeAB[2];
       int pipeAC[2];
       int pipeBD[2];
       int pipeBE[2];

       pipe(pipeAB);
       pipe(pipeAC);
       pipe(pipeBD);
       pipe(pipeBE);

       printf(" PID of A : %d\n",getpid());
       int num;

       printf("Enter a decimal number: ");
       scanf("%d", &num);

       // process b
       if(fork() == 0){
            printf(" PID of B : %d\n",getpid());
            printf(" Parent PID of B : %d\n",getppid());

            int n1;

            close(pipeAB[1]);
            read(pipeAB[0], &n1, sizeof(n1));
            close(pipeAB[0]);

            int odd;

            if( n1 % 2 == 0){
               odd = n1-1;
               printf(" largest odd number less than %d : %d\n",n1,odd);
            }
            else{
               odd = n1-2;
               printf(" largest odd number less than %d : %d\n",n1,odd);
            }

            // FIX: send odd to D and E
            write(pipeBD[1], &odd, sizeof(odd));
            write(pipeBE[1], &odd, sizeof(odd));

             // process d
             if(fork() == 0){
                   printf(" PID of D : %d\n",getpid());
                   printf(" Parent PID of D : %d\n",getppid());

                   int n3;

                   close(pipeBD[1]);
                   read(pipeBD[0], &n3, sizeof(n3));
                   close(pipeBD[0]);

                   int binary[100];
                   int i=0;
                   while( n3!=0){
                      binary[i]=n3%2;
                      n3=n3/2;
                      i++;
                   }
                   for(int j=i-1; j>=0;j--){
                      printf("%d",binary[j]);
                   }

                   printf("\n");
                   exit(0);
             }
             // process e
             else if(fork() == 0){
                   printf(" PID of E : %d\n",getpid());
                   printf(" Parent PID of E : %d\n",getppid());

                   int n4;

                   close(pipeBE[1]);
                   read(pipeBE[0], &n4, sizeof(n4));
                   close(pipeBE[0]);

                   int octal[100];
                   int i=0;
                   while( n4!=0){
                      octal[i]=n4%8;
                      n4=n4/8;
                      i++;
                   }
                   for(int j=i-1; j>=0;j--){
                      printf("%d",octal[j]);
                   }

                   printf("\n");
                   exit(0);
            }

            wait(NULL);
            wait(NULL);
            exit(0);
       }
       // process c
       else if(fork() == 0){
            printf(" PID of C : %d\n",getpid());
            printf(" Parent PID of C : %d\n",getppid());

            int n2;

            close(pipeAC[1]);
            read(pipeAC[0], &n2, sizeof(n2));
            close(pipeAC[0]);

            int even;

            if( n2 % 2 == 0){
               even = n2-2;
               printf(" largest even number less than %d : %d\n",n2,even);
            }
            else{
               even = n2-1;
               printf(" largest even number less than %d : %d\n",n2,even);
            }

             // process f
             if(fork() == 0){
                   printf(" PID of F : %d\n",getpid());
                   printf(" Parent PID of F : %d\n",getppid());
                   exit(0);
             }

            // process g
             else if(fork() == 0){
                   printf(" PID of G : %d\n",getpid());
                   printf(" Parent PID of G : %d\n",getppid());
                   exit(0);
            }

            wait(NULL);
            wait(NULL);
            exit(0);
       }

        close(pipeAB[0]);
        write(pipeAB[1], &num, sizeof(num));
        close(pipeAB[1]);

        close(pipeAC[0]);
        write(pipeAC[1], &num, sizeof(num));
        close(pipeAC[1]);

        close(pipeBD[0]);
        close(pipeBD[1]);

        close(pipeBE[0]);
        close(pipeBE[1]);

        wait(NULL);
        wait(NULL);

        return 0;
}



================================================================================
/*
develop a cprogram to perform the following tasksusing one parent, 
child, grandchildprocesses and one unnamed pipes

a) read the number of integersNfrom the user in  the parent process. 
reads and sends N number of integers to its child process using pipeA.

b) the child process reads the N number of integer values from pipeA, 
calculate the sum and sewnds it along with the number of integers to its
child process (the grandchild process) using pipe B.

C)the grandchild process reads ths sum value from pipe B calculates 
the average and sends it back to its grandparent process through pipe C.

d) the parent process reads the value from the grandchild using pipe c 
and print the calculated average value.

e) Each process should print the log message of their activities 
indicating their process ID, parent process ID, activity and value (if any).

you are required to use proper error han dling mechanisms and process synchronization techniques.

*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
      // parent process
       printf("Parent process PID: %d\n", getpid());
       
       int pipeA[2];
       int pipeB[2];
       int pipeC[2];

       pipe(pipeA);
       pipe(pipeB);
       pipe(pipeC);

       int n;
       printf("Enter number of integers: ");
       scanf("%d", &n);

       int num[n];

       printf("Enter %d numbers:\n", n);
       
       for(int i = 0; i < n; i++){
          scanf("%d", &num[i]);
       }

      if(fork() == 0){
        
        // child process
         printf("Child process PID: %d, PPID: %d\n",
                 getpid(), getppid());

         
         close(pipeA[1]);

         int n2;

         read(pipeA[0], &n2, sizeof(n2));

         int num2[n2];

         read(pipeA[0], num2, sizeof(int) * n2);

         close(pipeA[0]);

         int sum1 = 0;

         for(int i = 0; i < n2; i++){
            sum1 = sum1 + num2[i];
         }

         printf("Child calculated sum: %d\n", sum1);



           if(fork() == 0){

            // grand child process
            printf("Grandchild process PID: %d, PPID: %d\n",
                    getpid(), getppid());

            
            close(pipeB[1]);

            int sum2;

            read(pipeB[0], &sum2, sizeof(sum2));

            int n3;

            read(pipeB[0], &n3, sizeof(n3));

            close(pipeB[0]);

            float avg1;
             
            avg1 = (float)sum2 / n3;

            printf("Grandchild calculated average: %.2f\n", avg1);

            close(pipeC[0]);

            write(pipeC[1], &avg1, sizeof(avg1));

            close(pipeC[1]);

            exit(0);  
           }

          close(pipeB[0]);

          write(pipeB[1], &sum1, sizeof(sum1));

          write(pipeB[1], &n2, sizeof(n2));

          close(pipeB[1]);

          wait(NULL);

          exit(0);
      }

      close(pipeA[0]);

      write(pipeA[1], &n, sizeof(n));

      write(pipeA[1], num, sizeof(int) * n);

      close(pipeA[1]);

      close(pipeC[1]);

      float avg2;

      read(pipeC[0], &avg2, sizeof(avg2));

      close(pipeC[0]);

      printf("Average value of integers: %.2f\n", avg2);

      wait(NULL);

      return 0;
}


Parent process PID: 3210
Enter number of integers: 4
Enter 4 numbers:
10
20
30
40

Child process PID: 3211, PPID: 3210
Child calculated sum: 100

Grandchild process PID: 3212, PPID: 3211
Grandchild calculated average: 25.00

Average value of integers: 25.00



============================================================================

/*
problem satement
create a simplified vrsion of a process hierarchy and implement Inter-Process Communication(IPC)
using pipes.

Task description:

1. process A (Parent) shall read a single integer x from the user.
2. Process A must then create one child Process (B).
3. Process B shall create two grandchild processes (D and E)
4. Data must flow as follows:
A sends x to B.
B calculates the square of x (x^2) and sends that result to both D and E.

Individual Process Requirements:
  
1.Process B: Receive x from A, calculate x^2, and print: "Process B: received [x], Square is [x^2] ".
2.Process D: Receive the squared value from Ba nd print it in HexaDecimal format(Hint: use %x inside 
the printf function for converting to HexaDecimal value).
3. Process E: Receive the squared value from B and print it in Octal format.
(Hint: use %o inside the printf function for converting to Octal value).
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    // parent process A
    printf("Process A (Parent) PID: %d\n", getpid());

    int pipeA[2];
    int pipeD[2];
    int pipeE[2];

    pipe(pipeA);
    pipe(pipeD);
    pipe(pipeE);

    int x;

    printf("Enter a number: ");
    scanf("%d", &x);

    if(fork() == 0)
    {
        // child process B
        printf("Process B PID: %d, PPID: %d\n",
                getpid(), getppid());

        close(pipeA[1]);

        int num;

        read(pipeA[0], &num, sizeof(num));

        close(pipeA[0]);

        int square = num * num;

        printf("Process B: received %d, Square is %d\n",
                num, square);

        // process D
        if(fork() == 0)
        {
            printf("Process D PID: %d, PPID: %d\n",
                    getpid(), getppid());

            close(pipeD[1]);

            int valueD;

            read(pipeD[0], &valueD, sizeof(valueD));

            close(pipeD[0]);

            printf("Process D: Hexadecimal value = %x\n",
                    valueD);

            exit(0);
        }

        // process E
        if(fork() == 0)
        {
            printf("Process E PID: %d, PPID: %d\n",
                    getpid(), getppid());

            close(pipeE[1]);

            int valueE;

            read(pipeE[0], &valueE, sizeof(valueE));

            close(pipeE[0]);

            printf("Process E: Octal value = %o\n",
                    valueE);

            exit(0);
        }

        // B sends square to D and E
        close(pipeD[0]);

        write(pipeD[1], &square, sizeof(square));

        close(pipeD[1]);

        close(pipeE[0]);

        write(pipeE[1], &square, sizeof(square));

        close(pipeE[1]);

        wait(NULL);
        wait(NULL);

        exit(0);
    }

    // parent A sends x to B
    close(pipeA[0]);

    write(pipeA[1], &x, sizeof(x));

    close(pipeA[1]);

    wait(NULL);

    return 0;
}


Process A (Parent) PID: 3200
Enter a number: 5

Process B PID: 3201, PPID: 3200
Process B: received 5, Square is 25

Process D PID: 3202, PPID: 3201
Process D: Hexadecimal value = 19

Process E PID: 3203, PPID: 3201
Process E: Octal value = 31
