cmake_minimum_required(VERSION 4.0)
project(embedded2026 VERSION 0.0.0 LANGUAGES C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(cmake/global.cmake)
option(BUILD_DOC "Build documentation" ON)

include(cmake/doxygen.cmake)
add_subdirectory(mcal)
add_subdirectory(projects)
