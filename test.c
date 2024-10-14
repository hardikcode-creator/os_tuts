#include<stdio.h>
#include<stdlib.h>
int main(int argc, char **argv)
{
	int i=atoi(argv[1]);
	int j=atoi(argv[2]);
	char op=argv[3][0];
	printf("op->%c", op);
	
		if(op=='*')
		printf("printed in c %d", i*j);
return 0;
}
