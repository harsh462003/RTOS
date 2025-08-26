/*
1.	Demonstrate fork() system call. Let the parent process display its pid, ppid and a message ‘I’m the parent’. Also let the child display its pid, ppid and a message ‘I’m the child’.

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>  


int main()
{
	pid_t pid=fork();
	int status;

	if(pid==0)
	{
		// child process

		printf("I AM THE CHILD AND MY PID IS %d AND MY PARENT PROCESS IS %d\n",getpid(),getppid() );
	}

	else if(pid >0)
	{
		//Parent process
		wait(&status);
		printf("I AM THE PARENT PROCESS AND MY PID IS %d AND MY PARENT PROCESS PID IS %d \n",getpid(),getppid());
	}
	else
	{
		// forking failed
		printf("Forking failed:");
	}
}