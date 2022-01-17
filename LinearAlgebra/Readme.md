## Simple Linear Algebra Library
###### Educational purposes


### _Description:_
_The first project in my C++ Repo.   
Hope not the last :)  
Project's aim — repeat some linear algebra topics, code them, practice modern C++ with STL, lambdas and so on. Start using tests (Google tests) and CMake  
Here for the first time using Cmake myself and gtests_

### _To Run tests:_
1. `cd Tester`
2. `cmake -S . -B build -G "MinGW Makefiles"` _// or your [generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html)_
3. `cmake --build build`
4. `cd build && ctest`

### _To run user's code in "sandbox" file - `demo.cpp`:_
1. From `root` folder: `cmake -S . -B build -G "MinGW Makefiles"` _// or your [generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html)_
2. `cmake --build build`
3. `cd build`, `demo(.exe)`

### _Functionality / To Do:_

- [x] __Vector Class__
    - [x] Template
    - [x] Copy constructor and = operator
    - [x] Operators
    - [x] Ostream operator
    - [x] Norm  
    - [x] Normalization
    - [ ] Convert / Transform (with lambda as argument)
    - [x] Sum
    - [x] Friend class for Matrix class
    - [ ] Cast to Matrix
- [x] __Matrix Class__ (can also represent Vector)
    - [ ] Operators (via already realized Vector's ones)
    - [x] Ostream operator
    - [ ] Multiplication
        - [ ] Pow
        - [ ] Tests
    - [ ] Minor
    - [ ] Spur / Track (след)
    - [ ] Rang
    - [ ] Determinant
    - [x] Transposing
    - [ ] Converting to upper/lower triangled 
    - [ ] Rank (rang ?) and other measures
    - [ ] Inverse matrix
    - [ ] Equations systems solvers (?)
        - [ ] Gauss
        - [ ] Other
        - [ ] ...
    - [ ] Cast to Vector (if 1 row)
- [ ] __MakeFile__
  - [x] Cmake (?)
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