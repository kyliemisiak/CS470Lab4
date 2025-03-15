# Makefile for compiling the libFS library and test program

CC = gcc
CFLAGS = -Wall -g

# Object files
OBJ_FILES = Kylianna_libFS.o Kylianna_testFS.o

# Final executable
EXEC = test_app

# Default target to build the executable
all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC)

Kylianna_libFS.o: Kylianna_libFS.c Kylianna_libFS.h
	$(CC) $(CFLAGS) -c Kylianna_libFS.c

Kylianna_testFS.o: Kylianna_testFS.c Kylianna_libFS.h
	$(CC) $(CFLAGS) -c Kylianna_testFS.c

# Clean up generated files
clean:
	rm -f $(OBJ_FILES) $(EXEC)
