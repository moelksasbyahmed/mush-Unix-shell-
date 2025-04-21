#ifndef searching_h
#define searching_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
void search_excutable(char **args );
int  execute_command(char **args);
#endif