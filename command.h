#ifndef __COMMAND__H
#define __COMMAND__H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

/**
 * Command struct 
 */ 
typedef struct Command {
    char* command; //full command string
    char** tokens; // command string divided for tokens by TOK_DELIM
    struct Command* next;
} Command;

/**
 * Create Command struct from string line 
 * @param char* command - string with whole command to execute
 * @return Command* - struct representing command to executes
 */
Command* parse_command(char* command);

/**
 * Execute Command struct
 * @param Command* command - command struct
 * @return int status of execution
 */ 
int execute_command(Command* command);

/**
 * Split command line string into tokens, executable and arguments.
 * @param char* line - string with whole command
 * @return char** array of tokens - @param line splited by TOK_DELIM characters
 */ 
char** split_command(char* line);

#endif