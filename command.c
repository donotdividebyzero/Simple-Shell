#include "command.h"

Command* parse_command(char* command) {
    if (isspace(*command)) {
        return NULL;
    }
    
    /**
     * first character '#' is value of binary name from script file
     * NULL in case of empty line
     */
    if (*command == '#' || command == NULL) {
        return NULL;
    }

    Command* comm = malloc( sizeof(Command) );

    comm->command = command;
    char* tmpLine = (char*)malloc( strlen(comm->command) * sizeof(char) );
    strcpy(tmpLine, command);

    comm->tokens = split_command(tmpLine);
    comm->next = NULL;

    return comm;
}

char** split_command(char* line)
{
    int bufsize = TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*)); // realloc is just in case
        }

        token = strtok(NULL, TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
}

int execute_command(Command* command) 
{
    /**
     * -2 is because strings are terminated with '\0' (NULL) guard and strlen doesn't starts with 0
     */ 
    char* lastCharOfCommand = command->command + strlen(command->command) - 2;
    int waitForExecution = (int)(*lastCharOfCommand != '&'); // just to be sure when I remove '&' from command string

    pid_t pid = fork();
    if (pid == 0) { // '0' is no error response from fork()
        if (!waitForExecution) { //leaving '&' at end couses execvp to wronlgy interprete command tokens
            char* token = malloc(sizeof(char*));
            for(token = *command->tokens; *token != '&'; token++);
            *token = '\0';
            --token; // move back and check if last char is whitespace, if is remove it
            if (isspace(*token)) {
                *token = '\0';
            }
        }

        if (execvp(command->tokens[0], command->tokens) == -1) {
            perror("command execution");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("error creating fork\n");
        exit(EXIT_FAILURE);
    } else if (waitForExecution) { // parent proccess must wait only if command to execute do not end with '&'
        // Parent process
        int status;
        
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    
    return 1;
}
