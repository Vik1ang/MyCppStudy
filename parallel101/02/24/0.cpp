#include <cstddef>
#include <memory>

struct C {
    std::shared_ptr<C> m_child;
    std::shared_ptr<C> m_parent;
};

int main () {
    auto parent = std::make_shared<C>();
    auto child = std::make_shared<C>();

    // 建立相互引用
    parent->m_child = child;
    child->m_parent = parent;

    parent = nullptr; // parent 不会被释放, 因为 child还指向它
    child = nullptr; // child 不会被释放, 因为 parent 还指向它

    return 0;
}