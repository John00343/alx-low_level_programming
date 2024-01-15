#!/bin/bash
gcc -c *.c -fpic && gcc *.o -shared liball.so
