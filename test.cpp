#include <iostream>

#define _ARG_COUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, COUNT, ...) COUNT
#define COUNT_ARGS(...) _ARG_COUNT(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

// Wrapper macro to test
#define CAT(X, Y) X ## Y
#define CAT_REV(X, Y) CAT(Y, X)

#define SEQ(...) CAT_REV(COUNT_ARGS(__VA_ARGS__), SEQ_)(__VA_ARGS__)

#define SEQ_0() ()
#define SEQ_1(e1) (e1)
#define SEQ_2(e1, e2) (e1)(e2)
#define SEQ_3(e1, e2, e3) (e1)(e2)(e3)
#define SEQ_4(e1, e2, e3, e4) (e1)(e2)(e3)(e4)
#define SEQ_5(e1, e2, e3, e4, e5) (e1)(e2)(e3)(e4)(e5)
#define SEQ_6(e1, e2, e3, e4, e5, e6) (e1)(e2)(e3)(e4)(e5)(e6)
#define SEQ_7(e1, e2, e3, e4, e5, e6, e7) (e1)(e2)(e3)(e4)(e5)(e6)(e7)
#define SEQ_8(e1, e2, e3, e4, e5, e6, e7, e8) (e1)(e2)(e3)(e4)(e5)(e6)(e7)(e8)
#define SEQ_9(e1, e2, e3, e4, e5, e6, e7, e8, e9) (e1)(e2)(e3)(e4)(e5)(e6)(e7)(e8)(e9)
#define SEQ_10(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10) (e1)(e2)(e3)(e4)(e5)(e6)(e7)(e8)(e9)(e10)
#define SEQ_11(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11) (e1)(e2)(e3)(e4)(e5)(e6)(e7)(e8)(e9)(e10)(e11)
#define SEQ_12(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12) (e1)(e2)(e3)(e4)(e5)(e6)(e7)(e8)(e9)(e10)(e11)(e12)
#define SEQ_13(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13) (e1)(e2)(e3)(e4)(e5)(e6)(e7)(e8)(e9)(e10)(e11)(e12)(e13)
#define SEQ_14(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14) (e1)(e2)(e3)(e4)(e5)(e6)(e7)(e8)(e9)(e10)(e11)(e12)(e13)(e14)
#define SEQ_15(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15) (e1)(e2)(e3)(e4)(e5)(e6)(e7)(e8)(e9)(e10)(e11)(e12)(e13)(e14)(e15)
#define SEQ_16(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16) (e1)(e2)(e3)(e4)(e5)(e6)(e7)(e8)(e9)(e10)(e11)(e12)(e13)(e14)(e15)(e16)

#define SEQ_SZ(seq) CAT_REV(SEQ_SZ_0 seq, SEQ_SZ_)
#define SEQ_SZ_0(_) SEQ_SZ_1
#define SEQ_SZ_1(_) SEQ_SZ_2
#define SEQ_SZ_2(_) SEQ_SZ_3
#define SEQ_SZ_3(_) SEQ_SZ_4
#define SEQ_SZ_4(_) SEQ_SZ_5

#define SEQ_SZ_SEQ_SZ_0 0
#define SEQ_SZ_SEQ_SZ_1 1
#define SEQ_SZ_SEQ_SZ_2 2
#define SEQ_SZ_SEQ_SZ_3 3
#define SEQ_SZ_SEQ_SZ_4 4
#define SEQ_SZ_SEQ_SZ_5 5

// Check if a sequence is empty
#define IS_EMPTY(...) IS_EMPTY_(__VA_ARGS__, 0)
#define IS_EMPTY_(e1, ...) IS_EMPTY_HELPER(e1)
#define IS_EMPTY_HELPER(...) IS_EMPTY_HELPER_(__VA_ARGS__, 1, 0)
#define IS_EMPTY_HELPER_(a, b, ...) b

// Utility macros for conditional evaluation
#define IF(cond) CAT(IF_, cond)
#define IF_0(...) 
#define IF_1(...) __VA_ARGS__

// Example function to apply to each element
#define PRINT(x) std::cout << #x << std::endl;
#define HEAD(seq) HEAD_ seq
#define HEAD_(e1, ...) (e1)

#define FOR_EACH(macro, seq) CAT_REV(FOR_EACH_I_0 seq, macro)

#define FOR_EACH_I_0(_1) (_1) FOR_EACH_I_1
#define FOR_EACH_I_1(_1) CAT(macro, (_1)) FOR_EACH_I_2

int main(void)
{
    SEQ_SZ(SEQ(a, b, c))
    FOR_EACH(PRINT, SEQ(a, b, c));
    return 0;
}
