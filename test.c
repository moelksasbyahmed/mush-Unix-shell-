#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "headers/intro.h"
#include "headers/style.h"
#include "src/intro.c"
#include "src/style.c"
int main(int argc, char *argv[])
{
char input[100];
 intro();
while(1){
  shell_style();
  if (fgets(input, sizeof(input), stdin) == NULL) {
    break;  // Exit on EOF (Ctrl+D)
}

// Process input here
printf("You entered: %s", input);
}
  return 0;
}
