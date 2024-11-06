#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd_write, fd_read;
    char *myfifo1 = "/tmp/myfifo1"; // FIFO for writing to p2
    char *myfifo2 = "/tmp/myfifo2"; // FIFO for reading from p2

    mkfifo(myfifo1, 0666); // Create FIFO for writing
    mkfifo(myfifo2, 0666); // Create FIFO for reading

    char str1[180], str2[180];

    while (1) {
        printf("Enter message: ");
        fgets(str1, 180, stdin); // Take user input

        // Open FIFO for writing to p2
        fd_write = open(myfifo1, O_WRONLY);
        if (fd_write == -1) { perror("Error opening myfifo1 for writing"); exit(1); }
        write(fd_write, str1, strlen(str1) + 1); // Send data to p2
        close(fd_write); // Close write end after sending

        // Open FIFO for reading response from p2
        fd_read = open(myfifo2, O_RDONLY);
        if (fd_read == -1) { perror("Error opening myfifo2 for reading"); exit(1); }
        read(fd_read, str2, sizeof(str2)); // Receive response from p2
        close(fd_read); // Close read end after receiving

        printf("Response from p2: %s\n", str2); // Display p2’s response
    }

    return 0;
}

