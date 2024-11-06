#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int main(){
    
    key_t key=ftok("/home/soham/OS_codes/ass7/shmfile.txt",65);
    int shm_id=shmget((key_t)65,1024,0666|IPC_CREAT);
    while(1){
    char* str=(char *) shmat(shm_id,NULL,0);
    printf("Message from Server : %s\n",str);
    shmdt(str);
    }
}