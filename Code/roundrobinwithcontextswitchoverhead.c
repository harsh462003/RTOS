#include <stdio.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

int main() {
    int n, i, time_quantum, context_switch;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    for (i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for P%d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for P%d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);
    printf("Enter context switch overhead time: ");
    scanf("%d", &context_switch);

    int current_time = 0, completed = 0;
    int queue[1000], front = 0, rear = 0;
    int visited[n];  // track if process is in queue
    for (i = 0; i < n; i++) visited[i] = 0;

    // Initialize queue with processes that arrive at time 0
    for (i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && !visited[i]) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    // For Gantt chart: store process ID and time intervals (start, end)
    // We'll store events with an array of structs or parallel arrays
    typedef struct {
        int pid;  // 0 means context switch, -1 means idle
        int start;
        int end;
    } GanttEvent;

    GanttEvent gantt[10000];
    int gantt_index = 0;

    while (completed < n) {
        if (front == rear) {
            // No process ready: CPU idle till next arrival
            int next_arrival = 1e9;
            for (i = 0; i < n; i++) {
                if (processes[i].remaining_time > 0 && processes[i].arrival_time > current_time) {
                    if (processes[i].arrival_time < next_arrival) {
                        next_arrival = processes[i].arrival_time;
                    }
                }
            }
            if (next_arrival == 1e9) break;  // All done
            if (current_time < next_arrival) {
                // CPU idle event
                gantt[gantt_index].pid = -1;
                gantt[gantt_index].start = current_time;
                gantt[gantt_index].end = next_arrival;
                gantt_index++;
                current_time = next_arrival;

                // Add processes that arrive at current_time
                for (i = 0; i < n; i++) {
                    if (processes[i].arrival_time <= current_time && !visited[i] && processes[i].remaining_time > 0) {
                        queue[rear++] = i;
                        visited[i] = 1;
                    }
                }
            }
            continue;
        }

        int idx = queue[front++];
        int run_time = (processes[idx].remaining_time < time_quantum) ? processes[idx].remaining_time : time_quantum;

        // Process runs from current_time to current_time + run_time
        gantt[gantt_index].pid = processes[idx].pid;
        gantt[gantt_index].start = current_time;
        gantt[gantt_index].end = current_time + run_time;
        gantt_index++;

        current_time += run_time;
        processes[idx].remaining_time -= run_time;

        // Add processes that arrive during this run_time interval
        for (i = 0; i < n; i++) {
            if (processes[i].arrival_time > gantt[gantt_index - 1].start && 
                processes[i].arrival_time <= current_time && !visited[i] && processes[i].remaining_time > 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (processes[idx].remaining_time > 0) {
            // Not finished, add back to queue
            queue[rear++] = idx;
        } else {
            processes[idx].completion_time = current_time;
            completed++;
        }

        // If CPU is not done (processes remain), add context switch overhead as event, except if no processes left
        if (completed < n) {
            gantt[gantt_index].pid = 0;  // 0 for context switch
            gantt[gantt_index].start = current_time;
            gantt[gantt_index].end = current_time + context_switch;
            gantt_index++;

            current_time += context_switch;

            // During context switch overhead, new processes might arrive
            for (i = 0; i < n; i++) {
                if (processes[i].arrival_time > gantt[gantt_index - 1].start &&
                    processes[i].arrival_time <= current_time && !visited[i] && processes[i].remaining_time > 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
        }
    }

    // Calculate waiting and turnaround times
    float total_wt = 0, total_tat = 0;
    for (i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
    }

    // Print Gantt chart
    printf("\nGantt Chart:\n ");
    for (i = 0; i < gantt_index; i++) {
        int length = gantt[i].end - gantt[i].start;
        for (int j = 0; j < length; j++) printf("-");
    }
    printf("\n|");
    for (i = 0; i < gantt_index; i++) {
        int length = gantt[i].end - gantt[i].start;
        if (gantt[i].pid > 0) {
            // Print process centered in the block
            int space_before = (length - 3) / 2;
            int space_after = length - 3 - space_before;
            for (int j = 0; j < space_before; j++) printf(" ");
            printf("P%d", gantt[i].pid);
            for (int j = 0; j < space_after; j++) printf(" ");
        } else if (gantt[i].pid == 0) {
            int space_before = (length - 2) / 2;
            int space_after = length - 2 - space_before;
            for (int j = 0; j < space_before; j++) printf(" ");
            printf("CS");
            for (int j = 0; j < space_after; j++) printf(" ");
        } else {
            // Idle
            int space_before = (length - 4) / 2;
            int space_after = length - 4 - space_before;
            for (int j = 0; j < space_before; j++) printf(" ");
            printf("IDLE");
            for (int j = 0; j < space_after; j++) printf(" ");
        }
        printf("|");
    }
    printf("\n ");

    for (i = 0; i < gantt_index; i++) {
        int length = gantt[i].end - gantt[i].start;
        for (int j = 0; j < length; j++) printf("-");
    }
    printf("\n");

    // Print timeline
    printf("%d", gantt[0].start);
    for (i = 0; i < gantt_index; i++) {
        int length = gantt[i].end - gantt[i].start;
        printf("%*d", length, gantt[i].end);
    }
    printf("\n");

    // Print process details
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", 
               processes[i].pid, 
               processes[i].arrival_time, 
               processes[i].burst_time, 
               processes[i].waiting_time, 
               processes[i].turnaround_time);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
