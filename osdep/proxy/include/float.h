#ifndef __PROXY_FLOAT_H
#define __PROXY_FLOAT_H

#pragma TenDRA token EXP const : int         : __PROXY_FLT_RADIX #

#pragma TenDRA token EXP const : int         : __PROXY_FLT_DIG #
#pragma TenDRA token EXP const : float       : __PROXY_FLT_EPSILON #
#pragma TenDRA token EXP const : int         : __PROXY_FLT_MANT_DIG #
#pragma TenDRA token EXP const : float       : __PROXY_FLT_MIN #
#pragma TenDRA token EXP const : float       : __PROXY_FLT_MAX #
#pragma TenDRA token EXP const : int         : __PROXY_FLT_MIN_10_EXP #
#pragma TenDRA token EXP const : int         : __PROXY_FLT_MAX_10_EXP #
#pragma TenDRA token EXP const : int         : __PROXY_FLT_MIN_EXP #
#pragma TenDRA token EXP const : int         : __PROXY_FLT_MAX_EXP #

#pragma TenDRA token EXP const : int         : __PROXY_DBL_DIG #
#pragma TenDRA token EXP const : double      : __PROXY_DBL_EPSILON #
#pragma TenDRA token EXP const : int         : __PROXY_DBL_MANT_DIG #
#pragma TenDRA token EXP const : double      : __PROXY_DBL_MIN #
#pragma TenDRA token EXP const : double      : __PROXY_DBL_MAX #
#pragma TenDRA token EXP const : int         : __PROXY_DBL_MIN_10_EXP #
#pragma TenDRA token EXP const : int         : __PROXY_DBL_MAX_10_EXP #
#pragma TenDRA token EXP const : int         : __PROXY_DBL_MIN_EXP #
#pragma TenDRA token EXP const : int         : __PROXY_DBL_MAX_EXP #

#pragma TenDRA token EXP const : int         : __PROXY_LDBL_DIG #
#pragma TenDRA token EXP const : long double : __PROXY_LDBL_EPSILON #
#pragma TenDRA token EXP const : int         : __PROXY_LDBL_MANT_DIG #
#pragma TenDRA token EXP const : long double : __PROXY_LDBL_MIN #
#pragma TenDRA token EXP const : long double : __PROXY_LDBL_MAX #
#pragma TenDRA token EXP const : int         : __PROXY_LDBL_MIN_10_EXP #
#pragma TenDRA token EXP const : int         : __PROXY_LDBL_MAX_10_EXP #
#pragma TenDRA token EXP const : int         : __PROXY_LDBL_MIN_EXP #
#pragma TenDRA token EXP const : int         : __PROXY_LDBL_MAX_EXP #

#define FLT_RADIX        __PROXY_FLT_RADIX
#define FLT_ROUNDS       -1 /* XXX: perhaps this ought to come from TDF. maybe by rounding_mode_cond or round_as_state */

#define FLT_DIG          __PROXY_FLT_DIG
#define FLT_EPSILON      __PROXY_FLT_EPSILON
#define FLT_MANT_DIG     __PROXY_FLT_MANT_DIG
#define FLT_MIN          __PROXY_FLT_MIN
#define FLT_MAX          __PROXY_FLT_MAX
#define FLT_MIN_10_EXP   __PROXY_FLT_MIN_10_EXP
#define FLT_MAX_10_EXP   __PROXY_FLT_MAX_10_EXP
#define FLT_MIN_EXP     (__PROXY_FLT_MIN_EXP + 1)
#define FLT_MAX_EXP     (__PROXY_FLT_MAX_EXP + 1)

#define DBL_DIG          __PROXY_DBL_DIG
#define DBL_EPSILON      __PROXY_DBL_EPSILON
#define DBL_MANT_DIG     __PROXY_DBL_MANT_DIG
#define DBL_MIN          __PROXY_DBL_MIN
#define DBL_MAX          __PROXY_DBL_MAX
#define DBL_MIN_10_EXP   __PROXY_DBL_MIN_10_EXP
#define DBL_MAX_10_EXP   __PROXY_DBL_MAX_10_EXP
#define DBL_MIN_EXP     (__PROXY_DBL_MIN_EXP + 1)
#define DBL_MAX_EXP     (__PROXY_DBL_MAX_EXP + 1)

#define LDBL_DIG         __PROXY_LDBL_DIG
#define LDBL_EPSILON     __PROXY_LDBL_EPSILON
#define LDBL_MANT_DIG    __PROXY_LDBL_MANT_DIG
#define LDBL_MIN         __PROXY_LDBL_MIN
#define LDBL_MAX         __PROXY_LDBL_MAX
#define LDBL_MIN_10_EXP  __PROXY_LDBL_MIN_10_EXP
#define LDBL_MAX_10_EXP  __PROXY_LDBL_MAX_10_EXP
#define LDBL_MIN_EXP    (__PROXY_LDBL_MIN_EXP + 1)
#define LDBL_MAX_EXP    (__PROXY_LDBL_MAX_EXP + 1)

#endif

