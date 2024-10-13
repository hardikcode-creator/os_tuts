#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
typedef struct coordinates{

int x,y,index;

}coordinates;
void*runner(void*arr)
{
	coordinates*a=(coordinates*)arr;
	int ind=a->index;
	printf("\ndistance of point %d is %d", ind+1, ((a->x*a->x)+(a->y*a->y)));
}
int main()
{
	
        pthread_attr_t attr;
        pthread_attr_init(&attr);
	coordinates arr[3];
	for(int i=0;i<3;i++)
	{
		scanf("%d %d", &arr[i].x, &arr[i].y);
	}
	pthread_t tid[3];
	for(int i=0;i<3;i++)
		{	arr[i].index=i;
			pthread_create(&tid[i],&attr,runner,(void*)(&arr[i]));
		}
	for(int i=0;i<2;i++)
	{
		pthread_join(tid[i],NULL);
	}

	return 0;
}
