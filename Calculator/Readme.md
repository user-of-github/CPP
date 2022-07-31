## _Calculator_

### _Description_

_A type of Calculator app, which can compute provided string with arithmetic expression and count a response for it. Can
work with brackets and variable operators with different priorities.
Uses __[reversal polish notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation)__._
______________________________________

_Different types of brackets. Spaces between characters for comfortable input_

### Used:

* _C++ 17_
* _[CMake](https://cmake.org/)_
* _[Google Tests](https://github.com/google/googletest)_
* _[GitHub Actions CI](https://github.com/features/actions)_  
* _[Google C++ CodeStyle](https://google.github.io/styleguide/cppguide.html)_

### _To run tests:_

0. _You must have GNU 9.2.0+ installed_
1. _Move to `Tests` folder `cd Tests`_
2. _You may just run a script `test.sh`_
3. _Or do everything manually_
4. _`rm -rf ./build`_
5. _`cmake -S . -B build -G "MinGW Makefiles"`_
6. _`cmake --build build`_
7. _`cd build && ctest`_

### Cases to implement:

* [x] Minus (as sign and for numbers) (`-2` and `6 - (5 + 6)`)
* [ ] Chain of pows (2^2^2^2)
* [ ] Brackets
* [x] The idea of converters for different types of numbers (one default and other can be for my custom types)
* [x] The idea of extractors for different types of numbers
* [x] Make it work as template or constructor params
* [ ] Copy constructor, Move Constructor, operators
* [ ] Refactor

&nbsp;

###### Copyright © 2022 | All rights reserved