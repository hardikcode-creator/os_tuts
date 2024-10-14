#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include<stdbool.h>
#include<limits.h>
#include<pthread.h>

// Trie node structure
typedef struct TrieNode {
    struct TrieNode *children[26];  // Array to hold children nodes (26 letters)
    int frequency;                             // Store the frequency of the word ending here
} TrieNode;

// Function to create a new Trie node
TrieNode *createNode() {
    TrieNode *newNode = (TrieNode *)malloc(sizeof(TrieNode));
    if (newNode) {
        newNode->frequency = 0;
        for (int i = 0; i < 26; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}
// Function to insert a word into the Trie and update its frequency
void insert(TrieNode *root, const char *word) {
    TrieNode *currentNode = root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';  // Calculate the index of the character in the alphabet
        if (currentNode->children[index] == NULL) {
            currentNode->children[index] = createNode();
        }
        currentNode = currentNode->children[index];
    }
    // Increment the frequency at the end of the word
    currentNode->frequency++;
}
// Function to search for a word in the Trie and return its frequency
int search(TrieNode *root, const char *word) {
    TrieNode *currentNode = root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (currentNode->children[index] == NULL) {
            return 0;  // Word not found
        }
        currentNode = currentNode->children[index];
    }
    return currentNode->frequency;  // Return the frequency of the word
}


struct msg{
	long mtype;
	int key;
};

typedef struct data{
    char*str;
    int key;
}data;

int stringSize;
	FILE *textFile;
	pthread_mutex_t file_mutex;
	void decode_cipher(char *str, int shift)
{   
        
        int len=strlen(str);
               
                for(int j=0;j<len;j++)
                {
                        str[j]=(str[j]-'a'+(shift)%26)%26 +'a';
                        
                }
                
}

TrieNode*root;  
void*runner(void*arg){
    char*words=((data*)arg)->str;
  
    decode_cipher(words,((data*)arg)->key);
    char buffer[stringSize];
     int *cnt = (int*)malloc(sizeof(int));  // Allocate memory for the count
    *cnt = 0;
   
    pthread_mutex_lock(&file_mutex);
    
        (*cnt)+=search(root,words);

    // Unlock the mutex after reading from the file
    pthread_mutex_unlock(&file_mutex);



    pthread_exit((void*)cnt);
        
}

        
        

int main(int argv, char**argc)
{
	int i=atoi(argc[1]);
	 FILE *inputFile;
	 FILE *textFile;
    char buffer[1024]; // Buffer to store file content line by line
    root=createNode();
 if (pthread_mutex_init(&file_mutex, NULL) != 0) {
        perror("Mutex initialization failed");
        return 1;
    }

    // Open file in read mode
    char fileName[100]="input";
    strcat(fileName,argc[1]);
    strcat(fileName,".txt");
    printf("%s\n", fileName);
 	inputFile=fopen(fileName,"r");

    if(inputFile==NULL)
  {
	 printf("unable to open the input file");
	return 0;
	}

    int arr[4];
     int j=0;
	while(fgets(buffer,sizeof(buffer),inputFile))
	{

		arr[j]=atoi(buffer);
		j++;
	}

	fclose(inputFile);
    root=createNode();

 	int N=arr[0];
	 stringSize=arr[1];
	int  key=arr[2];
	char (*shmptr) [N][stringSize];
	int shmid=shmget(key,  sizeof(char[N][N][stringSize]), 0644);
	if (shmid == -1) {
    perror("shmget failed");
    exit(1);
}
	shmptr=shmat(shmid, NULL, 0);

	//for counting occurences of each string and store it in hashmap we could use threads
	// strings and then pass 
	
	
      
    	
    char fileName1[20]="words";
    strcat(fileName1,argc[1]);
    strcat(fileName1,".txt");
 
        textFile=fopen(fileName1,"r");

    if(textFile==NULL)
  {
         printf("unable to open the input file");
        return 0;
        }
        
         while (fscanf(textFile, "%s", buffer) != EOF) {
             
       insert(root,buffer);
    }


	///============================================
		int msqid;
		struct msg my_msg;
		struct msg recieve;
		recieve.key=0;

		if((msqid=msgget(arr[3],0644))==-1){
		perror("error in msgget\n");
		exit(1);
		}
		  pthread_attr_t attr;
        pthread_attr_init(&attr);


		my_msg.mtype=1;
		
		for(int k=0;k<2*N-1;k++)
		{
			my_msg.key=0;
			pthread_t tid[k+1];
			 data *data1 = (data*)malloc((k+1)*sizeof(data));
			 for (int l = 0; l <= k; l++) {
    if (l >= 0 && l < N && k-l >= 0 && k-l < N) {
        data1[l].key = recieve.key;
        data1[l].str = shmptr[l][k-l];
    }
}
			for(int l=0;l<=k;l++)
			{   if(l>=0 && l<N && k-l<N && k-l>=0){
			  
			   pthread_create(&tid[l], &attr, runner, (void*)&data1[l]);
			}
			}
		
			for(int l=0;l<=k;l++)
			{
			   
			    if( l<N && k-l<N){
			    void*result;
			    pthread_join(tid[l],&result);
			    my_msg.key+=*((int*)result);
			     free(result); 
			    }
			}
	
			
		
		if(msgsnd(msqid,&my_msg,sizeof(my_msg) - sizeof(my_msg.mtype),0)==-1)
		{
			perror("\nError in sending a message");
			exit(1);
		}
		
									
		if(msgrcv(msqid,&recieve,sizeof(my_msg) - sizeof(my_msg.mtype),2,0)==-1){
			perror("wrong input");
			exit(1);
		}

		}
	
   if(shmdt(shmptr)==-1)
	{
		perror("error in shmdt");
		exit(1);
	}

    // Destroy mutex
    pthread_mutex_destroy(&file_mutex);
	
    return 0;
}		
