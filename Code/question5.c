#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 2;
    }

    int j = atoi(argv[1]);
    if (j <= 0) {
        printf("Please enter a positive integer.\n");
        return 2;
    }

    int pid = fork();

    if (pid < 0) {
        // fork failed
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process - print even numbers from 0 up to j
        printf("Child (even numbers): ");
        for (int k = 0; k < j; k += 2) {
            printf("%d ", k);
        }
        printf("\n");
        exit(0);
    }
    else {
        // Parent process - print odd numbers from 1 up to j
        printf("Parent (odd numbers): ");
        for (int k = 1; k < j; k += 2) {
            printf("%d ", k);
        }
        printf("\n");

	int status;
	wait(&status);

    }

    return 0;
}


/*
#include <sys/wait.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc,char* args)
{
	if(argc!=2)
	{
		return 2;
	}

	int j=atoi(args[1]);
	int pid=fork();
	int k=0;
	if(pid<0)
	{
		//fork failed
		perror('Fork failed');
		return 1;

	}
	else if(pid==0)
	{
		//Child process
		while(k<j)
		{
			printf("%d",k);
			k=k+2;
			// prints odd from 0 to arg j
		}

	}
	else
	{
		//Parent process
		while(k<j)
		{
			printf("%d",k);
			k=k+2;
		}
	}
}
*/