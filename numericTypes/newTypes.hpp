#pragma once

#include <cstdint>
#include <climits>
#include <limits>
#include <type_traits>

template<typename T>
concept ArithmeticType = std::is_arithmetic_v<T>;

template <ArithmeticType T>
class NumericWrapper 
{
public:
    using Type = T;

    // Constants
    static constexpr T    MAX  = std::numeric_limits<T>::max();
    static constexpr T    MIN  = std::numeric_limits<T>::min();
    static constexpr auto BITS = sizeof(T) * CHAR_BIT;

    // Constructor
    constexpr NumericWrapper(T l_value = 0) : m_storedValue(l_value) {}

    // Implicit conversion to the underlying type
    constexpr operator T() const { return m_storedValue; }
    constexpr operator T&() { return m_storedValue; }

    // Assignment operator
    constexpr NumericWrapper& operator=(T l_value) 
    {
        m_storedValue = l_value;
        return *this;
    }

private:
    T m_storedValue;
};

// Type aliases
#define assertTypeAlignment(type)                                              \
	static_assert(sizeof(type) == sizeof(type::Type),                          \
	              "Misaligned type: " #type)

#define createUnsignedType(size)                                               \
	using u##size = NumericWrapper<u##int##size##_t>;                          \
	assertTypeAlignment(u##size);
#define createSignedType(size)                                                 \
	using i##size = NumericWrapper<int##size##_t>;                             \
	assertTypeAlignment(i##size);

#define createIntType(size) createUnsignedType(size) createSignedType(size)

#define createFPType(size)                                                     \
	using f##size =                                                            \
	    NumericWrapper<std::conditional_t<size <= 32, float, double>>;         \
	assertTypeAlignment(f##size);

createIntType(8);
createIntType(16);
createIntType(32);
createIntType(64);

createFPType(32);
createFPType(64);
