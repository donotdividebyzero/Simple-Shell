#include "utils.h"

void print_prompt()
{
    const char* PROMPT = "\n[velsh]#:";
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

void clearScreen()
{
  const char* CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, strlen(CLEAR_SCREEN_ANSI));
}

char* home_directory() 
{
    struct passwd *pw = getpwuid(getuid());
    return strcat(pw->pw_dir, "/");
}