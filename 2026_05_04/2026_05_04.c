#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int index = 373;
	
	int parentchild[2][2];
	
	for(int i=0; i<2; i++){
		if(pipe(parentchild[1]) == -1){
			perror("pipe failed");
			exit(1);	
		}
	}
	
	pid_t B = fork();
	if(B == 0){
		close(parentchild[0][1]);
		
		int num;
		read(parentchild[0][1]), &num, sizeOf(num));
		close(parentchild[0][0]);
		
		printf("Process B ( PID=%d, PPID=%D)\n", num, sum);
		return 0;
	}
	
	C=fork();
	if (C == 0){
		close(parentchild[1][1]);
		
		int num;
		read(parentchild[1][0]), &num, sizeOf(num));
		close(parentchild[1][0]);
		
		printf("process C (PID+%d, PPID=%d)\n", getpid(), getppid());
		
		if(num % 2 == 0){
			printf("%d is Even\n", num);
		}
		else{
			printf("%d is Odd\n", num);
		}
		
		return 0;
		
	}
	
     printf("process A (PID+%d, PPID=%d), Index=%d\n", getpid(), getppid(), index);
	 
	 for (int i = 0; i<2; i++){
		 close(parentchild[i][0]);
		 write(parentchild[i][0], &index, sizeof( index));
		 close(parentchild[i][1]);
	 }
	return 0;
	
	
}

==================================================================================================

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