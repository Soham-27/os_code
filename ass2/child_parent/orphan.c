#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); // Create a new process

    if (pid > 0) {
        // Parent process
        printf("Parent process (PID: %d) is going to sleep for 5 seconds...\n", getpid());
        sleep(5); // Parent sleeps for 5 seconds
        printf("Parent process (PID: %d) is exiting...\n", getpid());
        exit(0); // Parent exits
    } 
    else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) is now running...\n", getpid());
        sleep(2); // Child sleeps for 2 seconds
        printf("Child process (PID: %d) is exiting...\n", getpid());
        exit(0); // Child exits
    } 
    else {
        printf("Fork failed\n");
        exit(1);
    }

    return 0;
}

