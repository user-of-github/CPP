cmake_minimum_required(VERSION 3.19)
project(demo_sandbox_url_parser)
set(CMAKE_CXX_STANDARD 20)
add_executable(demo sandbox.cpp ./Library/Url/url.cpp ./Library/Utils/utils.cpp)