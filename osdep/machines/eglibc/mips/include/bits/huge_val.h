#ifndef __HACKED_BITS_HUGE_VAL_H
#define __HACKED_BITS_HUGE_VAL_H

/*
 * For equivalent effect of bits/huge_value.h, which uses gccisms.
 */
#if defined(_EGLIBC2_11)
typedef union { unsigned long long __ull; double __d; } __huge_val_t;
static __huge_val_t __huge_val = { 0x7ff0000000000000ULL };
#define HUGE_VAL (__huge_val.__d)
#endif

#endif

