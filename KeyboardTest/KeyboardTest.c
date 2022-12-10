#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>


char START[] = {0x7f, 0x7f, 'K', 'E', 'Y', 'T', 'E', 'S', 'T', 0x01, 0xcd, 0x00, 0x10, 0xc9};

// function prototyps
void test_fgetc();
void test_fgets();
void test_gets();
void test_fgetc_cons();
void test_fgets_cons();
void test_getk();


int main()
{
    test_fgetc();
    test_fgetc_cons();
    test_fgets();
    test_gets();
    test_fgets_cons();
    test_getk();
    return 0;
}

/**
 * Zeichen mit Echo von der Console lesen, wartet bis ein Zeichen da ist
 */
void test_fgetc()
{
    uint8_t ch;
    clrscr();
    cputs("     fgetc() Test\n");
    cputs("\n");
    cputs("Abbruch mit x\n");
    cputs("schreibe etwas\n");
    gotoxy(1,6);
    cputs("Eingabe: ");
    while(true)
    {
        ch = fgetc(stdin);
//        ch = getchar(); // getchar() geht auf fgetc(stdin)
        if( ch == 'x' )
        {
            break;
        }
    }
    return;
}

/**
 * Zeichen (ohne Echo?) von der Console lesen, wartet bis ein Zeichen da ist
 */
void test_fgetc_cons()
{
    uint8_t ch;
    clrscr();
    cputs("     fgetc_cons() Test\n");
    cputs("\n");
    cputs("Abbruch mit x\n");
    cputs("schreibe etwas\n");
    gotoxy(1,6);
    cputs("Eingabe: ");
    while(true)
    {
        ch = fgetc_cons();
        putchar(ch);
        if( ch == 'x' )
        {
            break;
        }
    }
    return;
}

void test_fgets()
{
    char cbuf[10];
    clrscr();
    cputs("     fgets() Test\n");
    cputs("\n");
    cputs("Abbruch mit x\n");
    cputs("schreibe etwas\n");
    gotoxy(1,6);
    while(true)
    {

        cputs("Eingabe: ");
        fgets(cbuf, 10, stdin);
        puts(cbuf);
        if( cbuf[0] == 'x' )
        {
            break;
        }
    }
    return;
}

void test_gets()
{
    char cbuf[256];
    clrscr();
    cputs("     gets() Test\n");
    cputs("\n");
    cputs("Abbruch mit x\n");
    cputs("schreibe etwas\n");
    gotoxy(1,6);
    while(true)
    {
        cputs("Eingabe: ");
        gets(cbuf);
        puts(cbuf);
        if( cbuf[0] == 'x' )
        {
            break;
        }
    }
    return;
}

void test_fgets_cons()
{
    char cbuf[10];
    clrscr();
    cputs("     fgets_cons() Test\n");
    cputs("\n");
    cputs("Abbruch mit x\n");
    cputs("schreibe etwas\n");
    gotoxy(1,6);
    while(true)
    {

        cputs("Eingabe: ");
        fgets_cons(cbuf, 10);
        puts(cbuf);
        if( cbuf[0] == 'x' )
        {
            break;
        }
    }
    return;
}

/**
 * getk() liefert die grade gedrückte Taste, ohne zu warten. Wird gerade keine Taste gedrückt wird 0 geliefert.
 */
void test_getk()
{
    uint8_t ch;
    clrscr();
    cputs("     getk Test\n");
    cputs("\n");
    cputs("Abbruch mit x\n");
    cputs("druecke eine Taste\n");
    while(true)
    {
        gotoxy(1,6);
        ch = getk();
        cputs("Zeichen: ");
        putchar((ch < 0x20) ? ' ' : ch);
        gotoxy(1,7);
        cprintf("Code:   %3d", ch);
        if( ch == 'x' )
        {
            // das x noch lesen, damit es später nicht stört
            fgetc_cons();
            break;
        }
    }
    return;
}
