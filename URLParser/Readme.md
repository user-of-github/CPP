## Simple web-URL Parser

###### Educational purposes

### _Description:_

_This is the second project in my CPP repository.  
Project's aim is to • practice regular expressions in C++, • create plugin for validating and parsing Url-expressions, •
use some modern C++ features, • also use Gtest and CMake_

### _To Run tests:_

* From root directory move to Tests: `cd Tests`
* Run `cmake -S . -B build -G "MinGW Makefiles"` // or
  your [generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) (NMake, Ninja...)
* Run `cmake --build build`
* Move to `build` and run tests: `cd build && ctest`
* Also it may be able to add configuration to Clion (or just choose CMakeLists in `Tests` folder) and run tests just by `ctrl + F5` or button `Run`
  clicking

### _To run custom user's code - `sandbox.cpp`:_

### _Functionality / To Do:_

- [ ] Validating of all kinds of Url
- [ ] Extracting Url parts:
    - [ ] Protocol
    - [ ] Domain
    - [ ] Pathname (filename ?)
    - [ ] Query string
    - [ ] ... ?
- [ ] Parsing query string to a pair of strings: <key, value>
- [ ] Maybe email parser ?
- [x] Build with CMake
- [x] Link to [gtest](https://github.com/google/googletest)  


### _Additional To Do:_  
* [ ] Check copy constructors and operators  
* [ ] Code style (tabs, empty lines, variable names, dublicating)

### _Some more features:_

* _Tests coverage from the very beginning of creating features_

#### _Developed with:_

* _C++ 11 and newer_
* _JetBrains Clion 2021_
* _CMake_
* _MinGW, GNU_
* _Google tests_
* _"C++ 17 STL Cookbook"_

###### © 2022 | All Rights Reserved