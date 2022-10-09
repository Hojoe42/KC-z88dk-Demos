# Hello World

Eines der einfachsten Programme. Hier geht es erste einmal darum wie wird das Programm mit z88dk compiliert und im JKCEmu gestartet.

## Kompilieren

### Voraussetzungen

Vorraussetzung für das Kompilieren ist ein installiertes z88dk. Das `bin` Verzeichnis sollte im Suchpfad sein, damit der Aufruf kurz und knapp mit 
`zcc` erfolgen kann. Als zweites muss das `z88dk/lib/config` Verzeichnis in der Umgebungsvariablen `ZCCCFG` hinterlegt sein.

### Komandozeile
Zum kompilieren kann folgender Aufruf verwendet werden:

```
$ zcc +kc -o HelloWorld.bin -create-app test.c
```
Damit wird eine Datei `HELLOWORLD.KCC` aus dem C Programm `test.c` erstellt.

## Starten im Emulator

Den JKCEmu starte ich mit:

```
start javaw -jar jkcemu-0.9.8.2.jar
```
Je nach Einstellungen muss zuerst auf den KC85/4 umgeschaltet werden. Das geschieht über den Einstellungen Dialog. Dort muss dann der entsprechende KC85 
ausgewählt werden, siehe dazu ![Einstellungen-KC85/4](/images/JKCEMU-85-4.png).

Im Datei Laden Dialog kann `HELLOWORLD.KCC` ausgewählt und gestartet werden, siehe: ![Laden](/images/Start-HelloWorld.png).

