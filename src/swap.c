#include "swap.h"

void swap_plus_noinline(uint8_t cond, __m128* a, __m128* b)
{
    __m128 va, vb, vc;
    va = *a;
    vb = *b;

    uint32_t w_mask;
    // the following asm is equivalent to
    // w_mask = (cond)?0x00000000:0xFFFFFFFF;
    // and runs in constant time.
    asm volatile("negb %1\n\t"
                 "sbbl %0, %0\n\t"
                 : "=r"(w_mask) /* output */
                 : "r"(cond)    /* input */
                 :              /* clobbered register */
    );


    __m128i mask = _mm_set1_epi32(w_mask);
    __m128i acc;
    asm volatile("vpxor %0, %1, %2\n\t"
                 "vpand %2, %5, %2\n\t"
                 "vpxor %0, %2, %0\n\t"
                 "vpxor %1, %2, %1\n\t"
                 : "+x"(va), "+x"(vb), "+x"(vc) /* output */
                 : "x"(va), "x"(vb), "x"(mask)              /* input */
                 : /* clobbered register */
    );

    *a = va;
    *b = vb;
}

void swap_eq_noinline(uint8_t cond, __m128* a, __m128* b)
{
    __m128 va, vb, vc;
    va = *a;
    vb = *b;

    uint32_t w_mask;
    // the following asm is equivalent to
    // w_mask = (cond)?0x00000000:0xFFFFFFFF;
    // and runs in constant time.
    asm volatile("negb %1\n\t"
                 "sbbl %0, %0\n\t"
                 : "=r"(w_mask) /* output */
                 : "r"(cond)    /* input */
                 :              /* clobbered register */
    );


    __m128i mask = _mm_set1_epi32(w_mask);
    __m128i acc;
    asm volatile("vpxor %0, %1, %2\n\t"
                 "vpand %2, %5, %2\n\t"
                 "vpxor %0, %2, %0\n\t"
                 "vpxor %1, %2, %1\n\t"
                 : "+x"(va), "+x"(vb), "=x"(vc) /* output */
                 : "x"(va), "x"(vb), "x"(mask)              /* input */
                 : /* clobbered register */
    );

    *a = va;
    *b = vb;
}