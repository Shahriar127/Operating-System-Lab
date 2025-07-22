#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <map>

using namespace std;

struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

struct GanttEntry
{
    int pid;
    int start_time;
    int end_time;
};

vector<GanttEntry> gantt_chart;

void calculateTimes(vector<Process> &processes, int quantum)
{
    queue<int> ready_queue;
    int current_time = 0;
    int completed = 0;
    int n = processes.size();
    gantt_chart.clear();

    // Initialize remaining time
    for (int i = 0; i < n; i++)
    {
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.arrival_time < b.arrival_time; });

    // Add first arriving processes to the queue
    for (int i = 0; i < n; i++)
    {
        if (processes[i].arrival_time <= current_time)
        {
            ready_queue.push(i);
        }
        else
        {
            break;
        }
    }

    while (completed != n)
    {
        if (!ready_queue.empty())
        {
            int idx = ready_queue.front();
            ready_queue.pop();

            int start_time = current_time;
            // Execute for quantum or remaining time, whichever is smaller
            int execution_time = min(quantum, processes[idx].remaining_time);
            current_time += execution_time;
            processes[idx].remaining_time -= execution_time;

            // Add to Gantt chart
            gantt_chart.push_back({processes[idx].pid, start_time, current_time});

            // Check for newly arrived processes during this execution
            for (int i = 0; i < n; i++)
            {
                if (processes[i].arrival_time > start_time &&
                    processes[i].arrival_time <= current_time &&
                    processes[i].remaining_time > 0)
                {
                    ready_queue.push(i);
                }
            }

            // If process not finished, add back to queue
            if (processes[idx].remaining_time > 0)
            {
                ready_queue.push(idx);
            }
            else
            {
                // Process completed
                completed++;
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            }
        }
        else
        {
            // No processes in ready queue, advance time
            current_time++;
            // Check if any process arrives at this time
            for (int i = 0; i < n; i++)
            {
                if (processes[i].arrival_time == current_time && processes[i].remaining_time > 0)
                {
                    ready_queue.push(i);
                }
            }
        }
    }
}

void printGanttChart()
{
    cout << "\nGantt Chart:\n";

    // Top bar
    cout << " ";
    for (const auto &entry : gantt_chart)
    {
        cout << "-------";
    }
    cout << "\n|";

    // Process names
    for (const auto &entry : gantt_chart)
    {
        cout << "  P" << setw(2) << entry.pid << "  |";
    }

    // Bottom bar
    cout << "\n ";
    for (const auto &entry : gantt_chart)
    {
        cout << "-------";
    }

    // Time markers
    cout << "\n"
         << setw(2) << gantt_chart[0].start_time;
    for (const auto &entry : gantt_chart)
    {
        cout << setw(7) << entry.end_time;
    }
    cout << "\n\n";
}

void printResults(const vector<Process> &processes)
{
    int total_turnaround = 0, total_waiting = 0;

    cout << "\nProcess Details:\n";
    cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto &p : processes)
    {
        cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.completion_time << "\t\t" << p.turnaround_time << "\t\t" << p.waiting_time << endl;
        total_turnaround += p.turnaround_time;
        total_waiting += p.waiting_time;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << (float)total_turnaround / processes.size() << endl;
    cout << "Average Waiting Time: " << (float)total_waiting / processes.size() << endl;
}

int main()
{
    int choice;

    vector<Process> processes;
    int quantum;

    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter time quantum: ";
    cin >> quantum;

    processes.resize(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        processes[i].pid = i + 1;
        cin >> processes[i].arrival_time >> processes[i].burst_time;
    }

    calculateTimes(processes, quantum);
    printGanttChart();
    printResults(processes);

    return 0;
}