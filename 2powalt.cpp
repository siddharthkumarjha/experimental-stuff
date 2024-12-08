#include <cstdint>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

int main(void)
{
        std::vector<std::string> v(105);

        for(uint16_t i = 0; i < 105; i++)
                v[i] = std::to_string(std::pow(2, i));

        for(const auto &ref : v)
                std::cout << ref << ' ';
        std::cout << std::endl;

        return 0;
}
