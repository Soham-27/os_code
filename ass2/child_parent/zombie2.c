#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
    pid_t pid=fork();
    if(pid<0){
        printf("fork failed !!");
    }
    
    if(pid>0){
        printf("Parent Process is running ....%d \n",getpid());
        sleep(2);
        printf("parent process exiting\n");
    }
    else{
        printf("child process is running ... %d\n",getpid());
        sleep(5);
        printf("child process exiting ...\n");
        exit(0);
    }
}