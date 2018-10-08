BINARY_NAME = velsh
DESTINATION_DIR=/usr/bin
CC = gcc
CFLAGS = -Wdiscarded-qualifiers -Wall -Wextra -std=gnu99 -g
OBJS = command.o utils.o history.o main.o

all: $(OBJS)
	$(CC) $(OBJS) -o $(BINARY_NAME)

install: 
	make all && install --target-directory=$(DESTINATION_DIR) $(BINARY_NAME)

uninstall:
	sudo rm -rf $(DESTINATION_DIR)/$(BINARY_NAME)


.PHONY: clean
clean:
	rm -rf *.o velsh
