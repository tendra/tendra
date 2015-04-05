# $Id: assert.h.ts 3158 2014-05-05 23:40:27Z kate $

# Copyright 2015, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c89", "stdlib.h.ts";

# 7.20 p2
+FIELD (struct) lldiv_t { long long int quot, rem; };

# 7.20.1.1
+FUNC long long int atoll(const char *);

# 7.20.1.2
+FUNC long double strtold(const char * ~restrict, char ** ~restrict);

# 7.20.1.3
+FUNC long long int strtoll(const char * ~restrict, char ** ~restrict, int);
+FUNC unsigned long long int strtoull(const char * ~restrict, char ** ~restrict, int);

# 7.20.4.4
+FUNC ~bottom _Exit(int);

# 7.20.6.1
+FUNC long long llabs(long long int);

# 7.20.6.2
+FUNC lldiv_t lldiv(long long int, long long int);

