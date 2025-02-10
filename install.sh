#!/bin/bash
mkdir -p $1/include
mkdir -p $1/lib
cp ./crt0.o $1/lib/crt0.o
cp ./tlibc.a $1/lib/libc.a
cp $(find ./include/ -name "*.h") $1/include