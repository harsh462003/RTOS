#include <stdio.h>

int main() {
    int n, i, time, remain, flag = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0, total_wait_time = 0, total_turnaround_time = 0;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    int burst_time[n], rem_burst_time[n];
    for (i = 0; i < n; i++) {
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
        rem_burst_time[i] = burst_time[i];  // Initialize remaining burst time
    }
    
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);
    
    printf("\nGantt Chart:\n");
    
    printf("0 ");
    time = 0;
    remain = n;  // Number of remaining processes
    
    while (remain != 0) {
        flag = 0;
        for (i = 0; i < n; i++) {
            if (rem_burst_time[i] > 0) {
                flag = 1;
                if (rem_burst_time[i] > time_quantum) {
                    time += time_quantum;
                    rem_burst_time[i] -= time_quantum;
                    
                    printf("| P%d | %d ", i + 1, time);
                } else {
                    time += rem_burst_time[i];
                    wait_time = time - burst_time[i];
                    rem_burst_time[i] = 0;
                    
                    turnaround_time = time;
                    
                    total_wait_time += wait_time;
                    total_turnaround_time += turnaround_time;
                    
                    remain--;
                    
                    printf("| P%d | %d ", i + 1, time);
                }
            }
        }
        if (flag == 0)  // No process remaining with burst time > 0
            break;
    }
    
    printf("\n\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    
    wait_time = 0;
    turnaround_time = 0;
    
    int wt[n], tat[n];
    int temp_bt[n];
    for (i = 0; i < n; i++) {
        temp_bt[i] = burst_time[i];
        wt[i] = 0;
        tat[i] = 0;
    }
    
    // Calculate waiting time and turnaround time for each process again for details
    time = 0;
    remain = n;
    int completed[n];
    for (i = 0; i < n; i++)
        completed[i] = 0;
    
    while (remain != 0) {
        for (i = 0; i < n; i++) {
            if (temp_bt[i] > 0) {
                if (temp_bt[i] > time_quantum) {
                    time += time_quantum;
                    temp_bt[i] -= time_quantum;
                } else {
                    time += temp_bt[i];
                    wt[i] = time - burst_time[i];
                    tat[i] = time;
                    temp_bt[i] = 0;
                    remain--;
                }
            }
        }
    }
    
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], wt[i], tat[i]);
    }
    
    printf("\nAverage Waiting Time = %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_turnaround_time / n);
    
    return 0;
}
