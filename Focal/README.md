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
- Strings müssen am Anfang und am Ende jeweils ein doppeltes Hochkomma (") besitzen.
- Exponenten müssen mit kleinem e geschrieben werden: '1e6' -> eine Million

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


