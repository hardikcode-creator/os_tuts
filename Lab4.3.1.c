#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define BUF_SIZE 200
#include<stdbool.h>
int main()
{
     
	int shmid;
	char*shmptr;
	shmid=shmget(1034,BUF_SIZE,0644);
	shmptr=shmat(shmid,NULL,0);
	while(true)
	{
		if(*shmptr!='\0')
		{
			printf("recieved string is %s\n",shmptr);
			*shmptr='\0';

		}
		sleep(1);

	}
if(shmdt(shmptr)==-1)
exit(1);
return 0;
}
