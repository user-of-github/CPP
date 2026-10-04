cmake_minimum_required(VERSION 4.4)
project(reports_service)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable C++20/23 modules scanning — Crow/asio headers are not modules-compatible
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Crow REQUIRED)

pkg_check_modules(PQXX REQUIRED libpqxx)
pkg_check_modules(XLSXWRITER REQUIRED xlsxwriter)

add_executable(reports_service ./src/main.cpp
        src/common/env.hpp
        src/modules/reports/reports_controller.hpp
        src/modules/reports/reports_controller.cpp
        src/modules/reports/reports_repository.hpp
        src/modules/reports/reports_repository.cpp
        src/modules/reports/excel_generator.hpp
        src/modules/reports/excel_generator.cpp)

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

# Disable C++ modules scanning for this target
set_property(TARGET reports_service PROPERTY CXX_SCAN_FOR_MODULES OFF)
