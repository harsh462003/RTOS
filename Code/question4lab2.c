/*
4.	Create a child through fork(). Let the child generate the fibonacci series (1, 1, 2, 3, 5, 8…) upto n numbers. The value of n has to passed as a command line argument. 
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>  
#include <stdint.h>
#include <stdlib.h>// Required for the atoi function 

void fibo(int n)
{
    printf("Function for printing the Fibonacci series:\n");
    int a = 1, b = 1, c;

    for (int i = 0; i < n; i++)
    {
        if (i == 0 || i == 1)
        {
            // First two terms are 1
            printf("%d ", 1);
        }
        else
        {
            c = a + b;
            printf("%d ", c);
            a = b;
            b = c;
        }
    }
    printf("\n");
}


int main(int argc, char *argv[])
{
	pid_t pid=fork();
	int status;
    int n = atoi(argv[1]);

	if(pid==0)
	{
		// child process
		printf("I AM THE CHILD AND MY PID IS %d \n",getpid());
		printf("the number is %d\n",n);
		fibo(n);


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