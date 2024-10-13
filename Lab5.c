#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdint.h>
void*runner(void*i)
{
	int a=(int)((intptr_t)i);
	for(int i=0;i<a;i++)
		printf("*");
	printf("\n");
}
int main(int argv, char **argc)

{

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	int i=argc[1][0]-'0';
	printf("entered integer is %d\n", i);
	pthread_t tid[i+1];
	for(int j=i;j>=1;j--)
	{
		pthread_create(&tid[j],&attr,runner,(void*)((intptr_t)j));
	}
	for(int j=1;j<=i;j++)
	{
		pthread_join(tid[j],NULL);
	}
return 0;
}

