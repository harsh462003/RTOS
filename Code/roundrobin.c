#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completed_time;
    int waiting_time;
    int turnaround_time;
    int started;  // flag to mark if process has started
} Process;

int main() {
    int n, time_quantum;
    Process processes[MAX_PROCESSES];
    int i, time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].completed_time = 0;
        processes[i].started = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    int queue[MAX_PROCESSES];
    int front = 0, rear = 0;
    int in_queue[MAX_PROCESSES] = {0};

    // Enqueue processes that have arrived at time 0
    for (i = 0; i < n; i++) {
        if (processes[i].arrival_time == 0) {
            queue[rear++] = i;
            in_queue[i] = 1;
        }
    }

    printf("\nGantt Chart:\n");
    printf("0 ");

    while (completed < n) {
        if (front == rear) {
            // If no process in queue, CPU is idle till next arrival
            time++;
            for (i = 0; i < n; i++) {
                if (!in_queue[i] && processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        int exec_time = (processes[idx].remaining_time > time_quantum) ? time_quantum : processes[idx].remaining_time;

        // Print process running
        printf("| P%d | %d ", processes[idx].pid, time + exec_time);

        if (!processes[idx].started) {
            processes[idx].started = 1;
        }

        processes[idx].remaining_time -= exec_time;
        time += exec_time;

        // Check for new arrivals during this time slice and enqueue
        for (i = 0; i < n; i++) {
            if (!in_queue[i] && processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }

        if (processes[idx].remaining_time > 0) {
            // Re-enqueue the current process if not finished
            queue[rear++] = idx;
        } else {
            // Process finished
            completed++;
            processes[idx].completed_time = time;
            processes[idx].turnaround_time = processes[idx].completed_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
        }
    }

    // Display table of results
    printf("\n\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
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
