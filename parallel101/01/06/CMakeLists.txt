cmake_minimum_required(VERSION 3.12)
project(hellocmake LANGUAGES CXX)

add_library(hellolib STATIC hello.cpp)
add_executable(a.out main.cpp other.cpp)
target_link_libraries(a.out PUBLIC hellolib)