## Simple web-URL Parser

###### Educational purposes

### _Description:_

_Here is the second project in my CPP repository.  
Project's aim is to • learn regular expressions fundamentals and practice them in C++, • create class for validating and parsing Url-expressions, •
use some modern C++ features, • also use Gtest and CMake_

### _To Run tests:_

* From root directory move to Tests: `cd Tests`
* Run `cmake -S . -B build -G "MinGW Makefiles"` // or
  your [generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) (NMake, Ninja...)
* Run `cmake --build build`
* Move to `build` and run tests: `cd build && ctest`
* Also it may be able to add configuration to Clion (or just choose CMakeLists in `Tests` folder) and run tests just
  by `ctrl + F5` or button `Run`
  clicking

### _To build a lib:_

### _Functionality / To Do:_

- [ ] Validating of all kinds of Url
- [ ] Extracting URL parts:
    - [x] Protocol
    - [ ] Host
    - [ ] Domain zone
    - [ ] Pathname (filename ?)
    - [ ] Query string
    - [ ] Hash
    - [ ] ... ?
- [ ] Parsing query string to a pair of strings: <key, value>
- [ ] Getting query parameter by name (key)
- [ ] Maybe email parser ?
- [x] Build with CMake
- [x] Link to [gtest](https://github.com/google/googletest)  
&nbsp;  
__+ Utils:__
  - [x] Trim
  - [ ] Split

### _Additional To Do:_
* [ ] Check copy constructors and operators
* [ ] Code style (tabs, empty lines, variable names, dublicating)

### _Some more features:_
* _Tests coverage from the very beginning of creating features_



###### © 2022 | All Rights Reserved