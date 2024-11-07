#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>


# define N 10

int buffer[N];
int in=0;
int out=0;


sem_t empty;
sem_t full;

pthread_mutex_t mutex;


void print_buffer() {
    printf("Buffer: [ ");
    for (int i = 0; i < N; i++) {
        printf("%d ", buffer[i]);
    }
    printf("]\n");
}

void * producer(void * arg){
	int id=*(int *)arg;
	while(1){
		int item=rand()%10;
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		
		buffer[in]=item;
		printf("Producer %d inserted item: %d\n", id, item);
        	print_buffer();
        	
        	in=(in+1)%N;
        	
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		sleep(rand() % 7);
	}
	return NULL;
}

void * consumer(void * arg){
	int id=*(int *)arg;
	while(1){
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		
		int item=buffer[out];
		buffer[out]=0;
        	printf("Consumer %d consumed item: %d\n", id, item);
        	print_buffer();
        	
        	
        	out=(out+1)%N;
        	
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		sleep(rand() % 7);
	}
	return NULL;
}
int main(){
	int p,q;
	printf("Enter number of producers: ");
    	scanf("%d", &p);
    	printf("Enter number of consumers: ");
    	scanf("%d", &q);
    	
    	pthread_t producers[p],consumers[q];
    	
    	sem_init(&empty,0,N);
    	sem_init(&full,0,0);
    	pthread_mutex_init(&mutex,NULL);
    	
    	int producer_ids[p];
    	for(int i=0;i<p;i++){
    		producer_ids[i]=i+1;
    		pthread_create(&producers[i],NULL,producer,&producer_ids[i]);
  	}
  	int consumer_ids[q];
	for (int i = 0; i < q; i++) {
    	consumer_ids[i] = i + 1;  // Assign a unique ID to each consumer
    pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
}


	//for (int i = 0; i < p; i++) {
    //pthread_join(producers[i], NULL);
	//}
//for (int i = 0; i < q; i++) {
  //  pthread_join(consumers[i], NULL);
	//}
	
	
	sem_destroy(&full);
sem_destroy(&empty);
pthread_mutex_destroy(&mutex);
	return 0;
}
