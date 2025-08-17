#include <iostream>

void f1() { char a[] = "secret"; }
void f2()
{
    char a[7];
    std::cout << a;
}

int main(int argc, char *argv[])
{
    f1();
    f2();
    return 0;
}
