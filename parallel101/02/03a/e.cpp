#include <iostream>
#include <string>

struct Pig {
    std::string m_name;
    int m_weight { 0 };
};

void show(Pig pig)
{
    std::cout << "name: " << pig.m_name << std::endl;
    std::cout << "weight: " << pig.m_weight << std::endl;
}

int main()
{
    Pig pig { "佩奇", 80 }; // m_weight 没指定，使用 {0} 指定的默认值

    show(pig);

    Pig pig2 = pig; // 调用 Pig(Pig const &)
    Pig pig3(pig);

    show(pig);

    return 0;
}