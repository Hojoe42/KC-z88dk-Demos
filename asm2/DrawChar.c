
char START[] = {0x7f, 0x7f, 'A', 'S', 'M', '2', 0x01, 0xcd, 0x00, 0x10, 0xc9};

extern void drawChar(char index) __z88dk_fastcall;

/** Gibt HALLO an der aktuellen Cursorposition aus */
int main()
{
    drawChar('H');
    drawChar('A');
    drawChar('L');
    drawChar('L');
    drawChar('O');
    return 0;
}

