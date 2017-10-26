#include <pthread.h>
#include <stdio.h>

void * printmessage(char *s)
{
	printf("%s\n", s);
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	pthread_t th1, th2;
	pthread_create(&th1, NULL, (void *)printmessage, (void *)"Hello");
	pthread_create(&th2, NULL, (void *)printmessage, (void *)"World");
	pthread_exit(NULL);
	return 0;
}