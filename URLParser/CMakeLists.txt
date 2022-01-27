CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project(url_sandbox)

SET(CMAKE_CXX_STANDARD 20)

add_executable(demo sandbox.cpp ./Library/Utils/utils.cpp ./Library/URL/url.cpp)