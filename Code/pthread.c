//user space program , we are creating new threads and executing them seperately 
//gobal variable - it has to be gobal
//problem we are expecting the thread 1 to be executing first .
//critical section problem 
//many questions are given solve those for now 
// Question 5 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
int gobalvar=0;
char garray[20];
int flag=0;


void *print_message_function1( void *ptr );
void *print_message_function2( void *ptr );

int main()
{
     pthread_t thread1, thread2;
     char *message1 = "Thread 1";
     char *message2 = "Thread 2";
     int  iret1, iret2;

    /* Create independent threads each of which will execute function */
     // creates the child 
     iret1 = pthread_create( &thread1, NULL, print_message_function1, (void*) message1);
     iret2 = pthread_create( &thread2, NULL, print_message_function2, (void*) message2);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 

     printf("Thread 1 returns: %d\n",iret1);
     printf("Thread 2 returns: %d\n",iret2);
     exit(0);
}
// concurrancy issue critical section problem because of accessing the flag 
void *print_message_function1( void *ptr )
{
     // char *message;
     // message = (char *) ptr;
     //printf("%s \n", message);
     gobalvar=50;
     strcpy(garray,"Hello There");
     // garray="Hello There";
     while(flag==0);// wont do anything this is fliped 
     printf("%s \n",garray);
     
}


void *print_message_function2( void *ptr )
{
     // char *message;
     // message = (char *) ptr;
     // converts all the char from small to caps vice a versa , then will change the flag
     for(int i=0;i<strlen(garray);i++)
     {
          if (garray[i]>=65 && garray[i]<=90)
          {
               garray[i]=garray[i]+32;
          }
          else
          {
               if (garray[i]>=97 && garray[i]<=122)
               {
                    garray[i]=garray[i]-32;
               }
          }
     }
     // printf("%s \n", garray);
     flag=1;
}
