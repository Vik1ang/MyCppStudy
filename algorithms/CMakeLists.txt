cmake_minimum_required(VERSION 3.2)

project(Algorithms
        LANGUAGES CXX
        VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    set(CMAKE_CXX_STANDARD 14)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif (MSVC)

option(USE_OPENMP "flag to use OpenMP for multithreading" ON)
if (USE_OPENMP)
    find_package(OpenMP 3.0 COMPONENTS CXX)
    if (OpenMP_CXX_FOUND)
        message(STATUS "Building with OpenMP Multithreading.")
    else ()
        message(STATUS "No OpenMP found, no multithreading.")
    endif ()
endif ()

add_subdirectory(search)

cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0057 NEW)