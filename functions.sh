#!/bin/sh

#simple utilty to see all the functions
find include -name "*.h" -not -name "syscall.h" | xargs grep -h " *(*);"
