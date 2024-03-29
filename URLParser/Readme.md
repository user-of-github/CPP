## Simple web-URL Parser

###### Educational purposes

### _Description:_

_Here is the second project in my CPP repository.  
Project's aim is to • learn regular expressions fundamentals and practice them in C++, • create class for validating and parsing Url-expressions, •
use some modern C++ features, • also use Gtest and CMake_

### _To Run tests:_

* From root directory move to Tests: `cd Tests`
* Run `cmake -S . -B build -G "MinGW Makefiles"` // or your [generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) (NMake, Ninja...)
* Run `cmake --build build`
* Move to `build` and run tests: `cd build && ctest`
* Also it may be able to add configuration to Clion (or just choose CMakeLists in `Tests` folder) and run tests just
  by `ctrl + F5` or button `Run`
  clicking

### _To build a lib:_  

* From root directory move to Library: `cd Library`
* Run `cmake -S . -B build -G "MinGW Makefiles"` // or
  your [generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) (NMake, Ninja...)
* Run `cmake --build build`

### _Functionality / To Do:_

- [x] Validating of web-Url-s
- [x] Extracting URL parts:
    - [x] Protocol
    - [x] Host
    - [x] Domain zone
    - [x] Port 
    - [x] Pathname (filename ?)
    - [x] Query string
    - [x] Hash
- [x] Parsing query string to pairs of strings: <key, value>
- [x] Getting query parameter by name (key)
- [x] Ostream operator 
- [ ] Maybe email parser ?
- [x] Build with CMake
- [x] Link to [gtest](https://github.com/google/googletest)  
&nbsp;  
__+ Utils:__
  - [x] Trim
  - [x] ± Split
- [ ] Maybe some badge in Readme ? 
- [x] Maybe GitHub actions for something ? // just running gtest


### _Additional To Do:_
* [x] Check copy constructors and operators
* [x] Code style

### _Some more features:_
* _Tests coverage from the very beginning of creating features_



###### © 2022 | All Rights Reserved