#include <stdio.h>

int main() {
    int n;
    int process[20], arrival_time[20], burst_time[20], priority[20];
    int waiting_time[20], turnaround_time[20], completion_time[20];
    int is_completed[20] = {0};
    int execution_order[20];  // 🔥 Gantt chart-এর জন্য
    int execution_start[20];  // start times
    int execution_end[20];    // end times
    int current_time = 0, completed = 0, step = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter ProcessID, ArrivalTime, BurstTime, Priority for each process:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &process[i], &arrival_time[i], &burst_time[i], &priority[i]);
    }

    // Scheduling loop
    while (completed < n) {
        int idx = -1;
        int highest_priority = 9999;

        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && !is_completed[i]) {
                if (priority[i] < highest_priority) {
                    highest_priority = priority[i];
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            waiting_time[idx] = current_time - arrival_time[idx];
            execution_order[step] = process[idx];
            execution_start[step] = current_time;
            current_time += burst_time[idx];
            execution_end[step] = current_time;
            completion_time[idx] = current_time;
            turnaround_time[idx] = completion_time[idx] - arrival_time[idx];
            is_completed[idx] = 1;
            completed++;
            step++;
        } else {
            current_time++;
        }
    }

    // Output
    printf("\n---------------------------------------------------------------\n");
    printf("PID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               process[i],
               arrival_time[i],
               burst_time[i],
               priority[i],
               waiting_time[i],
               turnaround_time[i]);
    }

    // Averages
    float avg_waiting = 0, avg_turnaround = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting += waiting_time[i];
        avg_turnaround += turnaround_time[i];
    }
    avg_waiting /= n;
    avg_turnaround /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround);

    // Gantt Chart
    printf("\nGantt Chart:\n");

    // Top bar
    printf(" ");
    for (int i = 0; i < step; i++) {
        printf("-------");
    }
    printf("\n|");

    // Process IDs
    for (int i = 0; i < step; i++) {
        printf("  P%d  |", execution_order[i]);
    }
    printf("\n ");

    // Bottom bar
    for (int i = 0; i < step; i++) {
        printf("-------");
    }
    printf("\n");

    // Timeline
    printf("%d", execution_start[0]);
    for (int i = 0; i < step; i++) {
        printf("     %d", execution_end[i]);
    }

    printf("\n");

    return 0;
}


// Enter number of processes: 3
// 1 0 5 2
// 2 2 3 1
// 3 4 2 3

// output:
// ---------------------------------------------------------------
// PID     Arrival Burst   Priority    Waiting Turnaround
// ---------------------------------------------------------------
// P1      0       5       2           3       8
// P2      2       3       1           0       3
// P3      4       2       3           6       8

// Average Waiting Time: 3.00
// Average Turnaround Time: 6.33

// Gantt Chart:
//  -----------------------
// |  P1  |  P2  |  P3  |
//  -----------------------
// 0     5     8    10
