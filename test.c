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

int main(int argc, char *argv[])
{
  int rc=fork();
  if(rc==0){
char input[100];
 //intro();
 char **args;
while(1){
  shell_style();
 args=tokenization(); 
 for(int i=0;args[i]!=NULL;i++){
  
printf("%s\n",args[i]);
}
search_excutable(args);
 

free(args);
 

}
  }
  else{
    wait(NULL);
  }

  return 0;
}
