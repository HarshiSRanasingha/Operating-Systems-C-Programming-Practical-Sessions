#include <stdio.h>
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

//===============================================

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