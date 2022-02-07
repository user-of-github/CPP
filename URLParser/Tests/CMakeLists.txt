cmake_minimum_required(VERSION 3.14)

project(tests_url_parser)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-std=gnu++2a")


include(CTest)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(unit_tests_pack test_utils.cpp test_url.cpp tests_main.cpp)

target_link_libraries(unit_tests_pack gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests_pack)