#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char * argv[])
{
	if(argc<=2)
	{
		printf("Invalid command line\n");
		return 0;
	}
	if(argv[1][0]=='t')
	{
		execvp("./twice",argv);
	}
	else if(argv[1][0]=='s')
	{
		execvp("./square",argv);
	}
	else
	{
		execvp("./half",argv);
	}
	return 0;
}
