#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

std::recursive_mutex mtx1;

/// NOTE: please lock mtx1 before calling other()
void other()
{
    mtx1.lock();
    // do something
    mtx1.unlock();
}

void func()
{
    mtx1.lock();
    other();
    mtx1.unlock();
}

int main()
{
    func();
    return 0;
}