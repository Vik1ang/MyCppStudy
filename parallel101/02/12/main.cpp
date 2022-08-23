#include <cstdio>
#include <cstdlib>
#include <stdio.h>

struct C {
    C()
    {
        printf("分配内存!\n");
    }

    ~C()
    {
        printf("释放内存!\n");
    }
};

int main()
{
    C* p = new C;

    if (rand() != 0) {
        printf("出了点小状况……\n");
        // delete p; // 心忘记释放指针
        return 1;
    }

    delete p;

    return 0;
}