#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid > 0) {
        printf("I am the parent process ID : %d\n", getpid());
        wait(NULL);  // Wait for the child to finish
    } 
    else if (pid == 0) {
        printf("I am the child process ID : %d\n", getpid());
    } 
    else {
        printf("Fork Failed\n");
    }

    return 0;
}

