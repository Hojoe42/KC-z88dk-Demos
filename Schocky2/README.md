# Schocky2

Hier ein Projekt das etwas umfangreicher ist. Die ursprüngliche Idee stammt von Crillion vom C64

![Schocky2](/images/Schocky2.png)

Ursprünglich war das gesamte Projekt in Assembler programmiert. Anfang der 1990er Jahre (1992 oder 1993) hatte ich damit begonnen. Damit habe ich mir 
Z80 Assembler beigebracht. Zuerst mit einfachen Routinen, um den Ball auf dem Bildschirm hoch und runter zu bewegen, später (über die Jahre) ist daraus 
fast ein ganzes Spiel entstanden. Es ist aber nie so richtig fertig geworden.

Nach mehr als 20 Jahren Pause habe ich es jetzt fertig gestellt. Ursprünglich wollte ich 'nur' in C ein Rahmen für das eigentliche Spiel erstellen. 
Aber wie das mit Assembler Code so ist, war das alles sehr monolithisch. Daher war es dann doch einfacher alles in C nach zu programmieren und dabei C 
zu lernen. 

Das Spiel besteht fast nur aus C Code. Es gibt ein paar Assembler Funktionen, welche meist einfache Wrapper um die jeweilige CAOS Funktion sind. In
den restlichen Assembler Dateien sind die Daten für die Grafiken oder Level.

Das Spiel funktioniert nur auf dem KC 85/4 und höher, da direkt in Bildspeicher geschrieben wird.

## Kompilieren

```
$ zcc +kc -o Schocky2.bin -create-app @Schocky2.lst
```

In `Schocky2.lst` sind alle Dateien aufgelistet die zusammen kompiliert, assembliert und gelinkt werde. Damit bleibt der zcc Aufruf übersichtlich
und in der *.lst Datei lassen sich einfach weitere Dateien hinzufügen.

Wer das Spiel nicht selbst kompilieren möchte findet im [KC Labor](http://www.kc85.info/) unter Download - Kategorie:Spiele - [Schocky2](http://www.kc85.info/index.php/download-topmenu/viewdownload/27-spiele/411-schocky2.html)
eine compilierte KCC Datei.
