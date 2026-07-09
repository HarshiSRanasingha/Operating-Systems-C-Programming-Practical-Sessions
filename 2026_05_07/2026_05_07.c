/*
Program: Parent -> Child -> Grandchild Communication using Unnamed Pipes

Tasks:
a) Parent reads N integers and sends them to Child using Pipe A
b) Child calculates sum and sends sum + N to Grandchild using Pipe B
c) Grandchild calculates average and sends it to Parent using Pipe C
d) Parent prints the average
e) Each process prints logs with PID and PPID

Compile:
    gcc process_pipe_avg.c -o process_pipe_avg

Run:
    ./process_pipe_avg
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 100

typedef struct {
    int sum;
    int count;
} Data;

void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int pipeA[2];   // Parent -> Child
    int pipeB[2];   // Child -> Grandchild
    int pipeC[2];   // Grandchild -> Parent

    pid_t child_pid, grandchild_pid;

    int N, numbers[MAX];

    /* Create pipes */
    if (pipe(pipeA) == -1)
        error_exit("Pipe A creation failed");

    if (pipe(pipeB) == -1)
        error_exit("Pipe B creation failed");

    if (pipe(pipeC) == -1)
        error_exit("Pipe C creation failed");

    /* Create child process */
    child_pid = fork();

    if (child_pid < 0) {
        error_exit("Fork failed");
    }

    /* ===================== PARENT PROCESS ===================== */
    if (child_pid > 0) {

        close(pipeA[0]); // Close read end of Pipe A
        close(pipeB[0]);
        close(pipeB[1]);
        close(pipeC[1]); // Parent only reads from Pipe C

        printf("\n[PARENT]\n");
        printf("PID=%d, PPID=%d\n", getpid(), getppid());

        printf("Enter number of integers: ");
        scanf("%d", &N);

        if (N <= 0 || N > MAX) {
            fprintf(stderr, "Invalid number of integers.\n");
            exit(EXIT_FAILURE);
        }

        printf("Enter %d integers:\n", N);

        for (int i = 0; i < N; i++) {
            scanf("%d", &numbers[i]);
        }

        /* Send N */
        if (write(pipeA[1], &N, sizeof(int)) == -1)
            error_exit("Parent write N failed");

        /* Send numbers */
        if (write(pipeA[1], numbers, sizeof(int) * N) == -1)
            error_exit("Parent write numbers failed");

        printf("Parent sent %d integers to Child through Pipe A\n", N);

        close(pipeA[1]);

        /* Read average from grandchild */
        float average;

        if (read(pipeC[0], &average, sizeof(float)) == -1)
            error_exit("Parent read average failed");

        printf("\nParent received average from Grandchild through Pipe C\n");
        printf("Calculated Average = %.2f\n", average);

        close(pipeC[0]);

        /* Wait for child */
        wait(NULL);

        printf("\nParent process completed.\n");
    }

    /* ===================== CHILD PROCESS ===================== */
    else {

        close(pipeA[1]); // Child only reads Pipe A
        close(pipeC[0]);
        close(pipeC[1]);

        printf("\n[CHILD]\n");
        printf("PID=%d, PPID=%d\n", getpid(), getppid());

        int count;
        int arr[MAX];

        /* Read N */
        if (read(pipeA[0], &count, sizeof(int)) == -1)
            error_exit("Child read N failed");

        /* Read integers */
        if (read(pipeA[0], arr, sizeof(int) * count) == -1)
            error_exit("Child read numbers failed");

        close(pipeA[0]);

        printf("Child received %d integers from Parent:\n", count);

        int sum = 0;

        for (int i = 0; i < count; i++) {
            printf("%d ", arr[i]);
            sum += arr[i];
        }

        printf("\nChild calculated Sum = %d\n", sum);

        /* Create grandchild */
        grandchild_pid = fork();

        if (grandchild_pid < 0) {
            error_exit("Grandchild fork failed");
        }

        /* ================= GRANDCHILD PROCESS ================= */
        if (grandchild_pid == 0) {

            close(pipeB[1]); // Grandchild reads Pipe B
            close(pipeC[0]); // Grandchild writes Pipe C

            printf("\n[GRANDCHILD]\n");
            printf("PID=%d, PPID=%d\n", getpid(), getppid());

            Data receivedData;

            if (read(pipeB[0], &receivedData, sizeof(Data)) == -1)
                error_exit("Grandchild read failed");

            close(pipeB[0]);

            printf("Grandchild received Sum=%d and Count=%d from Child\n",
                   receivedData.sum,
                   receivedData.count);

            float avg = (float)receivedData.sum / receivedData.count;

            printf("Grandchild calculated Average = %.2f\n", avg);

            /* Send average to Parent */
            if (write(pipeC[1], &avg, sizeof(float)) == -1)
                error_exit("Grandchild write average failed");

            printf("Grandchild sent Average to Parent through Pipe C\n");

            close(pipeC[1]);

            printf("Grandchild process completed.\n");

            exit(EXIT_SUCCESS);
        }

        /* ================= CHILD CONTINUES ================= */

        close(pipeB[0]); // Child writes Pipe B

        Data sendData;
        sendData.sum = sum;
        sendData.count = count;

        if (write(pipeB[1], &sendData, sizeof(Data)) == -1)
            error_exit("Child write failed");

        printf("Child sent Sum and Count to Grandchild through Pipe B\n");

        close(pipeB[1]);

        /* Wait for grandchild */
        wait(NULL);

        printf("Child process completed.\n");

        exit(EXIT_SUCCESS);
    }

    return 0;
}


/*
***********************************************

[PARENT]
PID=2100, PPID=1500
Enter number of integers: 5
Enter 5 integers:
10 20 30 40 50
Parent sent 5 integers to Child through Pipe A

[CHILD]
PID=2101, PPID=2100
Child received 5 integers from Parent:
10 20 30 40 50
Child calculated Sum = 150
Child sent Sum and Count to Grandchild through Pipe B

[GRANDCHILD]
PID=2102, PPID=2101
Grandchild received Sum=150 and Count=5 from Child
Grandchild calculated Average = 30.00
Grandchild sent Average to Parent through Pipe C

Parent received average from Grandchild through Pipe C
Calculated Average = 30.00


*/