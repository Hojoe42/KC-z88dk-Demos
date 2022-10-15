# Hello World

Eines der einfachsten Programme. Hier geht es erste einmal darum wie wird das Programm mit z88dk compiliert und im JKCEmu gestartet.

## Kompilieren

### Voraussetzungen

Vorraussetzung für das Kompilieren ist ein installiertes z88dk. Das `bin` Verzeichnis sollte im Suchpfad sein, damit der Aufruf kurz und knapp mit 
`zcc` erfolgen kann. Als zweites muss das `z88dk/lib/config` Verzeichnis in der Umgebungsvariablen `ZCCCFG` hinterlegt sein. Weitere Informationen 
gibt es im [z88dk Wiki - Installation](https://github.com/z88dk/z88dk/wiki/installation)

### Komandozeile
Zum kompilieren kann folgender Aufruf verwendet werden:

```
$ zcc +kc -o HelloWorld.bin -create-app test.c
```

Damit wird eine Datei `HELLOWORLD.KCC` aus dem C Programm `test.c` erstellt. 

## Starten im Emulator

Den JKCEmu starte ich unter Windows mit:

```
start javaw -jar jkcemu-0.9.8.2.jar
```

Je nach Einstellungen muss zuerst auf den KC85/4 umgeschaltet werden. Das geschieht über den Einstellungen Dialog. Dort muss dann der entsprechende KC85 
ausgewählt werden, siehe dazu ![Einstellungen-KC85/4](/images/JKCEMU-85-4.png).

Im Datei Laden Dialog kann `HELLOWORLD.KCC` ausgewählt und gestartet werden, siehe: ![Laden](/images/Start-HelloWorld.png).

## Weitere Details

### -create-app
Mit der Kommandozeile

```
$ zcc +kc -o HelloWorld.bin -create-app test.c
```

werden eigentlich zwei Dateien erzeugt, `HelloWorld.bin` und `HELLOWORLD.KCC`. Die `*.bin` Datei entspricht einem direktem Speicherabzug. Diese 
Datei kann ebenfalls geladen werden. Ohne weitere Konfigurationen erzeugt der Linker ein lauffähiges Programm ab der Adresse 1000H. Im JKCEmu kann die 
`*.bin` Datei auf die Adresse 1000H geladen und gestartet werden. Eine minimale Kommandozeile sieht daher so aus

```
$ zcc +kc -o HelloWorld.bin test.c
```

Der Parameter `-create-app` ist dafür verantwortlich eine etwas einfacher zu verwendende `*.KCC` zu erzeugen. Im Vorblock ist dort bereits die
Anfangsadresse, Endadresse und Startadresse enthalten.

### Debuginformationen

Im Entwicklungsalltag haben sich die beiden Parameter `--list` und `-g` gelegentlich als nützlich erwiesen. Der Parameter `-g` sorgt für die 
Ausgabe einer `*.def` Datei. Darin sind alle Symbole (Variablen, konstanten, Methoden, ...) mit ihrer jeweiligen Adresse enthalten. Das hilft im 
Debugger beim Setzen von Breakpoints.
Mit `--list` wird der erzeugte Assembler und Maschinencode in `*.lis` Dateien ausgegeben. Das hilft ebenfalls den Überblick im Debugger zu behalten
und zu prüfen welchen Code der z88dk erzeugt hat.


