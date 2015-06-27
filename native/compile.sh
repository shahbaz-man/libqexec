#!/bin/bash
gcc -shared -fPIC -I. -I/opt/jdk/include -I/opt/jdk/include/linux libqexec.c -o libqexec.so