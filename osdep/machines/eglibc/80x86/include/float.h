/* $Id$ */

#ifndef __HACKED_FLOAT_H
#define __HACKED_FLOAT_H

/*
 * eglibc does not provide this header; it is expected to be provided by gcc.
 * The definitions here must be compatible.
 */

#if defined(_EGLIBC2_19)

#pragma TenDRA token EXP const : int         : __ABI_FLT_RADIX #

#pragma TenDRA token EXP const : int         : __ABI_FLT_DIG #
#pragma TenDRA token EXP const : float       : __ABI_FLT_EPSILON #
#pragma TenDRA token EXP const : int         : __ABI_FLT_MANT_DIG #
#pragma TenDRA token EXP const : float       : __ABI_FLT_MIN #
#pragma TenDRA token EXP const : float       : __ABI_FLT_MAX #
#pragma TenDRA token EXP const : int         : __ABI_FLT_MIN_10_EXP #
#pragma TenDRA token EXP const : int         : __ABI_FLT_MAX_10_EXP #
#pragma TenDRA token EXP const : int         : __ABI_FLT_MIN_EXP #
#pragma TenDRA token EXP const : int         : __ABI_FLT_MAX_EXP #

#pragma TenDRA token EXP const : int         : __ABI_DBL_DIG #
#pragma TenDRA token EXP const : double      : __ABI_DBL_EPSILON #
#pragma TenDRA token EXP const : int         : __ABI_DBL_MANT_DIG #
#pragma TenDRA token EXP const : double      : __ABI_DBL_MIN #
#pragma TenDRA token EXP const : double      : __ABI_DBL_MAX #
#pragma TenDRA token EXP const : int         : __ABI_DBL_MIN_10_EXP #
#pragma TenDRA token EXP const : int         : __ABI_DBL_MAX_10_EXP #
#pragma TenDRA token EXP const : int         : __ABI_DBL_MIN_EXP #
#pragma TenDRA token EXP const : int         : __ABI_DBL_MAX_EXP #

#pragma TenDRA token EXP const : int         : __ABI_LDBL_DIG #
#pragma TenDRA token EXP const : long double : __ABI_LDBL_EPSILON #
#pragma TenDRA token EXP const : int         : __ABI_LDBL_MANT_DIG #
#pragma TenDRA token EXP const : long double : __ABI_LDBL_MIN #
#pragma TenDRA token EXP const : long double : __ABI_LDBL_MAX #
#pragma TenDRA token EXP const : int         : __ABI_LDBL_MIN_10_EXP #
#pragma TenDRA token EXP const : int         : __ABI_LDBL_MAX_10_EXP #
#pragma TenDRA token EXP const : int         : __ABI_LDBL_MIN_EXP #
#pragma TenDRA token EXP const : int         : __ABI_LDBL_MAX_EXP #

#define FLT_RADIX        __ABI_FLT_RADIX /* b */
#define FLT_ROUNDS       -1 /* XXX: perhaps this ought to come from TDF. maybe by rounding_mode_cond or round_as_state */

#define FLT_DIG          __ABI_FLT_DIG
#define FLT_EPSILON      __ABI_FLT_EPSILON
#define FLT_MANT_DIG     __ABI_FLT_MANT_DIG
#define FLT_MIN          __ABI_FLT_MIN
#define FLT_MAX          __ABI_FLT_MAX
#define FLT_MIN_10_EXP   __ABI_FLT_MIN_10_EXP
#define FLT_MAX_10_EXP   __ABI_FLT_MAX_10_EXP
#define FLT_MIN_EXP     (__ABI_FLT_MIN_EXP + 1)
#define FLT_MAX_EXP     (__ABI_FLT_MAX_EXP + 1)

#define DBL_DIG          __ABI_DBL_DIG
#define DBL_EPSILON      __ABI_DBL_EPSILON
#define DBL_MANT_DIG     __ABI_DBL_MANT_DIG
#define DBL_MIN          __ABI_DBL_MIN
#define DBL_MAX          __ABI_DBL_MAX
#define DBL_MIN_10_EXP   __ABI_DBL_MIN_10_EXP
#define DBL_MAX_10_EXP   __ABI_DBL_MAX_10_EXP
#define DBL_MIN_EXP     (__ABI_DBL_MIN_EXP + 1)
#define DBL_MAX_EXP     (__ABI_DBL_MAX_EXP + 1)

#define LDBL_DIG         __ABI_LDBL_DIG
#define LDBL_EPSILON     __ABI_LDBL_EPSILON
#define LDBL_MANT_DIG    __ABI_LDBL_MANT_DIG
#define LDBL_MIN         __ABI_LDBL_MIN
#define LDBL_MAX         __ABI_LDBL_MAX
#define LDBL_MIN_10_EXP  __ABI_LDBL_MIN_10_EXP
#define LDBL_MAX_10_EXP  __ABI_LDBL_MAX_10_EXP
#define LDBL_MIN_EXP    (__ABI_LDBL_MIN_EXP + 1)
#define LDBL_MAX_EXP    (__ABI_LDBL_MAX_EXP + 1)

#endif

#endif

