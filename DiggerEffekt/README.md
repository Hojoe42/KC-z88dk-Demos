# DiggerEffekt

Kleines Programm, welches das Flackern der Diamanten aus Digger, den Digger Effekt, nachstellt.

Wenn das Programm im JKCEmu ausprobiert wird, dann muss für die korrekte Anzeige in den Optionen für den KC85/4, unter Sonstiges der 
Haken "Zeitverhalten der Bildschirmansteuerung emulieren" gesetzt sein.

## Kompilieren

```
$ zcc +kc --list -g -o DEffekt.bin -create-app DiggerEffekt.c

```
