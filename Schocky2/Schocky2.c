#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "kc85.h"
#include "Schocky2.h"

// Prototypes
void intro();
bool_t outro();
void mainLoop();
void initGame();
void initRaum();
bool_t playRaum();
void berechnePunkteProStein();
void printRaumCh(uint8_t ch);
void printLeben();
void printRaumNummer();
void printPunkte();
void printMaxPunkte();
void printSteine();
void printBonus();
void printBonusZahl();
void printBonusBuffer();
bool_t isBonusNull();
void decBonus();
void addBonus();
void checkExtraLEben();
void printNumberString();
void moveBall();
void wait();
void printStatus(uint8_t zeile, uint8_t spalte);
void printStatus2();
void totesanimation();
void siegAnimation();
void addTon(uint16_t ton);
void loescheKollisionsFlags();
void kollisionsChecks();
void kollisionUntenCheck();
void kollisionObenCheck();
void kollisionRechtsCheck();
void kollisionLinksCheck();
void kollisionAusfuehren();
void kollisionAusfuehrenCh(uint8_t *chAdr);
void kollisionStein(uint8_t *chAdr, uint8_t spalte, uint8_t zeile);
void kollisionFWechsler(uint8_t *chAdr);
void kollisionDiskette(uint8_t *chAdr, uint8_t spalte, uint8_t zeile);
void tastaturAbfrage();
uint8_t* berechneVRamAdresse(uint8_t *pixelAdr);
uint8_t* berechnePixelRamAdresse(uint8_t *chAdr);
void stringToBcd(uint8_t *string, uint8_t *buffer);
void switchBild0Pixel();
void switchBild0Farbe();
uint8_t getKcFarbe(uint8_t ch);

#define PUNKTE_EXTRA_LEBEN 10000
#define TON_STEIN1 0x120
#define TON_DISKETTE 0x110
#define TON_WAND 0x130
#define TON_FARBWECHSELR 0x110
#define TON_TOT 0x150
#define TON_SIEG 0x0100

char START[] =
{ 0x7f, 0x7f, 'S', 'C', 'H', 'O', 'C', 'K', 'Y', '2', 0x01, 0xcd, 0x00, 0x10 };

uint8_t siegFarben[] =
{ FARBE_VG_ROT, FARBE_VG_BLAU, FARBE_VG_GRUEN, FARBE_VG_PURPUR, FARBE_VG_TUERKIES, FARBE_VG_WEISS, FARBE_SCHWARZ_SCHWARZ, FARBE_VG_GELB,
FARBE_VG_ROT, FARBE_VG_BLAU, FARBE_VG_GRUEN, FARBE_VG_PURPUR, FARBE_VG_TUERKIES, FARBE_VG_WEISS, FARBE_SCHWARZ_SCHWARZ, FARBE_VG_GELB,
FARBE_VG_WEISS, FARBE_VG_WEISS, FARBE_VG_WEISS, FARBE_VG_WEISS, FARBE_VG_WEISS, FARBE_VG_WEISS, FARBE_VG_WEISS, FARBE_VG_WEISS, };

/** Adresse des aktuellen Raums. */
uint8_t *aktuellerRaum;

/** Nummer des Raums / Levels */
uint8_t raumNummer;

/** Anzahl der Steine im aktuellem Raum. */
uint8_t anzahlSteine;

/** Anzahl der Leben. */
uint8_t anzahlLeben;

/** Ist der Ball gerade mit einem Totenkopf kollidiert? */
bool_t kollisionTotenkopf;

/** Aktuelle Byte Position des Balls im Bildspeicher.  */
uint8_t *aktuelleBallPosition;

/**
 * Aktuelle Ball Farbe (Vordergrundfarbe).
 * 0 -> Schwarz
 * 1 -> Blau
 * 2 -> Rot
 * 3 -> Grün
 * 4 -> Gelb
 * 5 -> Violett
 * 6 -> Türkis
 * 7 -> Orange
 */
uint8_t ballFarbe;

/** die Anfangs Positionen des Balls im Bildspeicher. Wenn der Ball nicht genau in eine Spalte passt, dann gibt es die linke und recht Anfangsposition. */
uint8_t *ballPosAlt1;
uint8_t *ballPosAlt2;

/** Die V-RAM Adresse des Balls.  */
uint8_t *ballCharVRam;

/** Zeiger auf das Zeichen im V-Ram bei einer Kollision in der Hauptrichtung, ansonsten 0.*/
uint8_t *chKollHaupt;
/** Zeiger auf das Zeichen im V-Ram bei einer Kollision in der Hauptrichtung, ansonsten 0.*/
uint8_t *chKollNeben;

/** Verschiebung des Balls um X Bit nach rechts. */
uint8_t ballShift;

/** aktuelle / gewünschte Flugrichtung des Balls, entweder BALL_RICHTUNG_UP oder BALL_RICHTUNG_DOWN */
uint8_t ballHochRunter;
/** aktuelle / gewünschte Flugrichtung des Balls, entweder BALL_HORIZONTAL_NEUTRAL, BALL_RICHTUNG_RECHTS oder BALL_RICHTUNG_LINKS */
uint8_t ballRechtsLinks;

bool_t kollisionRechts;
bool_t kollisionLinks;
bool_t kollisionOben;
bool_t kollisionUnten;
bool_t kollisionDiagonal;

bool_t stepMode;
uint8_t stepChar;
bool_t step;

/** Zähler für die Warteschleife nach jedem Ball Schritt. */
int16_t ballStepWaitCount;

/** Temporärer Speicher um die Strings aufzunehmen, die beim Umwanden von Zahlen in Strings entstehen. */
char itoaBuffer[20];

/** gesamten gesammelten Punkte */
uint32_t punkte;

/** beim überschreiten welcher Punktzahl gibt es ein zusätzliches Leben */
uint32_t punkteNextLeben;

/** die Punkte pro Stein innerhalb eines Levels. */
uint8_t punkteProStein;

/** Damit startet der Bonus Countdown pro Level. */
uint16_t startBonus;
/** wenn 0 wird der Bonus um 1 verringert */
uint16_t bonusCountDown;
/** aller wie viel Ballsteps wird der Bonus um 1 herunter gezählt */
uint16_t bonusCountDownStart;
/** die ungepackte BCD Zahl des Bonus */
char bonusBuffer[3];

uint16_t ton1;
uint16_t ton2;

bool_t trainer;
uint8_t startRaum;

// temporäre Variablen (innerhalb von Methoden)
uint8_t tmpZeile;
uint8_t tmpSpalte;
uint8_t *tmpIrmAdr;

void initGame()
{
    // eigene Zeichentabelle hinterlegen
    CCTL2 = (uint16_t) &ZEITAB;
    INIT_WINDOW();
    // Page Modus einschalten
    CAOS_PRINT_CH(0x011);
    ballStepWaitCount = 80;
    bonusCountDownStart = 20;
}

void initRun()
{
    aktuellerRaum = &RAUM_DATA;
    anzahlLeben = 5;
    ballShift = 0;
    punkte = 0;
    punkteNextLeben = PUNKTE_EXTRA_LEBEN;
    raumNummer = 1;
    stepMode = false;
    stepChar = 0;
    step = false;
    startBonus = 400;
    if( trainer )
    {
        while( raumNummer != startRaum )
        {
            aktuellerRaum += RLAENGE;
            raumNummer++;
        }
    }
}

void mainLoop()
{
    while( RAUM_CHECK_VALUE == *(aktuellerRaum + RAUM_CHECK) )
    {
        initRaum();
        msleep(1000);
        bool_t next = playRaum();
        if( next )
        { // nächster Raum
            aktuellerRaum += RLAENGE;
            if( startBonus < 950 )
            {
                startBonus += 50;
            }
            else if( startBonus == 950 )
            {
                startBonus = 999;
            }
            raumNummer++;
        }
        if( anzahlLeben == 0 )
        {
            break;
        }
    }
}

void initRaum()
{
    anzahlSteine = 0;
    COLOR = FARBE_VG_WEISS | FARBE_HG_SCHWARZ;
    CAOS_CLS();
    ballFarbe = *(aktuellerRaum + RAUM_COLOR);
    uint8_t *raum = aktuellerRaum;
    uint8_t i = 0;
    do
    {
        uint8_t ch = *raum++;
        printRaumCh(ch);
        i++;
        if( (i & 0x00F) == 0 ) // Zeilenende erreicht?
        {
            // 2 Zeilen nach unten und zum Zeilenanfang (19h) zurück
            CAOS_PRINT_STRING("\x0a\x0a\x19");
        }
    } while( i != 0 );
    ballHochRunter = BALL_RICHTUNG_UP;
    COLOR = ballFarbe;
    aktuelleBallPosition = *(uint8_t**) (aktuellerRaum + RAUM_BALL_POS);
    ballShift = 0;
    ballRechtsLinks = BALL_HORIZONTAL_NEUTRAL;
    ballPosAlt1 = aktuelleBallPosition;
    ballPosAlt2 = aktuelleBallPosition;
    ballCharVRam = berechneVRamAdresse(aktuelleBallPosition);
    memcpy(aktuelleBallPosition, &BALL, 8);
    berechnePunkteProStein();
    bonusCountDown = bonusCountDownStart;
    itoa(startBonus, itoaBuffer, 10);
    stringToBcd(itoaBuffer, bonusBuffer);
    kollisionTotenkopf = false;
    printLeben();
    printRaumNummer();
    printPunkte();
    printMaxPunkte();
    printSteine();
    printBonus();
    printBonusZahl();
}

bool_t playRaum()
{
    while( anzahlSteine > 0 )
    {
        tastaturAbfrage();
        kollisionsChecks();
        kollisionAusfuehren();
        if( ton1 != 0 )
        {
            CAOS_TON_FIX(ton1, ton2);
            ton1 = 0;
            ton2 = 0;
        }
        if( kollisionTotenkopf )
        {
            anzahlLeben--;
            printLeben();
            totesanimation();
            return false;
        }
        moveBall();
        if( !isBonusNull() )
        {
            bonusCountDown--;
            if( bonusCountDown == 0 )
            {
                decBonus();
                printBonusZahl();
                bonusCountDown = bonusCountDownStart;
            }
        }
        wait();
    }
    siegAnimation();
    addBonus();
    sleep(1);
    return true;
}

void totesanimation()
{
    for( int i = 0; i < 8; i++ )
    {
        memcpy(aktuelleBallPosition, &BALL_TOT + i * 8, 8);
        CAOS_TON_FIX(TON_TOT + (i * 8), 0);
        msleep(200);
    }
}

void siegAnimation()
{
    switchBild0Farbe();
    for( int i = 0; i < sizeof(siegFarben); i++ )
    {
        uint8_t farbe = siegFarben[i];
        if( ballShift == 0 )
        {
            uint8_t *src = aktuelleBallPosition + 6;
            uint8_t *dest = aktuelleBallPosition + 7;
            for( int j = 0; j < 7; ++j )
            {
                *dest-- = *src--;
            }
            *aktuelleBallPosition = farbe;
        }
        else
        {
            uint8_t *src1 = aktuelleBallPosition + 6;
            uint8_t *src2 = aktuelleBallPosition + 0x106;
            uint8_t *dest1 = aktuelleBallPosition + 7;
            uint8_t *dest2 = aktuelleBallPosition + 0x107;
            for( int j = 0; j < 7; ++j )
            {
                *dest1-- = *src1--;
                *dest2-- = *src2--;
            }
            *aktuelleBallPosition = farbe;
            *(aktuelleBallPosition + 0x100) = farbe;
        }
        CAOS_TON(TON_SIEG - (i * 2), 0, 0x0001);
        msleep(60);
    }
    CAOS_TON(0, 0, 0x0101);
    switchBild0Pixel();
}

void kollisionAusfuehren()
{
    kollisionAusfuehrenCh(chKollHaupt);
    kollisionAusfuehrenCh(chKollNeben);
}

void kollisionAusfuehrenCh(uint8_t *chAdr)
{
    if( chAdr == NULL )
    {
        return;
    }
    uint16_t relAdr = chAdr - &VIDEO0;
    uint8_t zeile = (uint8_t) (relAdr / 40);
    uint8_t spalte = relAdr - (uint8_t) (zeile * 40);
    switch( *chAdr )
    {
        case '\xa2': // Totenkopf "\xa2\xa3\x08\x08\x0a\xa4\xa5\x0b"
            kollisionTotenkopf = true;
            break;
        case '\xa3':
            kollisionTotenkopf = true;
            break;
        case '\xa4':
            kollisionTotenkopf = true;
            break;
        case '\xa5':
            kollisionTotenkopf = true;
            break;
        case '\xa8': // Farbwechseler "\xa8\xa9\x08\x08\x0a\xaa\xab\x0b"
            kollisionFWechsler(chAdr);
            break;
        case '\xa9':
            kollisionFWechsler(chAdr);
            break;
        case '\xaa':
            kollisionFWechsler(chAdr);
            break;
        case '\xab':
            kollisionFWechsler(chAdr);
            break;
        case '\xac': // Verschieber "\xac\xad\x08\x08\x0a\xae\xaf\x0b"
            kollisionDiskette(chAdr, spalte, zeile);
            break;
        case '\xad':
            kollisionDiskette(chAdr, --spalte, zeile);
            break;
        case '\xae':
            kollisionDiskette(chAdr, spalte, --zeile);
            break;
        case '\xaf':
            kollisionDiskette(chAdr, --spalte, --zeile);
            break;
        case '\xb0': // Stein "\xb0\xb1\x08\x08\x0a\xb2\xb3\x0b"
            kollisionStein(chAdr, spalte, zeile);
            break;
        case '\xb1':
            kollisionStein(chAdr, --spalte, zeile);
            break;
        case '\xb2':
            kollisionStein(chAdr, spalte, --zeile);
            break;
        case '\xb3':
            kollisionStein(chAdr, --spalte, --zeile);
            break;
        default:
            break;
    }
}

void kollisionStein(uint8_t *chAdr, uint8_t spalte, uint8_t zeile)
{
    switchBild0Farbe();
    uint8_t *farbAdr = berechnePixelRamAdresse(chAdr);
    uint8_t farbe = *farbAdr;
    switchBild0Pixel();
    // gleiche Vordergrundfarbe?
    if( (farbe & 0x78) == (ballFarbe & 0x78) )
    {
        CURSO = zeile * 256 + spalte;
        printRaumCh(0);
        punkte += punkteProStein;
        checkExtraLEben();
        printPunkte();
        anzahlSteine--;
        printSteine();
        addTon(TON_STEIN1);
    }
}

void kollisionDiskette(uint8_t *chAdr, uint8_t spalte, uint8_t zeile)
{
    if( kollisionDiagonal )
    {
        addTon(TON_WAND);
        return;
    }
    switchBild0Farbe();
    uint8_t *farbAdr = berechnePixelRamAdresse(chAdr);
    uint8_t farbe = *farbAdr;
    switchBild0Pixel();
    // ungleiche Vordergrundfarbe?
    if( (farbe & 0x78) != (ballFarbe & 0x78) )
    {
        return;
    }
    int16_t delta = chAdr - ballCharVRam;
    uint16_t *zielAdr = chAdr + delta + delta;
    uint8_t ch = *zielAdr;
    if( ch != 0x20 )
    { // hinter dem Schieber ist kein Platz
        addTon(TON_WAND);
        return;
    }
    // alte Position löschen
    CURSO = zeile * 256 + spalte;
    printRaumCh(0);
    // neue Position neu zeichnen
    if( delta == (int16_t) 1 )
    {
        CURSO = zeile * 256 + spalte + 2;
    }
    else if( delta == (int16_t) -1 )
    {
        CURSO = zeile * 256 + spalte - 2;
    }
    else if( delta == (int16_t) 40 )
    {
        CURSO = (zeile + 2) * 256 + spalte;
    }
    else if( delta == (int16_t) -40 )
    {
        CURSO = (zeile - 2) * 256 + spalte;
    }
    printRaumCh(0x50 | (farbe >> 3));
    addTon(TON_DISKETTE);
}

void kollisionFWechsler(uint8_t *chAdr)
{
    switchBild0Farbe();
    uint8_t *farbAdr = berechnePixelRamAdresse(chAdr);
    uint8_t farbe = *farbAdr;
    switchBild0Pixel();
    ballFarbe = farbe & 0x78; // Hintergrundfarbe löschen
    addTon(TON_FARBWECHSELR);
}

void kollisionsChecks()
{
    loescheKollisionsFlags();
    if( ((uint16_t) aktuelleBallPosition & 0x07) != 0 )
    {
        return;
    }
    ballCharVRam = berechneVRamAdresse(aktuelleBallPosition);
    if( ballHochRunter == BALL_RICHTUNG_UP )
    {
        if( ballRechtsLinks == BALL_HORIZONTAL_NEUTRAL )
        {
            kollisionObenCheck();
        }
        else if( ballRechtsLinks == BALL_HORIZONTAL_LINKS )
        {
            kollisionObenCheck();
            kollisionLinksCheck();
            uint8_t *adr = ballCharVRam - 41;
            if( !kollisionOben && !kollisionLinks && *(adr) != 0x20 )
            {
                ballHochRunter = BALL_RICHTUNG_DOWN;
                ballRechtsLinks = BALL_HORIZONTAL_RECHTS;
                kollisionDiagonal = true;
                chKollNeben = adr;
            }
        }
        else
        {
            kollisionObenCheck();
            kollisionRechtsCheck();
            uint8_t *adr = ballCharVRam - 39;
            if( !kollisionOben && !kollisionRechts && *(adr) != 0x20 )
            {
                ballHochRunter = BALL_RICHTUNG_DOWN;
                ballRechtsLinks = BALL_HORIZONTAL_LINKS;
                kollisionDiagonal = true;
                chKollNeben = adr;
            }
        }
    }
    else
    {
        if( ballRechtsLinks == BALL_HORIZONTAL_NEUTRAL )
        {
            kollisionUntenCheck();
        }
        else if( ballRechtsLinks == BALL_HORIZONTAL_LINKS )
        {
            kollisionUntenCheck();
            kollisionLinksCheck();
            uint8_t *adr = ballCharVRam + 39;
            if( !kollisionUnten && !kollisionLinks && *(adr) != 0x20 )
            {
                ballHochRunter = BALL_RICHTUNG_UP;
                ballRechtsLinks = BALL_HORIZONTAL_RECHTS;
                kollisionDiagonal = true;
                chKollNeben = adr;
            }
        }
        else
        {
            kollisionUntenCheck();
            kollisionRechtsCheck();
            uint8_t *adr = ballCharVRam + 41;
            if( !kollisionUnten && !kollisionRechts && *(adr) != 0x20 )
            {
                ballHochRunter = BALL_RICHTUNG_UP;
                ballRechtsLinks = BALL_HORIZONTAL_LINKS;
                kollisionDiagonal = true;
                chKollNeben = adr;
            }
        }
    }
}

void kollisionObenCheck()
{
    uint8_t *adr = ballCharVRam - 40;
    if( *(adr) != 0x20 )
    {
        ballHochRunter = BALL_RICHTUNG_DOWN;
        kollisionOben = true;
        chKollHaupt = adr;
    }
}

void kollisionUntenCheck()
{
    uint8_t *adr = ballCharVRam + 40;
    if( *(adr) != 0x20 )
    {
        ballHochRunter = BALL_RICHTUNG_UP;
        kollisionUnten = true;
        chKollHaupt = adr;
    }
}

void kollisionLinksCheck()
{
    uint8_t *adr = ballCharVRam - 1;
    if( *(adr) != 0x20 )
    {
        ballRechtsLinks = BALL_HORIZONTAL_RECHTS;
        kollisionLinks = true;
        chKollNeben = adr;
    }
}

void kollisionRechtsCheck()
{
    uint8_t *adr = ballCharVRam + 1;
    if( *(adr) != 0x20 )
    {
        ballRechtsLinks = BALL_HORIZONTAL_LINKS;
        kollisionRechts = true;
        chKollNeben = adr;
    }
}

void loescheKollisionsFlags()
{
    kollisionRechts = false;
    kollisionLinks = false;
    kollisionOben = false;
    kollisionUnten = false;
    kollisionDiagonal = false;
    chKollHaupt = NULL;
    chKollNeben = NULL;
}

void addTon(uint16_t ton)
{
    if( ton1 == 0 )
    {
        ton1 = ton;
    }
    else
    {
        ton2 = ton;
    }
}

void tastaturAbfrage()
{
    uint8_t ch = TAST_KEY;
    if( ((uint16_t) aktuelleBallPosition & 0x07) == 0 )
    {
        if( ch == 0x08 ) // links
        {
            ballRechtsLinks = BALL_HORIZONTAL_LINKS;
        }
        else if( ch == 0x09 ) // rechts
        {
            ballRechtsLinks = BALL_HORIZONTAL_RECHTS;
        }
        else
        {
            ballRechtsLinks = BALL_HORIZONTAL_NEUTRAL;
        }
    }
    if( ch == 0x13 ) // Stop Taste
    {
        kollisionTotenkopf = true;
    }
    if( DEBUG )
    {
        // Step Mode
        if( !stepMode && ch == 'S' )
        {
            stepMode = true;
            stepChar = 'S';
            step = false;
            return;
        }
        if( stepMode )
        {
            if( stepChar == 0 )
            {
                if( ch != 0 )
                {
                    stepChar = ch;
                    step = true;
                }
            }
            else
            {
                step = false;
                if( ch != stepChar )
                {
                    stepChar = 0;
                }
            }
        }
        if( ch == 's' )
        {
            stepMode = false;
        }
        if( ch == 'e' )
        {
            anzahlSteine = 0;
        }
    }
}

void wait()
{
    for( int i = 0; i < ballStepWaitCount; i++ )
    {
        // nix :-)
    }
}

/**
 * Bewegt den Ball um eine Position weiter.
 */
void moveBall()
{
    if( stepMode && !step )
    {
        return;
    }
    if( ballHochRunter == BALL_RICHTUNG_UP )
    {
        *(ballPosAlt1 + 7) = 0;
        *(ballPosAlt2 + 7) = 0;
        aktuelleBallPosition--;
    }
    else
    {
        aktuelleBallPosition++;
        *(ballPosAlt1) = 0;
        *(ballPosAlt2) = 0;
    }
    if( ballRechtsLinks == BALL_HORIZONTAL_LINKS )
    {
        if( ballShift == 0 )
        {
            ballShift = 7;
            aktuelleBallPosition = aktuelleBallPosition - 0x100;
        }
        else
        {
            ballShift--;
            if( ballShift == 0 )
            {
                memcpy(ballPosAlt2, &(BALL) + 8, 8);
            }
        }
    }
    if( ballRechtsLinks == BALL_HORIZONTAL_RECHTS )
    {
        if( ballShift == 7 )
        {
            ballShift = 0;
            aktuelleBallPosition = aktuelleBallPosition + 0x100;
            memcpy(ballPosAlt1, &(BALL) + 8, 8);
        }
        else
        {
            ballShift++;
        }
    }
    if( ballShift == 0 )
    { // der Ball befindet sich genau in einer Spalte (ohne Überlappung)
        ballPosAlt1 = aktuelleBallPosition;
        ballPosAlt2 = aktuelleBallPosition;
        if( ballHochRunter == BALL_RICHTUNG_UP )
        {
            switchBild0Farbe();
            *ballPosAlt1 = ballFarbe;
            switchBild0Pixel();
            memcpy(aktuelleBallPosition, &BALL, 8);
        }
        else
        {
            switchBild0Farbe();
            *(ballPosAlt1 + 7) = ballFarbe;
            switchBild0Pixel();
            memcpy(aktuelleBallPosition, &BALL, 8);
        }
    }
    else
    {
        ballPosAlt1 = aktuelleBallPosition;
        ballPosAlt2 = aktuelleBallPosition + 0x100;
        uint8_t shift = ballShift << 4;
        if( ballHochRunter == BALL_RICHTUNG_UP )
        {
            switchBild0Farbe();
            memset(ballPosAlt1, ballFarbe, 8);
            memset(ballPosAlt2, ballFarbe, 8);
            switchBild0Pixel();
            memcpy(ballPosAlt1, &(BALL) + shift, 8);
            memcpy(ballPosAlt2, &(BALL) + shift + 8, 8);
        }
        else
        {
            switchBild0Farbe();
            memset(ballPosAlt1, ballFarbe, 8);
            memset(ballPosAlt2, ballFarbe, 8);
            switchBild0Pixel();
            memcpy(ballPosAlt1, &(BALL) + shift, 8);
            memcpy(ballPosAlt2, &(BALL) + shift + 8, 8);
        }
    }
}

/**
 * 08 -> Cursor links
 * 09 -> Cursor rechts
 * 0a -> Cursor unten
 * 0b -> Cursor oben
 */
void printRaumCh(uint8_t ch)
{
    switch( ch & 0x0F0 )
    {
        case 0x10:          // Mauer 1
            COLOR = 0x07;
            CAOS_PRINT_STRING("\xa0\xa0\x08\x08\x0a\xa0\xa0\x0b");
            break;
        case 0x20:          // Mauer 2
            COLOR = 0x07;
            CAOS_PRINT_STRING("\xa1\xa0\x08\x08\x0a\xa1\xa0\x0b");
            break;
        case 0x30:          // Totenkopf
            COLOR = 0x17;
            CAOS_PRINT_STRING("\xa2\xa3\x08\x08\x0a\xa4\xa5\x0b");
            break;
        case 0x40:          // Farbwechsler
            COLOR = getKcFarbe(ch);
            CAOS_PRINT_STRING("\xa8\xa9\x08\x08\x0a\xaa\xab\x0b");
            break;
        case 0x50:          // Schieber
            COLOR = getKcFarbe(ch);
            CAOS_PRINT_STRING("\xac\xad\x08\x08\x0a\xae\xaf\x0b");
            break;
        case 0x60:          // Stein
            COLOR = getKcFarbe(ch);
            CAOS_PRINT_STRING("\xb0\xb1\x08\x08\x0a\xb2\xb3\x0b");
            anzahlSteine++;
            break;
        default:            // Luft
            COLOR = ballFarbe;
            CAOS_PRINT_STRING("\x20\x20\x08\x08\x0a\x20\x20\x0b");
            break;
    }
}

/**
 * Liefert zu einem Steincode oder logischem Farbcode die passende Farbe (Bitcodierung) im KC.
 */
uint8_t getKcFarbe(uint8_t ch)
{
    return (ch & 0x0f) << 3 | 0x07;
}

void printLeben()
{
    COLOR = FARBE_VG_WEISS;
    CURSO = 0x0b21;
    CAOS_PRINT_STRING("Leben");
    if( anzahlLeben > 5 )
    {
        COLOR = FARBE_VG_GRUEN;
    }
    else if( anzahlLeben < 2 )
    {
        COLOR = FARBE_VG_ROT;
    }
    else
    {
        COLOR = FARBE_VG_WEISS;
    }
    CURSO = 0x0c23;
    ltoa(anzahlLeben, itoaBuffer, 10);
    CAOS_PRINT_STRING(itoaBuffer);
    CAOS_PRINT_CH(' ');
}

void printRaumNummer()
{
    COLOR = FARBE_VG_WEISS;
    CURSO = 0x0f21;
    CAOS_PRINT_STRING("Raum");
    CURSO = 0x1023;
    ltoa(raumNummer, itoaBuffer, 10);
    CAOS_PRINT_STRING(itoaBuffer);
}

void printPunkte()
{
    COLOR = FARBE_VG_WEISS;
    CURSO = 0x0321;
    CAOS_PRINT_STRING("Punkte");
    CURSO = 0x0422;
    ltoa(punkte, itoaBuffer, 10);
    CAOS_PRINT_STRING(itoaBuffer);
}

void printMaxPunkte()
{
    COLOR = FARBE_VG_WEISS;
    CURSO = 0x0721;
    CAOS_PRINT_STRING("Rekord");
    CURSO = 0x0822;
    ltoa(LAST_RECORD, itoaBuffer, 10);
    CAOS_PRINT_STRING(itoaBuffer);
}

void printSteine()
{
    COLOR = FARBE_VG_WEISS;
    CURSO = 0x1321;
    CAOS_PRINT_STRING("Bl|cke"); // | -> ö
    CURSO = 0x1423;
    ltoa(anzahlSteine, itoaBuffer, 10);
    CAOS_PRINT_STRING(itoaBuffer);
    CAOS_PRINT_CH(' ');
}

void printBonus()
{
    COLOR = FARBE_VG_WEISS;
    CURSO = 0x01A21;
    CAOS_PRINT_STRING("Bonus");
}

void printBonusZahl()
{
//    CURSO = 0x1B22;
    printBonusBuffer();
}

void printBonusBuffer()
{
    tmpIrmAdr = (uint8_t*) ((0x80 + 0x22) * 256 + 0x1b * 8);
    uint8_t *buff = bonusBuffer;
    for( int i = 0; i < 3; i++ )
    {
        uint8_t *srcAdr = 0xEE80 + *buff * 8;
        memcpy(tmpIrmAdr, srcAdr, 8);
        tmpIrmAdr = tmpIrmAdr + 256;
        buff++;
    }
}

bool_t isBonusNull()
{
    for( int i = 0; i < 3; i++ )
    {
        if( bonusBuffer[i] > 0 )
        {
            return false;
        }
    }
    return true;
}

void addBonus()
{
    uint8_t increment = 1;
    for( int i = 2; i >= 0; i-- )
    {
        uint8_t ton = TON_SIEG - ((2 - i) * 10);
        while( bonusBuffer[i] > 0 )
        {
            bonusBuffer[i]--;
            punkte += increment;
            checkExtraLEben();
            printBonusBuffer();
            printPunkte();
            CAOS_TON(ton, ton, 0x021f);
            ton -= 5;
            msleep(200);
        }
        increment = increment * 10;
    }
}

void decBonus()
{
    bool_t b = true;
    for( int i = 2; i >= 0; i-- )
    {
        if( b )
        {
            if( bonusBuffer[i] > 0 )
            {
                bonusBuffer[i]--;
                b = false;
            }
            else
            {
                bonusBuffer[i] = 9;
            }
        }
    }
}

void checkExtraLEben()
{
    if( punkte > punkteNextLeben )
    {
        CAOS_TON(0x080, 0, 0x011f);
        anzahlLeben++;
        printLeben();
        punkteNextLeben += PUNKTE_EXTRA_LEBEN;
    }
}

/**
 * Kopiert und Konnvertiert den übergebenen String, der eine Zahl darstellen muss, in eine ungepackte BCD Zahl.
 *
 * "123" -> 001H 002H 003H
 */
void stringToBcd(uint8_t *string, uint8_t *buffer)
{
    while( *string != '\0' )
    {
        *buffer = (*string) - 0x30;
        string++;
        buffer++;
    }
}

void berechnePunkteProStein()
{
    if( anzahlSteine < 10 )
    {
        punkteProStein = 250;
    }
    else
    {
        punkteProStein = 2500 / anzahlSteine;
    }
}

/** Schreibt die aktuelle in itoaBuffer befindliche Zahl an die aktuelle Cursorposition. */
void printNumberString()
{
    tmpZeile = CURSO / 256;
    tmpSpalte = (uint8_t) CURSO;
    tmpIrmAdr = (uint8_t*) ((0x80 + tmpSpalte) * 256 + tmpZeile * 8);
    uint8_t *buff = itoaBuffer;
    while( *buff )
    {
        // Zeichendaten Adr berechen
        uint8_t *srcAdr = 0xED00 + *buff * 8;
        memcpy(tmpIrmAdr, srcAdr, 8);
        tmpIrmAdr = tmpIrmAdr + 256;
        buff++;
    }
}

void printStatus(uint8_t zeile, uint8_t spalte)
{
    uint16_t tmpCursor = CURSO;
    CURSO = 0x0000;
    CAOS_PRINT_STRING("Zeile: ");
    CAOS_AHEX(zeile);
    CAOS_PRINT_STRING(" Spalte: ");
    CAOS_AHEX(spalte);
//    CAOS_HLHX(aktuelleBallPosition);
    CAOS_PRINT_CH(' ');
    CURSO = tmpCursor;
}

void printStatus2()
{
    uint16_t tmpCursor = CURSO;
    CURSO = 0x0120;
// aktuelleBallPosition
    CAOS_PRINT_STRING("BPos:");
    CURSO = 0x0221;
    CAOS_HLHX((uint16_t) aktuelleBallPosition);
    CURSO = 0x0320;
    CAOS_PRINT_STRING("BPos L");
    CURSO = 0x0421;
    CAOS_HLHX((uint16_t) ballPosAlt1);
    CURSO = 0x0520;
    CAOS_PRINT_STRING("BPos R");
    CURSO = 0x0621;
    CAOS_HLHX((uint16_t) ballPosAlt1);
// ballshift
    CURSO = 0x0720;
    CAOS_PRINT_STRING("BShift");
    CURSO = 0x0821;
    CAOS_AHEX(ballShift);

// Cursor Position wieder herstellen
    CURSO = tmpCursor;
}

/**
 * Berechnet die Videoram Adresse aus der Pixel-Ram Adresse.
 */
uint8_t* berechneVRamAdresse(uint8_t *pixelAdr)
{
    static uint8_t zeile;
    static uint8_t spalte;
    zeile = ((uint8_t) pixelAdr) >> 3;
    spalte = (uint8_t) ((uint16_t) pixelAdr >> 8) - (uint8_t) 0x80;
    return &VIDEO0 + 40 * zeile + spalte;
}

/**
 * Berechnet die 1. Pixel /Farb -Ram Adresse aus der VRam Adresse.
 */
uint8_t* berechnePixelRamAdresse(uint8_t *chAdr)
{
    uint16_t relAdr = chAdr - &VIDEO0;
    uint8_t zeile = (uint8_t) (relAdr / 40);
    uint8_t spalte = relAdr - (uint8_t) (zeile * 40);
    return (spalte + 0x80) * 256 + zeile * 8;
}

/**
 * Schalten den Zugriff auf die Pixelebene von Bild 0 an.
 */
void switchBild0Pixel()
{
    outp(0x84, 0x28);
}

/**
 * Schalten den Zugriff auf die Farbebene von Bild 0 an.
 */
void switchBild0Farbe()
{
    outp(0x84, 0x2a);
}

void intro()
{
    // ä -> {
    // ö -> |
    // ü -> }
    COLOR = FARBE_VG_WEISS | FARBE_HG_BLAU;
    CAOS_CLS();
    CURSO = 0x0210;
    CAOS_PRINT_STRING("Schocky");
    CURSO = 0x0402;
    CAOS_PRINT_STRING("Anleitung");
    CURSO = 0x0702;
    CAOS_PRINT_STRING("Ziel:");
    CURSO = 0x0804;
    CAOS_PRINT_STRING("Alle farbigen Bl|cke mit dem");
    CURSO = 0x0904;
    CAOS_PRINT_STRING("farblich passenden Ball zerst|ren.");
    CURSO = 0x0C02;
    CAOS_PRINT_STRING("Steuerung");
    CURSO = 0x0D04;
    CAOS_PRINT_STRING("\210   Ball nach Links");
    CURSO = 0x0E04;
    CAOS_PRINT_STRING("\211   Ball nach Rechts");
    CURSO = 0x1002;
    CAOS_PRINT_STRING("STOP in aussichtslosen Situationen");
    CURSO = 0x1102;
    CAOS_PRINT_STRING("(F8 im JKCEMU)");
    CURSO = 0x1700;
    CAOS_PRINT_STRING("  Programm by Holger J|dicke\r\n");
    CAOS_PRINT_STRING("           aka Hojoe\r\n");
    CAOS_PRINT_STRING("  Version vom 13.07.2022 mit 22 Leveln");
    msleep(1000);
    CURSO = 0x1e15;
    CAOS_PRINT_STRING("dr}cke eine Taste");
    while( TAST_KEY == '\0' )
        ;
}

bool_t outro()
{
    COLOR = FARBE_VG_WEISS | FARBE_HG_BLAU;
    CAOS_CLS();
    CURSO = 0x0210;
    CAOS_PRINT_STRING("Schocky");
    CURSO = 0x0502;
    if( trainer )
    {
        CAOS_PRINT_STRING("Trainings ");
    }
    CAOS_PRINT_STRING("Ergebnis");
    // Punkte
    CAOS_PRINT_STRING("\r\n\r\n\r\n    ");
    ltoa(punkte, itoaBuffer, 10);
    CAOS_PRINT_STRING(itoaBuffer);
    CAOS_PRINT_STRING(" Punkte erreicht");
    if( punkte > LAST_RECORD )
    {
        CAOS_PRINT_STRING("\r\n    neuer ");
        COLOR = FARBE_VG_WEISS | FARBE_HG_BLAU | 0x80;
        CAOS_PRINT_STRING("Record");
        COLOR = FARBE_VG_WEISS | FARBE_HG_BLAU;
        LAST_RECORD = punkte;
    }
    // Räume
    if( anzahlLeben > 0 )
    {
        raumNummer--;
    }
    if( trainer )
    {
        if( raumNummer >= startRaum )
        {
            CAOS_PRINT_STRING("\r\n\r\n    Von Raum ");
            ltoa(startRaum, itoaBuffer, 10);
            CAOS_PRINT_STRING(itoaBuffer);
            CAOS_PRINT_STRING("\r\n\r\n    bis Raum ");
            ltoa(raumNummer, itoaBuffer, 10);
            CAOS_PRINT_STRING(itoaBuffer);
            CAOS_PRINT_STRING(" ge}bt");
        }
    }
    else
    {
        if( anzahlLeben == 0 )
        {
            CAOS_PRINT_STRING("\r\n\r\n    Bis in Raum ");
            ltoa(raumNummer, itoaBuffer, 10);
            CAOS_PRINT_STRING(itoaBuffer);
            CAOS_PRINT_STRING(" vorgedrungen");
        }
        else
        {
            CAOS_PRINT_STRING("\r\n\r\n    ");
            ltoa(raumNummer, itoaBuffer, 10);
            CAOS_PRINT_STRING(itoaBuffer);
            CAOS_PRINT_STRING(" R{ume geschafft ");
        }
    }
    // Anzahl Leben
    if( anzahlLeben > 0 )
    {
        CAOS_PRINT_STRING("\r\n\r\n    ");
        ltoa(anzahlLeben, itoaBuffer, 10);
        CAOS_PRINT_STRING(itoaBuffer);
        CAOS_PRINT_STRING(" Leben }brig");
    }
    uint8_t ch;
    while( (ch = TAST_KEY) != '\0' )
        ;
    CURSO = 0x01902;
    CAOS_PRINT_STRING("dr}cke");
    CURSO = 0x01A04;
    CAOS_PRINT_STRING("E              -> zur}ck ins CAOS");
    CURSO = 0x01B04;
    CAOS_PRINT_STRING("<andere Taste> -> noch einmal");
    while( (ch = TAST_KEY) == '\0' )
        ;
    return ch != 'E' && ch != 'e';
}

int main()
{
    if( ARGN > 0 )
    {
        trainer = true;
        startRaum = (uint8_t) ARG1;
        if( startRaum == 0 )
        {
            startRaum = 1;
        }
    }
    else
    {
        trainer = false;
        startRaum = 1;
    }
    initGame();
    if( !trainer )
    {
        intro();
    }
    do
    {
        initRun();
        mainLoop();
    } while( outro() );
    CAOS_RESET();
    return 0;
}

