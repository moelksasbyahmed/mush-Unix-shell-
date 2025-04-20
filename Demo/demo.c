#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
   int rc = fork();
   if(rc==0){
    printf("Child process\n");
   
   while(1){
printf(">");
        fflush(stdout);
        
      char *line;
      size_t len = 0;
        ssize_t read;
        if(read = getline(&line, &len, stdin) == -1){
            perror("getline");
       
            free(line);

            exit(EXIT_FAILURE);
        }
      
        char delim[] = " \t\n";
        char *temp=line;
        char *token;
        int args_count = 0;
        char**args = malloc(100 * sizeof(char*)); // Allocate memory for 100 arguments
        if (args == NULL) {
            perror("malloc failed");
            free(line);
            exit(EXIT_FAILURE);
        }
        while((token=strsep(&temp, delim))!=NULL){
            if(*token=='\0') continue;
          args[args_count++]=token;

        }

        for(int i=0;i<args_count;i++){
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
        snprintf(full_path, sizeof(full_path), "%s/%s", paths[j], args[i]);
        if(access(full_path, X_OK)==0){
          printf("Executable file found: %s\n", full_path);
          found = 1;
          break;
        }
      }
    
      if(!found){
        printf("Not an executable file: %s\n", full_path);
      }
    
    
    }
 
 
      }
  }

}
  else if( rc>0){
      printf("Parent process\n");
      wait(NULL);
            // Free allocated memory for args
        }
    
     else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    return 0;
}