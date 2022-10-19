#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include "Farbpalette.h"

char START[] =
{ 0x7f, 0x7f, 'F', 'A', 'R', 'B', 'E', 'N', 0x01, 0xcd, 0x00, 0x10, 0xc9 };

// externe ASM Funktionen
extern uint16_t berechneFarbAdr(uint16_t zeileSpalte) __z88dk_fastcall __smallc __z88dk_callee;
extern void setPixel();

// Prototypes
void zeichneVgFarben(uint8_t x, uint8_t vFarbe);
void zeichneHgFarben(uint8_t x, uint8_t hFarbe);
void zeichneBeschriftung();
void zeichneNummer(uint8_t spalte, uint8_t farbNummer, bool_t zweispaltig);
void zeichneKlammern();
void zeichneKlammer(uint16_t x1, uint8_t y1, uint16_t x2, uint8_t y2);
void plotPixel(uint16_t x, uint8_t y, uint16_t farbe);

uint16_t x1;
uint8_t y1;

int main()
{
    textcolor(WHITE);
    textbackground(WHITE);
    clg();
    gotoxy(2, 5);
    if(kc_type)
    {
      cputs("### Die Farbpalette des KC 85/4 ###");
    }
    else
    {
      cputs("### Die Farbpalette des KC 85/3 ###");
    }
    zeichneVgFarben(80, 8);
    zeichneVgFarben(128, 0);
    zeichneHgFarben(176, 0);
    zeichneBeschriftung();
    zeichneKlammern();
    gotoxy(0,29);
    cputs("beenden mit ENTER");
    while(getch() != 10);
    return 0;
}

void zeichneVgFarben(uint8_t x, uint8_t vFarbe)
{
    for( int y = 144; y >= 88; y = y - 8 )
    {
        for( int l = y; l <= y + 3; l++ )
        {
            for( int i = x; i < x + 40; i++ )
            {
                plotPixel(i, l, (vFarbe<<3) | 0x100);
            }
        }
        vFarbe++;
    }
}

void zeichneHgFarben(uint8_t x, uint8_t hFarbe)
{
    for( int y = 144; y >= 88; y = y - 8 )
    {
        for( int l = y; l <= y + 3; l++ )
        {
            for( int i = x; i < x + 40; i++ )
            {
                plotPixel(i, l, hFarbe);
            }
        }
        hFarbe++;
    }
    // Umrandung des weißen Hintergrundes
    drawb(175, 163, 42, 6);
}

void zeichneBeschriftung()
{
    zeichneNummer(7, 8, true);
    zeichneNummer(28, 0, false);
    gotoxy(9,10);
    cputs("Vordergrund- Hintergrund-");
    gotoxy(14,11);
    cputs("farben  farben");
    gotoxy(13,23);
    cputs("Farbnummern");
}

void zeichneNummer(uint8_t spalte, uint8_t farbNummer, bool_t zweispaltig)
{
    for(int l=13; l <= 20; l++)
    {
        gotoxy(spalte,l);
        if(zweispaltig)
          printf("%2d", farbNummer);
        else
          printf("%d", farbNummer);
        farbNummer++;
    }
}

void zeichneKlammern()
{
    zeichneKlammer(77, 107, 170, 101);
    zeichneKlammer(174, 107, 218, 101);
    zeichneKlammer(52, 166, 122, 173);
    zeichneKlammer(126, 166, 234, 173);
}

void zeichneKlammer(uint16_t x1, uint8_t y1, uint16_t x2, uint8_t y2)
{
    int8_t dy = y1 > y2 ? 2 : -2;
    draw(x1,   y1,    x1,   y2+dy);
    draw(x1,   y2+dy, x1+2, y2);
    draw(x1+2, y2,    x2-2, y2);
    draw(x2-2, y2,    x2,   y2+dy);
    draw(x2,   y2+dy, x2,   y1);
}

void plotPixel(uint16_t x, uint8_t y, uint16_t farbe)
{
    if((farbe & 0xff00) > 0)
    {
        HOR = x;
        VERT = y;
        FARB = farbe & 0xf8;
        setPixel();
    }
    else
    {
        uint8_t *farbAdr = (uint8_t *)berechneFarbAdr( ((255-y) *256) | x>>3 );
        outp(0x84, 0x2a);
        *farbAdr = (uint8_t)farbe;
        outp(0x84, 0x28);
    }
}

