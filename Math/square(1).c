#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char * argv[])
{
	printf("Process id inside square = %d\n",getpid());
	if(argc==3)
	{
		int n=atoi(argv[2]);
		printf("Result = %d\n", n*n);
	}
	else
	{
		int n=atoi(argv[argc-1]),i;
		n*=n;
		char * s[argc];
		char s1[101];
		s[0]=argv[0];
		for(i=3;i<argc;++i)
			s[i-2]=argv[i-1];
		sprintf(s1, "%d", n);
		s[i-2]=s1;
		s[i-1]=NULL;
		if(argv[2][0]=='t')
		{
			execvp("./twice",s);
		}
		else if(argv[2][0]=='s')
		{
			execvp("./square",s);
		}
		else
		{
			execvp("./half",s);
		}
	}
	return 0;
}
