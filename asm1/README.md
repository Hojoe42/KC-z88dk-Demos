# ASM1

In diesem Programm geht es darum wie Assembler Code aufgerufen werden kann. Im Beispiel wird die CAOS Funktion zur Ausgabe eine Zeichens verwendet.

## Kompilieren

```
$ zcc +kc --list -o ASM1.bin -create-app Asm1.c
```

Durch die Verwendung von `--list` ist es möglich sich hinterher anzuschauen wie der Assembler Code aus dem C Code aufgerufen wird.

## Weitere Details

Das Programm selbst macht nicht allzu viel. In der main() Methode wird mehrfach eine der beiden `drawChar()` Funktionen aufgerufen. 
An den beiden drawChar() Methoden ist zu sehen wie einfach C und Assembler Code miteinander kombiniert werde kann. 

Die beiden Funktionen `drawChar1()` und `drawChar2` sind unterschiedlich implementiert. Grundsätzlich werden in C Funktionsparameter über den Stack übergeben.
Weiterhin ist der Aufrufer verantwortlich den Stack wieder aufzuräumen. Daher sind in `drawChar1()` am Anfang die POP und PUSH Aufrufe notwendig, um 
den Parameter vom Stack zu lesen, diesen aber nach außen unverändert zu lassen.

An der Funktion drawChar1() sind zwei zusätzliche 'function decorator' definiert. Damit ist es möglich ein anderes Aufrufverhalten dieser Funktion zu konfigurieren.
* `__naked` wird üblicher Weise verwendet, wenn die Funktion nur Assemblercode enthält. Dann wird je nach Aufrufvariante am Anfang und Ende einer 
  Methode kein zusätzlicher Code generiert, der für C Code notwendig wäre. Konsequenz daraus ist, dass es hier notwendig ist manuell am Ende ein `ret` einzufügen.
* `__z88dk_fastcall` damit ist es möglich den Parameter der Funktion in einem oder mehreren Registern zu übergeben. Je nachdem ob der Wert 
  8, 16 oder 32 Bit groß ist, wird er in L, HL oder DEHL übergeben. Dadurch kann in unserem Fall das übergebene Zeichen direkt dem Register L entnommen 
  werden und der Code wird deutlich aufgeräumter.

Weitere Informationen zu den 'function decorators' befinden sich im z88dk Wiki unter [CallingConventions](https://github.com/z88dk/z88dk/wiki/CallingConventions) 

Am Anfang des Programms wird eine Konstante `Start` definiert. Sie enthält die Informationen für einen Menüeintrag. Damit wird das Programm im Menü 
angezeigt und kann mehrfach gestartet werden.

```
char START[] = {
0x7f, 0x7f,                    7F ist das Standard Prolog Byte im KC
'A', 'S', 'M', '1',            der im Menü anzuzeigende Text als einzelne Zeichen
0x01,                          der IRM bleibt beim Start eingeschaltet
0xcd, 0x00, 0x10,              ASM Code: CALL 1000H
0xc9};                         ASM Code: RET
```

Bei unveränderten Einstellungen liegen die compilierten C Programme ab 1000H im Speicher und werden mit einem Sprung auf diese Adresse gestartet.