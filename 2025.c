#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

struct patient{
	char name[100];
    int heart_rate;
    int oxygen level;
	char status[100];
    
};

int main(){

	int pipeAB[2];
    pipe(pipeAB);

    int n;

    printf("Enter number of persons: ");
    scanf("%d",&n);

    struct patient patients1[n];

    for(int i=0;i<n;i++){
		printf("\nEnter name: ");
        scanf("%s", patients1[i].name);

		printf("\nEnter heart rate: ");
        scanf("%s", patients1[i].heart_rate);

		printf("\nEnter oxygen level: ");
        scanf("%s", patients1[i].oxygen_level);
	}
		if(fork()==0){
            struct patient patients2[n];

        close(pipeAB[1];
        read(pipeAB[0],patients2,sizeof(patients2));
        close(pipeAB[0]);

        int count=0;

		for(int i=0;i<n;i++){
			if((heart_rate<60 || heart_rate >100) || (oxygen_level <90)){
				strcpy(patients2[i].status, "CRITICAL");
				count++;
			}
			else if(((heart_rate >60 && heart_rate<65) || (heart_rate>95 && heart_rate <100)) && (oxygen_level >90 && oxygen_level <92) ){
				strcpy(patients2[i].status, "ALERT");
			}
			else if((heart_rate >60 && heart_rate<100) && (oxygen_level <90)){
				strcpy(patients2[i].status, "STABLE");
			}
        }    
            printf("\n--- Hospital Patient Monitoring System ---\n");
			printf("\nTotal Patient Monitered : %d\n",n);
			printf("\tPatient Name\t\tHeart Rate\t\tOxygen levelStatus\t\n");

        for(int i=0; i<n; i++){
			printf("\t%s\t\t%d\t\t%d\t\t%s",
                   patients2[i].name,
                   patients2[i].heart_rate,
                   patients2[i].Oxygen_level,
                   patients2[i].status);
        }
			printf("Total Patients In CRITICAL Condition : %d", count),
			exit(0);
		}
      
        close(pipeAB[0];
        write(pipeAB[1],patients1,sizeof(patients1));
        close(pipeAB[1]);

		wait(NULL);
        return 0;
  }


//=============================================================================

Enter number of persons: 4

Enter name: Amal
Enter heart rate: 75
Enter oxygen level: 98

Enter name: Nimal
Enter heart rate: 55
Enter oxygen level: 88

Enter name: Sunil
Enter heart rate: 97
Enter oxygen level: 91

Enter name: Kamal
Enter heart rate: 110
Enter oxygen level: 85

--- Hospital Patient Monitoring System ---

Total Patients Monitored : 4

Patient Name   Heart Rate   Oxygen Level   Status
Amal           75           98             STABLE
Nimal          55           88             CRITICAL
Sunil          97           91             ALERT
Kamal          110          85             CRITICAL

Total Patients In CRITICAL Condition : 2