/*
5.	Let the parent create a child using fork(). 
Let the parent geneate an odd series upto n numbers  (1, 3, 5, 7, 9…) and 
let the child create an even series upto n numbers (0, 2, 4, 6, 8 …). 
(i) Pass the value of n as a command line argument. 
(ii) Read the value of n from the user.
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
void printodd(int n)
{
	for (int i=1;i<n;i=i+2)
	{
		printf("%d  ",i);
	}
	printf("\n");

}
void printeven(int n)
{
	for (int i=0;i<n;i=i+2)
	{
		printf("%d  ",i);
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
		printf("printing the even numbers \n");
		printeven(n);

	}

	else if(pid >0)
	{
		//Parent process
		wait(&status);
		printf("I AM THE PARENT PROCESS AND MY PID IS %d AND MY PARENT PROCESS PID IS %d \n",getpid(),getppid());
		printf("printing the odd numbers \n");
		printodd(n);
	}
	else
	{
		// forking failed
		printf("Forking failed:");
	}


	int number;
	if (pid > 0) {  // Only parent reads input
    printf("Enter the number ");
    scanf("%d", &number);
} 



	int status2;
	pid_t pid2=fork();
	if(pid2==0)
	{
		printf("Child process 2\n");
		printodd(number);

	}
	else if(pid2>0)
	{
		wait(&status2);
		printf("Parent process\n");
		printeven(number);
	}
	else
	{
		printf("Failed to make the child process");
	}
}