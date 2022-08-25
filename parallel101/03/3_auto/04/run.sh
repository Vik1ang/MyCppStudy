export CXX=/usr/bin/clang++
set -e

cmake -B build
cmake --build build
build/cpptest