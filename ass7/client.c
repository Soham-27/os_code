#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>

int main(){
	do{
	int shmid=shmget((key_t)65,1024,0666 | IPC_CREAT);
	char * str=(char*)shmat(shmid,(void*)0,0);
	printf("Data read from memory: %s\n", str); 
      
    // Detach from shared memory after reading
    shmdt(str);
	
	}while(1);
	return 0;
}

