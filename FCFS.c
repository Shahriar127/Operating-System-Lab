#include <stdio.h>

int main() {
    int n, i, j;
    int process[20];
    int arrival_time[20];
    int burst_time[20];
    int waiting_time[20];
    int turnaround_time[20];
    int completion_time[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter Process ID, Arrival Time and Burst Time for Process %d:\n", i + 1);
        printf("Process ID: ");
        scanf("%d", &process[i]);
        printf("Arrival Time: ");
        scanf("%d", &arrival_time[i]);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
    }

    // Sorting by arrival time (FCFS order)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (arrival_time[i] > arrival_time[j]) {
                // Swap arrival time
                int temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;
                // Swap burst time
                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;
                // Swap process ID
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    // Calculate Completion Time, Turnaround Time, Waiting Time
    completion_time[0] = arrival_time[0] + burst_time[0];
    turnaround_time[0] = completion_time[0] - arrival_time[0];
    waiting_time[0] = turnaround_time[0] - burst_time[0];

    for (i = 1; i < n; i++) {
        if (arrival_time[i] > completion_time[i - 1]) {
            completion_time[i] = arrival_time[i] + burst_time[i];
        } else {
            completion_time[i] = completion_time[i - 1] + burst_time[i];
        }
        turnaround_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turnaround_time[i] - burst_time[i];
    }

    // Display results
    printf("\n--------------------------------------------------------\n");
    printf("Process\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    printf("--------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               process[i],
               arrival_time[i],
               burst_time[i],
               completion_time[i],
               waiting_time[i],
               turnaround_time[i]);
    }

    // Calculate Average Waiting Time and Turnaround Time
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (i = 0; i < n; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}


// Enter number of processes: 4

// Enter Process ID, Arrival Time and Burst Time for Process 1:
// Process ID: 1
// Arrival Time: 0
// Burst Time: 5

// Enter Process ID, Arrival Time and Burst Time for Process 2:
// Process ID: 2
// Arrival Time: 2
// Burst Time: 3

// Enter Process ID, Arrival Time and Burst Time for Process 3:
// Process ID: 3
// Arrival Time: 4
// Burst Time: 1

// Enter Process ID, Arrival Time and Burst Time for Process 4:
// Process ID: 4
// Arrival Time: 6
// Burst Time: 2


// Output:
// --------------------------------------------------------
// Process Arrival Burst Completion  Waiting Turnaround
// --------------------------------------------------------
// P1      0       5       5         0       5
// P2      2       3       8         3       6
// P3      4       1       9         4       5
// P4      6       2       11        3       5

// Average Waiting Time: 2.50
// Average Turnaround Time: 5.25
