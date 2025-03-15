//Author: Kylianna Misiak
//CS470 Lab 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Kylianna_libFS.h"

FileEntry file_table[MAX_FILES];
int file_count = 0;

// Create a new file
int fileCreate(const char *filename) {

    // Check if file already exists
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_table[i].filename, filename) == 0) {
            printf("Error: File '%s' already exists.\n", filename);
            return -1;
        }
    }

    // Create the file on the local disk
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Unable to create file '%s'.\n", filename);
        return -1;
    }
    fclose(file);

    // Add file to the file table
    strcpy(file_table[file_count].filename, filename);
    file_table[file_count].size = 0;
    file_table[file_count].is_open = 0;  // File is closed
    file_count++;

    printf("File '%s' created successfully.\n", filename);
    return 0;
}


// Open an existing file
int fileOpen(const char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }
    return fd;
}

// Read data from the file
int fileRead(int fileDescriptor, char *buffer, size_t size) {
    // Move the file descriptor to the start of the file
    if (lseek(fileDescriptor, 0, SEEK_SET) == -1) {
        perror("Error seeking file");
        return -1;
    }

    // Read data from the file
    ssize_t bytesRead = read(fileDescriptor, buffer, size);
    if (bytesRead == -1) {
        perror("Error reading file");
        return -1;
    }
    
    // Null-terminate the buffer if there is any data
    buffer[bytesRead] = '\0'; 

    return bytesRead;
}


// Write data to the file
int fileWrite(int fileDescriptor, const char *buffer, size_t size) {
    ssize_t bytesWritten = write(fileDescriptor, buffer, size);
    if (bytesWritten == -1) {
        perror("Error writing file");
        return -1;
    }
    return bytesWritten;
}

// Close an open file
int fileClose(int fileDescriptor) {
    if (close(fileDescriptor) == -1) {
        perror("Error closing file");
        return -1;
    }
    return 0;
}

//Delete a file
int fileDelete(const char *filename) {
    if (remove(filename) == -1) {
        perror("Error deleting file");
        return -1;
    }
    return 0;
}
