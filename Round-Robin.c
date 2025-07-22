#include <stdio.h>

#define MAX 100

typedef struct {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int waiting;
    int turnaround;
    int completed;
} Process;

typedef struct {
    int pid;
    int start;
    int end;
} Gantt;

int main() {
    int n, timeQuantum;
    Process p[MAX];
    Gantt g[MAX];
    int gIndex = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter ProcessID, ArrivalTime and BurstTime for each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &p[i].pid, &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
        p[i].waiting = 0;
        p[i].turnaround = 0;
        p[i].completed = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    int time = 0, done = 0;

    while (done < n) {
        int idle = 1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                idle = 0;

                g[gIndex].pid = p[i].pid;
                g[gIndex].start = time;

                if (p[i].remaining > timeQuantum) {
                    time += timeQuantum;
                    p[i].remaining -= timeQuantum;
                } else {
                    time += p[i].remaining;
                    p[i].waiting = time - p[i].arrival - p[i].burst;
                    p[i].remaining = 0;
                    p[i].turnaround = p[i].waiting + p[i].burst;
                    p[i].completed = 1;
                    done++;
                }

                g[gIndex].end = time;
                gIndex++;
            }
        }

        if (idle)
            time++; // CPU idle, advance time
    }

    // Output
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }

    // Average Times
    float avg_wait = 0, avg_turn = 0;
    for (int i = 0; i < n; i++) {
        avg_wait += p[i].waiting;
        avg_turn += p[i].turnaround;
    }
    printf("\nAverage Waiting Time: %.2f", avg_wait / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turn / n);

    // Gantt Chart
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gIndex; i++) {
        printf(" P%d |", g[i].pid);
    }
    printf("\n");

    printf("%d", g[0].start);
    for (int i = 0; i < gIndex; i++) {
        printf("   %d", g[i].end);
    }
    printf("\n");

    return 0;
}



// Enter number of processes: 3
// Enter ProcessID, ArrivalTime and BurstTime:
// 1 0 5
// 2 2 4
// 3 4 6
// Enter Time Quantum: 3



// Process	Arrival	Burst	Waiting	Turnaround
// P1	    0	    5	    6	    11
// P2	    2	    4	    6	    10
// P3	    4	    6	    5	    11

// Average Waiting Time: 5.67
// Average Turnaround Time: 10.67

// Gantt Chart:
// | P1 | P2 | P3 | P1 | P2 | P3 |
// 0    3    6    9   11   12   15
