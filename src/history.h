#ifndef __HISTORY__H
#define __HISTORY__H

#include <stdlib.h>
#include "utils.h"
#include <signal.h>
#include <stdio.h>
#include <ctype.h>
#include "command.h"

#define MAX_HISTORY_SIZE 20

struct Command;

void register_history_hook();

void push_to_history(char* command);
void push_command_to_history(Command* comm, int persist);

void print_history();

void dump_history_to_file();
void load_history();

char* histofy_file();


void history_cleanup();

#endif
