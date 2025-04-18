#include <iostream>

class test
{
public:
    void foo()
    {
        if (this != nullptr)
        {
            std::cout << "from foo" << std::endl;
        }
        else
        {
            std::cout << "returning nullptr from foo" << std::endl;
        }
    }
};

int main(void)
{
    ((test *)0)->foo();
    return 0;
}
