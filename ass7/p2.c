#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd_read, fd_write;
    char *myfifo1 = "/tmp/myfifo1"; // FIFO for reading from p1
    char *myfifo2 = "/tmp/myfifo2"; // FIFO for writing to p1

    mkfifo(myfifo1, 0666); // Create FIFO for reading
    mkfifo(myfifo2, 0666); // Create FIFO for writing

    char str1[180], str2[180];
    FILE *file; // File pointer for writing results

    while (1) {
        // Open FIFO for reading from p1
        fd_read = open(myfifo1, O_RDONLY);
        if (fd_read == -1) { perror("Error opening myfifo1 for reading"); exit(1); }
        read(fd_read, str1, sizeof(str1)); // Receive data from p1
        close(fd_read); // Close read end after receiving

        // Process message received from p1
        printf("User1: %s\n", str1);

        // Initialize counters
        int lines = 0, words = 0, characters = 0;
        int i = 0;

        // Calculate words, lines, and characters
        while (str1[i] != '\0') {
            characters++;
            if (str1[i] == ' ') words++;
            if (str1[i] == '.') lines++;
            i++;
        }
        words++; // Count the last word

        // Prepare the response string
        snprintf(str2, sizeof(str2), "Words Count: %d\nLines Count: %d\nCharacters Count: %d", words, lines, characters - 1);

        // Append the result to results.txt
        file = fopen("results.txt", "a"); // Open file in append mode
        if (file == NULL) { perror("Error opening file"); exit(1); }
        fprintf(file, "Message: %s\n%s\n\n", str1, str2); // Write the message and stats
        fclose(file); // Close the file

        // Send response to p1
        fd_write = open(myfifo2, O_WRONLY);
        if (fd_write == -1) { perror("Error opening myfifo2 for writing"); exit(1); }
        write(fd_write, str2, strlen(str2) + 1); // Send response to p1
        close(fd_write); // Close write end after sending
    }

    return 0;
}

