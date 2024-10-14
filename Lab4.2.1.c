  // Prepare the message                                                                              
  #include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define message structure
struct my_msg {
    long mytype;   // Message type
    char text[200];
};

int main() {
    struct my_msg msg;
    int qid;
    key_t key = 1034; // Unique key for the message queue

    // Access the message queue
    if ((qid = msgget(key, 0644)) == -1) {
        perror("msgget");
        exit(1);
    }

    // Receive and print messages in reverse order
    for (int i = 3; i >= 1; i--) {
        if (msgrcv(qid, &msg, sizeof(msg.text)+1, i, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("Received message of type %ld: %s\n", msg.mytype, msg.text);
    }

    return 0;
}



