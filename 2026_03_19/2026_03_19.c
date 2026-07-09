=============================Q1================================
#include <stdio.h>
#include <unistd.h>

int main(){
	//factorial--------------------------
	int child1, child2;
	int n,i,j,k;
	printf("enter a num:");
	scanf("%d",&n );
	child1=fork();
	if(child1==0){
		int fact=1;
			for(i=1;i<=n;i++){
				fact=fact*1;
			}
	
	    prinf("the factorial of %d is %d\n",n,fact);

    //fibonacci-----------------------	
		int child5=fork();
		if(child5==0){
			int a=0. b=1, c=0;
			for(j=1;j<=n;j++){
				a=b+c;
				b=c;
				c=a;
			}
	    }
	    prinf("the fibonacci is %d\n",a);
	
	}
	
	// 2 to the power----------------------
	else{
		child2=fork();
		if(child2==0){
			int s=1;
			if(n==0){
				s=1;
			}
			else{
				for(k=0; k<n; k++){
					s*=2;
				}
			}
			prinf("2 to the power is %d\n",s);
		}
	}
	
	//square------------------------
	int child3=fork();
	if(child3==0){
		int r= n*n;
		prinf("square of %d is %d\n",n,r);
	}
	
}

===========================Q2==================================

	#include <stdio.h>
	#include <unistd.h>

	int main(){
		int n;
		printf("Enter a number:");
		scanf("%d",&n);
		int c=fork();
		if(c==0){
			prinf("%d * 2 = %d\n",n,n*2);
		}
		else{
			prinf("%d / 2 = %d\n",n,n/2);
		}
		return 0;
	}

_______________________
	Enter a number:22
	22 / 2 = 11
	22 * 2 = 44
	
===========================Q3==================================

	#include <stdio.h>
	#include <unistd.h>

	int main(){
		int i=0;
		pid_t childpid=fork();
		if(childpid==-1){
			printf("faild to fork");
			return -1;
		}
		else if(childpid==0){
			for(i=0;i<5;i++){
				printf("child\n");
			}
		}
		else{
			for(i=0;i<5;i++){
				printf("parent\n");
			}
		}
		return 0;
	}
	
_______________________

	parent
	parent
	parent
	parent
	parent
	child
	child
	child
	child
	child

=========================Q4==========================

#include <stdio.h>
#include <unistd.h>
int main(){
		int a,b;
		printf("Enter  number1:");
		scanf("%d",&a);
		printf("Enter  number2:");
		scanf("%d",&b);
		
		int c=fork();
		if(c==0){
			printf("%d + %d = %d\n",a,b,a+b);
		}
		else{
			int d=fork();
		    if(d==0){
			      printf("%d - %d = %d\n",a,b,a-b);
		    }
			else{
				int e=fork();
		        if(e==0){
			         printf("%d * %d = %d\n",a,b,a*b);
		        }
				else{
					int f=fork();
		            if(f==0){
			            printf("%d / %d = %d\n",a,b,a/b);
		            }
				}
			}
		}
		return 0;
	}
	
==========================Q5=============================

#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 128
#define MSGKEY 1111
int main(){
	int msgpid;
	

	struct person{ //create structure
		int age;
		char name[100]; //declare as array in char data type
		char regno[100]; // same as above
	};
	
		/*   
    This defines a structure called person with:

    age → integer
    name → string
    regno → string
    */
	
	struct person p1,p2; // p1 for centre, p2 for reciever
	int f;
	
	/*
	fork() creates a child process
    After this:
       f == 0 → child process (receiver)
       f > 0 → parent process (sender)
	*/
	
	f=fork();
	if(f==0){
		int msgpid;
		msgpid = msgget (MSGKEY, IPC_CREAT|0666); //Creates or accesses a message queue
		msgrcv(msgpid,&p2,1024,0,0); //Receives message into p2
		printf("Recieved name:%s\n",p2.name); //Prints received data
		printf("Recieved regno:%s\n",p2.regno); //Prints received data
		printf("Recieved age:%d\n",p2.age); //Prints received data
		msgctl(msgpid,IPC_RMID,0); //Deletes the message queue after use
	}
	else{
		msgpid = msgget (MSGKEY, IPC_CREAT|0666); //Gets message queue
		printf("Enter the name: ");
		scanf("%s",&p1.name); //Takes user input
		printf("Enter the regno: ");
		scanf("%s",&p1.regno); //Takes user input
		printf("Enter the age: ");
		scanf("%d",&p1.age); //Takes user input
		
		int buflen=sizeof(p1)+1;
		
		if(msgsnd(msgpid,&p1,buflen,IPC_NOWAIT)<0){ //Sends data
			printf("Message not send\n");
		}
		else{
			printf("Message send\n");
			exit(0);
		}
	}
}