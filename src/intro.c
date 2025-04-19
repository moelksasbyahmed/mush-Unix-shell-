#include "../headers/intro.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define clear printf("\033[H\033[J")
#define RESEST "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define Blue "\x1b[34m"
void cursor_handle (int delay_ms){
    for (int i = 0; i < 3; i++) {
        printf("\033[?25l");  
        fflush(stdout);
        usleep(delay_ms * 1000);
        printf("\033[?25h");  
        fflush(stdout);
        usleep(delay_ms * 1000);
    }
}
void clear_screen() {
    clear ;
}
void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}
void type_text(const char *text, int delay_ms) {
    for (int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        fflush(stdout);  
        usleep(delay_ms * 1000); 
    }
}
void intro (){
    clear_screen();
   type_text("HEY THERE ....",100);
   cursor_handle(500);
   move_cursor(5, 25);
   type_text("THIS IS ,",50);
    move_cursor(7, 25);

    type_text("MUSH "RED,50);

    move_cursor(9, 25);
    type_text(RED "MANSOURA SHELL" RESEST ,50);
    cursor_handle(500);
    move_cursor(11,0);
    type_text("CREATED BY :",50);
    move_cursor(13, 25);
    type_text( RED "MOHAMED ELKASABY ",50);
    
    move_cursor(15, 25);
    type_text("EMAIL : mohamed.alkspynm@gmail.com",100);
    cursor_handle(500);
 
    clear_screen();
    type_text(GREEN"PlEASE ENTER YOUR NAME ",10);
    char s[50];
    move_cursor(5,25);
 
    scanf("%49s", s);
    move_cursor(10,32);
char s1[100];
sprintf(s1, "welcome %s", s);

    type_text(s1,50);
    cursor_handle(500);
    clear_screen();


   
 
}

