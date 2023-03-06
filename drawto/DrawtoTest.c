#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <graphics.h>

char START[] = {0x7f, 0x7f, 'D', 'R', 'A', 'W', 'T', 'O', 0x01, 0xcd, 0x00, 0x10, 0xc9};

void drawSquare()
{
    setpos(50, 50);
    drawto(50, 100);
    sleep(1);
    drawto(100, 100);
    sleep(1);
    drawto(100, 50);
    sleep(1);
    drawto(50, 50);
}

int main()
{
    clrscr();
    drawSquare();
    return 0;
}
