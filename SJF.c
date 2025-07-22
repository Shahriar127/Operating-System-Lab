#include <stdio.h>

int main() {
    int n, i, j;
    int process[20], burst[20], waiting[20], turnaround[20];
    int completion[20];
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter ProcessID and BurstTime for each process:\n");
    for (i = 0; i < n; i++) {
        scanf("%d %d", &process[i], &burst[i]);
    }

    // Sort by burst time
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (burst[i] > burst[j]) {
                int temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    waiting[0] = 0;
    turnaround[0] = burst[0];
    completion[0] = burst[0];

    for (i = 1; i < n; i++) {
        waiting[i] = waiting[i - 1] + burst[i - 1];
        turnaround[i] = waiting[i] + burst[i];
        completion[i] = completion[i - 1] + burst[i];
    }

    printf("\n-----------------------------------------------\n");
    printf("PID\tBurst\tWaiting\tTurnaround\n");
    printf("-----------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", process[i], burst[i], waiting[i], turnaround[i]);
    }

    float avg_waiting = 0, avg_turnaround = 0;
    for (i = 0; i < n; i++) {
        avg_waiting += waiting[i];
        avg_turnaround += turnaround[i];
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting / n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround / n);

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    for (i = 0; i < n; i++) {
        printf("  P%d  |", process[i]);
    }
    printf("\n");

    printf("0");
    for (i = 0; i < n; i++) {
        printf("     %d", completion[i]);
    }
    printf("\n");

    return 0;
}



// Enter number of processes: 3
// Enter ProcessID and BurstTime:
// 1 6
// 2 4
// 3 2


// PID     Burst   Waiting Turnaround
// P3      2       0       2
// P2      4       2       6
// P1      6       6       12

// Average Waiting Time: 2.67
// Average Turnaround Time: 6.67

// Gantt Chart:
// |  P3  |  P2  |  P1  |
// 0     2     6     12
