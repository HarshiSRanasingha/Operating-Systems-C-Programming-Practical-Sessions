 =======================QUESTION 01===============================
 
                          A
						 / \
	SUM OF DIGITS	<=  B   C  => EVEN OR ODD?
				            |
							D
							
							
#include<stdio.h>
#include<unistd.h>
int main(){
	    printf("enter a number: ");
		scanf("%d",&n );
		
        printf("A (PID: %d)\n",getpid());
	
        if(fork() == 0)
        {
                printf("B (PID:%d), (PPID: %d)\n",getpid(),getppid());
				
				num1 = n;
				sum = 0;
				while(num <=0){
					sum = sum + num1%10;
					num1 = num1/10;
				}
				printf("Sum of %d 's digits is %d ",num1,sum);
        }
		else if(fork() == 0)
        {
          printf("C (PID:%d), (PPID: %d)\n",getpid(),getppid());
		  
		  num2 = n;
		  
		  if(num2%2 == 0){
			  printf(" %d is a even number",num2);
		  }
		  else{
			  printf(" %d is a odd number",num2);
		  }
		  
			  if(fork() == 0){
				  printf("d (PID:%d), (PPID: %d)\n",getpid(),getppid());
				  
			  }
        }
    return 0;
}

-----------------------------------------------------------------------------
#include <stdio.h>

int main() {
    int num, sum = 0, digit;

    // A: Input number
    printf("Enter a number: ");
    scanf("%d", &num);

    int temp = num;

    // B: Calculate sum of digits
    while (temp != 0) {
        digit = temp % 10;
        sum += digit;
        temp /= 10;
    }

    printf("Sum of digits = %d\n", sum);

    // C: Check even or odd
    if (sum % 2 == 0) {
        // D: Output
        printf("The sum of digits is EVEN\n");
    } else {
        // D: Output
        printf("The sum of digits is ODD\n");
    }

    return 0;
}

----------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>

int main() {
    int num, sum = 0, digit;

    // A: Input number
    printf("Enter a number: ");
    scanf("%d", &num);

    // B: Calculate sum of digits
    int temp = num;
    while (temp != 0) {
        digit = temp % 10;
        sum += digit;
        temp /= 10;
    }

    printf("Sum of digits = %d\n", sum);

    // C/D: Check even or odd
    if (sum % 2 == 0) {
        printf("The sum is EVEN\n");
    } else {
        printf("The sum is ODD\n");
    }

    return 0;
}

--------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

// Function to calculate sum of digits
int sum_of_digits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main() {
    pid_t pidB, pidC, pidD;
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    // Create process B
    pidB = fork();

    if (pidB < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if (pidB == 0) {
        // Process B
        printf("\nProcess B (PID: %d, Parent: %d)\n", getpid(), getppid());
        printf("Sum of digits = %d\n", sum_of_digits(num));
        exit(0);
    }

    // Back to A, create process C
    pidC = fork();

    if (pidC < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if (pidC == 0) {
        // Process C
        printf("\nProcess C (PID: %d, Parent: %d)\n", getpid(), getppid());

        if (num % 2 == 0)
            printf("Number is EVEN\n");
        else
            printf("Number is ODD\n");

        // Create process D from C
        pidD = fork();

        if (pidD == 0) {
            // Process D
            printf("\nProcess D (PID: %d, Parent: %d)\n", getpid(), getppid());
            printf("I am child of C\n");
            exit(0);
        }

        exit(0);
    }

    // Process A
    printf("\nProcess A (PID: %d)\n", getpid());

    return 0;
}

=============================QUESTION 02==============================

  SAME QUESTION DO WITH PIPE
  
                          A
						 / \
	SUM OF DIGITS	<=  B   C  => EVEN OR ODD?
				            |
							D
							
							
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    int num, received_num;
    int sum = 0, digit;

    // Create pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // A: Input number
    printf("Enter a number: ");
    scanf("%d", &num);

    // Write to pipe
    write(fd[1], &num, sizeof(num));

    // Read from pipe
    read(fd[0], &received_num, sizeof(received_num));

    // B: Calculate sum of digits
    int temp = received_num;
    while (temp != 0) {
        digit = temp % 10;
        sum += digit;
        temp /= 10;
    }

    printf("Sum of digits = %d\n", sum);

    // C: Check even or odd
    if (sum % 2 == 0) {
        // D: Output
        printf("The sum of digits is EVEN\n");
    } else {
        printf("The sum of digits is ODD\n");
    }

    return 0;
}

----------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	
	
}
