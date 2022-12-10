# Focal

Das Programm ist ein für den KC 85/2+ angepasster Focal Interpreter. Der ursprüngliche C Code des Focal Interpreters stammt von
<http://www.catb.org/retro/>. Dort befindet sich unter 'Focal' ein Archiv mit den C Quellen. Diese Quellen wurden leicht modifiziert um sie mit dem
z88dk für den KC zu kompilieren.

In der englischen Wikipedia gibt es einen längeren Artikel zu [Focal](https://en.wikipedia.org/wiki/FOCAL_\(programming_language\)). Dort gibt es einen
ersten Einblick in die Syntax. Unter <http://bitsavers.informatik.uni-stuttgart.de/pdf/dec/pdp8/focal/> gibt es verschiedene Dokumente, welche einige 
verschiedenen Dialekte der Sprache genauer beschreiben.

In [focal.doc](focal.doc) ist der Sprachumfang dieses Focal Interpreters beschrieben. Einige besondere Eigenheiten:
- Bei Sprüngen muss die vollständige Zeilennummer angegeben werden. `G 5.5` funktioniert nicht, es muss `G 5.50` lauten.
- Formatanweisungen müssen vollständig angegeben werden. `TYPE "A+B= ", %1, A+B!` muss durch `TYPE "A+B= ", %1.0, A+B!` ersetzt werden.
- Bei Funktionen müssen immer runde Klammern verwendet werden und es muss genau ein Parameter angegeben werden. Das gibt auch für FRAN, obwohl der Parameter von der Funktion nicht ausgewertet wird.
- Die Ausgabe der Symboltabelle mit `TYPE $` wird nicht unterstützt.
- Strings müssen am Anfang und am Ende jeweils ein doppeltes Hochkomma (") besitzen.
- Exponenten müssen mit kleinem e geschrieben werden: '1e6' -> eine Million

## Kompilieren

Siehe [compile.bat](compile.bat) für die genaue Kommandozeile zum kompilieren. 

Für die Mathematik Libs wird die `genmath` verwendet und da wir uns auf dem KC mit speziellem IX Register befinden wird die Variante `genmath_iy` 
verwendet. 

## Vorschau

Hier ein Bild von Focal auf dem KC Emulator: 

![FocalAufKC.png](/images/FocalAufKC.png)

## Beispiele

Ein Focal Programm zum Berechnen des Wochentags zu einem eingegebenem Datum:

```
01.01 C     CALNDR FROM 'PROGRAMMING LANGUAGES' COPYRIGHT 1970               
01.02 C     BY DIGITAL EQUIPMENT CORPORATION                                        
01.03 C     LAST CHANGE: 8/13/71                                                    
01.04 
01.05 C     GIVEN THE MONTH/DATE/YEAR, THE "PERPETUAL                                 
01.06 C CALENDAR" WILL TYPE THE DAY OF THE WEEK.                                      
01.07 
01.30 A "WHAT IS THE DATE?  (MM/DD/YYYY) ",M,D,Y
01.32 I (M-13) 1.35;T "IN ORDER TO MAKE ROOM FOR THE MONTHS, THERE WERE NO DAYS!"!;G 1.30
01.35 I (D-32) 5.30;T "MONTHS WITH",%3.0,D," DAYS DON'T EXIST IN",%4.0,Y,"!"!;G 1.30

05.30 S M=M-2;I (M) 5.40,5.40;G 5.45
05.40 S M=M+12;S Y=Y-1;
05.45 S C=FITR(Y/100);S Y=Y-100*C
05.50 S X=D+FITR(2.6*M-.2)+Y+FITR(Y/4)+FITR(C/4)-2*C
05.53 I (X) 5.55,5.60,5.60
05.55 S X=X+7; G 5.53
05.60 I (X-6) 5.70,5.70;S X=X-7;G 5.60
05.70 T !"THE DAY IS ";D 6.10
05.90 T !!;G 1.30

06.10 I (X) 6.26,6.20;I (X-2) 6.21,6.22,6.15
06.15 I (X-4) 6.23,6.24;I (X-6) 6.25,6.26
06.20 T "SUNDAY"
06.21 T "MONDAY"
06.22 T "TUESDAY"
06.23 T "WEDNESDAY"
06.24 T "THURSDAY"
06.25 T "FRIDAY";I (FABS(D-13)),6.30;
06.26 T "SATURDAY"
06.30 T " THE 13TH!!"
```

und hier noch eine kleine Wirtschaftssimulation

```
01.01 C     HAMURABI, WRITTEN BY DOUG DYMENT (1969)
01.02 C     FOR DIGITAL EQUIPMENT CORPORATION
01.03 C     angepasst an den KC85 by Dirk (2022)
01.04 C     - German Version -
01.05
01.10 S P=95;S S=2800;S H=3000;S E= 200;S Y=3;S A=1000;S I=5;S Q=1

02.10 S D=0
02.20 D 6;T !!!"Letztes Jahr"!D," verhungerten,"
02.25 T !I," wanderten zu,";S P=P+I;I (-Q)2.30
02.27 S P=FITR(P/2);T !"**PEST**"!
02.30 T !"Population ist"P,!!"Die Stadt besitzt"
02.35 T A," Hektar."!!;I (H-1)2.50;T "Wir haben geerntet"
02.40 D 3.20
02.50 T !" Ratten frassen "E," Scheffel, Du hast jetzt"
02.60 T S," Scheffel im Kornhaus."!

03.10 D 6; D 8;S Y=C+17;T "Land wird gehandelt fuer"
03.20 T Y," Scheffel pro Hektar;"!;S C=1
03.30 D 4.30;A " Kaufen?"Q;I (Q)7.20,3.80
03.40 I (Y*Q-S)3.90,3.60;D 4.60;G 3.30
03.50 D 4.50;G 3.30
03.60 D 3.90:G 4.80
03.70 S A=A+Q;S S=Y*Q;S C=0
03.80 A "zu verkaufen?"Q;I (Q)7.20,3.90;S Q=-Q;I (A+Q)3.50
03.90 S A=A+Q;S S=S-Y*Q;S C=0

04.10 T "Scheffel verwenden"
04.11 A " als Nahrung?"Q;I (Q)7.70;I (Q-S)4.20,4.70;D 4.60;G 4.10
04.20 S S=S-Q;S C=1
04.30 A "Wie viele Hektar"
04.35 A " bepflanzen mit Samen? "D
04.40 I (D)7.20;I (A-D)4.45;I (FITR(D/2)-S-1)4.65;D 4.60;G 4.30
04.45 D 4.50;G 4.30
04.50 D 7;T A," Hektar."!
04.60 D 7;D 2.60
04.65 I (D-10*P-1)5.10;D 7;T P," Einwohner."!;G 4.30
04.70 D 4.20
04.80 D 6;T "Du hast kein Getreide zum saehen !!"; T !; S D=0

05.10 S S=S-FITR(D/2);D 8;S Y=C;S H=D*Y
05.20 D 8;S E=0;I (FITR(C/2)-C/2)5.30;S E=S/C
05.30 S S=S-E+H;D 8;S I=FITR(C*(20*A+S)/P/100+1);S C=FITR(Q/20)
05.40 S Q=FITR(10*FABS(FRAN(8)));I (P-C)2.10;S D=P-C;S P=C;G 2.20

06.10 T !!"HAMURABI:  "%5.0

07.10 I (C)7.20;S C=C-1;D 6;T "Aber du hast nur";R
07.20 D 6;T !"Auf Wiedersehen!"!!;Q

08.10 S C=FITR(5*FABS(FRAN(8)))+1
```
