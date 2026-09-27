cmake_minimum_required(VERSION 4.4)
project(reports_service)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Crow REQUIRED)

pkg_check_modules(PQXX REQUIRED libpqxx)
pkg_check_modules(XLSXWRITER REQUIRED xlsxwriter)

add_executable(reports_service ./src/main.cpp)

target_include_directories(reports_service PRIVATE
        ${PQXX_INCLUDE_DIRS}
        ${XLSXWRITER_INCLUDE_DIRS}
)

target_link_libraries(reports_service PRIVATE
        Crow::Crow
        ${CMAKE_THREAD_LIBS_INIT}
        ${PQXX_LIBRARIES}
        ${XLSXWRITER_LIBRARIES}
)
