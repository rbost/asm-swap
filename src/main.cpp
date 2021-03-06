#include "swap.h"

#include "gtest/gtest.h"


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Swap, 64_bits_ok)
{
    uint64_t a0 = 1;
    uint64_t b0 = 2;

    uint64_t a1 = a0, a2 = a0;
    uint64_t b1 = b0, b2 = b0;

    swap_64_ok(0, &a1, &b1);
    EXPECT_EQ(a0, a1);
    EXPECT_EQ(b0, b1);


    swap_64_ok(1, &a2, &b2);
    EXPECT_EQ(a0, b2);
    EXPECT_EQ(b0, a2);
}

TEST(Swap, 64_bits_ko)
{
    uint64_t a0 = 1;
    uint64_t b0 = 2;

    uint64_t a1 = a0, a2 = a0;
    uint64_t b1 = b0, b2 = b0;

    swap_64_ko(0, &a1, &b1);
    EXPECT_EQ(a0, a1);
    EXPECT_EQ(b0, b1);


    swap_64_ko(1, &a2, &b2);
    EXPECT_EQ(a0, b2);
    EXPECT_EQ(b0, a2);
}

TEST(Swap, eq_noinline)
{
    __m128i a0 = _mm_set1_epi8(1);
    __m128i b0 = _mm_set1_epi8(2);

    __m128i a1 = a0, a2 = a0;
    __m128i b1 = b0, b2 = b0;

    swap_eq_noinline(0, (__m128*)&a1, (__m128*)&b1);
    EXPECT_TRUE(_mm_testc_si128(a0, a1) & _mm_testc_si128(b0, b1));

    swap_eq_noinline(1, (__m128*)&a2, (__m128*)&b2);
    EXPECT_TRUE(_mm_testc_si128(a0, b2)&_mm_testc_si128(b0, a2));
}

TEST(Swap, plus_only_input_noinline)
{
    __m128i a0 = _mm_set1_epi8(1);
    __m128i b0 = _mm_set1_epi8(2);

    __m128i a1 = a0, a2 = a0;
    __m128i b1 = b0, b2 = b0;

    swap_plus_only_input_noinline(0, (__m128*)&a1, (__m128*)&b1);
    EXPECT_TRUE(_mm_testc_si128(a0, a1) & _mm_testc_si128(b0, b1));

    swap_plus_only_input_noinline(1, (__m128*)&a2, (__m128*)&b2);
    EXPECT_TRUE(_mm_testc_si128(a0, b2)&_mm_testc_si128(b0, a2));
}

TEST(Swap, eq_only_input)
{
    __m128i a0 = _mm_set1_epi8(1);
    __m128i b0 = _mm_set1_epi8(2);

    __m128i a1 = a0, a2 = a0;
    __m128i b1 = b0, b2 = b0;

    swap_eq_only_input(0, (__m128*)&a1, (__m128*)&b1);
    EXPECT_TRUE(_mm_testc_si128(a0, a1) & _mm_testc_si128(b0, b1));

    swap_eq_only_input(1, (__m128*)&a2, (__m128*)&b2);
    EXPECT_TRUE(_mm_testc_si128(a0, b2)&_mm_testc_si128(b0, a2));
}

TEST(Swap, plus_only_input)
{
    __m128i a0 = _mm_set1_epi8(1);
    __m128i b0 = _mm_set1_epi8(2);

    __m128i a1 = a0, a2 = a0;
    __m128i b1 = b0, b2 = b0;

    swap_plus_only_input(0, (__m128*)&a1, (__m128*)&b1);
    EXPECT_TRUE(_mm_testc_si128(a0, a1) & _mm_testc_si128(b0, b1));

    swap_plus_only_input(1, (__m128*)&a2, (__m128*)&b2);
    EXPECT_TRUE(_mm_testc_si128(a0, b2)&_mm_testc_si128(b0, a2));
}

TEST(Swap, eq_all_output)
{
    __m128i a0 = _mm_set1_epi8(1);
    __m128i b0 = _mm_set1_epi8(2);

    __m128i a1 = a0, a2 = a0;
    __m128i b1 = b0, b2 = b0;

    swap_eq_all_output(0, (__m128*)&a1, (__m128*)&b1);
    EXPECT_TRUE(_mm_testc_si128(a0, a1) & _mm_testc_si128(b0, b1));

    swap_eq_all_output(1, (__m128*)&a2, (__m128*)&b2);
    EXPECT_TRUE(_mm_testc_si128(a0, b2)&_mm_testc_si128(b0, a2));
}

TEST(Swap, eq_mixed_1)
{
    __m128i a0 = _mm_set1_epi8(1);
    __m128i b0 = _mm_set1_epi8(2);

    __m128i a1 = a0, a2 = a0;
    __m128i b1 = b0, b2 = b0;

    swap_eq_mixed_1(0, (__m128*)&a1, (__m128*)&b1);
    EXPECT_TRUE(_mm_testc_si128(a0, a1) & _mm_testc_si128(b0, b1));

    swap_eq_mixed_1(1, (__m128*)&a2, (__m128*)&b2);
    EXPECT_TRUE(_mm_testc_si128(a0, b2)&_mm_testc_si128(b0, a2));
}

TEST(Swap, eq_mixed_2)
{
    __m128i a0 = _mm_set1_epi8(1);
    __m128i b0 = _mm_set1_epi8(2);

    __m128i a1 = a0, a2 = a0;
    __m128i b1 = b0, b2 = b0;

    swap_eq_mixed_2(0, (__m128*)&a1, (__m128*)&b1);
    EXPECT_TRUE(_mm_testc_si128(a0, a1) & _mm_testc_si128(b0, b1));

    swap_eq_mixed_2(1, (__m128*)&a2, (__m128*)&b2);
    EXPECT_TRUE(_mm_testc_si128(a0, b2)&_mm_testc_si128(b0, a2));
}