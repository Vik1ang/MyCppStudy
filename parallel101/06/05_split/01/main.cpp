#include "mtprint.h"
#include "ticktock.h"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/partitioner.h>
#include <tbb/task.h>
#include <thread>
#include <vector>

int main()
{
    size_t n = 32;

    tbb::task_arena ta(4);
    ta.execute([&] {
        tbb::parallel_for(
            tbb::blocked_range<size_t>(0, n), [&](tbb::blocked_range<size_t> r) {
                mtprint("thread", tbb::this_task_arena::current_thread_index(), "size", r.size());
                std::this_thread::sleep_for(std::chrono::milliseconds(400));
            },
            tbb::static_partitioner {});
    });

    return 0;
}