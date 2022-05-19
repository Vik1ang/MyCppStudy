CMAKE_MINIMUM_REQUIRED(VERSION 3.10.0)

PROJECT(LEETCODE)

add_subdirectory(src)

target_include_directories(lc PRIVATE include)
