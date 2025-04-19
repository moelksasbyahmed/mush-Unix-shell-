#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#define stdo   STDOUT_FILENO    
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"


void close1 (){
  fopen("test.txt", "w");
  FILE *fp = fopen("test.txt", "w");
  if (fp == NULL) {
    perror("Error opening file");
    exit(1);
  }
  
 // close (stdo);

}            
const char ms []={" you clicked the ctrl +c jjj"};

 void handle_signint(int m ){

 write(stdo,ms,sizeof(ms)-1);

 sleep(10); 
  exit(1);

}
int main(int argc, char *argv[])
{
  close1();
printf(RED );
printf("this is a wooowowowo");
printf(GREEN);

  int rc=fork();
  if(rc==0){
      printf("this is child ");
    while (1){
      printf("this is child ... \n");
     sleep(1);
      signal(SIGINT,handle_signint);
      
    }
  }
  else if(rc>1){
    printf("this is parent");
    wait(NULL);
    printf("the parent is done waiting ");

  }
  else{
    printf("there is an error  ");

  }
  return 0;
}
