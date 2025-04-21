#include "../headers/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h> 
#define MAX_ARGS 100
bool  bashmode = false;

char **tokenization() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    char **args = malloc(MAX_ARGS * sizeof(char *));
    if (!args) {
        perror("malloc failed");
        return NULL;
    }

    read = getline(&line, &len, stdin);
    if (read == -1) {
        if (bashmode) {
            free(line);
            return NULL;
        } else {
            free(args);
            free(line);
            return NULL;
        }
    }

    if (read > 0 && line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }
char *spaced_line =malloc (len*2);
int j=0;
for(int i =0;line[i]!='\0';i++){
    if(line[i]=='>'){
        spaced_line[j++]=' ';
        spaced_line[j++]='>';
        spaced_line[j++]=' ';
    }
    else{
        spaced_line[j++]=line[i];
    }

}
spaced_line[j]='\0';
    char *temp = spaced_line;
    char *token;
    int arg_count = 0;
    const char *delim = " \t\n";

    while ((token = strsep(&temp, delim)) != NULL) {
        if (*token == '\0') continue;

        if (arg_count >= MAX_ARGS - 1) {
            fprintf(stderr, "Error: Too many arguments\n");
            free(line);
            for (int i = 0; i < arg_count; i++) free(args[i]);
            free(args);
            return NULL;
        }

        args[arg_count++] = strdup(token); 
    }

    args[arg_count] = NULL;
    free(line);
    free(spaced_line); 
    return args;
}