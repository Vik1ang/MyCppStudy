#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

/**
 * @brief using fibonacci search algorithm finds an index of a given element in
 * a sorted array
 *
 * @param arr sorted array
 * @param value value that we're looking for
 * @returns if the array contains the value, returns an index of the element.
 * otherwise -1.
 */
int fibonacci_search(const std::vector<int> &arr, int value) {
    // initialize last and current members of Fibonacci sequence
    int last = 0, current = 1;
    int length = arr.size(); // array size
    // next member of Fibonacci sequence which is "last" + "current"
    int next = last + current;

    // "next" will store the smallest Fibonacci number greater or equal to "length"
    while (next < length) {
        last = current;
        current = next;
        next = last + current;
    }

    // "offset" is the end of eliminated range from front
    int offset = -1;
    int index;

}