#!/bin/bash

gcc $1.c -o $1 -Wall -Wextra -no-pie -Wl,-z,relro -Wl,-z,now
patchelf --set-interpreter ./ld-2.29.so --set-rpath . studysim
