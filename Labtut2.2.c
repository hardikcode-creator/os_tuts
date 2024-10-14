#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
   

    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Inside the child process
        printf("Child process (PID: %d) is executing 'cat %s'\n", getpid(), argv[1]);
        execlp("cat", "cat", argv[1], NULL); // Execute 'cat' command

        // If execlp fails
        perror("execlp failed in child");
        return 1;
    } else {
        // Inside the parent process
        wait(NULL); // Wait for the child process to finish
        printf("Parent process (PID: %d) is executing 'ls'\n", getpid());
        execlp("ls", "ls",NULL); // Execute 'ls' command

        // If execlp fails
        perror("execlp failed in parent");
        return 1;
    }

    return 0;
}

