#include <stdio.h>

int main() {
    int n;
    int arrival[20], burst[20], remaining[20];
    int waiting[20], turnaround[20];
    int complete = 0, time = 0, shortest = -1;
    int min_remaining;
    int finish_time;
    int check = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter Arrival Time and Burst Time for each process (all in one line):\n");
    printf("Format: arrival1 burst1 arrival2 burst2 ...\n\n");

    // Example input for 3 processes: 0 8 1 4 2 2

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arrival[i], &burst[i]);
        remaining[i] = burst[i];
    }

    while (complete != n) {
        min_remaining = 9999;
        shortest = -1;

        // Find process with shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0 && remaining[i] < min_remaining) {
                min_remaining = remaining[i];
                shortest = i;
                check = 1;
            }
        }

        if (check == 0) {
            time++;
            continue;
        }

        remaining[shortest]--;

        if (remaining[shortest] == 0) {
            complete++;
            finish_time = time + 1;

            waiting[shortest] = finish_time - burst[shortest] - arrival[shortest];
            if (waiting[shortest] < 0)
                waiting[shortest] = 0;
        }

        time++;
    }

    // Turnaround times
    for (int i = 0; i < n; i++) {
        turnaround[i] = burst[i] + waiting[i];
    }

    // Print results
    printf("\n-------------------------------------------------------\n");
    printf("Process\tArrival\tBurst\tWaiting\tTurnaround\n");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               i + 1, arrival[i], burst[i], waiting[i], turnaround[i]);
    }

    // Averages
    float avg_waiting = 0, avg_turnaround = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting += waiting[i];
        avg_turnaround += turnaround[i];
    }
    avg_waiting /= n;
    avg_turnaround /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround);

    return 0;
}


// 3
// 0 8 1 4 2 2


// Process Arrival Burst Waiting Turnaround
// P1      0       8     9        17
// P2      1       4     3         7
// P3      2       2     0         2

// Average Waiting Time: 4.00
// Average Turnaround Time: 8.67
