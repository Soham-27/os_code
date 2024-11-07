#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define N 10  // Size of the buffer

sem_t empty;
sem_t full;

int in = 0;
int out = 0;
int buffer[N] = {0}; // Initialize buffer with zeroes

pthread_mutex_t mutex;

void printBuffer() {
    printf("Buffer :[");
    for (int i = 0; i < N; i++) {
        printf("%d ", buffer[i]);
    }
    printf("]\n");
}

void* producer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        int item = rand() % 10;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer ID %d inserted %d in buffer\n", id, item);
        printBuffer();

        in = (in + 1) % N;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(rand() % 3); // Random sleep to simulate production time
    }
    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        buffer[out] = 0; // Clear the consumed item for better visualization
        printf("Consumer ID %d consumed %d from buffer\n", id, item);
        printBuffer();

        out = (out + 1) % N;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(rand() % 3); // Random sleep to simulate consumption time
    }
    return NULL;
}

int main() {
    int p, q;
    printf("Enter the number of producers: ");
    scanf("%d", &p);
    printf("Enter the number of consumers: ");
    scanf("%d", &q);

    pthread_t producers[p], consumers[q];

    // Initialize semaphores
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    int producer_ids[p];
    int consumer_ids[q];

    // Create producer threads
    for (int i = 0; i < p; i++) {
        producer_ids[i] = i + 1;
        if (pthread_create(&producers[i], NULL, producer, &producer_ids[i]) != 0) {
            perror("Failed to create producer thread");
            exit(EXIT_FAILURE);
        }
    }

    // Create consumer threads
    for (int i = 0; i < q; i++) {
        consumer_ids[i] = i + 1;
        if (pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]) != 0) {
            perror("Failed to create consumer thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for threads to complete (in this case, they run indefinitely)
    for (int i = 0; i < p; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < q; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Destroy semaphores and mutex (in practice, unreachable unless threads are terminated externally)
    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&mutex);

    return 0;
}

