#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#define ARRAY_SIZE 5
 #include <stdio.h>
int main(int argc,char** argv){
        pid_t pid;
        int s;

        int pfds[2];

        pipe(pfds);
        pid=fork();

        if(pid ==0)

        { dup2(pfds[1],1);


                //close(pfds[0]);
                //close(pfds[1]);
                if(execlp("ls","ls",NULL) == -1){     perror("error in executing ls\n");
                }
        }
        else
        {
                if(fork()==0){
                        //second child
                dup2(pfds[0],0);
                close(pfds[1]);
                close(pfds[0]);
                if(execlp("wc","wc","-l",NULL) == -1){
                        perror("error in executing wc ls\n");
                }

                }
                else{
                        //parent process
                        close(pfds[0]);
                        close(pfds[1]);
                        wait(&s);
                        wait(&s);  }
        }

        return 0;
}

