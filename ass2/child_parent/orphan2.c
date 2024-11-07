#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  // Create a new child process

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        sleep(5);  // Let the parent process exit first
        printf("Child process is now an orphan, adopted by init. PID: %d, PPID: %d\n", getpid(), getppid());
        // Child process continues to run independently
        sleep(5);  // Simulate additional work in the child process
    } else {
        // Parent process
        printf("Parent process is exiting. PID: %d\n", getpid());
        exit(0);  // Parent process exits immediately
    }

    return 0;
}
