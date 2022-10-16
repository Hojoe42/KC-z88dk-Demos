
        PUBLIC drawChar
        PUBLIC _drawChar

        INCLUDE "target/kc/def/caos.def"

; Funktion drawChar
;
; gibt das im Register L übergebene Zeichen mittels der CAOS CRT Funktion aus
;
.drawChar
._drawChar
        ld      A,L
        call    PV1
        db      FNCRT
        ret

