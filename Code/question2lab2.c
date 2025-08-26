/*2.	Let the parent fork and let the child execute ls command. Observe the result with and without having wait()  system call in the parent. */


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
		printf("I AM THE CHILD AND MY PID IS %d \n",getpid());
		execlp("ls", "ls", NULL);
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