set -e

gcc -fomit-frame-pointer -fverbose-asm -S main.cpp -o main.S