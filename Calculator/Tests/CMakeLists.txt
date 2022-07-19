cmake_minimum_required(VERSION 3.14)
project(test_calculator)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        unit_tests_pack
        main.cpp
        test_utils.cpp
        types_for_tests.hpp
        data_for_tests.hpp
        ../Library/Utils/utils.cpp
        test_calculator.cpp)
target_link_libraries(
        unit_tests_pack
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests_pack)
