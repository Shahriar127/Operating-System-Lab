#include <stdio.h>

int main()
{
    int n;
    int process[20], arrival[20], burst[20], priority[20];
    int waiting[20], turnaround[20], completion[20];
    int is_completed[20] = {0};
    int current_time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter ProcessID, ArrivalTime, BurstTime, Priority (lower number = higher priority) for each process:\n");
    printf("Format: PID Arrival Burst Priority (all in one line)\n\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d %d", &process[i], &arrival[i], &burst[i], &priority[i]);
    }

    // Arrays to store Gantt chart info
    int gantt_pid[20];
    int gantt_start[20];
    int gantt_end[20];
    int gantt_index = 0;

    while (completed < n)
    {
        int idx = -1;
        int highest_priority = 9999;

        for (int i = 0; i < n; i++)
        {
            if (arrival[i] <= current_time && !is_completed[i])
            {
                if (priority[i] < highest_priority)
                {
                    highest_priority = priority[i];
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            // Process starts at current_time
            gantt_pid[gantt_index] = process[idx];
            gantt_start[gantt_index] = current_time;

            waiting[idx] = current_time - arrival[idx];
            current_time += burst[idx];
            completion[idx] = current_time;
            turnaround[idx] = completion[idx] - arrival[idx];
            is_completed[idx] = 1;
            completed++;

            gantt_end[gantt_index] = current_time;
            gantt_index++;

            // Aging: improve priority of waiting processes
            for (int i = 0; i < n; i++)
            {
                if (!is_completed[i] && arrival[i] <= current_time)
                {
                    if (priority[i] > 1)
                        priority[i]--;
                }
            }

            // Print priorities after aging
            printf("\nTime %d - Priorities after aging:\n", current_time);
            for (int i = 0; i < n; i++)
            {
                if (!is_completed[i])
                    printf("P%d: %d  ", process[i], priority[i]);
                else
                    printf("P%d: Completed  ", process[i]);
            }
            printf("\n");
        }
        else
        {
            // If no process is ready, CPU is idle, just move time forward
            current_time++;
        }
    }

    // Output
    printf("\n-----------------------------------------------------------\n");
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n", process[i], arrival[i], burst[i], waiting[i], turnaround[i]);
    }

    float avg_waiting = 0, avg_turnaround = 0;
    for (int i = 0; i < n; i++)
    {
        avg_waiting += waiting[i];
        avg_turnaround += turnaround[i];
    }
    avg_waiting /= n;
    avg_turnaround /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround);

    // Print Gantt Chart
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gantt_index; i++)
    {
        printf("  P%d  |", gantt_pid[i]);
    }
    printf("\n");

    // Print timeline
    printf("%d", gantt_start[0]);
    for (int i = 0; i < gantt_index; i++)
    {
        printf("     %d", gantt_end[i]);
    }
    printf("\n");

    return 0;
}


// Enter number of processes: 4

// Enter ProcessID, ArrivalTime, BurstTime, Priority:
// 1 0 4 3
// 2 1 3 1
// 3 2 5 4
// 4 3 2 2


// out:

// |  P2  |  P4  |  P1  |  P3  |
// 0     4     6     10    15
