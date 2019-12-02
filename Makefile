BINARY_NAME = velsh
CC = gcc
CFLAGS = -Wdiscarded-qualifiers -Wall -Wextra -std=gnu99 -g

all:
	$(CC) src/*.c -o $(BINARY_NAME)


clean:
	rm $(BINARY_NAME)

.PHONY: clean