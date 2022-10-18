# ClsTest

Mit der `clg()` Funktion aus [<graphics.h>](https://github.com/z88dk/z88dk/wiki/Classic-Monochrome-Graphics) gab es ein paar Bugs. Daher hatte ich 
dieses Miniprogramm erstellt, um zu prüfen ob der Farbspeicher bei `clg()` und `clrscr()` korrekt gelöscht wird.

Weiterhin ist zu sehen wie farbiger Text an bestimmte Bildschirmpositionen ausgegeben werden kann.

## Kompilieren

```
$ zcc +kc -o cls.bin -create-app ClsTest.c
```

## sdcc

Standardmäßig wird der sccz80 C Compiler verwendet. Obiger Aufruf wird daher mit sccz80 kompiliert. z88dk enthält noch einen 2. C Compiler, den zsdcc, 
eine angepasste Variante des [sdcc](https://sourceforge.net/projects/sdcc/).
Der sdcc generiert etwas anderen Assembler Code und möglicherweise ist der Optimizer etwas besser. Mit ist aufgefallen, das der sdcc mehr (berechtigte) 
Warnungen ausgibt. Es kann sich ebenfalls anbieten seine C Programme mit dem sdcc zu kompilieren und Größe und Geschwindigkeit der erstellten Programme zu vergleichen.

```
zcc +kc -compiler sdcc -Cs--reserve-regs-iy -o cls-sdcc.bin -create-app ClsTest.c
```

Mit dem Parameter `-compiler sdcc` wird der sdcc zum Übersetzen des C Programms verwendet.

Mit `-Cs--reserve-regs-iy` wird dem Compiler gesagt, dass der erzeugte Code das IY Register nicht verwenden darf. Beim Assemblieren der vom
C Compiler erzeugten Assembler Quelltexte werden beim Target `+kc` alle Zugriffe auf das IY und IX vertauscht. Damit gibt es schlussendlich keine Zugriffe 
auf IX. Das ist wichtig da IX beim KC bei freigegebenen Interrupts nicht verändert werden darf. 

Die Option zum Vertauschen von IX und IY für das Target `+kc` und einige weitere Optionen sind in [lib/config/kc.cfg](https://github.com/z88dk/z88dk/blob/master/lib/config/kc.cfg)
definiert.

Soll in Assemblercode auf IX zugegriffen werden, z. B. um die Tastatur manuell abzufragen, dann muss das Register IY verwendet werden. Beim Übersetzen 
wird der Zugriff dann _richtig_ getauscht.
