#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>


char START[] = {0x7f, 0x7f, 'G', 'E', 'T', 'K', 0x01, 0xcd, 0x00, 0x10, 0xc9};

uint8_t getSomething();
uint8_t something;

int main()
{
    something = 0;
    while(true)
    {
        uint8_t x = getSomething();
        uint8_t ch = getk();
        gotoxy(0, 0);
        cprintf("something: %d  und ch: %d  ", x, ch);
        if( ch == 'X')
        {
            gotoxy(0, 30);
            cputs("ENDE");
            break;
        }
        else if( ch == 'H')
        {
            gotoxy(0, 1);
            cputs("Hello World");
        }
    }
    return 0;
}
uint8_t getSomething()
{
    return something++;
}
