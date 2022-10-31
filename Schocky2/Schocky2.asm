INCLUDE  "target/kc/def/caos.def"

        PUBLIC _LAST_RECORD
        PUBLIC _CAOS_RESET
        PUBLIC _CAOS_CLS
        PUBLIC _INIT_WINDOW
        PUBLIC _CAOS_PRINT_CH
        PUBLIC _CAOS_PRINT_STRING
        PUBLIC _CAOS_AHEX
        PUBLIC _CAOS_HLHX
        PUBLIC _CAOS_TON
        PUBLIC _CAOS_TON_FIX

; im letzten Versuch gesammelte Punkte
_LAST_RECORD:
                DB      000H, 000H, 00H, 00H

; Rücksprung zum CAOS (RESET)
_CAOS_RESET:
                CALL    0F003H
                DB      0DH

; Bildschirm löschen
_CAOS_CLS:
                CALL    0F003H
                DB      023H            ; String Ausgabe
                DB      0CH             ; CLS
                DB      0
                RET
                
; Initialisiert das Fenstern 0, mit Start 0,0 und Größe 32,40
; und aktiviert es
_INIT_WINDOW:
                LD      HL,0
                LD      DE,02028H
                LD      A,0
                CALL    0F003H
                DB      03CH
                LD      A,0
                CALL    0F003H
                DB      03DH
                RET

; gibt das Zeichen in Register L aus
_CAOS_PRINT_CH:
                LD      A,L
                CALL    0F003H
                DB      000H            ; Zeichen Ausgabe
                RET

; gibt den 0 terminierten (max 255 Zeichen langen) String aus, auf den Register HL zeigt
_CAOS_PRINT_STRING:
                LD      DE,START_STRING
PRINT_STRING_1: LD      A,(HL)
                LD      (DE),A
                INC     HL
                INC     DE
                CMP     A,0
                JR      NZ,PRINT_STRING_1
                LD      A,0C9H
                LD      (DE),A
                CALL    0F003H
                DB      023H
START_STRING:   DEFS    0FFH, 0
                DB      000H
                RET

; gibt die übergebene 8-Bit Zahl als HEX String aus
; siehe CAOS UP 1C: AHEX
_CAOS_AHEX:
                LD      A,L
                CALL    0F003H
                DB      1Ch
                RET

; gibt die übergebene 16- Bit Zahl als Hex String aus
; siehe CAOS UP 1A: HLHX
_CAOS_HLHX:
                CALL    0F003H
                DB      1Ah
                RET

;; Gibt einen Ton mit voller Lautsärke und fester Dauer von 60 ms aus
_CAOS_TON_FIX:
                POP     HL              ; Rücksprungadresse
                POP     BC              ; Kanal 1 Tonhöhe
                POP     DE              ; Kanal 2 Tonhöhe
                PUSH    HL              ; Rücksprung Adresse wieder auf den Stack
                LD      (ARG1),BC
                LD      (ARG2),DE
                LD      HL,031fH
                LD      (ARG3),HL
                CALL    0F003H
                DB      35h
                RET

_CAOS_TON:
                POP     HL              ; Rücksprungadresse
                POP     BC              ; Param 3: Dauer / Lautstärke
                LD      (ARG3),BC
                POP     BC              ; Param 2: Kanal 2 Tonhöhe
                LD      (ARG2),BC
                POP     BC              ; Param 1: Kanal 1 Tonhöhe
                LD      (ARG1),BC
                PUSH    HL              ; Rücksprung Adresse wieder auf den Stack
                CALL    0F003H          ; CAOS UP: TON
                DB      35h
                RET

                