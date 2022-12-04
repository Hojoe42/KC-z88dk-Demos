# kompilieren mit dem sdccz80
zcc +kc -o cls-sccz80.bin -create-app ClsTest.c

# kompilieren mit dem sdcc
zcc +kc -compiler sdcc -Cs--reserve-regs-iy -o csl-sdcc.bin -create-app ClsTest.c
