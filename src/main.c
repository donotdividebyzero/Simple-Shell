#include <stdlib.h>
#include "utils.h"
#include "history.h"
#include "command.h"


int main(int argc, const char * argv[])
{
    clearScreen();
    print_prompt();
    register_history_hook();

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* stream;

    if (argc > 1) { // run as script file
        stream = fopen(argv[1], "r");
    } else {
        stream = stdin; //standart input
    }

    Command* command;

    while ((read = getline(&line, &len, stream)) != -1) {
        command = parse_command(line);
        if (command != NULL) {
            char* newCommandStringNameReference = (char*)malloc(strlen(line) * sizeof(char));
            strcpy(newCommandStringNameReference, line);
            command->command = newCommandStringNameReference;
            push_command_to_history(command, 1);
            execute_command(command);
            print_prompt();
        }
    }

    free(line);
    fclose(stream);

    return 0;
}