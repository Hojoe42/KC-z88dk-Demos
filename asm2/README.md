# ASM2

In diesem Programm geht es um die Einbindung von Assembler Code aus externen Dateien. Im Beispiel wird die CAOS Funktion zur Ausgabe eine Zeichens verwendet. 
Andere CAOS Funktionen können analog eingebunden werden.

Im Beispiel [ASM1](../asm1/README.md) wurde der Assembler Code innerhalb der C Datei direkt in eine C Funktion eingefügt. Das ist bei kurzen Programmen
praktisch, bei längeren Programmen und um den Assembler Code wiederzuverwenden ist es besser diesen in eine (oder mehrere) extra Dateien auszulagern.
Wie das aussehen kann wird in diesem Beispiel gezeigt.

## Kompilieren

```
$ zcc +kc -o ASM2.bin -create-app DrawChar.c DrawChar.asm
```

Dieses Beispiel verwendet mehrere Quelldateien, einmal die `DrawChar.c` mit dem C Quelltext und einmal `DrawChar.asm` mit der Assembler Funktion. 
Diese Dateien müssen beim Aufruf des `zcc` alle mit angegeben werden.

## Weitere Hinweise

Im C Quelltext muss die aufzurufende Funktion als `extern` definiert sein, da sie sich in einer anderen Datei befindet.

```
extern void drawChar(char index) __z88dk_fastcall;
```

In der Assembler Datei muss die Funktion mittels `PUBLIC` als eine öffentliche Funktion definiert sein, damit sie von außerhalb aufgerufen werden kann. 
Zusätzlich ist es notwendig einen Unterstrich voran zu stellen. Nur dann ist es möglich die Funktion aus C Quelltexten heraus aufzurufen. Bei Aufrufen 
aus anderen Assembler Dateien wird die Variante ohne Unterstrich verwendet. Es ist daher üblich bei öffentlichen Funktionen jeweils beide Varianten anzugeben.

Es gibt eine Menge vordefinierter Konstanten für den KC. Diese werden mit der folgenden Zeile eingebunden:

```
INCLUDE "target/kc/def/caos.def"
```

Zum nachlesen, die Datei liegt im z88dk Projekt unter [lib/target/kc/def/caos.def](https://github.com/z88dk/z88dk/blob/master/lib/target/kc/def/caos.def).