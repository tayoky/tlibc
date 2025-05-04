#!/bin/sh

#simple utilty to see all the functions
find include -name "*.h" | xargs grep -h " *(*);"
