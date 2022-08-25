#include <cstdio>
#include <stdio.h>

int main()
{
    int x = 233;
    int& ref = x;
    ref = 42;
    printf("%d\n", x);
    x = 1024;
    printf("%d\n", ref);

    return 0;
}
