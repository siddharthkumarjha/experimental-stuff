#include <iostream>
#include <list>
#include <vector>

template <typename value_type, template <typename> class container_type = std::vector> class stack
{
    using reference        = value_type &;
    using const_reference  = value_type const &;
    using rvalue_reference = value_type &&;

private:
    container_type<value_type> c;

public:
    void push(rvalue_reference value_to_push)
    {
        c.emplace_back(std::forward<value_type>(value_to_push));
    }

    void pop() { c.pop_back(); }

    const_reference top() const { return c.back(); }
};

int main(int argc, char *argv[])
{
    stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    std::cout << s1.top() << '\n';
    s1.pop();
    std::cout << s1.top() << '\n';

    stack<int, std::list> s2;
    s2.push(4);
    s2.push(5);
    s2.push(6);
    std::cout << s2.top() << '\n';
    s2.pop();
    std::cout << s2.top() << '\n';
    return 0;
}
