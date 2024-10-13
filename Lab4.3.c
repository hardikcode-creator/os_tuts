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
	int*shmptr;
	if(fork()==0)
	{
		shmid=shmget(1034,BUF_SIZE,0644);
		shmptr=(int*)shmat(shmid,NULL,0);
		if(shmptr==(void*)-1)
		{
			perror("error in shmat");
			exit(1);
		}
		printf("child has recieved %d", *shmptr);
		if(shmdt(shmptr)==-1)
		{
			perror("error in detaching");
			exit(1);
		}
	}
	else{
		shmid=shmget(1034,BUF_SIZE,0644|IPC_CREAT);
		shmptr=(int*)shmat(shmid,NULL,0);
		*shmptr=getpid();
		 if(shmdt(shmptr)==-1)
                {
                        perror("error in detaching");
                        exit(1);
                
		}

		 if(shmctl(shmid,IPC_RMID,0)==-1)
		 {
			 perror("error in deleting");
			 exit(1);
		 
		 }
		 wait(NULL);
		 printf("\n%d",getpid());
	}
	return 0;
}
