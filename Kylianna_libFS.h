//Author: Kylianna Misiak
//CS470 Lab 4
//Header File


#ifndef KYLIANNA_LIBFS_H
#define KYLIANNA_LIBFS_H

// Constants
#define MAX_FILES 100
#define MAX_FILENAME 50
#define MAX_FILE_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// File system structures
typedef struct {
    char filename[MAX_FILENAME];
    int size;
    int is_open;
} FileEntry;

// Function prototypes for the file system operations
int fileCreate(const char *filename);
int fileOpen(const char *filename);
int fileRead(int fileDescriptor, char *buffer, size_t size);
int fileWrite(int fileDescriptor, const char *buffer, size_t size);
int fileClose(int fileDescriptor);
int fileDelete(const char *filename);

#endif 
