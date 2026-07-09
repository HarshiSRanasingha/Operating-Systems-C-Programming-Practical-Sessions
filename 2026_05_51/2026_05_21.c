#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	
	pipeAB[2];
	pipeBC[2];
	pipeAC[2];
	
	pipe(pipeAB);
	pipe(pipeBC);
	pipe(pipeAC);
	
	char name[100];
	int heart_rate;
	int oxygen_level;
	char status[100];
	
	printf(" Enter patient details:");
		printf(" Enter patient name:");
		scanf("%s",&name);
		printf(" Enter patient heart rate:");
		scanf("%d",&heart_rate);
		printf(" Enter oxygen level:");
		scanf("%d",&oxygen_level);	
	
	    if(fork() == 0){
	
		// Decision Unit (Read and Analyze)
		
		    close(pipeAB[1]);
			read(pipeAB[0],&heart_rate,sizeof(heart_rate);
			read(pipeAB[0],&oxygen_level,sizeof(oxygen_level);
			close(pipeAB[0]);
			
			if((heart_rate < 60 || heart_rate > 100) || (oxygen_level < 90) ){
					status = CRITICAL;
			}
			else if((60 < heart_rate <65 || 95 < heart_rate < 100) && (90 < oxygen_level < 92){
					status= ALERT;
			}
			else if((60 < heart_rate < 100) && (oxygen_level > 92)){
					status = STABLE;
			}
		}
		
		
		if(fork() == 0 ){
			
			close(pipeAB[1]);
			read(pipeAB[0],&name,sizeof(name);
			read(pipeAB[0],&heart_rate,sizeof(heart_rate);
			read(pipeAB[0],&oxygen_level,sizeof(oxygen_level);
			read(pipebB[0],&status,sizeof(status);
			close(pipeAB[0]);
			
			// Monitoring data ( write data)
			
			printf("=========== Hospital Patient Monitoring System ==========");
			printf("Total Patient Monitored :");
			scanf("%d", &n);
			
			printf("Patient name \t Heart Rate \t Oxygen Level \t Status");
			for( int i=0; i<n; i++){
				
				printf("%s \t %d \t %d \t %s", &name2, &heart_rate2, &oxygen_level2, &status2);
			}
			
			
			
		}

	
	
}


//=============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

struct Patient
{
        char name[100];
        int heartrate;
        int oxygenlevel;
        char status[25];
};

int main()
{

        int pipeAB[2];
        pipe(pipeAB);

        int pcount;
        printf("enter number of patients : ");
        scanf("%d", &pcount);

        if (fork() == 0)
        {
                struct Patient patients[pcount];
                close(pipeAB[1]);
                read(pipeAB[0], patients, sizeof(patients));
                close(pipeAB[0]);

                for (int i=0; i<pcount; i++)
                {
                        if (patients[i].heartrate < 60 || patients[i].heartrate > 100 || patients[i].oxygenlevel < 90)
                        {
                                strcpy(patients[i].status, "CRITICAL");
                        }
                        else if (patients[i].heartrate < 65 || patients[i].heartrate > 95 && patients[i].oxygenlevel < 92)
                        {
                                strcpy(patients[i].status, "ALERT");
                        }
                        else
                        {
                                strcpy(patients[i].status, "STABLE");
                        }
                }

                printf("Name    HR      OL      Stat\n");
                for (int i=0; i<pcount; i++)
                {
                        printf("%s      %d      %d      %s\n", patients[i].name, patients[i].heartrate, patients[i].oxygenlevel, patients[i].status);
                }

                exit(0);
        }

        struct Patient patients[pcount];
        for (int i=0; i<pcount; i++)
        {
                printf("enter name : ");
                scanf("%s", patients[i].name);

                printf("enter heart rate : ");
                scanf("%d", &patients[i].heartrate);

                printf("enter oxygen level : ");
                scanf("%d", &patients[i].oxygenlevel);

                strcpy(patients[i].status, "");
        }

        close(pipeAB[0]);
        write(pipeAB[1], patients, sizeof(patients));
        close(pipeAB[0]);

        wait(NULL);

        return 0;
}