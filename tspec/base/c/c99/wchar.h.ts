# $Id: assert.h.ts 3158 2014-05-05 23:40:27Z kate $

# Copyright 2015, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c95", "wchar.h.ts";
+IMPLEMENT "c/c89", "time.h.ts", "tm"; # XXX: should this be in C95?

# 7.24.2.n
+FUNC int vfwscanf(FILE * ~restrict, const wchar_t * ~restrict, va_list);
+FUNC int vswscanf(const wchar_t * ~restrict, const wchar_t * ~restrict, va_list);
+FUNC int vwscanf(const wchar_t * ~restrict, va_list);

# 7.24.4.1.1
+FUNC float wcstof(const wchar_t * ~restrict, wchar_t ** ~restrict);
+FUNC long double wcstold(const wchar_t * ~restrict, wchar_t ** ~restrict);

# 7.24.4.1.2
+FUNC long long int wcstoll(const wchar_t * ~restrict, wchar_t ** ~restrict, int);
+FUNC unsigned long long int wcstoull( const wchar_t * ~restrict, wchar_t ** ~restrict, int);

