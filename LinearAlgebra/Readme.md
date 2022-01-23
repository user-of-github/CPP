## Simple Linear Algebra Library
###### Educational purposes


### _Description:_
_The first project in my C++ Repo.   
Hope not the last :)  
Project's aim — repeat some linear algebra topics, code them, try practicing modern C++. Start using tests (Google tests) and CMake. Maybe even GitHub Actions (?)  
Here for the first time using CMake myself and Gtests_

### _To Run tests:_
1. `cd Tester`
2. `cmake -S . -B build -G "MinGW Makefiles"` _// or your [generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html)_
3. `cmake --build build`
4. `cd build && ctest`

### _To run custom user's code - `sandbox.cpp`:_
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
    - [x] Operators (via already realized Vector's ones)
    - [x] Ostream operator
    - [x] Multiplication // native
        - [x] Pow
    - [x] Determinant
    - [x] Transposing
    - [x] Triangulation (Gauss-method, Upper)
    - [x] Identity (Unit) matrix
    - [x] Extracting submatrix for minor 
    - [x] Minor
      - [x] Cofactor 
    - [x] Is symmetric  
    - [x] Track (Spur)
    - [ ] Rank (rang ?) and other measures
    - [ ] Norm (?)
    - [x] Inverse matrix
    - [ ] Equations systems solvers (?)
        - [ ] Gauss 
        - [ ] Jacobi
        - [ ] Simple iterations
        - [ ] Zeidel
        - [ ] Kramer 
    - [ ] Cast to Vector (if 1 row)
- [ ] __MakeFile__
  - [x] Cmake
- [x] __Tests:__
  - [ ] Connect to `CodeCov`
  - [x] Test with `Google tests` ([gtest CMake tutorial](https://google.github.io/googletest/quickstart-cmake.html))
  - [x] Or at least start testing with `assert.h` (`cassert`) 
  - [ ] Bage with tests in Readme.md
- [ ] __GitHub Actions__ (— for what ?? — don't know, but may be useful)
    


### _Some more features:_  
* Template classes
* Google C++ code style (style guide)
* Modern features: STD functions, auto lambda expressions, constexpr and so on
* Google Tests, hundreds of code-lines with tests
* CMake


#### _Developed with:_
* JetBrains Clion
* Google Tests
* GNU
&nbsp;  

###### © 2022 | All Rights Reserved