#include <cstdlib>
#include <iostream>

/**
 * @namespace search
 * @brief Search algorithms
 */
namespace search {
/**
 * @namespace hash_search
 * @brief hash search algo
 */
namespace hash_search {
enum {
    MAX = 6      ///< Determines how much data
    HASHMAX = 5  ///< Determines the length of the hashtable
};

/**
 * a one-way linked list
 */
using node = struct list {
    int key;
    struct list* next;
};

/**
 * Mode of hash detection: Division method
 * @param key key to hash
 * @return hash value for `key`
 */
int hash(int key) { return key % HASHMAX; }

int hashSearch(int key, int* counter) {  // hash lookup function
    int index = hash(key);

}
}  // namespace hash_search
}  // namespace search