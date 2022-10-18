#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <graphics.h>
#include <conio.h>

char START[] =
{ 0x7f, 0x7f, 'C', 'L', 'S', 'T', 'E', 'S', 'T', 0x01, 0xcd, 0x00, 0x10, 0xc9 };

int main()
{
    gotoxy(1, 2);
    cputs("vor clg() with 'default' white on black");
    sleep(2);
    clg();

    gotoxy(1, 3);
    textcolor(7);      // white
    textbackground(1); // blue
    cputs("some text - white on blue");
    sleep(2);

    gotoxy(1, 4);
    cputs("before clrscr()");
    sleep(2);
    clrscr();

    gotoxy(1, 5);
    textbackground(2); // red
    cputs("before clrscr()");
    sleep(2);
    clrscr();

    return 0;
}
