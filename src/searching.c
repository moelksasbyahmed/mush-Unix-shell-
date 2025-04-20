#include "../headers/searching.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <errno.h>
void search_excutable(char **args){
    for(int i=0;args[i]!=NULL;i++){
        if(strcmp(args[i],"exit")==0){
            free(args);
            exit(0);
        }
        if(strchr(args[i],'/')!=NULL){
       if(access(args[i],X_OK)==0){
         printf("Executable file found: %s\n", args[i]);
       
       }
       else{
         printf("Not an executable file: %s\n", args[i]);
       
       
       
       }
     }
     else{
       const char *paths []={"/bin", "/usr/bin", "/usr/local/bin","~/shell/commands"};
       
       char full_path[256];
       int found = 0;
       for(int j =0;j<sizeof(paths)/sizeof(paths[0]);j++){
         snprintf(full_path, sizeof(full_path), "%s/%s", paths[j], args[0]);
         if(access(full_path, X_OK)==0){
            pid_t pid = fork();
    if (pid == 0) {
        execv(full_path, args);
        perror("execv failed");  
        exit(EXIT_FAILURE);
    }
     else if (pid > 0) {
    found=1;
        wait(NULL); 
      break;
    } else {
        perror("fork failed");
    }
     
     
     
     
     }
     else{
            printf("Not an executable file: %s\n", full_path);
        }
     }
    
  
  
       }
     
   }
 
    }
