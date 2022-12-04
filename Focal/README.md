# Focal

Das Programm ist ein für den KC 85/2+ angepasster Focal Interpreter. Der ursprüngliche C Code des Focal Interpreters stammt von
<http://www.catb.org/retro/>. Dort befindet sich unter 'Focal' ein Archiv mit den C Quellen. Diese Quellen wurden leicht modifiziert um sie mit dem
z88dk für den KC zu kompilieren.

In der englischen Wikipedia gibt es einen längeren Artikel zu [Focal](https://en.wikipedia.org/wiki/FOCAL_\(programming_language\)). Dort gibt es einen
ersten Einblick in die Syntax. Unter <http://bitsavers.informatik.uni-stuttgart.de/pdf/dec/pdp8/focal/> Gibt es verschiedene Dokumente welche einige 
verschiedenen Dialekte der Sprache genauer beschreiben.

In [focal.doc](focal.doc) ist der Sprachumfang dieses Focal Interpreters beschrieben. Einige besondere Eigenheiten:
- Bei Sprüngen muss die vollständige Zeilennummer angegeben werden. `G 5.5` funktioniert nicht, es muss `G 5.50` lauten.
- Formatanweisungen müssen vollständig angegeben werden. `TYPE "A+B= ", %1, A+B!` muss durch `TYPE "A+B= ", %1.0, A+B!` ersetzt werden.
- Es werden nur Runde Klammern unterstützt, diese können dafür geschachtelt werden.
- Die Ausgabe der Symboltabelle mit `TYPE $` wird nicht unterstützt.

## Kompilieren

Siehe [compile.bat](compile.bat) für die genaue Kommandozeile zum kompilieren. 

Für die Mathematik Libs wird die `genmath` verwendet und da wir uns auf dem KC mit speziellem IX Register befinden wird die Variante `genmath_iy` 
verwendet. 

## Vorschau

Hier ein Bild von Focal auf dem KC Emulator: 

![FocalAufKC.png](/images/FocalAufKC.png)

## Beispiel

Ein Focal Programm zum Berechnen des Wochentags zu einem eingegebenem Datum:

```
01.01 C     CALNDR FROM 'PROGRAMMING LANGUAGES' COPYRIGHT 1970               
01.02 C     BY DIGITAL EQUIPMENT CORPORATION                                        
01.03 C     LAST CHANGE: 8/13/71                                                    
01.04 
01.05 C     GIVEN THE MONTH/DATE/YEAR, THE "PERPETUAL                                 
01.06 C CALENDAR" WILL TYPE THE DAY OF THE WEEK.                                      
01.07 
01.30 A "WHAT IS THE DATE?  (MM/DD/YYYY) ",M,K,C
01.32 I (M-13) 1.35;T "IN ORDER TO MAKE ROOM FOR THE MONTHS, THERE WERE NO DAYS!"!;G 1.30
01.35 I (K-32) 1.40;T "MONTHS WITH",%3.0,K," DAYS DON'T EXIST IN",%4.0,C,"!"!;G 1.30
01.40 S C=C/100;S D=FITR(.1+100*(C-FITR(C)));S C=FITR(C)
01.50 S M=M-2;I (M) 5.40,5.40;G 5.50

05.40 S M=M+12;S D=D-1;I (-D) 5.50,5.50;S D=99;S C=C-1
05.50 S X=FITR(FITR(2.6*M-.2)+K+D+FITR(D/4)+FITR(C/4)-2*C)
05.60 I (X-6) 5.70,5.70;S X=X-7;G 5.60
05.70 T !"THE DAY IS ";D 6.10
05.90 T !!;G 1.30

06.10 I (X) 6.26,6.20;I (X-2) 6.21,6.22,6.15
06.15 I (X-4) 6.23,6.24;I (X-6) 6.25,6.26
06.20 T "SUNDAY
06.21 T "MONDAY
06.22 T "TUESDAY
06.23 T "WEDNESDAY
06.24 T "THURSDAY
06.25 T "FRIDAY";I (FABS(K-13)),6.30;
06.26 T "SATURDAY"
06.30 T " THE 13TH!!"
```
