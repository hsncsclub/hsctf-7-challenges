#!/bin/bash

gcc $1.c -o $1 -Wall -Wextra -no-pie -Wl,-z,relro -Wl,-z,now
