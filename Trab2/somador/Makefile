CC = gcc
SOURCE = somador.c
EXEC_NAME = sum
CFLAGS = -lm -pthread
C_DEBUG_FLAGS = -D DEBUG -Wall

default:
	$(CC) $(SOURCE) -o $(EXEC_NAME) $(CFLAGS)

debug:
	$(CC) $(SOURCE) -o $(EXEC_NAME) $(CFLAGS) $(C_DEBUG_FLAGS)

clean:
	rm $(EXEC_NAME)