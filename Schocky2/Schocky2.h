#include <stdlib.h>

#define DEBUG false

//
// externe Daten
//

/** Zeiger auf die Zeichentabelle */
extern uint8_t ZEITAB;

/** Adresse ab der die Ball Pixeldaten / die Ball Sprites stehen. */
extern uint8_t BALL;

/** Adresse ab der die Ball Pixeldaten für die Todesanimation stehen. */
extern uint8_t BALL_TOT;

/** Adresse ab der die Räume im Speicher stehen. */
extern uint8_t RAUM_DATA;

extern uint32_t LAST_RECORD;

// Länge eines Raums Bytes
#define RLAENGE 0x120

// Offset im Raum zu prüfen ob an der Stelle ein gültiger Raum ist
#define RAUM_CHECK      0x0100
// Offset im Raum mit der Start-Position des Balls im IRM, 2 Bytes
#define RAUM_BALL_POS   0x0101
// Offset im Raum mit dem Farbbyte (für den Ball / Raum)
#define RAUM_COLOR      0x0103
// Prüfziffer ob es sich um einen Raum handelt
#define RAUM_CHECK_VALUE 0x042

// Bewegungsrichtung des Balls: Hoch
#define BALL_RICHTUNG_UP 0
// Bewegungsrichtung des Balls: Runter
#define BALL_RICHTUNG_DOWN 1
// keine horizontale Bewegung
#define BALL_HORIZONTAL_NEUTRAL 0
// Bewegungsrichtung des Balls: Rechts
#define BALL_HORIZONTAL_RECHTS 1
// Bewegungsrichtung des Balls: Links
#define BALL_HORIZONTAL_LINKS 2

//
// externe (ASM) Funktionen
//

/** Rücksprung zum CAOS */
extern void CAOS_RESET();

/** CLS mittels CAOS Aufruf. */
extern void CAOS_CLS();

/** Initialisiert window 0 mit maximaler Größe */
extern void INIT_WINDOW();

/** Gibt ein Zeichen mittels CAOS aus. */
extern void CAOS_PRINT_CH(uint8_t ch)
__z88dk_fastcall;

/** Gibt einen String mittels CAOS UP 23h aus */
extern void CAOS_PRINT_STRING(char *string)
__z88dk_fastcall;

/** Ausgabe des HEX-Strings für das übergebene Zeichen */
extern void CAOS_AHEX(uint8_t ch)
__z88dk_fastcall;

/** Ausgabe des HEX-Strings für das übergebene 16 Bit Wort */
extern void CAOS_HLHX(uint16_t wort)
__z88dk_fastcall;

extern void CAOS_TON_FIX(uint16_t ton1, uint16_t ton2)
__z88dk_callee;

extern void CAOS_TON(uint16_t ton1, uint16_t ton2, uint16_t dauerLautstaerke)
__z88dk_callee;

