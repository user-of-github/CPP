## Simple Linear Algebra Library

###### Educational purposes

### _Description:_

_The first project in my C++ Repo.   
Hope not the last :)  
Simple Linear Algebra lib to work with numeric vectors, matrices, systems of equations and so on  
Project's aim — • repeat some linear algebra topics, • code them, • try practicing (modern) C++, • start using tests (Google tests) and • CMake, • maybe even GitHub Actions. Here for the first time using CMake myself and Gtests_

### _To Run tests:_

1. `cd Tester`
2. `cmake -S . -B build -G "MinGW Makefiles"` _// or your [generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html)_
3. `cmake --build build`
4. `cd build && ctest`  
5. In JetBrains Clion it is possible to choose main `CMakeLists.txt` (so it's necessary to choose one from `Tester` folder) — and it will be possible to run tests automatically by `ctrl + F5` or `Run` button. Also it will be necessary to choose `All CTest | Debug` in select of configuration

### _To build a static library:_
1. `cd Library`  
2. `cmake . -B build -G "MinGW Makefiles"` _// or your [generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html)_  
3. `cmake --build build`

### _Functionality / To Do:_

- [x] __Vector class__
    - [x] Template
    - [x] Copy constructor and = operator
    - [x] Operators
    - [x] Ostream operator
    - [x] Norm
    - [x] Normalization
    - [ ] &times; Convert / Transform (with lambda as argument)
    - [x] Sum
    - [x] Friend class for Matrix class
    - [x] Cast to Matrix
- [x] __Matrix class__ (can also represent Vector)
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
    - [x] Rank
    - [ ] &times; Norm (?)
    - [x] Inverse matrix
    - [x] Cast to Vector (if 1 row)
- [x] __Equations systems solvers class__
  - [x] Gauss
  - [ ] &times; Jacobi
  - [ ] &times; Simple iterations
  - [ ] &times; Zeidel
  - [x] Cramer
  - [x] By inverse matrix    
- [x] __CMake__
- [x] __Tests:__
    - [ ] &times; Connect to `CodeCov`
    - [x] Test with `Google tests` ([gtest CMake tutorial](https://google.github.io/googletest/quickstart-cmake.html))
    - [x] Or at least start testing with `assert.h` (`cassert`)
    - [ ] &times; Bage with tests in Readme.md
- [ ] &times; __GitHub Actions__ (— for what ? — don't know yet, but may be useful)

### _Some more features:_

* Template classes
* Google C++ code style (style guide)
* Modern features: STD functions, auto lambda expressions, constexpr and so on
* Google Tests, hundreds of code-lines with tests
* CMake-s for tests and for building a lib 

   
&nbsp;  


###### © 2022 | All Rights Reserved