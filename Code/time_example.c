#include <sys/wait.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid, i;
    int status;
    struct timespec start, end;
    struct timespec req;
    int t;

    req.tv_sec = 0;  
    req.tv_nsec = 500000000;   // 500,000,000 nanoseconds (0.5 seconds)

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    if ((pid = fork()) == 0) {
        // ---- Child Process ----
        printf("I am the child process with pid=%d and ppid=%d\n", getpid(), getppid());

        //sleep(10);   // option to use sleep instead of busy wait
        for (i = 0; i < 1000000000; i++);  // busy wait loop

        exit(0);  // terminate child
    } 
    else {
        // ---- Parent Process ----
        printf("I am the parent process with pid=%d and ppid=%d\n", getpid(), getppid());

        //sleep(20);   // option to use sleep instead of busy wait
        for (i = 0; i < 2000000000; i++);  // busy wait loop

        wait(&status);  // wait for child to finish

        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        int difference_seconds = end.tv_sec - start.tv_sec;
        uint64_t delta_ns = (end.tv_nsec - start.tv_nsec);

        printf("Difference in time in nanoseconds is: %lu\n", delta_ns);
        printf("Difference in time in seconds is: %d\n", difference_seconds);
    }

    return 0;
}
