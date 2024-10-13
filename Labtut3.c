#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#define ARRAY_SIZE 5

int main(int argc,char** argv){
        int pipe_fd[2];
        char buf[30];

        if(pipe(pipe_fd) == -1)
        {

                perror("pipe creation failed");
                exit(1);
	}
        pid_t child_pid=fork();

        if(child_pid == -1)
        { perror("child process creation failed");
                exit(1);
        }
        else if (child_pid ==0)
        {
                close(pipe_fd[0]);
                int child_array[ARRAY_SIZE] ={1,2,3,4,5};

                write(pipe_fd[1],child_array,sizeof(child_array));
                close(pipe_fd[1]);
        }
//no need of wait as pipes are blocking in nature
        else{
                close(pipe_fd[1]);
		
		int parent_array[ARRAY_SIZE];
              	
	      	read(pipe_fd[0],parent_array,sizeof(parent_array));
               close(pipe_fd[0]);

                int sum=0;
                for(int i=0;i< ARRAY_SIZE;i++){   sum +=parent_array[i];

                }
                 printf("sum %d\n",sum);

                
                }


return 0;
}
