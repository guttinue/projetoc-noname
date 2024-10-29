#include <stdio.h>
#include "../include/screen.h"

void clrscr() {
    printf("\e[1;1H\e[2J");
}

void gotoxy(int x, int y) {
    printf("\e[%d;%dH", y, x);
}

void hidecursor() {
    printf("\e[?25l");
}

void showcursor() {
    printf("\e[?25h");
}