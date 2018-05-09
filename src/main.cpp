#include "swap.h"

#include "gtest/gtest.h"


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(Swap, eq_noinline)
{
    __m128 a0 = _mm_set1_epi8(1);
    __m128 b0 = _mm_set1_epi8(2);

    __m128 a1 = a0, a2 = a0;
    __m128 b1 = b0, b2 = b0;

    swap_eq_noinline(0, (__m128*)&a1, (__m128*)&b1);
    EXPECT_TRUE(_mm_testc_si128(a0, a1));
    EXPECT_TRUE(_mm_testc_si128(b0, b1));

    swap_eq_noinline(1, (__m128*)&a2, (__m128*)&b2);
    EXPECT_TRUE(_mm_testc_si128(a0, b2));
    EXPECT_TRUE(_mm_testc_si128(b0, a2));
}

TEST(Swap, plus_noinline)
{
    __m128 a0 = _mm_set1_epi8(1);
    __m128 b0 = _mm_set1_epi8(2);

    __m128 a1 = a0, a2 = a0;
    __m128 b1 = b0, b2 = b0;

    swap_plus_noinline(0, (__m128*)&a1, (__m128*)&b1);
    EXPECT_TRUE(_mm_testc_si128(a0, a1));
    EXPECT_TRUE(_mm_testc_si128(b0, b1));

    swap_plus_noinline(1, (__m128*)&a2, (__m128*)&b2);
    EXPECT_TRUE(_mm_testc_si128(a0, b2));
    EXPECT_TRUE(_mm_testc_si128(b0, a2));
}

TEST(Swap, eq_inline)
{
    __m128 a0 = _mm_set1_epi8(1);
    __m128 b0 = _mm_set1_epi8(2);

    __m128 a1 = a0, a2 = a0;
    __m128 b1 = b0, b2 = b0;

    swap_eq_inline(0, (__m128*)&a1, (__m128*)&b1);
    EXPECT_TRUE(_mm_testc_si128(a0, a1));
    EXPECT_TRUE(_mm_testc_si128(b0, b1));

    swap_eq_inline(1, (__m128*)&a2, (__m128*)&b2);
    EXPECT_TRUE(_mm_testc_si128(a0, b2));
    EXPECT_TRUE(_mm_testc_si128(b0, a2));
}
TEST(Swap, plus_inline)
{
    __m128 a0 = _mm_set1_epi8(1);
    __m128 b0 = _mm_set1_epi8(2);

    __m128 a1 = a0, a2 = a0;
    __m128 b1 = b0, b2 = b0;

    swap_plus_inline(0, (__m128*)&a1, (__m128*)&b1);
    EXPECT_TRUE(_mm_testc_si128(a0, a1));
    EXPECT_TRUE(_mm_testc_si128(b0, b1));

    swap_plus_inline(1, (__m128*)&a2, (__m128*)&b2);
    EXPECT_TRUE(_mm_testc_si128(a0, b2));
    EXPECT_TRUE(_mm_testc_si128(b0, a2));
}