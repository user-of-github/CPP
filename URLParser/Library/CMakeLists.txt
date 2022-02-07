cmake_minimum_required(VERSION 3.19)
project(URLParserStaticLibrary)
set(CMAKE_CXX_STANDARD 20)
add_library(URLParser ./Library/URL/url.cpp ./Library/Utils/utils.cpp)