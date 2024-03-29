import <vector>;
import <iostream>;
import <numeric>;
import <ranges>;
import <cmath>;
import <generator>;

std::generator<int> myfunc(auto &&v) {
    for (auto &&vi: v
         | std::views::filter([] (auto &&x) { return x >= 0; })
         | std::views::transform([] (auto &&x) { return sqrtf(x); })
         ) {
        co_yield vi;
    }
}

int main() {
    std::vector v = {4, 3, 2, 1, 0, -1, -2};
    for (auto &&vi: myfunc(v)) {
        std::cout << vi << std::endl;
    }
    return 0;
}