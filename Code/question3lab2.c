/*
3.	Let the parent create 4 children. Make them execute ls, ls –l, pwd and  date commands. (One child executes one command.)
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    // Child 1: Execute "ls"
    pid = fork();
    if (pid == 0)
    {
        printf("Child 1 (PID: %d) executing 'ls'\n", getpid());
        execlp("ls", "ls", NULL);
        perror("execlp failed");
        return 1;
    }
    wait(&status); // Parent waits

    // Child 2: Execute "ls -l"
    pid = fork();
    if (pid == 0)
    {
        printf("Child 2 (PID: %d) executing 'ls -l'\n", getpid());
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        return 1;
    }
    wait(&status);

    // Child 3: Execute "pwd"
    pid = fork();
    if (pid == 0)
    {
        printf("Child 3 (PID: %d) executing 'pwd'\n", getpid());
        execlp("pwd", "pwd", NULL);
        perror("execlp failed");
        return 1;
    }
    wait(&status);

    // Child 4: Execute "date"
    pid = fork();
    if (pid == 0)
    {
        printf("Child 4 (PID: %d) executing 'date'\n", getpid());
        execlp("date", "date", NULL);
        perror("execlp failed");
        return 1;
    }
    wait(&status);

    // Parent process
    printf("Parent process (PID: %d) finished launching all children.\n", getpid());

    return 0;
}
