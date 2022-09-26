#include <cstdio>
#include <mutex>

std::mutex mtx1;

int main() {
  if (mtx1.try_lock()) {
    printf("succeed\n");
  } else {
    printf("failed\n");
  }

  if (mtx1.try_lock()) {
    printf("succeed");
  } else {
    printf("failed\n");
  }

  return 0;
}
