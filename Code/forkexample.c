#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // for fork()
#include <sys/types.h>
#include <sys/wait.h>

void generateFibonacci(int n) {
    long long a = 1, b = 1, next;
    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return;
    }
    if (n >= 1) printf("%lld ", a);
    if (n >= 2) printf("%lld ", b);
    for (int i = 3; i <= n; i++) {
        next = a + b;
        printf("%lld ", next);
        a = b;
        b = next;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_terms>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID %d) generating Fibonacci series:\n", getpid());
        generateFibonacci(n);
        exit(0);
    } else {
        // Parent process
        wait(NULL);  // Wait for child to finish
        printf("Parent process (PID %d) finished waiting for child.\n", getpid());
    }

    return 0;
}
