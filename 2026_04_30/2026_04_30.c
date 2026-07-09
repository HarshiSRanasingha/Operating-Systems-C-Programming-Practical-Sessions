======================01=======================
#include <stdio.h>

int main() {
    int num, original, digit, sum;

    printf("Armstrong numbers between 100 and 999 are:\n");

    for (num = 100; num <= 999; num++) {
        original = num;
        sum = 0;

        while (original != 0) {
            digit = original % 10;
            sum += digit * digit * digit;
            original /= 10;
        }

        if (sum == num) {
            printf("%d\n", num);
        }
    }

    return 0;
}

---------------------------------------
Armstrong numbers between 100 and 999 are:
153
370
371
407

=====================02===============================

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
