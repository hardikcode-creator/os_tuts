#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); // Create a child process

    if (pid == -1) {
        // Error in creating the child process
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Inside the child process
        pid_t pid_grandchild = fork(); // Create a grandchild process

        if (pid_grandchild == -1) {
            perror("Fork failed for grandchild");
            return 1;
        } else if (pid_grandchild == 0) {
            // Inside the grandchild process
            printf("Grandchild Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        } else {
            // Child process waits for the grandchild process
            wait(NULL);
            printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        }
    } else {
        // Parent process waits for the child process
        wait(NULL);
        printf("Parent Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
    }

    return 0;
}

