#ifndef __UTILS__H
#define __UTILS__H

#include <unistd.h>
#include <pwd.h>
#include <string.h>

void print_prompt();
void clearScreen();
char* home_directory();

#endif