#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

std::string uint128ToString(const unsigned __int128 &value) {
  static const char *charmap = "0123456789";

  std::string result;
  result.reserve(40); // max. 40 digits possible ( uint64_t has 20)
  unsigned __int128 helper = value;

  do {
    result += charmap[helper % 10];
    helper /= 10;
  } while (helper);
  std::reverse(result.begin(), result.end());
  return result;
}

std::string uint128ToString(const __int128 &value) {
  static const char charmap[] = "0123456789";

  std::string result;
  result.reserve(40); // max. 40 digits possible ( uint64_t has 20)
  __int128 helper = (value > 0) ? value : (0 - value);

  int8_t v = 0;
  do {
    v = helper % 10;
    result += charmap[v];
    helper /= 10;
  } while (helper);

  if (value < 0) {
    result.push_back('-');
  }
  std::reverse(result.begin(), result.end());
  return result;
}

int main(void) {
  std::vector<unsigned __int128> v(105);
  for (uint16_t i = 0; i < 105; i++)
    v[i] = ((static_cast<unsigned __int128>(1u)
             << static_cast<unsigned __int128>(i)));

  for (const auto &ref : v)
    std::cout << uint128ToString(ref) << ' ';
  std::cout << std::endl;

  __int128 var = -1331313;
  std::cout << '\n' << uint128ToString(var) << '\n';

  return 0;
}
