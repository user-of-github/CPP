## Simple URL Parser

###### Educational purposes

### _Description:_

_This is the second project in my CPP repository.  
Project's aim is to • practice regular expressions in C++, • create plugin for validating and parsing URL-expressions, • use some modern C++ features, • also use Gtest and CMake_

### _To Run tests:_
* From root directory move to Tests: `cd Tests`  
* Run `cmake -S -B build -G "MinGW Makefiles""` // or your generator (NMake, Ninja...)  
* Move to `build` and run tests: `cd build && ctest`
* After this maybe it'll become able to add configuration to Clion and run tests just by `ctrl + F5` or button `Run` clicking


### _To run custom user's code - `sandbox.cpp`:_

### _Functionality / To Do:_
- [ ] Validating of all kinds of URL
- [ ] Extracting URL parts:
    - [ ] Protocol
    - [ ] Domain
    - [ ] Pathname (filename ?)
    - [ ] Query string
    - [ ] ... ?
- [ ] Parsing query string to a pair of strings: <key, value>   
- [ ] Maybe email parser ?

### _Some more features:_
* _Tests coverage from the very beginning of creating features_

#### _Developed with:_  
* _C++ 11 and newer_ 
* _JetBrains Clion 2021_
* _CMake_
* _Google tests_
* _"C++ 17 STL Cookbook"_  

###### © 2022 | All Rights Reserved