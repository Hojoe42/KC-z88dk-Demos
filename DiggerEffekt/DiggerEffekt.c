#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>

// prototypes
void setCtc();
void anzeigeInit();
void ctcAnzeigen();
void diamanten();
void diamant(uint8_t chx, uint8_t chy);
void line(uint16_t x, uint8_t y, uint8_t laenge, uint8_t farbe);
void reset();

#define GELB 0xb0
#define ORANGE 0xd0
// Wartezeit in Millisekunden nach einem Tastendruck
#define WAIT 250

char const START[] = { 0x7f, 0x7f, 'D', 'E', 'F', 'F', 'E', 'K', 'T', 0x01, 0xcd, 0x00, 0x10 };

uint8_t const *ARGN = 0xb781;
uint16_t const *ARG1 = 0xb782;
uint16_t const *ARG2 = 0xb784;
uint16_t const *ARG3 = 0xb786;
uint16_t const *ARG4 = 0xb788;
uint8_t const *FARB = 0xb7d6;

uint8_t ctcSteuerbyte = 0x05;
uint8_t ctcKonstante = 0x21;

int main()
{
    anzeigeInit();
    setCtc();
    uint8_t *TAST_KEY = 0x1fd;
    while( true )
    {
        uint8_t ch = *TAST_KEY;
//        gotoxy(0,0);
//        printf("%2X",ch);
        if( ch == 'b' || ch == 'B' )
        {
            break;
        }
        else if( ch == 0x08 )
        {
            ctcKonstante -=0x10;
            setCtc();
        }
        else if( ch == 0x09 )
        {
            ctcKonstante +=0x10;
            setCtc();
        }
        else if( ch == 0x0a )
        {
            ctcKonstante--;
            setCtc();
        }
        else if( ch == 0x0b )
        {
            ctcKonstante++;
            setCtc();
        } 
        else if( ch == 'z' || ch == 'Z' )
        {
            if((ctcSteuerbyte & 0x40) == 0x40)
            {
                ctcSteuerbyte = ctcSteuerbyte & 0xBF;
            }
            else
            {
                ctcSteuerbyte = ctcSteuerbyte | 0x40;                
            }
            setCtc();
        }
        else if( ch == 'c' || ch == 'C' )
        {
            ctcSteuerbyte = 0x45;
            ctcKonstante = 0x0c;
            setCtc();
        }
        else if( ch == 'd' || ch == 'D' )
        {
            ctcSteuerbyte = 0x05;
            ctcKonstante = 0x21;
            setCtc();
        }
        if(ch != 0)
        {
            msleep(WAIT);                
        }
        
    }
    reset();
    return 0;
}

void setCtc()
{
//    outp(0x8e, 0x07);
    outp(0x8e, ctcSteuerbyte);
    outp(0x8e, ctcKonstante);        
    ctcAnzeigen();
}

void ctcAnzeigen()
{
    gotoxy(20, 28);
    if((ctcSteuerbyte & 0x40) == 0x40)    
    {
        cputs("Zaehler   ");
    }
    else
    {
        cputs("Zeitgeber");
    }
    gotoxy(20, 29);
    if((ctcSteuerbyte & 0x20) == 0x20)    
    {
        cputs("Teiler 256");
    }
    else
    {
        cputs("Teiler 16 ");
    }
    // Zeitkonstante
    gotoxy(20, 30);
    printf("%2X",ctcKonstante);
}

void anzeigeInit()
{
    textcolor(7);      // white
    textbackground(1); // blue    
    clrscr();
    gotoxy(10, 1);
    cputs("Der Digger Effekt");
    gotoxy(2,3);
    cputs("Programm beenden:           <B>");
    gotoxy(2,4);                       
    cputs("CTC Zeitkonstante plus   1: <Hoch>");
    gotoxy(2,5);                       
    cputs("CTC Zeitkonstante minus  1: <Runter>");
    gotoxy(2,6);                       
    cputs("CTC Zeitkonstante plus  16: <Rechts>");
    gotoxy(2,7);                       
    cputs("CTC Zeitkonstante minus 16: <Links>");
    gotoxy(2,8);
    cputs("Zaehler / Zeitgeber:        <Z>");
    gotoxy(2,9);                       
    cputs("CAOS Einstellungen:         <C>");
    gotoxy(2,10);                       
    cputs("Digger Einstellungen:       <D>");
    diamanten();
    gotoxy(2,28);
    cputs("CTC:");
    gotoxy(2,30);
    cputs("CTC Zeitkonstante:");    
}

void diamanten()
{
        uint8_t const x = 16;
        uint8_t const y = 14;
        diamant(x, y);
        diamant(x-2, y+2);diamant(x+2, y+2);
        diamant(x-4, y+4);diamant(x+4, y+4);
        diamant(x-6, y+6);diamant(x+6, y+6);
        diamant(x-4, y+8);diamant(x+4, y+8);
        diamant(x-2, y+10);diamant(x+2, y+10);
        diamant(x, y+12);
}

// x und y in Zeichen Koordinaten 0-39, 0-32
void diamant(uint8_t chx, uint8_t chy)
{
#asm
        // die Grafik Libs vom z88dk schalten nicht korrekt auf die Pixelebene zurück, 
        // daher hier, vor einem CAOS Aufruf, auf die Pixelebene umschalten
        PUSH    AF
        LD      A,(IY+1)
        AND     A,0xfd  // Pixel Zugriff
        LD      (IY+1),A
        OUT     (084H),A
        POP     AF
#endasm
    uint16_t x = chx * 8;
    uint16_t y = (32 - chy) * 8;
    y++;
    line(x+6, y, 3, ORANGE);
    y++;
    line(x+5, y, 5, ORANGE);
    y++;
    line(x+4, y, 1, ORANGE);
    line(x+10, y, 1, ORANGE);
    y++;
    line(x+3, y, 9, ORANGE);
    y++;
    line(x+2, y, 11, GELB);
    y++;
    line(x+1, y, 1, GELB);
    line(x+13, y, 1, GELB);
    y++;
    line(x+0, y, 15, GELB);
    y++;
    line(x+0, y, 15, GELB);
    y++;
    line(x+0, y, 2, ORANGE);
    line(x+13, y, 2, ORANGE);
    y++;
    line(x+1, y, 13, ORANGE);
    y++;
    line(x+2, y, 11, ORANGE);
    y++;
    line(x+3, y, 9, ORANGE);
    y++;
    line(x+4, y, 1, GELB);
    line(x+10, y, 1, GELB);
    y++;
    line(x+5, y, 5, ORANGE);
    y++;
    line(x+6, y, 3, ORANGE);
}

// x und y in Pixel Koordinaten
void line(uint16_t x, uint8_t y, uint8_t laenge, uint8_t farbe)
{
    *ARG1 = x;
    *ARG2 = y;
    *ARG3 = x+laenge-1;
    *ARG4 = y;
    *FARB = farbe;
#asm
        call    0f003H
        db      0x3e  // Line
#endasm
}

void reset() __naked __z88dk_fastcall
{
#asm
        call    0f003H
        db      0x0d
        ret
#endasm
}