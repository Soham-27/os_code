#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main(){
	pid_t pid=fork();
	if (pid>0){
		printf("this is parent process %d\n",getpid());
		printf("parent process is sleeping");
		sleep(5);
        exit(0);
		printf("parent process is waking up and running");
	}
	else if ( pid ==0){
		printf("this is child process %d \n",getpid());
		printf("child process exiting \n");
	}
	else{
		printf("fork failed");
	}
}

	
