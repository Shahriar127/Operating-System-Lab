#include <iostream>
#include <vector>

using namespace std;

bool isSafe(int processes, int resources,
            vector<vector<int>> &alloc,
            vector<vector<int>> &max,
            vector<int> &avail) {
    vector<vector<int>> need(processes, vector<int>(resources));
    vector<bool> finished(processes, false);
    vector<int> safeSeq;

    // Calculate the need matrix
    for (int i = 0; i < processes; ++i)
        for (int j = 0; j < resources; ++j)
            need[i][j] = max[i][j] - alloc[i][j];

    vector<int> work = avail;

    int count = 0;
    while (count < processes) {
        bool found = false;
        for (int p = 0; p < processes; ++p) {
            if (!finished[p]) {
                bool canAllocate = true;
                for (int r = 0; r < resources; ++r) {
                    if (need[p][r] > work[r]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int r = 0; r < resources; ++r)
                        work[r] += alloc[p][r];

                    safeSeq.push_back(p);
                    finished[p] = true;
                    found = true;
                    ++count;
                }
            }
        }

        if (!found) {
            cout << "System is NOT in a safe state.\n";
            return false;
        }
    }

    cout << "System is in a safe state.\nSafe sequence is: ";
    for (int i : safeSeq)
        cout << "P" << i << " ";
    cout << endl;

    return true;
}

int main() {
    int processes, resources;

    cout << "Enter number of processes: ";
    cin >> processes;

    cout << "Enter number of resources: ";
    cin >> resources;

    vector<vector<int>> alloc(processes, vector<int>(resources));
    vector<vector<int>> max(processes, vector<int>(resources));
    vector<int> avail(resources);

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < processes; ++i)
        for (int j = 0; j < resources; ++j)
            cin >> alloc[i][j];

    cout << "Enter Maximum Matrix:\n";
    for (int i = 0; i < processes; ++i)
        for (int j = 0; j < resources; ++j)
            cin >> max[i][j];

    cout << "Enter Available Resources:\n";
    for (int i = 0; i < resources; ++i)
        cin >> avail[i];

    isSafe(processes, resources, alloc, max, avail);

    return 0;
}


// Enter number of processes: 5
// Enter number of resources: 3
// Enter Allocation Matrix:
// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2
// Enter Maximum Matrix:
// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3
// Enter Available Resources:
// 3 3 2

// output:
// System is in a safe state.
// Safe sequence is: P1 P3 P4 P0 P2 
