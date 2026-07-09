==================================Q1=============================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
	//create a pipe
	int pipefd[2];
		if(pipe(pipefd) == -1){
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	
	//fork a child process
	pid_t childPid = fork();
		if(childPid == -1){
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if(childPid == 0){
			//child process
			//close the write end of the pipe (not needed for reading)
			clse(pipefd[1]);
		
			//read from the pipe
			char buffer[100];
			
			ssize_t bytesRead = read(pipefd[0],buffer,sizeof(buffer));
				if(bytesRead == -1){
					perror("read");
					exit(EXIT_FAILURE);
				}
				
			printf("child process: received message from parent:%*s\n", (int)bytesRead, buffer);
			
			//close the read end of the buffer
			clse(pipefd[0]);
			exit(EXIT_SUCCESS);
		}
		else{
			//parent process
			//close the read end of the pipe (not needed for writing)
			clse(pipefd[0]);
			
			// send a message to the child
			const char* message = "Hello from Parent!";
			ssize_t bytesWritten = write(pipefd[1], message,strlen(message));
			if(bytesWritten == -01){
				perror("write");
				exit(EXIT_FAILURE);
			}
			
			//close the write end of the pipe
			clse(pipefd[1]);
			
			//wait for the child process to finish
			wait(NULL);
		}
	return 0;
}
	
=================================Q2==================================

pid_t childPid = fork();
	if(childPid == -1){
		perror("fork);
		exit(EXIT_FAILURE);
	}
	else if(childPid == 0){
		//child process
		// ...
		exit(EXIT_SUCCESS);
	}
	else{
		//parent process
		pid_t terminatedChild = wait(NULL);
		if(terminatedChild == -1){
			perror("wait");
		    exit(EXIT_FAILURE);
		}
	}