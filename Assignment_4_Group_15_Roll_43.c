#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


	int fd_c[2],fd_d[2];
	char r_c[100],r_d[100];
	static int ac=0,ad=0;
void f3(int n)
{
   ad=-1;
}
void f4(int n)
{
   ac=-1;
}
void f1(int n)
{
				 	ad=1;
}
void f2(int n)
{
	 ac=1;
}
int main()
{
 int count=1;
	int cpoint=0,dpoint=0;
	pid_t c,d;
	pipe(fd_d);
	pipe(fd_c);
	c=fork();
	if(c!=0)
	{
		d=fork();
		if(d==0)
		{
		 while(1)
		 {
		 signal(SIGALRM,f1);
		 pause();
		 if(ad)
		 {
		  printf("signal caught in d-child\n");
			 time_t t;
		 	srand((int)time(&t) % getpid());
	   int x=rand()%1000;
	   close(fd_d[0]);
	   char s[100];
	   printf("No got in d child is %d\n",x);
	   sprintf(s,"%d",x);
			write(fd_d[1],s,strlen(s)+1); 
			kill(getppid(),SIGUSR1);
		 }
		 }
		}
		else
		{
			time_t t;
			while(1)
			{
			srand((int)time(&t) % getpid());
			int ch=rand()%2;
			printf("Starting of a new round\n");
			kill(c,SIGALRM);
			kill(d,SIGALRM);
			signal(SIGUSR1,f3);
			signal(SIGUSR2,f4);
			pause();
			if(ac==-1 && ad==-1)
			{
			if(ch==1)
			   printf("Selected MAX\n");
			else
			  printf("Selected MIN\n");
			close(fd_d[1]);
			read(fd_d[0],r_d,sizeof(r_d));
			close(fd_c[1]);
			read(fd_c[0],r_c,sizeof(r_c));
			int cn=atoi(r_c);
			int dn=atoi(r_d);
			printf("no obtained from c-child %d, no obtained from d-child %d\n",cn,dn);
			if(ch==1)
			{
				if(cn>dn)
					cpoint++;
				else if(cn<dn)
					dpoint++;
			}
			else
			{
				if(cn<dn)
					cpoint++;
				else if(cn>dn)
					dpoint++;                           
			}
	  printf("%d round ends and score is till now\n",count);
			printf("c-child point %d, d-child point %d\n\n\n",cpoint,dpoint);
			sleep(1);
			if(cpoint==10 || dpoint==10)
			{
			         printf("Last round is %dth round\n",count);
												if(cpoint==10)
	               printf("C winner\n");
	           else if(dpoint==10)
	                printf("D winner\n");
           	else
	                printf("Draw\n");
											printf("killing C and D child\n");
											kill(c,SIGKILL);
											kill(d,SIGKILL);
											kill(getpid(),SIGKILL);
			  			   break;
   }
   count++;
   ac=0,ad=0;
		}
		}
		}
               
	   
	}
	else
	{
	while(1)
	{
	 signal(SIGALRM,f2);
	 pause();
	 if(ac)
	 {
	  printf("signal caught in c-child\n");
	 time_t t;
		srand((int)time(&t) % getpid());
	 int x=rand()%1000;
	 close(fd_c[0]);
	 char s[100];
	 sprintf(s,"%d",x);
	 printf("No got in c-child is %d\n",x);
		write(fd_c[1],s,strlen(s)+1);
		kill(getppid(),SIGUSR2);
		}
		}
	}
	return 0;
}
