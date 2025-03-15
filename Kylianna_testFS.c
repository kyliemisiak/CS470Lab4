//Author: Kylianna Misiak
//File: CS470 Lab 4, Library File System Program
//tester file

//headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Kylianna_libFS.h"
#include <ctype.h>

// Function menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Create a file\n");
    printf("2. Open a file\n");
    printf("3. Write to a file\n");
    printf("4. Read from a file\n");
    printf("5. Close the file\n");
    printf("6. Delete a file\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

//wait for user to press enter
void waitForUser(){
	printf("\nPress Enter to continue...");
	getchar();
}

int main() {

    int choice;
    char filename[MAX_FILENAME];

    //file index
    int fileDescriptor = -1;
    char buffer[256];
    char introText[] = "Hello, my name is Kylianna Misiak.\n\n"
                       "I am a computer science student in my last year.\n"
		       "This project involves creating a file system library in C.\n";

    while (1) {
        displayMenu();

	//get user choice
        scanf("%d", &choice);
        getchar();

        switch (choice) {
	    //create file
            case 1:
		printf("Enter the filename to create: ");
		fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';
		if(fileCreate(filename) != 0){
			printf("Error creating file.\n");
		}
		waitForUser();
		break;

	    //Open file
            case 2:
		printf("Enter the filename to open: ");
		fgets(filename, MAX_FILENAME, stdin);
		filename[strcspn(filename, "\n")] = '\0';
                fileDescriptor = fileOpen(filename);
                if (fileDescriptor != -1) {
                    printf("File opened successfully.\n");
                }
		waitForUser();
                break;

	    //Write to file (intro text)
            case 3:
                if (fileDescriptor == -1) {
                    printf("Error: Please open a file first.\n");
                } else {
                    printf("Writing the introduction to file '%s'...\n", filename);
                    fileWrite(fileDescriptor, introText, strlen(introText));
                }
		waitForUser();
                break;

	    //Read from file - print to terminal
            case 4:
                if (fileDescriptor == -1) {
                    printf("Please open a file first.\n");
                } else {
                    printf("Reading from file...\n");
                    fileRead(fileDescriptor, buffer, sizeof(buffer) - 1);
                    printf("File contents:\n%s\n", buffer);
                }
		waitForUser();
                break;

	    //Close file
            case 5:
                if (fileDescriptor != -1) {
                    fileClose(fileDescriptor);
                    fileDescriptor = -1;
                    printf("File closed successfully.\n");
                } else {
                    printf("No file is currently open.\n");
                }
		waitForUser();
                break;

	    //Delete File
            case 6:
		printf("Enter the filename to delete: ");
		fgets(filename, MAX_FILENAME, stdin);
		filename[strcspn(filename, "\n")] = 0;
                if(fileDelete(filename) == 0){
                	printf("File '%s' deleted successfully.\n", filename);
                }
		break;

	    //Exit program
            case 7:
                if (fileDescriptor != -1) {
                    fileClose(fileDescriptor);
                }
                printf("Exiting program.\n");
                exit(0);

            //default choice
            default:
                printf("Invalid choice. Please try again.\n");
		waitForUser();
		break;
        }
    }

    return 0;
}
