#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

// Divides the task into two subprocesses if n >= 0
// 	else, directlly computes max
void foo(int arr[], int l, int r)
{
	int status;
	if(r-l<9)
	{
		// Linear search for max
		int max = -1;
		int i;
		for(i=l;i<=r;++i)
		{
			if(arr[i] > max)
			max = arr[i];	
		}
		
		printf("PID = %d \t parent PID = %d \t max = %d\n",getpid(),getppid(),max);
		exit(max);	
	}
	else
	{
		//Create 2 child processes
		int left_process_id, right_process_id;
		if((left_process_id = fork()) == 0)
		{
			//Left child
			r = (l+r)/2;
			foo(arr, l, r);		
		}
		else if((right_process_id = fork()) == 0)
		{
			//Right child
			l = (l+r)/2 + 1;
			foo(arr, l, r);		
		}
		else
		{
			//Parent
			waitpid(left_process_id, &status, 0);
			int left_max = status >> 8;//Get the returned value
		
			waitpid(right_process_id, &status, 0);
			int right_max = status >> 8;//Get the returned value
			
			int max = left_max > right_max ? left_max : right_max;
			printf("PID = %d \t parent PID = %d \t max = %d\n", getpid(), getppid(), max);
			exit(max);		
		}
	
	}

}


int main(int argc, char * argv[])
{
	srand((unsigned int)time(NULL));
	int n,i,status;
	
	//Check for valid command line argument
	if(argc!=2)
	{
		printf("Invalid arguments!!\n");
		exit(0);
	}
	
	n = atoi(argv[1]);

	int arr[n];
	
	int cpid;
	
	//Generate random numbers
	for(i=0;i<n;++i)
		arr[i] = rand()%128;
	
	
	printf("Original array is : ");	
	for(i=0;i<n;++i)
		printf("%d ",arr[i]);
	
	printf("\n\n");
	
	//Fork a child process which computes max
	if((cpid = fork()) == 0)//Child process
	{
		foo(arr, 0, n-1);	
	}
	else//Parent process
	{
		waitpid(cpid, &status, 0);
		
		int max = status >> 8;
		printf("The maximum value in the array is : %d\n",max);
	}
	exit(0);
}