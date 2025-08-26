

#include <stdio.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

int main() {
    int n, i, j;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for P%d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for P%d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
    }

    // Sort processes by arrival time (simple bubble sort)
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate start, completion, waiting, turnaround times
    int current_time = 0;
    for (i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;  // CPU idle if process arrives later
        }
        processes[i].start_time = current_time;
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].start_time - processes[i].arrival_time;
        current_time = processes[i].completion_time;
    }

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    printf(" ");

    for (i = 0; i < n; i++) {
        printf("--------");
    }
    printf("\n|");

    for (i = 0; i < n; i++) {
        printf("  P%d   |", processes[i].pid);
    }
    printf("\n ");

    for (i = 0; i < n; i++) {
        printf("--------");
    }
    printf("\n");

    // Print timeline
    printf("%d", processes[0].start_time);
    for (i = 0; i < n; i++) {
        printf("       %d", processes[i].completion_time);
    }
    printf("\n");

    // Print process details
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    float total_wt = 0, total_tat = 0;
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].waiting_time,
            processes[i].turnaround_time);

        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
