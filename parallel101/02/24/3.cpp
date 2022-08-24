#include <cstddef>
#include <memory>

struct C {
    std::unique_ptr<C> m_child;
    C *m_parent;
};

int main()
{
    auto parent = std::unique_ptr<C>();
    auto child = std::unique_ptr<C>();

    // 建立相互引用
    parent->m_child = std::move(child); // 移交child所属权给 parent
    child->m_parent = parent.get();

    parent = nullptr; // parent 会被释放, 因为 child 指向他的是弱引用
    // 此时 child 也已经被释放了，因为 child 完全隶属于 parent

    return 0;
}