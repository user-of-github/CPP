cmake_minimum_required(VERSION 3.14)
project(test_library)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        unit_tests_pack
        test_main.cpp
        test_vector.cpp
        test_matrix.cpp
        test_equ_system_solve.cpp
)
target_link_libraries(
        unit_tests_pack
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests_pack)