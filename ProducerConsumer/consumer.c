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
  int out=shmget(6743,sizeof(int),IPC_CREAT|0777);
  int shm=shmget(2312,(20*sizeof(int)),IPC_CREAT|0777);
  int ll=shmget(2838,sizeof(int),IPC_CREAT|0777);
  int hh=shmget(7627,sizeof(int),IPC_CREAT|0777);


  int var=shmget(2324,sizeof(int),IPC_CREAT|0777);
  int *u,*w,*xy,*yx,*t;
  t=(int *)shmat(hh,0,0);
  int *gg=(int *)shmat(shm,0,0);

	semctl(ne,0,SETVAL,20);
	semctl(nf,0,SETVAL,0);
  semctl(c1,0,SETVAL,1);
  semctl(c2,0,SETVAL,1);
  semctl(s2,0,SETVAL,1);
  semctl(s1,0,SETVAL,1);

	int *a,*i,*b,*o;
	struct sembuf vop,pop;
	pop.sem_num=0,vop.sem_num=0;
	pop.sem_flg=0,vop.sem_flg=0;
    pop.sem_op=-1,vop.sem_op=1;
  int *nn=(int *)shmat(out,0,0);
  *nn=0;
   int n=atoi(argv[argc-1]);
   printf("No of consumer: %d\n",n);
   
   int *y=(int *)shmat(var,0,0);
   *y=0;
   pid_t pid;
   int c=50;
   if(n==1)
   {
       
      a=(int *)shmat(shm,0,0);
       i=(int *)shmat(out,0,0);
       xy=(int *)shmat(ll,0,0);
       *i=0;
       u=(int *)shmat(var,0,0);
       while(1)
       {
          sleep(2);
          printf("In consumer\n");
          for(int j=0;j<20;j++)
            printf("%d ",a[j]);
          printf("\n");
                      //printf("yes consuming....");
          p(c1);
          p(nf);
          int m=a[*i];
          *u=*u+m;
          a[*i]=-1;
          printf("Data consumed %d from %d  by consumer %d\n",m,*i,getpid());
          (*i)=((*i)+1)%20;
          v(ne);
          v(c1);
          int k=0;
          for(int j=0;j<20;j++)
          {
            if(a[j]!=-1)
            {
              k++;
              break;
            }
          }
          if(k==0)
          {
            printf("Buffer empty:consumer waits\n");
            //printf("%d ,%d xy,t \n",*xy,*t);
            if(*xy==*t)
              break;
            v(s1);
          }
       }
   }
   else
   {
   	pid=fork();
   	if(pid==0)
   	{
   	   
       a=(int *)shmat(shm,0,0);
       i=(int *)shmat(out,0,0);
       xy=(int *)shmat(ll,0,0);
       u=(int *)shmat(var,0,0);
       while(1)
       {
          sleep(1);
          //printf("hey consuming....");
          printf("In consumer\n");
          for(int j=0;j<20;j++)
            printf("%d ",a[j]);
          printf("\n");
          p(c1);
          p(c2);
          p(nf);
          int m=a[*i];
          *u=*u+m;
          a[*i]=-1;
          printf("Data consumed %d from %d  by consumer %d\n",m,*i,getpid());
          (*i)=((*i)+1)%20;
          v(ne);
          v(c2);
          v(c1);
          int k=0;
          for(int j=0;j<20;j++)
          {
            if(a[j]!=-1)
            {
              k++;
              break;
            }
          }
          if(k==0)
          {
            printf("Buffer empty:consumer waits\n");
            if(*xy==*t)
              break;
            v(s1);
            v(s2);
          }
   	   }
      }
   	else if(pid>0)
   	{
   	   
       b=(int *)shmat(shm,0,0);
       o=(int *)shmat(out,0,0);
       w=(int *)shmat(var,0,0);
       yx=(int *)shmat(ll,0,0);

       while(1)
       {
          sleep(2);
          //printf("cool consuming....");
          printf("In consumer\n");
          for(int j=0;j<20;j++)
            printf("%d ",b[j]);
          printf("\n");
          p(c2);
          p(c1);
          p(nf);
          int m=b[*o];
          *w=*w+m;
          b[*o]=-1;
          printf("**Data consumed %d from %d  by consumer %d\n",m,*o,getpid());
          (*o)=((*o)+1)%20;
          v(ne);
          v(c1);
          v(c2);
          int k=0;
          for(int j=0;j<20;j++)
          {
          	if(b[j]!=-1)
          	{
          		k++;
          		break;
          	}
          }
          if(k==0)
          {
          	printf("Buffer empty:consumer waits\n");
            if(*yx==*t)
              break;
            v(s1);
            v(s2);
          }

       }
   	}
   }
   printf("sum=%d\n",*y);
   return 0;
}