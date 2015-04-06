# $Id$

# Copyright 2015, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+USE "c/c89", "stddef.h.ts", "ptrdiff_t";
+USE "c/c89", "stddef.h.ts", "size_t";
+USE "c/c89", "signal.h.ts", "sig_atomic_t";
+USE "c/c95", "wchar.h.ts",  "wint_t";
+USE "c/c89", "stddef.h.ts", "wchar_t";
+USE "c/c95", "wchar.h.ts",  "ranges";

# Arbitary type widths are permitted here. We can add more as required,
# which would typically only be when an implementation exists for that token.
#
# These are guarded by defines so that they may be elided for system headers
# which do not provide them (likewise for other optional types).

# 7.18.1.2, 7.18.1.3 mandatory types
+TYPE (signed) int_fast8_t;   +TYPE (unsigned) uint_fast8_t;
+TYPE (signed) int_least8_t;  +TYPE (unsigned) uint_least8_t;
+TYPE (signed) int_fast16_t;  +TYPE (unsigned) uint_fast16_t;
+TYPE (signed) int_least16_t; +TYPE (unsigned) uint_least16_t;
+TYPE (signed) int_fast32_t;  +TYPE (unsigned) uint_fast32_t;
+TYPE (signed) int_least32_t; +TYPE (unsigned) uint_least32_t;
+TYPE (signed) int_fast64_t;  +TYPE (unsigned) uint_fast64_t;
+TYPE (signed) int_least64_t; +TYPE (unsigned) uint_least64_t;

# 7.18.1.1, 7.18.1.2, 7.18.1.3 optional types
+IFDEF ~have_int8
+TYPE (signed) int8_t;        +TYPE (unsigned) uint8_t;
+ENDIF
+IFDEF ~have_int16
+TYPE (signed) int16_t;       +TYPE (unsigned) uint16_t;
+ENDIF
+IFDEF ~have_int24
+TYPE (signed) int24_t;       +TYPE (unsigned) uint24_t;
+TYPE (signed) int_fast24_t;  +TYPE (unsigned) uint_fast24_t;
+TYPE (signed) int_least24_t; +TYPE (unsigned) uint_least24_t;
+ENDIF
+IFDEF ~have_int32
+TYPE (signed) int32_t;       +TYPE (unsigned) uint32_t;
+ENDIF
+IFDEF ~have_int48
+TYPE (signed) int48_t;       +TYPE (unsigned) uint48_t;
+TYPE (signed) int_fast48_t;  +TYPE (unsigned) uint_fast48_t;
+TYPE (signed) int_least48_t; +TYPE (unsigned) uint_least48_t;
+ENDIF
+IFDEF ~have_int64
+TYPE (signed) int64_t;       +TYPE (unsigned) uint64_t;
+ENDIF

# 7.18.2.1 promotions used for _MIN/_MAX below
+IFDEF ~have_int8_t
+TYPEDEF ~promote( int_least8_t) ~int_least8_t;
+TYPEDEF ~promote(uint_least8_t) ~uint_least8_t;
+ENDIF
+IFDEF ~have_int16_t
+TYPEDEF ~promote( int_least16_t) ~int_least16_t;
+TYPEDEF ~promote(uint_least16_t) ~uint_least16_t;
+ENDIF
+IFDEF ~have_int24_t # xxx: i think this may be incorrect to assume int24_t would be int
+TYPEDEF ~promote( int24_t)       ~int24_t;
+TYPEDEF ~promote(uint24_t)       ~uint24_t;
+TYPEDEF ~promote( int_least24_t) ~int_least24_t;
+TYPEDEF ~promote(uint_least24_t) ~uint_least24_t;
+TYPEDEF ~promote( int_fast24_t)  ~int_fast24_t;
+TYPEDEF ~promote(uint_fast24_t)  ~uint_fast24_t;
+ENDIF
+IFDEF ~have_int32_t
+TYPEDEF ~promote( int32_t)       ~int32_t;
+TYPEDEF ~promote(uint32_t)       ~uint32_t;
+TYPEDEF ~promote( int_least32_t) ~int_least32_t;
+TYPEDEF ~promote(uint_least32_t) ~uint_least32_t;
+TYPEDEF ~promote( int_fast32_t)  ~int_fast32_t;
+TYPEDEF ~promote(uint_fast32_t)  ~uint_fast32_t;
+ENDIF
+IFDEF ~have_int48_t
+TYPEDEF ~promote( int48_t)       ~int48_t;
+TYPEDEF ~promote(uint48_t)       ~uint48_t;
+TYPEDEF ~promote( int_least48_t) ~int_least48_t;
+TYPEDEF ~promote(uint_least48_t) ~uint_least48_t;
+TYPEDEF ~promote( int_fast48_t)  ~int_fast48_t;
+TYPEDEF ~promote(uint_fast48_t)  ~uint_fast48_t;
+ENDIF
+IFDEF ~have_int64_t
+TYPEDEF ~promote( int64_t)       ~int64_t;
+TYPEDEF ~promote(uint64_t)       ~uint64_t;
+TYPEDEF ~promote( int_least64_t) ~int_least64_t;
+TYPEDEF ~promote(uint_least64_t) ~uint_least64_t;
+TYPEDEF ~promote( int_fast64_t)  ~int_fast64_t;
+TYPEDEF ~promote(uint_fast64_t)  ~uint_fast64_t;
+ENDIF

# 7.18.2.1
+IFDEF ~have_int8_t
+CONST int INT8_MIN, INT8_MAX;
+CONST int UINT8_MAX;
+CONST ~int_least8_t INT_LEAST8_MIN, INT_LEAST8_MAX;
+CONST ~uint_least8_t UINT_LEAST8_MAX;
+CONST int INT_FAST8_MIN, INT_FAST8_MAX;
+CONST int UINT_FAST8_MAX;
+ENDIF
+IFDEF ~have_int16_t
+CONST int INT16_MIN, INT16_MAX;
+CONST int UINT16_MAX;
+CONST ~int_least16_t INT_LEAST16_MIN, INT_LEAST16_MAX;
+CONST ~uint_least16_t UINT_LEAST16_MAX;
+CONST int INT_FAST16_MIN, INT_FAST16_MAX;
+CONST int UINT_FAST16_MAX;
+ENDIF
+IFDEF ~have_int32_t
+CONST ~int32_t INT32_MIN, INT32_MAX;
+CONST ~uint32_t UINT32_MAX;
+CONST ~int_least32_t INT_LEAST32_MIN, INT_LEAST32_MAX;
+CONST ~uint32_t UINT_LEAST32_MAX;
+CONST ~int_fast32_t INT_FAST32_MIN, INT_FAST32_MAX;
+CONST ~uint_fast32_t UINT_FAST32_MAX;
+ENDIF
+IFDEF ~have_int64_t
+CONST ~int64_t INT64_MIN, INT64_MAX;
+CONST ~uint64_t UINT64_MAX;
+CONST ~int_least64_t INT_LEAST64_MIN, INT_LEAST64_MAX;
+CONST ~uint_least64_t UINT_LEAST64_MAX;
+CONST ~int_fast64_t INT_FAST64_MIN, INT_FAST64_MAX;
+CONST ~uint_fast64_t UINT_FAST64_MAX;
+ENDIF

# 7.18.1.4
+IFDEF ~have_intptr_t
+TYPE (signed)   intptr_t;
+TYPE (unsigned) uintptr_t;
+ENDIF

# 7.18.2.4
+IFDEF ~have_intptr_t
+TYPEDEF ~promote(intptr_t) ~intptr_t;
+TYPEDEF ~promote(uintptr_t) ~uintptr_t;
+CONST ~intptr_t INTPTR_MIN, INTPTR_MAX;
+CONST ~uintptr_t UINTPTR_MAX;
+ENDIF

# 7.18.1.5
+TYPE (signed)   intmax_t;
+TYPE (unsigned) uintmax_t;

# 7.18.2.5
+CONST intmax_t  INTMAX_MIN, INTMAX_MAX;
+CONST uintmax_t UINTMAX_MAX;

# 7.18.3
+CONST __ptrdiff_t PTRDIFF_MIN, PTRDIFF_MAX;
+CONST __sig_atomic_t SIG_ATOMIC_MIN, SIG_ATOMIC_MAX;
+CONST __size_t SIZE_MAX;
+CONST __wint_t WINT_MIN, WINT_MAX;

# 7.18.4.1
+IFDEF ~have_int8_t
+MACRO int INT8_C(int);
+ENDIF
+IFDEF ~have_int16_t
+MACRO int INT16_C(int);
+ENDIF
+IFDEF ~have_int24_t
+MACRO int INT24_C(int);
+ENDIF
+IFDEF ~have_int32_t
+MACRO int INT32_C(int);
+ENDIF
+IFDEF ~have_int48_t
+MACRO int INT48_C(int);
+ENDIF
+IFDEF ~have_int64_t
+MACRO int INT64_C(int);
+ENDIF

# 7.18.4.2
+MACRO int INTMAX_C(int);
+MACRO int UINTMAX_C(int);

