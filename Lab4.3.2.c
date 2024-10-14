#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUF_SIZE 200
int main()
{
	int shmid;
	char*shmptr;
	shmid=shmget(1034,BUF_SIZE,0644|IPC_CREAT);
	shmptr=shmat(shmid,NULL,0);
	while(1)
	{
		fgets(shmptr,BUF_SIZE,stdin);
       	}
	if(shmdt(shmptr)==-1)
	{
		perror("error in shmdt");
		exit(1);
	}

	
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        perror("Error while deleting the memory segments\n");
        exit(-1);
    }
return 0;
}
