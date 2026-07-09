===================================Question 01 - method 1=================================

                          A
						 / \
	SUM OF DIGITS	<=  B   C  => EVEN OR ODD?
				            |
							D


vi pipe.c 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int index = 372;
	
	int pipeAB[2];   // A ---> B
	int pipeAC[2];   // A ---> C
	
	pipe(pipeAB);
	pipe(pipeAC);
	
	int B = fork();
	
	if(B == 0){
		//  child b : Degital sum
		
		close(pipeAB[1]);  // close write end
		int num;
		read(pipeAB[0], &num, sizeof(num));
		close(pipeAB[0]);
		
		printf("Process B (PID=%d, PPID=%d)\n", getpid(), getppid());
		
		int sum = 0, n = num;
		while (n > 0) {
			sum += n % 10;
			n /= 10;
		}
		printf("Digit sum of %d = %d\n", num, sum);
		return 0;
		
	}
	
	int C = fork();
	
	if(C == 0){
		//-----------------------------
		//child C : Odd/Even
		//-----------------------------
		close(pipeAC[1]);  // close write end
		int num;
		read(pipeAC[0], &num, sizeof(num));
		close(pipeAC[0]);
		
		printf("Process C (PID=%d, PPID=%d)\n", getpid(), getppid());
		
		if (num % 2 == 0 ){
			printf("%d is Even", num);
		}
		else{
			printf("%d is Odd", num);
		}
		return 0;
	}
	
	//------------------------------
	// parent A
	//------------------------------
	printf("Process A (PID=%d, PPID=%d), Index=%d\n", getpid(), getppid(), index);
	
	// write to B
	close(pipeAB[0]);
	write(pipeAB[1], &index, sizeof(index));
	close(pipeAB[1]);
	
	// write to C
	close(pipeAC[0]);
	write(pipeAC[1], &index, sizeof(index));
	close(pipeAC[1]);
	
    return 0;
}

--------------output--------------------

gcc pipe.c -o pipe
./pipe

Process A (PID=6874, PPID=6084), Index=372
Process C (PID=6876, PPID=6874)
Process B (PID=6875, PPID=6874)
Digit sum of 372 = 12
372 is Even

                 ┌──────────────┐
                 │  Process A   │
                 │  (Parent)    │
                 │  index = 372 │
                 └──────┬───────┘
                        │
        ┌───────────────┴───────────────┐
        │                               │
        │                               │
   send 372                         send 372
 (pipeAB)                         (pipeAC)
        │                               │
        ▼                               ▼
 ┌──────────────┐              ┌──────────────┐
 │  Process B   │              │  Process C   │
 │ (Child B)    │              │ (Child C)    │
 └──────┬───────┘              └──────┬───────┘
        │                               │
        │                               │
  Reads 372                        Reads 372
        │                               │
        ▼                               ▼
 Digit Sum                        Even/Odd Check
 3 + 7 + 2 = 12                  372 % 2 = 0
        │                               │
        ▼                               ▼
 Prints:                         Prints:
 "Digit sum = 12"               "372 is Even"
 
 
 
 
 

========================Question 01 - - method 02===========================

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int index = 372;

    int pipeAB[2], pipeBA[2]; // A --> B and B --> A
    int pipeAC[2], pipeCA[2]; // A --> C and C --> A

    pipe(pipeAB);
    pipe(pipeBA);
    pipe(pipeAC);
    pipe(pipeCA);

    int B = fork();

    if (B == 0) {
        //------------------------------------
        // Child B : Reads, does digit sum, sends back
        //------------------------------------
        close(pipeAB[1]); // close write end of AB
        close(pipeBA[0]); // close read end of BA

        int num;
        read(pipeAB[0], &num, sizeof(num));
        close(pipeAB[0]);

        printf("Process B (PID=%d, PPID=%d)\n", getpid(), getppid());

        // Digit sum
        int n = num, sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }

        // send result back to parent
        write(pipeBA[1], &sum, sizeof(sum));
        close(pipeBA[1]);

        return 0;
    }

    int C = fork();

    if (C == 0) {   // FIXED: was 'c'
        //--------------------------------------
        // Child C : Reads, does odd/even, sends back
        //---------------------------------------

        close(pipeAC[1]);  // close write end (A --> C)
        close(pipeCA[0]);  // FIXED: should close read end

        int num;
        read(pipeAC[0], &num, sizeof(num)); // FIXED: removed '$'
        close(pipeAC[0]);

        printf("Process C (PID=%d, PPID=%d)\n", getpid(), getppid());

        int check = (num % 2 == 0) ? 1 : 0;

        // send result to parent
        write(pipeCA[1], &check, sizeof(check));
        close(pipeCA[1]); // FIXED: wrong pipe name before

        return 0;
    }

    //-----------------------------------------
    // Parent A : sends and receives
    //-----------------------------------------

    printf("Process A (PID=%d, PPID=%d), Index=%d\n", getpid(), getppid(), index);

    // send to B
    close(pipeAB[0]);
    write(pipeAB[1], &index, sizeof(index));
    close(pipeAB[1]);

    // send to C
    close(pipeAC[0]);
    write(pipeAC[1], &index, sizeof(index));
    close(pipeAC[1]);

    // receive from B
    close(pipeBA[1]);
    int sum;
    read(pipeBA[0], &sum, sizeof(sum));
    close(pipeBA[0]);

    // receive from C
    close(pipeCA[1]);
    int check;
    read(pipeCA[0], &check, sizeof(check));
    close(pipeCA[0]);

    //---------------------------------------
    // Display the result
    //----------------------------------------

    printf("Digit sum received from B = %d\n", sum);

    if (check == 1) {
        printf("C says: %d is Even\n", index);
    } else {
        printf("C says: %d is Odd\n", index);
    }

    return 0;
}


------------------output----------------

Process A (PID=9567, PPID=6084), Index=372
Process B (PID=9568, PPID=9567)
Process C (PID=9569, PPID=9567)
Digit sum received from B = 12
C says: 372 is Even


                 ┌──────────────┐
                 │  Process A   │
                 │  (Parent)    │
                 │  index=372   │
                 └──────┬───────┘
                        │
        ┌───────────────┴───────────────┐
        │                               │
        │                               │
   send 372                         send 372
 (pipeAB)                         (pipeAC)
        │                               │
        ▼                               ▼
 ┌──────────────┐              ┌──────────────┐
 │  Process B   │              │  Process C   │
 │ (Child B)    │              │ (Child C)    │
 └──────┬───────┘              └──────┬───────┘
        │                               │
        │                               │
  Digit Sum                        Even/Odd Check
  3+7+2 = 12                      372 % 2 = 0
        │                               │
        ▼                               ▼
   send 12                          send 1
  (pipeBA)                        (pipeCA)
        │                               │
        └───────────────┬───────────────┘
                        ▼
                 ┌──────────────┐
                 │  Process A   │
                 │  Receives    │
                 │  sum = 12    │
                 │  check = 1   │
                 └──────┬───────┘
                        ▼
              ┌─────────────────────┐
              │   FINAL OUTPUT      │
              │ Digit sum = 12      │
              │ 372 is Even         │
              └─────────────────────┘