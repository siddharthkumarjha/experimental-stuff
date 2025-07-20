#include <exception>
#include <functional>
#include <iostream>
#include <optional>
#include <type_traits>

template <typename callable, typename... Args> auto pcall(callable cb, Args... arg)
{
    using CallableRetType = std::invoke_result_t<callable, Args...>;
    using RetOptType      = std::optional<CallableRetType>;
    auto task             = std::bind(cb, std::forward<Args>(arg)...);

    try
    {
        if constexpr (std::is_void_v<CallableRetType>)
            return task();
        else
            return RetOptType{task()};
    }
    catch (std::exception const &excuse)
    {
        std::cerr << excuse.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "Unknown error occurred\n";
    }

    if constexpr (!std::is_void_v<CallableRetType>)
        return RetOptType{std::nullopt};
}

int foo(bool arg)
{
    if (arg)
    {
        std::cout << "running foo\n";
    }
    else
    {
        std::cout << "throwing from foo \n";
        throw 34;
    }
    return 3;
}

int main(int argc, char *argv[])
{
    auto ret_val = pcall(foo, true);
    if (ret_val)
    {
        std::cout << *ret_val << '\n';
    }
    return 0;
}
