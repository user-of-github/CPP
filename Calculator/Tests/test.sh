#!/bin/bash

rm -rf ./build

cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
cd build && ctest

# shellcheck disable=SC2162
read -p "Press any key to continue... " -n1 -s
