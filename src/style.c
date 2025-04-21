#include "../headers/style.h"
#include <stdlib.h>
#include <stdio.h>

void shell_style(){
   // printf("\033[H");
    char cwd [1024];
    printf(RED"MANSOURA SHELL :"RESEST);
    if(getcwd(cwd, sizeof(cwd)) != NULL) {
        printf(RED"%s >"RESEST , cwd);
    } else {
        perror("getcwd() error");
    }
   
    fflush(stdout);
}