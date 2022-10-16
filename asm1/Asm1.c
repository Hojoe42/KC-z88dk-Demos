
char START[] = {0x7f, 0x7f, 'A', 'S', 'M', '1', 0x01, 0xcd, 0x00, 0x10, 0xc9};

void drawChar1(char ch);
void drawChar2(char ch) __naked __z88dk_fastcall;

int main()
{
    drawChar1('H');
    drawChar1('A');
    drawChar2('L');
    drawChar2('L');
    drawChar2('O');
    return 0;
}

void drawChar1(char ch)
{
#asm
        POP     DE      ; Rücksprungadresse
        POP     HL      ; Parameter
        PUSH    HL
        PUSH    DE
        ld      A,L
        call    0f003H
        db      0
#endasm
}

void drawChar2(char ch) __naked __z88dk_fastcall
{
#asm
        ld      A,L
        call    0f003H
        db      0
        ret
#endasm
}
