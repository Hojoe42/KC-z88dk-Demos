#include <stdlib.h>

// IX Arbeitszellen
extern uint8_t TAST_KEY;

extern uint8_t VIDEO1;
extern uint8_t VIDEO0;

// Monitor RAM Arbeitszellen
extern uint8_t ARGC;
extern uint8_t ARGN;
extern uint16_t ARG1;
extern uint16_t ARG2;
extern uint16_t ARG3;
extern uint16_t ARG4;

extern uint16_t CURSO;
extern uint8_t STBT;
extern uint8_t COLOR;
extern uint16_t WEND;
extern uint16_t CCTL0;
extern uint16_t CCTL1;
extern uint16_t CCTL2;
extern uint16_t CCTL3;

#define FARBE_VG_BLAU      (1 << 3)
#define FARBE_VG_ROT       (2 << 3)
#define FARBE_VG_PURPUR    (3 << 3)
#define FARBE_VG_GRUEN     (4 << 3)
#define FARBE_VG_TUERKIES  (5 << 3)
#define FARBE_VG_GELB      (6 << 3)
#define FARBE_VG_WEISS     (7 << 3)

#define FARBE_HG_SCHWARZ   0
#define FARBE_HG_BLAU      1
#define FARBE_HG_ROT       2
#define FARBE_HG_PURPUR    3
#define FARBE_HG_GRUEN     4
#define FARBE_HG_TUERKIES  5
#define FARBE_HG_GELB      6
#define FARBE_HG_GRAU      7

#define FARBE_BLAU_WEISS       0x00F
#define FARBE_ROT_WEISS        0x017
#define FARBE_GRUEN_WEISS      0x027
#define FARBE_GELB_WEISS       0x037
#define FARBE_VIOLETT_WEISS    0x04F
#define FARBE_TUERKIES_WEISS   0x02F
#define FARBE_ORANGE_WEISS     0x057
#define FARBE_SCHWARZ_SCHWARZ  0
