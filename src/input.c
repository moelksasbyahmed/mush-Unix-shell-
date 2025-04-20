#include "../headers/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_ARGS 100

char **tokenization() {
    char *line = NULL;
    size_t len = 0; 
    ssize_t read;
    
  
    char **args = malloc(MAX_ARGS * sizeof(char *));
    if (!args) {
        perror("malloc failed");
        return NULL;
    }
    

    if ((read = getline(&line, &len, stdin)) == -1) {
        free(args);
        return NULL;  
    }

   
    if (read > 0 && line[read-1] == '\n') {
        line[read-1] = '\0';
    }

  
    char *temp = line;
    char *token;
    int arg_count = 0;
    const char *delim = " \t\n";
    
    while ((token = strsep(&temp, delim)) != NULL) {
        if (*token == '\0') continue;  

        if (arg_count >= MAX_ARGS - 1) {
            fprintf(stderr, "Error: Too many arguments\n");
            free(line);
            free(args);
            return NULL;
        }
        if(strcmp(token, "exit") == 0) {
            free(line);
            free(args);
            exit(0); 
        }
        
        args[arg_count++] = token;
    }
    
    args[arg_count] = NULL;  
     
  
    return args;
}