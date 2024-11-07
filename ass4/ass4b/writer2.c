#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>

int a=10;
int readcount=0;

pthread_mutex_t wr;
pthread_mutex_t mutex;

void * reader(void * arg){
	long int num=(long int)arg;
	while(1){
		pthread_mutex_lock(&mutex);
		readcount++;
		if(readcount==1){
			pthread_mutex_lock(&wr);
		}
		pthread_mutex_unlock(&mutex);
		printf("Reader %ld in its critical section \n",num);
		printf("Reader %ld reads data %d",num,a);
		sleep(1);
		readcount--;
		if(readcount==0){
			pthread_mutex_unlock(&wr);
		}
		pthread_mutex_unlock(&mutex);
		printf("Reader %ld exiting",num);
		sleep(rand()%7);
	}
	return NULL;
}
void * writer(void * arg){
	long int num=(long int)arg;
	while(1){
	pthread_mutex_lock(&wr);
	printf("Writer %ld in critical section",num);
	a++;
	printf("Writer %ld update data %d",num,a);
	sleep(1);
	pthread_mutex_unlock(&wr);
	printf("\nWriter %ld has left critical section", num);
	sleep(rand() % 10);
	}
	return NULL;
}	
	
int main(){
	int nor,now;
	printf("Enter the no of reader");
	scanf("%d",&nor);
	printf("Enter the no of writers");
	scanf("%d",&now);
		
	long int i,j;
	
	pthread_t r[10],w[10];
	
	pthread_mutex_init(&wr,NULL);
	pthread_mutex_init(&mutex,NULL);
	
	for(i=0;i<nor;i++){
		pthread_create(&r[i],NULL,reader,(void*)i);
	}
	
	for(j=0;j<now;j++){
		pthread_create(&w[j],NULL,writer,(void*)j);
	}
	
	for(i=0;i<nor;i++){
		pthread_join(r[i],NULL);
	}
	for(j=0;j<now;j++){
		pthread_join(w[j],NULL);
	}
	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&wr);
	return 0;
}
