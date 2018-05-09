#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <immintrin.h>

// all the following functions execute the following pseudo code
//
// va = *a;
// vb = *b;
// mask = (cond)?0x00:0xFF;
//
// vc = (va ^ vb) & mask;
// va = va ^ vc;
// vb = vb ^ vc;
//
// *a = va;
// *b = vb;
    
__attribute__((always_inline))
inline void swap_64_ok(uint8_t cond, uint64_t* a, uint64_t* b)
{
    uint64_t va, vb, vc;
    va = *a;
    vb = *b;
    vc = va;
    asm volatile("testb %3, %3\n\t"
                 "cmovneq %1, %0\n\t"
                 "cmovneq %2, %1\n\t"
                 : "+r"(va), "+r"(vb), "+r"(vc) /* output */
                 : "r"(cond) /* input */
                 :                    /* clobbered register */
    );
    *a = va;
    *b = vb;
}

__attribute__((always_inline))
inline void swap_64_ko(uint8_t cond, uint64_t* a, uint64_t* b)
{
    uint64_t va, vb, vc;
    va = *a;
    vb = *b;
    vc = va;
    asm volatile("testb %3, %3\n\t"
                 "cmovneq %1, %0\n\t"
                 "cmovneq %2, %1\n\t"
                 : "+r"(va), "+r"(vb) /* output */
                 : "r"(vc), "r"(cond) /* input */
                 :                    /* clobbered register */
    );
    *a = va;
    *b = vb;
}
    
void swap_plus_noinline(uint8_t cond, __m128* a, __m128* b);
void swap_eq_noinline(uint8_t cond, __m128* a, __m128* b);
    
__attribute__((always_inline))
inline void swap_plus_only_input(uint8_t cond, __m128* a, __m128* b)
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

__attribute__((always_inline))
inline void swap_eq_only_input(uint8_t cond, __m128* a, __m128* b)
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


__attribute__((always_inline))
inline void swap_eq_all_output(uint8_t cond, __m128* a, __m128* b)
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
                 "vpand %2, %3, %2\n\t"
                 "vpxor %0, %2, %0\n\t"
                 "vpxor %1, %2, %1\n\t"
                 : "+x"(va), "+x"(vb), "=x"(vc), "+x"(mask) /* output */
                 :               /* input */
                 : /* clobbered register */
    );

    *a = va;
    *b = vb;
}

__attribute__((always_inline))
inline void swap_eq_mixed_1(uint8_t cond, __m128* a, __m128* b)
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
                 "vpand %2, %3, %2\n\t"
                 "vpxor %0, %2, %0\n\t"
                 "vpxor %1, %2, %1\n\t"
                 : "+x"(va), "+x"(vb), "=x"(vc), "+x"(mask) /* output */
                 : "x"(va), "x"(vb), "x"(mask)              /* input */
                 : /* clobbered register */
    );

    *a = va;
    *b = vb;
}

__attribute__((always_inline))
inline void swap_eq_mixed_2(uint8_t cond, __m128* a, __m128* b)
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
    asm volatile("vpxor %4, %5, %2\n\t"
                 "vpand %2, %6, %2\n\t"
                 "vpxor %0, %2, %4\n\t"
                 "vpxor %1, %2, %5\n\t"
                 : "+x"(va), "+x"(vb), "=x"(vc), "+x"(mask) /* output */
                 : "x"(va), "x"(vb), "x"(mask)              /* input */
                 : /* clobbered register */
    );

    *a = va;
    *b = vb;
}


#ifdef __cplusplus
}
#endif