#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

std::mutex mtx1;

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