#ifndef intro_h
#define intro_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define clear printf("\033[H\033[J")

void clear_screen();
void move_cursor(int row, int col);
void type_text(const char *text, int delay_ms);
void intro();
void cursor_handle (int delay_ms);
#endif

