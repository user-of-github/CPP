#!/bin/bash

rm -rf ./build
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
cd build && ctest