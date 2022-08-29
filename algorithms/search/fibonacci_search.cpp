#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

/**
 * @namespace search
 * @brief Searching algorithms
 */
namespace search {
/**
 * @namespace binary_search
 * @brief Fibonacci search searching algorithm
 */
namespace fibonacci_search {
/**
 * @brief using fibonacci search algorithm finds an index of a given element in
 * a sorted array
 *
 * @param arr sorted array
 * @param value value that we're looking for
 * @returns if the array contains the value, returns an index of the element.
 * otherwise -1.
 */
int fibonacciSearch(const std::vector<int> &arr, int value) {
    // initialize last and current members of Fibonacci sequence
    int last = 0, current = 1;
    size_t length = arr.size();  // array size
    // next member of Fibonacci sequence which is "last" + "current"
    int next = last + current;

    // "next" will store the smallest Fibonacci number greater or equal to
    // "length"
    while (next < length) {
        last = current;
        current = next;
        next = last + current;
    }

    // "offset" is the end of eliminated range from front
    int offset = -1, index(0);
    // while loop until there are elements left to consider.
    // when "next" becomes 1, last is equal to 0, so search is done,
    // because arr[offset] will already be eliminated.
    while (next > 1) {
        // check if "last" is valid location
        index = std::min(offset + last, static_cast<int>(length - 1));
        // if value is greater than the value at "index", eliminate the subarray
        // from offset to index
        if (arr[index] < value) {
            next = current;
            current = last;
            last = next - current;
            offset = index;
        } else if (arr[index] >
                   value) {  // if value is less than the value at "index",
                             // eliminate the subarray after index + 1
            next = last;
            current = current - last;
            last = next - current;
        } else {  // element is found
            return index;
        }
    }

    // comparing the last element
    if (current && !arr.empty() && arr[offset + 1] == value) {
        return offset + 1;
    }

    // value was not found, return -1
    return -1;
}
}  // namespace fibonacci_search
}  // namespace search

/**
 * @brief random tests for checking performance when an array doesn't contain an
 * element
 */
bool no_occurence_tests() {
    bool passed = true;
    int rand_num(0), rand_value(0), index(0), num_tests = 1000;
    std::vector<int> arr;
    while (num_tests--) {
        arr.clear();
        for (int i = 0; i < 100; i++) {
            rand_num = std::rand() % 1000;
            arr.push_back(rand_num);
        }
        rand_value = std::rand() % 1000;
        while (std::find(arr.begin(), arr.end(), rand_value) != arr.end()) {
            std::remove(arr.begin(), arr.end(), rand_value);
        }
        sort(arr.begin(), arr.end());
        index = search::fibonacci_search::fibonacciSearch(arr, rand_value);
        passed = passed && (index == -1);
    }
    return passed;
}

/**
 * @brief random tests which cover cases when we have one, multiple or zero
 * occurences of the value we're looking for
 */
bool random_tests() {
    bool passed = true;
    int rand_num(0), rand_value(0), index(0), real_value(0), num_tests = 1000;
    std::vector<int> arr;
    while (num_tests--) {
        arr.clear();
        for (int i = 0; i < 100; i++) {
            rand_num = std::rand() % 1000;
            arr.push_back(rand_num);
        }
        rand_value = std::rand() % 1000;
        std::sort(arr.begin(), arr.end());
        index = search::fibonacci_search::fibonacciSearch(arr, rand_value);
        if (index != -1) {
            real_value = arr[index];
            passed = passed && (real_value == rand_value);
        } else {
            passed = passed && (std::find(arr.begin(), arr.end(), rand_value) ==
                                arr.end());
        }
    }
    return passed;
}

/**
 * Main Function
 * testing algo
 */
int main() {
    assert(no_occurence_tests());
    assert(random_tests());

    return EXIT_SUCCESS;
}