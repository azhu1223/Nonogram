#!/bin/sh

if [ "$#" -gt 0 ]; then
    if [ "$#" -gt 1 ] || [ "$1" = "--help" ]; then
        echo "Usage: ./build.sh [--full/--help]"
        exit 0
    elif [ "$1" = "--full" ]; then
        rm -rf build/*
    fi
fi

(cd build && cmake .. && cmake --build . && ctest)
