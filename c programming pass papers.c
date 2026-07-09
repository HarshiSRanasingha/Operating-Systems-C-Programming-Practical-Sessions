//============== C programming pass papers ===============

//------------ 2025 year (2023 exam)- q2 -----------

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){

    pid_t pid1, pid2, pid3;
	sleep(2);
	printf("Task name = Main Task Manager\n");
    printf("PID = %d , PPID = %d , level = %d \n",getpid(),getppid(),0);

    if((pid1=fork())==0){
		sleep(2);
		printf("Task name = File backup Task\n");
		printf("PID = %d , PPID = %d , level = %d \n",getpid(),getppid(),1);

			if(fork()==0){
				sleep(1);
				printf("Task name = Read File\n");
				printf("PID = %d , PPID = %d , level = %d \n",getpid(),getppid(),2);
                exit(0);
			}
			if(fork()==0){
				sleep(1);
				printf("Task name = write backup\n");
				printf("PID = %d , PPID = %d , level = %d \n",getpid(),getppid(),2);
				exit(0);
			}
		wait(NULL);
		wait(NULL);
        exit(0);
	}
    if((pid2=fork())==0){
		sleep(2);
		printf("Task name = Network Monitoring Task\n");
		printf("PID = %d , PPID = %d , level = %d /n",getpid(),getppid(),1);

		if(fork()==0){
				sleep(1);
				printf("Task name = capture packets\n");
				printf("PID = %d , PPID = %d , level = %d \n",getpid(),getppid(),2);
				exit(0);
			}
			if(fork()==0){
				sleep(1);
				printf("Task name = Analyze Traffic\n");
				printf("PID = %d , PPID = %d , level = %d \n",getpid(),getppid(),2);
				exit(0);
			}
		wait(NULL);
		wait(NULL);
		exit(0);
	}
    if((pid3=fork())==0){
		sleep(2);
		printf("Task name = Log Cleanup Task\n");
		printf("PID = %d , PPID = %d , level = %d \n",getpid(),getppid(),1);
		exit(0);
	}

    wait(NULL);
	wait(NULL);
    wait(NULL);
	exit(0);
    
 return 0;
}

/*
Task name = Main Task Manager
PID = 1234 , PPID = 567 , level = 0 
Task name = File backup Task
PID = 1235 , PPID = 1234 , level = 1 
Task name = Read File
PID = 1236 , PPID = 1235 , level = 2 
Task name = write backup
PID = 1237 , PPID = 1235 , level = 2 
Task name = Network Monitoring Task
PID = 1238 , PPID = 1234 , level = 1 
Task name = capture packets
PID = 1239 , PPID = 1238 , level = 2 
Task name = Analyze Traffic
PID = 1240 , PPID = 1238 , level = 2 
Task name = Log Cleanup Task
PID = 1241 , PPID = 1234 , level = 1 
*/



//---------------- 2025 year (2023 exam)- q3 -----------

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

struct Person{
	char name[100];
    int heart_rate;
    int oxygen_level;
    char status[100];
};

int main(){

	int pipeAB[2];
    int pipeBC[2];

	pipe(pipeAB);
	pipe(pipeBC);

	int n;
	printf("Enter number of patients:");
    scanf("%d",&n);

    struct Person person1[n];

	for(int i=0; i<n; i++){
		printf("Enter name :\n");
        scanf("%s",&person1[i].name);
        printf("Enter heart rate :\n");
        scanf("%d",&person1[i].heart_rate);
        printf("Enter oxygen level :\n");
        scanf("%d",&person1[i].oxygen_level);
	}

	if(fork()==0){
		//analyze and decision unit
        struct Person person2[n];
        
		close(pipeAB[1]);
		read(pipeAB[0],person2,sizeof(person2));
        close(pipeAB[0]);

		for(int i=0; i<n; i++){
			int oxy = person2[i].oxygen_level;
            int heart = person2[i].heart_rate;
            int critical1=0;

            if((heart < 60 || heart > 100) && (oxy < 90) ){
				strcpy(person2[i].status,"CRITICAL");
                critical=critical1+1;
			}
			else if((heart > 60 && heart < 65) || (heart > 95 && heart < 100) && (oxy < 90 && oxy > 92));{
				strcpy(person2[i].status,"ALERT");
			}
			else if((heart > 60 && heart < 100) && (oxy > 92)){
				strcpy(person2[i].status,"STABLE");
			}	
		}
		
		if(fork()==0){
		//monitoring unit
		struct Person person3[n];

		close(pipeBC[1]);
		read(pipeBC[0],person3,sizeof(person3));
		read(pipeBC[0],critical2,sizeof(critical2));
        close(pipeBC[0]);

		printf("============== Hospital Patient Monitoring System ================\n");
		printf("Total Patients Monitered : %d\n",n);
		printf(" \n");
		printf("Patient Name /t Heart Rate /t Oxygen Level /t Status\n");

		for(int i=0; i<n; i++){
			printf("%s /t %d /t %d /t %s \n",person3[i].name, person3[i].heart_rate, person3[i].oxygen_level, person3[i].status);
		}
		
		printf(" \n");
		printf("Total Patients in Critical Condition: %",critical2);

		exit(0);

		}
		
        close(pipeBC[0]);
		write(pipeBC[1],person2,sizeof(person2));
		write(pipeBC[1],critical1,sizeof(critical1));
		close(pipeBC[1]); 

		wait(NULL);
		exit(0);

	}
    
	close(pipeAB[0]);
	write(pipeAB[1],person1,sizeof(person1));
    close(pipeAB[1]);

		wait(NULL);
        exit(0);

	return 0;
}

/*
Enter number of patients: 5

Patient 1:
Enter name: John
Enter heart rate: 85
Enter oxygen level: 98

Patient 2:
Enter name: Jane
Enter heart rate: 45
Enter oxygen level: 88

... (etc)

======== Hospital Patient Monitoring System =========

Total Patients Monitored: 5

| Patient Name | Heart Rate | Oxygen Level | Status |
|--------------|------------|--------------|--------|
| John         | 85         | 98           | STABLE |
| Jane         | 45         | 88           | CRITICAL |
| Alex         | 97         | 90           | ALERT  |
| Emily        | 76         | 85           | CRITICAL |
| Chris        | 65         | 91           | ALERT  |

Total Patients in Critical Condition: 2
*/



//------------- 2024 year (2022 exam) - q2 ------------

#include <stdio.h>

int main() {
    printf("Armstrong numbers from 100 to 999:\n");
    
    for(int i = 100; i <= 999; i++) {
        int sum = 0;
        int digit = 0;
        int num = i;
        int original = i;  
        
        while(num != 0) {
            digit = num % 10;
            sum = sum + (digit * digit * digit);
            num = num / 10;
        }
        
        if(sum == original) {
            printf("%d is an Armstrong Number\n", original);
        }
    }
    
    return 0;
}

/*
Armstrong numbers from 100 to 999:
153 is an Armstrong Number
370 is an Armstrong Number
371 is an Armstrong Number
407 is an Armstrong Number
*/


//----------------- 2024 year (2022 exam) q3 -------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

int main()
{
    int pipe1[2], pipe2[2], pipe3[2];

    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);

    float temp1, temp2, temp3;
    char scale1, scale2, scale3;

    printf("Enter first temperature (e.g., 100 C): ");
    scanf("%f %c", &temp1, &scale1);

    printf("Enter second temperature (e.g., 97 F): ");
    scanf("%f %c", &temp2, &scale2);

    printf("Enter third temperature (e.g., 400 K): ");
    scanf("%f %c", &temp3, &scale3);

    scale1 = toupper(scale1);
    scale2 = toupper(scale2);
    scale3 = toupper(scale3);

    if (fork() == 0)
    {
        float temp;
        char scale;

        close(pipe1[1]);

        read(pipe1[0], &temp, sizeof(temp));
        read(pipe1[0], &scale, sizeof(scale));

        close(pipe1[0]);

        float result = (temp * 9 / 5) + 32;

        printf("\n------ Child 1 ------\n");
        printf("PID = %d, PPID = %d\n", getpid(), getppid());
        printf("Received Temperature : %.2f%c\n", temp, scale);
        printf("Converted Temperature : %.2fF\n", result);

        exit(0);
    }

    else if (fork() == 0)
    {
        float temp;
        char scale;

        close(pipe2[1]);

        read(pipe2[0], &temp, sizeof(temp));
        read(pipe2[0], &scale, sizeof(scale));

        close(pipe2[0]);

        float result = (temp - 32) * 5 / 9;

        printf("\n------ Child 2 ------\n");
        printf("PID = %d, PPID = %d\n", getpid(), getppid());
        printf("Received Temperature : %.2f%c\n", temp, scale);
        printf("Converted Temperature : %.2fC\n", result);

        exit(0);
    }

    else if (fork() == 0)
    {
        float temp;
        char scale;

        close(pipe3[1]);

        read(pipe3[0], &temp, sizeof(temp));
        read(pipe3[0], &scale, sizeof(scale));

        close(pipe3[0]);

        float result = temp - 273.15;

        printf("\n------ Child 3 ------\n");
        printf("PID = %d, PPID = %d\n", getpid(), getppid());
        printf("Received Temperature : %.2f%c\n", temp, scale);
        printf("Converted Temperature : %.2fC\n", result);

        exit(0);
    }

    close(pipe1[0]);
    write(pipe1[1], &temp1, sizeof(temp1));
    write(pipe1[1], &scale1, sizeof(scale1));
    close(pipe1[1]);

    close(pipe2[0]);
    write(pipe2[1], &temp2, sizeof(temp2));
    write(pipe2[1], &scale2, sizeof(scale2));
    close(pipe2[1]);

    close(pipe3[0]);
    write(pipe3[1], &temp3, sizeof(temp3));
    write(pipe3[1], &scale3, sizeof(scale3));
    close(pipe3[1]);

    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("\n------ Parent Process Finished ------\n");

    return 0;
}

//-------------- 2023 year (2021 exam) q2 --------------- 
// ask to do using threads, but did with fork()  function
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int a, b;
    
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    
    printf("\nMain Thread - PID: %d\n", getpid());
    printf("Creating 4 threads...\n\n");
    
    // Thread 1 - Addition
    if (fork() == 0) {
        printf("Thread 1 (Addition) - PID: %d, PPID: %d, Result: %d\n", 
               getpid(), getppid(), a + b);
        exit(0);
    }
    
    // Thread 2 - Subtraction
    if (fork() == 0) {
        printf("Thread 2 (Subtraction) - PID: %d, PPID: %d, Result: %d\n", 
               getpid(), getppid(), a - b);
        exit(0);
    }
    
    // Thread 3 - Multiplication
    if (fork() == 0) {
        printf("Thread 3 (Multiplication) - PID: %d, PPID: %d, Result: %d\n", 
               getpid(), getppid(), a * b);
        exit(0);
    }
    
    // Thread 4 - Division
    if (fork() == 0) {
        if (b != 0) {
            printf("Thread 4 (Division) - PID: %d, PPID: %d, Result: %.2f\n", 
                   getpid(), getppid(), (float)a / b);
        } else {
            printf("Thread 4 (Division) - PID: %d, PPID: %d, Error: Divide by zero!\n", 
                   getpid(), getppid());
        }
        exit(0);
    }
    
    
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    
    printf("\n========== All Threads Completed ==========\n");
    printf("Main Thread (PID: %d) exiting...\n", getpid());
    
    return 0;
}


//--------------- 2023 year (2021 exam) q3 ------------
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pipeAB[2];
    int pipeBC[2];
    int pipeCA[2];
    
    pipe(pipeAB);
    pipe(pipeBC);
    pipe(pipeCA);
    
    printf("Parent Process || PID: %d || PPID: %d\n", getpid(), getppid());
    
    int n;
    printf("Enter the number of integers: ");
    scanf("%d", &n);
    
    int numbers1[n];
    printf("Enter %d numbers: \n", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &numbers1[i]);
    }
    
    close(pipeAB[0]);
    write(pipeAB[1], numbers1, sizeof(numbers1));
    close(pipeAB[1]);
    
    if(fork() == 0) {
        printf("Child Process || PID: %d || PPID: %d\n", getpid(), getppid());
        
        int numbers2[n];
        
        close(pipeAB[1]);
        read(pipeAB[0], numbers2, sizeof(numbers2));
        close(pipeAB[0]);
        
        int sum1 = 0;
        for(int i = 0; i < n; i++) {
            sum1 = sum1 + numbers2[i];
        }
        printf("Child Process: Sum = %d\n", sum1);
        
        if(fork() == 0) {
            printf("Grandchild Process || PID: %d || PPID: %d\n", getpid(), getppid());
            
            int sum2 = 0;
            
            close(pipeBC[1]);
            read(pipeBC[0], &sum2, sizeof(sum2));
            close(pipeBC[0]);
            
            float avg2 = (float)sum2 / n;
            printf("Grandchild Process: Sum = %d, Average = %.2f\n", sum2, avg2);
            
            close(pipeCA[0]);
            write(pipeCA[1], &sum2, sizeof(sum2));
            write(pipeCA[1], &avg2, sizeof(avg2));
            close(pipeCA[1]);
            
            exit(0);
        }
        
        close(pipeBC[0]);
        write(pipeBC[1], &sum1, sizeof(sum1));
        close(pipeBC[1]);
        
        wait(NULL);
        exit(0);
    }
    
    close(pipeCA[1]);
    int sum3 = 0;
    float avg3 = 0.0;
    
    read(pipeCA[0], &sum3, sizeof(sum3));
    read(pipeCA[0], &avg3, sizeof(avg3));
    close(pipeCA[0]);
    
    wait(NULL);
    
    printf("\n========== Final Results ==========\n");
    printf("Sum of %d integers: %d\n", n, sum3);
    printf("Average value: %.2f\n", avg3);
    printf("====================================\n");
    
    return 0;
}


//---------- 2022 year (2020 exam) q2 ------------

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    printf("------ process A ------\n");

    int pipeAB[2], pipeAC[2];
    int pipeBD[2], pipeBE[2];
    int pipeCF[2], pipeCG[2];

    pipe(pipeAB);
    pipe(pipeAC);
    pipe(pipeBD);
    pipe(pipeBE);
    pipe(pipeCF);
    pipe(pipeCG);

    int numbersA[100];
    int n;

    printf("starting value n: ");
    scanf("%d", &n);

    for(int i = 0; i < 100; i++) {
        numbersA[i] = n + i;
    }

    // Create Process B
    if(fork() == 0) {
        printf("------ process B ------\n");

        int numbersB[100];

        close(pipeAB[1]);
        read(pipeAB[0], numbersB, sizeof(numbersB));
        close(pipeAB[0]);

        int evenB[100];
        int eveni = 0;

        printf("Even numbers in array: ");
        for(int i = 0; i < 100; i++) {
            if(numbersB[i] % 2 == 0) {
                evenB[eveni] = numbersB[i];
                printf("%d ", evenB[eveni]);
                eveni++;
            }
        }
        printf("\n");

        // Create Process D
        if(fork() == 0) {
            printf("------ process D ------\n");

            int evenD[100];

            close(pipeBD[1]);
            read(pipeBD[0], evenD, sizeof(evenD));
            close(pipeBD[0]);

            int sumE = 0;
            for(int i = 0; i < eveni; i++) {
                sumE = sumE + evenD[i];
            }

            printf("Sum of even numbers: %d\n", sumE);
            exit(0);
        }
        // Create Process E
        else if(fork() == 0) {
            printf("------ process E ------\n");

            int evenE[100];

            close(pipeBE[1]);
            read(pipeBE[0], evenE, sizeof(evenE));
            close(pipeBE[0]);

            int max = evenE[0];
            for(int i = 0; i < eveni; i++) {
                if(max < evenE[i]) {
                    max = evenE[i];
                }
            }

            printf("Maximum of even numbers: %d\n", max);
            exit(0);
        }

        // Send even numbers to processes D and E
        close(pipeBD[0]);
        write(pipeBD[1], evenB, sizeof(evenB));
        close(pipeBD[1]);

        close(pipeBE[0]);
        write(pipeBE[1], evenB, sizeof(evenB));
        close(pipeBE[1]);

        wait(NULL);
        wait(NULL);
        exit(0);
    }
    // Create Process C
    else if(fork() == 0) {
        printf("------ process C ------\n");

        int numbersC[100];

        close(pipeAC[1]);
        read(pipeAC[0], numbersC, sizeof(numbersC));
        close(pipeAC[0]);

        int oddC[100];
        int oddi = 0;

        printf("Odd numbers in array: ");
        for(int i = 0; i < 100; i++) {
            if(numbersC[i] % 2 != 0) {
                oddC[oddi] = numbersC[i];
                printf("%d ", oddC[oddi]);
                oddi++;
            }
        }
        printf("\n");

        // Create Process F
        if(fork() == 0) {
            printf("------ process F ------\n");

            int oddF[100];

            close(pipeCF[1]);
            read(pipeCF[0], oddF, sizeof(oddF));
            close(pipeCF[0]);

            int sumO = 0;
            for(int i = 0; i < oddi; i++) {
                sumO = sumO + oddF[i];
            }

            printf("Sum of odd numbers: %d\n", sumO);
            exit(0);
        }
        // Create Process G
        else if(fork() == 0) {
            printf("------ process G ------\n");

            int oddG[100];

            close(pipeCG[1]);
            read(pipeCG[0], oddG, sizeof(oddG));
            close(pipeCG[0]);

            int min = oddG[0];
            for(int i = 0; i < oddi; i++) {
                if(min > oddG[i]) {
                    min = oddG[i];
                }
            }

            printf("Minimum of odd numbers: %d\n", min);
            exit(0);
        }

        // Send odd numbers to processes F and G
        close(pipeCF[0]);
        write(pipeCF[1], oddC, sizeof(oddC));
        close(pipeCF[1]);

        close(pipeCG[0]);
        write(pipeCG[1], oddC, sizeof(oddC));
        close(pipeCG[1]);

        wait(NULL);
        wait(NULL);
        exit(0);
    }

    // Parent Process A sends array to B and C
    close(pipeAB[0]);
    write(pipeAB[1], numbersA, sizeof(numbersA));
    close(pipeAB[1]);

    close(pipeAC[0]);
    write(pipeAC[1], numbersA, sizeof(numbersA));
    close(pipeAC[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}


//------------ 2022 year (2020 exam) q3 --------------

// ask to do using threads, but did with fork()  function

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num1, num2;
    int max_num, min_num;
    
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);
    
    if(num1 > num2) {
        max_num = num1;
        min_num = num2;
    } else {
        max_num = num2;
        min_num = num1;
    }
    
    printf("Maximum number: %d\n", max_num);
    printf("Minimum number: %d\n", min_num);
    
    if(fork() == 0) {
        int num = max_num;
        char binary[100];
        int index = 0;
        
        printf("Binary thread of %d: ", max_num);
        if(num == 0) {
            printf("0");
        } else {
            while(num > 0) {
                binary[index] = (num % 2) + '0';
                num = num / 2;
                index++;
            }
            for(int i = index - 1; i >= 0; i--) {
                printf("%c", binary[i]);
            }
        }
        printf("\n");
        exit(0);
    }
    
    if(fork() == 0) {
        int num = max_num;
        char octal[100];
        int index = 0;
        
        printf("Octal thread of %d: ", max_num);
        if(num == 0) {
            printf("0");
        } else {
            while(num > 0) {
                octal[index] = (num % 8) + '0';
                num = num / 8;
                index++;
            }
            for(int i = index - 1; i >= 0; i--) {
                printf("%c", octal[i]);
            }
        }
        printf("\n");
        exit(0);
    }
    
    wait(NULL);
    wait(NULL);
    
    return 0;
}



//--------- 2022/2021 year (2019 exam ) q2 ----------------
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){

		printf("------ process A ------");

        int pipeAB[2];
		int pipeAC[2];
		int pipeBD[2];
		int pipeBE[2];
		int pipeCF[2];
		int pipeCG[2];

        pipe(pipeAB);
		pipe(pipeAC);
        pipe(pipeBD);
		pipe(pipeBE);
		pipe(pipeCF);
		pipe(pipeCG);

		int numbersA[100];
		int n;

        printf("starting value n :");
        scanf("%d",&n);

		for(int i=0; i<100;i++){
			numbersA[i]=n+i;
		}

		if(fork()==0){
			printf("------ process B ------");

            int numbersB[100];

            close(pipeAB[1]);
            read(pipeAB[0],numbersB,sizeof(numbersB));
            close(pipeAB[0]);

            int evenB[100];
            int eveni=0;

            for(int i=0;i<100;i++){
				if(numbersB[i] % 2 == 0){
					evenB[eveni] = numbersB[i];
                    eveni++;
                }
			}

				if(fork()==0){
					printf("------ process D ------");

					int evenD[100];

					close(pipeBD[1]);
					read(pipeBD[0],evenD,sizeof(evenD));
					close(pipeBD[0]);

                    int sumE=0;
                    for(int i=0; i<eveni;i++){
						sumE = sumE+evenD[i];
					}

                    printf("sum of even numbers: %d",sumE);

					exit(0);

				}
				else if(fork()==0){
					printf("------ process E ------");

					int evenE[100];

					close(pipeBE[1]);
					read(pipeBE[0],evenE,sizeof(evenE));
					close(pipeBE[0]);

					int max=evenE[0];
                    for(int i=0; i<eveni;i++){
						if(max < evenE[i]){
                           max = evenE[i];
						}
					}

					printf("max of even numbers: %d",max);

					exit(0);
				}

		close(pipeBD[0]);
        write(pipeBD[1],evenB,sizeof(evenB));
        close(pipeBD[1]);

		close(pipeBE[0]);
        write(pipeBE[1],evenB,sizeof(evenB));
        close(pipeBE[1]);

		wait(NULL);
        wait(NULL);

        exit(0);

		}
        else if(fork()==0){
			printf("------ process C ------");
			int numbersC[100];

			close(pipeAC[1]);
            read(pipeAC[0],numbersC,sizeof(numbersC));
            close(pipeAC[0]);

			int oddC[100];
            int oddi=0;

            for(int i=0;i<100;i++){
				if(numbersC[i] % 2 != 0){
					oddC[oddi] = numbersC[i];
					oddi++;
                }
			}

			if(fork()==0){
				printf("------ process F ------");

				int oddF[100];

				close(pipeCF[1]);
				read(pipeCF[0],oddF,sizeof(oddF));
				close(pipeCF[0]);

				 int sumO=0;
                    for(int i=0; i<oddi;i++){
						sumO = sumO+oddF[i];
					}

                    printf("sum of odd numbers: %d",sumO);

					exit(0);

			}
            else if(fork()==0){
				printf("------ process G ------");

				int oddG[100];

				close(pipeCG[1]);
				read(pipeCG[0],oddG,sizeof(oddG));
				close(pipeCG[0]);

				int min=oddG[0];
                    for(int i=0; i<oddi;i++){
						if(min > oddG[i]){
                           min = oddG[i];
						}
					}

					printf("min of odd numbers: %d",min);

					exit(0);

			}

		close(pipeCF[0]);
        write(pipeCF[1],oddC,sizeof(oddC));
        close(pipeCF[1]);

		close(pipeCG[0]);
        write(pipeCG[1],oddC,sizeof(oddC));
        close(pipeCG[1]);

        wait(NULL);
        wait(NULL);

        exit(0);
		}

		close(pipeAB[0]);
        write(pipeAB[1],numbersA,sizeof(numbersA));
        close(pipeAB[1]);

		close(pipeAC[0]);
        write(pipeAC[1],numbersA,sizeof(numbersA));
        close(pipeAC[1]);

	wait(NULL);
    wait(NULL);

	return 0;
}

/*
------ process A ------
starting value n :5
------ process B ------
------ process C ------
------ process D ------
sum of even numbers: 2700
------ process E ------
max of even numbers: 104
------ process F ------
sum of odd numbers: 2650
------ process G ------
min of odd numbers: 5
*/



//------------- 2020 year (2018 exam) q2 --------------


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int counter = 0;
    
    printf("Process A (PID: %d, PPID: %d) - counter: %d\n", getpid(), getppid(), counter);
    
    if(fork() == 0) {
        counter = counter + 5;
        printf("Process B (PID: %d, PPID: %d) - counter: %d\n", getpid(), getppid(), counter);
        
        if(fork() == 0) {
            counter = counter + 10;
            printf("Process G (PID: %d, PPID: %d) - counter: %d\n", getpid(), getppid(), counter);
            exit(0);
        }
        else if(fork() == 0) {
            counter = counter + 10;
            printf("Process D (PID: %d, PPID: %d) - counter: %d\n", getpid(), getppid(), counter);
            exit(0);
        }
        
        wait(NULL);
        wait(NULL);
        exit(0);
    }
    else if(fork() == 0) {
        counter = counter + 5;
        printf("Process C (PID: %d, PPID: %d) - counter: %d\n", getpid(), getppid(), counter);
        
        if(fork() == 0) {
            counter = counter + 10;
            printf("Process E (PID: %d, PPID: %d) - counter: %d\n", getpid(), getppid(), counter);
            exit(0);
        }
        else if(fork() == 0) {
            counter = counter + 20;
            printf("Process F (PID: %d, PPID: %d) - counter: %d\n", getpid(), getppid(), counter);
            exit(0);
        }
        
        wait(NULL);
        wait(NULL);
        exit(0);
    }
    
    wait(NULL);
    wait(NULL);
    
    return 0;
}



//================== practice question ==============================


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

struct Student{
	int id;
    char name[100];
	int assignment_mark;
	int exam_mark;
	float final_mark;
	char grade;
};

int main(){

	int pipeAB[2];
	int pipeBC[2];

	pipe(pipeAB);
	pipe(pipeBC);

	int n;

    printf("enter number of students");
	scanf("%d",&n);

    struct Student std1[n];

	for(int i=0; i<n; i++){
		printf("enter id :");
		scanf("%d",&std1[i].id);
		printf("enter name :");
		scanf("%s",std1[i].name);
		printf("enter assignment mark:");
		scanf("%d",&std1[i].assignment_mark);
		printf("enter exam mark; :");
		scanf("%d",&std1[i].exam_mark);
	}

	if(fork()==0){
		struct Student std2[n];

		close(pipeAB[1]);
		read(pipeAB[0],std2,sizeof(std2));
		close(pipeAB[0]);

		int failed=0;
		float highest=0;
		float sum=0;

		for(int i=0; i<n; i++){
			std2[i].final_mark = (float) ((std2[i].assignment_mark * 0.3)+(std2[i].exam_mark*0.7));
			
			if(std2[i].final_mark > highest){
				highest = std2[i].final_mark;
			}

			sum = sum + std2[i].final_mark;

			if(std2[i].final_mark >=75){
				std2[i].grade = 'A';
			}
			else if(std2[i].final_mark >=65){
				std2[i].grade = 'B';
			}
			else if(std2[i].final_mark >= 55){
				std2[i].grade = 'C';
			}
			else if(std2[i].final_mark >= 45){
				std2[i].grade = 'S';
			}
            else{
				std2[i].grade = 'F';
				failed++;
			}
	
		}
        float avg= sum/n;
		
		if(fork()==0){

			struct Student std3[n];

			int failed2;
			float highest2;
			float avg2;

			close(pipeBC[1]);
			read(pipeBC[0],std3,sizeof(std3));
			read(pipeBC[0],&failed2,sizeof(failed2));
			read(pipeBC[0],&highest2,sizeof(highest2));
			read(pipeBC[0],&avg2,sizeof(avg2));
			close(pipeBC[0]);

			printf("========== STUDENT PERFORMANCE REPORT ==========\n");
			printf("ID  \t    Name   \t   Final Mark  \t    Grade \n");
			
			for(int i=0; i<n; i++){
				printf("%d \t %s \t %f \t %c \n",std3[i].id, std3[i].name, std3[i].final_mark, std3[i].grade);
			}

			printf("Total Students : %d \n",n);
			printf("Failed Students : %d \n", failed2);
			printf("Highest Final Mark : %f \n",highest2);
			printf("Average Final Mark : %f \n",avg2);

			exit(0);
		}

		close(pipeBC[0]);
		write(pipeBC[1],std2,sizeof(std2));
		write(pipeBC[1],&failed,sizeof(failed));
		write(pipeBC[1],&highest,sizeof(highest));
		write(pipeBC[1],&avg,sizeof(avg));
		close(pipeBC[1]);

		wait(NULL);
		exit(0);
	}

	close(pipeAB[0]);
	write(pipeAB[1],std1,sizeof(std1));
	close(pipeAB[1]);



	wait(NULL);
	exit(0);

	return 0;

}















vi q2.sh
insert
esc+:wq
bash.sh

vi q3.c
gcc q3.c -o q3
./q3












