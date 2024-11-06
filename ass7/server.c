#include <sys/ipc.h>    // For ftok() and shared memory operations
#include <sys/shm.h>    // For shmget(), shmat(), and shmdt() functions
#include <stdio.h>      // For printf() and gets() functions
  
int main() 
{ 
    // Generating a unique key for the shared memory segment
    key_t key = ftok("/homes/oslab/shmfile.txt",65); 
  
    // Create a shared memory segment
    int shmid = shmget((key_t)65, 1024, 0666 | IPC_CREAT); 
  
    // Attach the shared memory segment to the server's address space
    char *str = (char*) shmat(shmid, (void*)0, 0); 
  
    // Write data to the shared memory
    printf("Write Data: "); 
     fgets(str, 1024, stdin); 
  
    printf("Data written in memory: %s\n", str); 
      
    // Detach from shared memory once writing is done
    shmdt(str); 

    // Keeps the server running to allow time for the client to access the shared memory
    while(1);

    return 0; 
}

