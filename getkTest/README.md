# getkTest

Das Programm zeigt wie die Tastatur mit getk() aus [<stdio.h>](https://github.com/z88dk/z88dk/wiki/stdio) abgefragt werden kann. 
Das Programm wurde ursprünglich geschrieben um einen [Fehler](https://github.com/z88dk/z88dk/issues/2081) in getk() nachzustellen. 

Das Programm zeigt einen Zähler und den dezimalen Tastaturcode der gerade gedrückten Taste. Wenn keine Taste gedrückt ist, dann wird 0 angezeigt.

Das Programm reagiert auf die Tasten X und H. Mit X wird das Programm beendet.

## Kompilieren

```
$ zcc +kc -o getk.bin -create-app GetkTest.c
```
