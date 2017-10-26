#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>
#define p(s)  semop(s,&pop,1)
#define v(s)  semop(s,&vop,1)


int main(int argc,char* argv[])
{
	int s2=semget(1233,1,IPC_CREAT|0777);
	int s1=semget(1212,1,IPC_CREAT|0777);
	int c2=semget(1214,1,IPC_CREAT|0777);
	int c1=semget(1222,1,IPC_CREAT|0777);
	int ne=semget(1311,1,IPC_CREAT|0777);
	int nf=semget(1242,1,IPC_CREAT|0777);
	int in=shmget(6756,sizeof(int),IPC_CREAT|0777);
	int shm=shmget(2312,(20*sizeof(int)),IPC_CREAT|0777);
	int ll=shmget(2838,sizeof(int),IPC_CREAT|0777);
	int hh=shmget(7627,sizeof(int),IPC_CREAT|0777);


	int *t=(int *)shmat(hh,0,0);
	int *gg=(int *)shmat(shm,0,0);
	

	semctl(ne,0,SETVAL,20);
	semctl(nf,0,SETVAL,0);
	semctl(s2,0,SETVAL,1);
	semctl(s1,0,SETVAL,1);
	semctl(c1,0,SETVAL,1);
	semctl(c2,0,SETVAL,1);

	int *a,*i,*o,*b;
	int *xx,*yy;
	struct sembuf vop,pop;
	pop.sem_num=0,vop.sem_num=0;
	pop.sem_flg=0,vop.sem_flg=0;
    pop.sem_op=-1,vop.sem_op=1;

   int n=atoi(argv[argc-1]);
   *t=n;
   printf("No of producer: %d\n",n);
  
   int *p=(int *)shmat(ll,0,0);
   *p=0;
   pid_t pid;
   int c=50;
   if(n==1)
   {
       
       a=(int *)shmat(shm,0,0);
       i=(int *)shmat(in,0,0);
       xx=(int *)shmat(ll,0,0);
       for(int j=0;j<20;j++)
       	a[j]=-1;
       *i=0;
       int data=1;
       while(c)
       {
       	sleep(1);
       	//printf("Yes produce\n");
          p(s1);
          p(ne);
          a[*i]=data;
          printf("Data produced %d at %d  by producer %d\n",data,*i,getpid());
          data++;
          (*i)=((*i)+1)%20;
          v(nf);
          v(s1);
          int k=0;
          for(int j=0;j<20;j++)
          {
          	if(a[j]==-1)
          	{
          		k++;
          		break;
          	}
          }
          if(k==0)
          {
          	printf("Buffer full:producer waits\n");
          	v(c1);
          }
          c--;

       }
       *xx=*xx+1;
       v(c1);
       //printf("%d in pro \n",*xx);
   }
   else
   {
   	pid=fork();
   	if(pid==0)
   	{
   	   
       a=(int *)shmat(shm,0,0);
       i=(int *)shmat(in,0,0);
       xx=(int *)shmat(ll,0,0);
       for(int j=0;j<20;j++)
       	a[j]=-1;
       *i=0;
       int data=1;
       while(c)
       {
       	sleep(2);
       		//printf("hey produce\n");
          p(s1);
          p(s2);
          p(ne);
          //printf("hey\n");
          a[*i]=data;
          printf("Data produced %d at %d  by producer %d\n",data,*i,getpid());
          data++;
          (*i)=((*i)+1)%20;
          v(nf);
          v(s2);
          v(s1);
          int k=0;
          for(int j=0;j<20;j++)
          {
          	if(a[j]==-1)
          	{
          		k++;
          		break;
          	}
          }
          if(k==0)
          {
          	printf("Buffer full:producer waits\n");
          	v(c1);
          	v(c2);
          }
          c--;

       }
       *xx=*xx+1;
   	}
   	else if(pid>0)
   	{
   	   
       b=(int *)shmat(shm,0,0);
       o=(int *)shmat(in,0,0);
       yy=(int *)shmat(ll,0,0);
       int data=1;
       while(c)
       {
       	  sleep(3);
       	  	//printf("cool produce\n");
          p(s2);
          p(s1);
          p(ne);
          b[*o]=data;
          printf("Data produced %d at %d  by producer %d\n",data,*o,getpid());
          data++;
          (*o)=((*o)+1)%20;
          v(nf);
          v(s1);
          v(s2);
          int k=0;
          for(int j=0;j<20;j++)
          {
          	if(b[j]==-1)
          	{
          		k++;
          		break;
          	}
          }
          if(k==0)
          {
          	printf("Buffer full:producer waits\n");
          	v(c1);
          	v(c2);
          }
          c--;

       }
       *yy=*yy+1;
   	}
   }
   return 0;
}