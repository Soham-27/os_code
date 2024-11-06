#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

#define max 10
sem_t writer;
int readcount=0;
int var=0;
pthread_mutex_t mutex;

void * readerFunc(void * args){
	while(1){
		pthread_mutex_lock(&mutex);
		readcount++;
		if(readcount==1)
			sem_wait(&writer);
			pthread_mutex_unlock(&mutex);
			printf("\n Reading is performed and the value read is : %d",var);
			pthread_mutex_lock(&mutex);
			readcount--;
		if(readcount==0)
			sem_post(&writer);
			pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}


void * writerFunc(void * args){
	while(1){
		sem_wait(&writer);
		var++;
		printf("\n\nWriting is performed and the value changed to: %d", var);
		sem_post(&writer);
		sleep(1);
	}
}

int main(){
	int read,write,i;
	if(sem_init(&writer,0,1)!=0){
		printf("failed");
		exit(0);
	}
	if(pthread_mutex_init(&mutex,NULL)!=0){
		printf("mutex failed");
		exit(0);
	}
	printf("enter the reader");
	scanf("%d",&read);
	printf("\n enter the writer");
	scanf("%d",&write);
	pthread_t reads[max], writes[max];
    for(i = 0; i < write; i++) {
        if(pthread_create(&writes[i], NULL, writerFunc, NULL) != 0) {
            printf("\nWriter thread no %d creation failed!", i + 1);
        } else {
            printf("\n\nWriter thread no %d created!", i + 1);
        }
    }

    for(i = 0; i < read; i++) {
        if(pthread_create(&reads[i], NULL, readerFunc, NULL) != 0) {
            printf("\nReader thread no %d creation failed!", i + 1);
        } else {
            printf("\n\nReader thread no %d created!", i + 1);
        }
    }
    
    for(i = 0; i < read; i++) {
        pthread_join(reads[i], NULL);
    }

    for(i = 0; i < write; i++) {
        pthread_join(writes[i], NULL);
    }
	sem_destroy(&writer);
    pthread_mutex_destroy(&mutex);
    return 0;
    }
    
	
		
