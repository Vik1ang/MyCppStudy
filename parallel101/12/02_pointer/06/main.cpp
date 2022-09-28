#include <cstdint>
#include <cstdio>

int func(int* psecond)
{
    if (psecond != NULL) {
        *psecond = 2;
    }
    return 1;
}

int main()
{
    int second;
    int first = func(NULL);
    printf("first: %d\n", first);
    return 0;
}