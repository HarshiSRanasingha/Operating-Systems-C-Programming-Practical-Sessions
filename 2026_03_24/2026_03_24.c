============================Q1============================
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

############################

Enter the name: harshi
Enter the regno: 2022ict78
Enter the age: 25
Message send

============================Q2============================

#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
int main(){
	int msqid;
	key_t key=15;
	
	msqid = msgget (key, IPC_CREAT|0664);
	if(msqid<0){
		printf("msgget failed.");
	}
	else{
		printf("\nMessage queue created successfully with key %d \n",msqid);
	}
}


============================Q3============================

#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MSGKEY 1111
int main(){
	int msqid;
	char mtext[1000];
	msqid = msgget (MSGKEY, IPC_CREAT|0666);
	
	msgrcv(msqid,&mtext,1024,0,0);
	printf("Recieved String: %s\n",mtext); 
	msgctl(msqid,IPC_RMID,0); 
	return 0;
}


============================Q4============================

#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXSIZE 128
#define MSGKEY 1111
int main(){
	int msgqid;
	
	struct person{
		int age;
		char name[100]; 
		char regno[100]; 
	};
	
	struct person p1;
	p1.age=25;
	msgqid = msgget (MSGKEY, IPC_CREAT|0666);
		printf("Enter the name: ");
		scanf("%s",&p1.name); 
		printf("Enter the regno: ");
		scanf("%s",&p1.regno);
		printf("Enter the age: ");
		scanf("%d",&p1.age); 
	
	int buflen=sizeof(p1)+1;
	
	if(msgsnd(msgqid,&p1,buflen,IPC_NOWAIT)<0){
			printf("Message not send\n");
		}
	else{
			printf("Message sent\n");
	        exit(0);
	}

    struct person p2;
    int msgqid;
	msgqid = msgget (MSGKEY, IPC_CREAT|0666); 
	msgrcv(msgqid,&p2,1024,0,0); 
		printf("Recieved String:%s\n",p2.name); 
		printf("Recieved String:%s\n",p2.regno); 
		printf("Recieved String:%d\n",p2.age);
		msgctl(msgqid,IPC_RMID,0);	
}

######################

Enter the name: harshi
Enter the regno: 2022ict78
Enter the age: 25
Message sent


============================Q5============================
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXSIZE 128
#define MSGKEY 1111
int main(){
	
	
	struct person{
		int age;
		char name[100]; 
		char regno[100]; 
	};
	
    struct person p2;
    int msgqid;
	msgqid = msgget(MSGKEY, IPC_CREAT|0666); 
	msgrcv(msgqid,&p2,1024,0,0); 
		printf("Recieved String:%s\n",p2.name); 
		printf("Recieved String:%s\n",p2.regno); 
		printf("Recieved String:%d\n",p2.age);
		msgctl(msgqid,IPC_RMID,0);	
		/*
		int buflen=sizeof(p2)+1;
	
	if(msgsnd(msgqid,&p2,buflen,IPC_NOWAIT)<0){
			printf("Message not send\n");
		}
	else{
			printf("Message sent\n");
	        exit(0);
	} */
	return 0;
}

######################

Recieved String:sam
Recieved String:12345
Recieved String:-1224724430
Message sent


===============================Q5============================
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXSIZE 128
#define MSGKEY 1111
int main(){
	
	
	struct person{
		int age;
		char name[100]; 
		char regno[100]; 
		char grade[100];
	};
	
	struct person p2;
    int msgqid;
	msgqid = msgget(MSGKEY, IPC_CREAT|0666); 
	msgrcv(msgqid,&p2,1024,0,0); 
		printf("Recieved String:%s\n",p2.name); 
		printf("Recieved String:%s\n",p2.regno); 
		printf("Recieved String:%d\n",p2.age);
		printf("Recieved String:%s\n",p2.grade);
		msgctl(msgqid,IPC_RMID,0);
		int buflen=sizeof(p2)+1;
	
	    if(msgsnd(msgqid,&p2,buflen,IPC_NOWAIT)<0){
			printf("Message not send\n");
		    }
	    else{
			printf("Message sent\n");
	        exit(0);
	        }
		return 0;
}
