#include <cstdint>
#include <cstdio>

int func(int* psecond)
{
    if (psecond != 0) {
        *psecond = 2;
    }
    return 1;
}

int func(int second)
{
    return 42;
}

int main()
{
    int first = func(0);
    printf("first: %d\n", first);
    return 0;
}