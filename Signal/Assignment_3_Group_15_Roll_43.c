#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int sig_id)
{
    printf("\n\n   ---   Process with id %d caught signal %d   ---\n\n", getpid(), sig_id);
    exit(1);	
}

int main()
{
	printf("\n\n\n");
	printf("Currently in pid = %d\nThe next statement is fork();\n", getpid());
	pid_t x = fork();
	if (x==0)
	{
		printf("\tThis is process %d's child and my pid is %d\n", getppid(), getpid());
		int status;

		printf("\tCurrently in pid = %d\n\tThe next statement is fork();\n", getpid());
		pid_t v = fork();

		if (v==0)
		{
			signal(SIGFPE, handler);
			int f = 8;
			printf("\t\tThis is process %d and my parent has pid %d\n", getpid(), getppid());
			printf("%d\n",f/0);
		}
		else if(v>0)
		{
			waitpid(v,&status,0);
			signal(SIGSEGV,handler);
			int a[100];
			printf("\tThis is process %d and my child has pid %d\n", getpid(), v);
			printf("%d\n",a[10000]);
		}
	}
	else
	{
		int status2, i;
		waitpid(x,&status2,0);
		signal(SIGINT,handler);
		printf("This is the parent process with pid %d and my child has pid=%d\n", getpid(), x);
		while(1)
		{
			printf("\n\nWaiting for keyboard interrupt");
			fflush(stdout);
			sleep(1);
			for(i=0; i<3; i++)
			{
				printf(" .");
				fflush(stdout);
				sleep(1);
			}	
			
		}
		printf("\n\n\n");
	}
  return 0;
		
}
