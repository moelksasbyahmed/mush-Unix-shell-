#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "headers/intro.h"
#include "headers/style.h"
#include "src/intro.c"
#include "src/style.c"
#include "headers/searching.h"
#include "src/searching.c"

#include "src/input.c"
#include "headers/input.h"
FILE *f=NULL;
void bash_mode (char * argv ){
  f =fopen(argv, "r");
  if (f == NULL) {
    perror("Error opening file");
    exit(1);
  }
  dup2(fileno(f), STDIN_FILENO);
  bashmode=true;
}
 void handle_signint(int sig) {
    if (current_child_pid != -1) {
        kill(current_child_pid, SIGINT);
    }
 
  
  }


int main(int argc, char *argv[])
{
  signal(SIGINT, handle_signint);

if(argc>1){
  bash_mode(argv[1]);
  printf("this is a bash mode");
}
  

intro();
clear_screen();
  

 
 char **args;
while(1){

  shell_style();
 args=tokenization(); 
 
if(args==NULL){
  if(bashmode){
    break;
  }
  else{
   continue ;
  }

}

 search_excutable(args);



for(int i =0;args[i]!=NULL;i++){
  free(args[i]);
}
free(args);
}



  return 0;
}
