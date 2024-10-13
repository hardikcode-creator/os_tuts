#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    

    // Use execlp to execute the 'cat' command with the provided filename
    execlp("cat", "cat", argv[1], (char *)NULL);

    // If execlp fails
    perror("execlp failed");
    return 1;
}
