rem genmath verwendet das IX Register :-(
rem zcc +kc -lgenmath -DAMALLOC -o focal.bin -create-app focal0.c focal1.c focal2.c focal3.c
rem zcc +kc -lgenmath_iy -DAMALLOC -o focal.bin -create-app focal0.c focal1.c focal2.c focal3.c

zcc +kc -lgenmath_iy -o focal.bin -create-app focal0.c focal1.c focal2.c focal3.c
