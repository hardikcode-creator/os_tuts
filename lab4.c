#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define message structure
struct my_msg {
    long mytype;
    char text[200];
};

int main() {
    struct my_msg msg;
    int qid;
    key_t key = 1034; // You can use any unique key

    // Create a message queue or get the ID of an existing one
    if ((qid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    // Prepare the message
    msg.mytype = 1; // Set the message type
    strcpy(msg.text, "Hardik Agrawal, 2022A7PS0045H"); // Set the message content (Name and BITS ID)

    // Send the message
    if (msgsnd(qid, &msg, sizeof(msg.text), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent: %s\n", msg.text);
    return 0;
}

