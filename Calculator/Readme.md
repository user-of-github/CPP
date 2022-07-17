## _Calculator_

### _Description_

_A type of Calculator app, which can compute provided string with arithmetic expression and count a response for it. Can
work with brackets and variable operators with different priorities.
Uses __[reversal polish notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation)__._

### Used:

* _C++ 17_
* _[CMake](https://cmake.org/)_
* _[Google Tests](https://github.com/google/googletest)_
* _[GitHub Actions CI](https://github.com/features/actions)_


### _To run tests:_  
0. Move to `Tests` folder `cd Tests`  
1. You may just run a script `test.sh`  
2. Or do everything manually 
3. `rm -rf ./build`  
4. `cmake -S . -B build -G "MinGW Makefiles"`  
5. `cmake --build build`  
6. `cd build && ctest`

&nbsp;

###### Copyright © 2022 | All rights reserved