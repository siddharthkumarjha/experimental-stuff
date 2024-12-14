#include "newTypes.hpp"
#include <iostream>

#define createOpType(x, cmpOp)                                                 \
    inline static constexpr struct x##Type : op                                \
    {                                                                          \
        inline constexpr bool operator()(i32 const &lCmpRes) const             \
        {                                                                      \
            return (lCmpRes cmpOp 0);                                          \
        }                                                                      \
    } x = x##Type{};

struct op {};
createOpType(eq, ==);
createOpType(lt, <);

class Foo
{
    int* external_counter = nullptr;

public:
    Foo() = default;
    explicit Foo(int& counter) : external_counter(&counter) {}

    void bar()
    {
        if (external_counter)
            ++*external_counter;

        //...
    }
};

int main() 
{
    u32 var = 42; // Use u32 as a type
    f64 fvar;
    fvar = 64;
    var++;
    var -= 2;

    f64 newVar[] = {91, 10, 88, 81, 83.1, 84.2, 83.9};
    for (auto const &ref : newVar)
        std::cout << ref << ' ';
    std::cout << std::endl;

    std::cout << std::boolalpha << lt(-1) << "\n";
    std::cout << var << " " << (var > u32::MAX) << '\n';
    std::cout << f32::MAX << std::endl;
    std::cout << sizeof(f64) << std::endl;


    Foo bad{i32{}};
    bad.bar();
    //Foo ok_compile_error{0};
    int counter = 0;
    [[maybe_unused]] Foo ok{i32{}};
    ok.bar();

    return 0;
}
