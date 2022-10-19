                EXTERN kc_type

                PUBLIC berechneFarbAdr
                PUBLIC _berechneFarbAdr
                PUBLIC setPixel
                PUBLIC _setPixel
                PUBLIC _HOR
                PUBLIC _VERT
                PUBLIC _FARB
                PUBLIC _kc_type
                
                INCLUDE "target/kc/def/caos.def"

defc    _HOR    = HOR;
defc    _VERT   = VERT;
defc    _FARB   = FARB;
defc    _kc_type   = kc_type;

                
; Berechnet die Adresse des Farbspeichers
; IN:  HL       Zeile und Spalte
; OUT: HL       Adresse im Farbspeicher
;
berechneFarbAdr:
_berechneFarbAdr:
        ld      D,0
        call    PV1
        db      FNPADR
        LD      A,D
        CMP     0       ; beim KC85/4 bleibt Register D auf 0 und HL enthält die Adr im Farbspeicher
        JR      Z,end   ; beim KC85/3 ist in DE die Adresse im Farbspeicher
        LD      HL,DE
end:    RET


; Ruft die CAOS Funktion zum setzen eines Bildpunktes auf, die Parameter werden aus den IRM Arbeitszellen HOR, VERT und FARB entnommen
;
setPixel:
_setPixel:
        LD      A,(IY + 1)
        RES     1,A
        LD      (IY + 1),A
        OUT     (0x84),a
        call    PV1
        db      FNPUSE
        RET