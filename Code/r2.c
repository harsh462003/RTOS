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

typedef struct {
    int pid;  // process id: >0 for process, 0 for context switch, -1 for idle
    int start_time;
    int end_time;
} GanttEvent;

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
    int visited[n];
    for (i = 0; i < n; i++) visited[i] = 0;

    // Add processes arrived at time 0 to queue
    for (i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && !visited[i]) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    GanttEvent gantt[10000];
    int gantt_index = 0;

    while (completed < n) {
        if (front == rear) {
            // CPU idle until next arrival
            int next_arrival = 1e9;
            for (i = 0; i < n; i++) {
                if (processes[i].remaining_time > 0 && processes[i].arrival_time > current_time) {
                    if (processes[i].arrival_time < next_arrival)
                        next_arrival = processes[i].arrival_time;
                }
            }
            if (next_arrival == 1e9) break;  // all done

            // Add idle event
            gantt[gantt_index].pid = -1;
            gantt[gantt_index].start_time = current_time;
            gantt[gantt_index].end_time = next_arrival;
            gantt_index++;

            current_time = next_arrival;

            // Add newly arrived processes
            for (i = 0; i < n; i++) {
                if (processes[i].arrival_time <= current_time && !visited[i] && processes[i].remaining_time > 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        int run_time = (processes[idx].remaining_time < time_quantum) ? processes[idx].remaining_time : time_quantum;

        // Run process
        gantt[gantt_index].pid = processes[idx].pid;
        gantt[gantt_index].start_time = current_time;
        gantt[gantt_index].end_time = current_time + run_time;
        gantt_index++;

        current_time += run_time;
        processes[idx].remaining_time -= run_time;

        // Add processes that arrive during this run time
        for (i = 0; i < n; i++) {
            if (processes[i].arrival_time > gantt[gantt_index-1].start_time &&
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

        // Context switch overhead if still processes remain
        if (completed < n) {
            gantt[gantt_index].pid = 0;  // context switch
            gantt[gantt_index].start_time = current_time;
            gantt[gantt_index].end_time = current_time + context_switch;
            gantt_index++;

            current_time += context_switch;

            // Add any newly arrived processes during context switch
            for (i = 0; i < n; i++) {
                if (processes[i].arrival_time > gantt[gantt_index-1].start_time &&
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

    // Print Gantt chart in clean fixed width style
    printf("\nGantt Chart:\n ");
    for (i = 0; i < gantt_index; i++) {
        printf("-------");
    }
    printf("\n|");

    for (i = 0; i < gantt_index; i++) {
        if (gantt[i].pid > 0)
            printf("  P%d   |", gantt[i].pid);
        else if (gantt[i].pid == 0)
            printf("  CS   |");
        else
            printf(" IDLE  |");
    }
    printf("\n ");

    for (i = 0; i < gantt_index; i++) {
        printf("-------");
    }
    printf("\n");

    // Print timeline
    printf("%d", gantt[0].start_time);
    for (i = 0; i < gantt_index; i++) {
        printf("      %d", gantt[i].end_time);
    }
    printf("\n");

    // Print process info
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
