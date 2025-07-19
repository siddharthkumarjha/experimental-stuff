#include <iostream>

class A
{
public:
    A(int a) { std::cout << "A: " << a << '\n'; }
};

class B : virtual public A
{
public:
    B(int b) : A(4) { std::cout << "B: " << b << '\n'; }
};

class C : virtual public A
{
public:
    C(int c) : A(3) { std::cout << "C: " << c << '\n'; }
};

class D : virtual public B, virtual public C
{
public:
    D(int d) : C(2), B(1), A(0) { std::cout << "D: " << d << '\n'; }
};

int main()
{
    D d(5);
    return 0;
}
