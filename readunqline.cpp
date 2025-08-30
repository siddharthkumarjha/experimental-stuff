#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <vector>

struct Line : std::string
{
    friend std::istream &operator>>(std::istream &in, Line &l) { return std::getline(in, l); }
};

std::vector<std::string> read_unq_line(std::istream &in)
{
    std::unordered_set<std::string> s{std::istream_iterator<Line>{in}, std::istream_iterator<Line>{}};
    return {std::make_move_iterator(s.begin()), std::make_move_iterator(s.end())};
}

int main(int argc, char *argv[])
{
    auto v = read_unq_line(std::cin);
    std::cout << "\n=========================================================\n";
    for (const auto &l : v)
    {
        std::cout << l << '\n';
    }
    return 0;
}
