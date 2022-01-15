## Simple Linear Algebra Library
###### Educational purposes


### _Description:_
_The first project in my C++ Repo.   
Hope not the last :)  
Project's aim — repeat some linear algebra topics, code them practice modern C++ with STL, lambdas and so on. Start using tests (Google tests) and CMake_

### _To Run tests:_
1. `cd Tester`
2. `cmake -S . -B build -G "MinGW Makefiles"` _// or your [generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html)_
3. `cmake --build build`
4. `cd build && ctest`

### _Functionality / To Do:_

- [x] __Vector Class__
    - [x] Template
    - [x] Copy constructor and = operator
      - [x] Tests
    - [x] Operators
      - [x] Tests
    - [x] Ostream operator
    - [x] Norm  
      - [x] Tests
    - [x] Normalization
      - [x] Tests
    - [ ] Convert / Transform (with lambda as argument)
    - [x] Sum
    - [x] Friend class for Matrix class
- [x] __Matrix Class__ (can also represent Vector)
    - [ ] Operators (via already realized Vector's ones)
    - [x] Ostream operator
    - [ ] Multiplication
        - [ ] Pow
        - [ ] Tests
    - [ ] Minor 
        - [ ] Tests
    - [ ] Determinant
      - [ ] Tests
    - [ ] Transposing
      - [ ] Tests
    - [ ] Converting to upper/lower triangled 
      - [ ] Tests
    - [ ] Rank (rang ?) and other measures
      - [ ] Tests
    - [ ] Inverse matrix
      - [ ] Tests
    - [ ] Equations systems solvers (?)
        - [ ] Gauss
        - [ ] Other
        - [ ] ...
- [ ] __MakeFile__
  - [ ] Cmake (?)
- [x] __Tests: Connect to `CodeCov` or `Google tests` ([gtest](https://google.github.io/googletest/quickstart-cmake.html))__
  - [x] Or at least start testing with `assert.h`  
    


### _Some more features:_  
* Template classes
* Google C++ code style (style guide)
* Modern STD functions, auto lambda expressions
* Google Tests


#### _Developed with:_
* JetBrains Clion
* Google Tests
&nbsp;  

###### © 2022 | All Rights Reserved