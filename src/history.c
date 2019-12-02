#include "history.h"
#include "utils.h"

Command* head;

char* history_file()
{
    return strcat(home_directory(), ".velsh_history");
}

void register_history_hook() {
    load_history();
    signal(SIGQUIT, print_history);
}

void print_history() {
    Command* conductor = head;

    while(conductor->next != NULL) {
        printf("%s", conductor->command);
        conductor = conductor->next;
    }

    printf("%s", conductor->command);
    print_prompt();
}

void push_command_to_history(Command* comm, int persist) {
    if (head == NULL) {
        head = comm;

        if (persist) {
            dump_history_to_file();
        }
        return;
    }

    Command* conductor = head;
    int counter = 1;

    while(conductor->next != NULL) {
        counter++;
        conductor = conductor->next;
    }

    conductor->next = comm;

    if (counter >= MAX_HISTORY_SIZE) {
        head = head->next;
    }

    if(persist) {
        dump_history_to_file();
    }
}

void push_to_history(char* command) {
    if (command == NULL) {
        return;
    }

    if (isspace(*command)) {
        return;
    }

    Command* comm = malloc( sizeof(Command) );
    char* newCommandStringNameReference = (char*)malloc(strlen(command) * sizeof(char));
    strcpy(newCommandStringNameReference, command);
    comm->command = newCommandStringNameReference;
    comm->next = NULL;

    push_command_to_history(comm, 0);
}


/**
 * @TODO fix history cleanup - history lined list is not freeing memory 
 */
void history_cleanup() {
    Command* conductor = head;
    Command* tmp;

    while(conductor != NULL) {
        tmp = conductor->next;
        free(conductor);
        conductor = tmp;
    }

    head = NULL;
}

void load_history()
{
    FILE *f = fopen(history_file(), "r");
 
    if (f == NULL) return; // just return because there is nothing to load

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, f)) != -1) {
        push_to_history(line);
    }

    fclose(f);
}

void dump_history_to_file()
{
    FILE *f = fopen(history_file(), "w");

    if (f == NULL) {
        printf("Error opening history file!\n");
        exit(1);
    }

    Command* conductor = head;

    while(conductor->next != NULL) {
        fprintf(f, "%s", conductor->command);
        conductor = conductor->next;
    }

    fprintf(f, "%s\n", conductor->command);
    fclose(f);
}