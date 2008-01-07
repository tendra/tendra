# Copyright (c) 2002, The TenDRA Project
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
# $TenDRA$
#
+IMPLEMENT "iso99", "stddef.h", "null";
+IMPLEMENT "iso99", "stddef.h", "size_t";

# 7.23.1

+TYPE (arith) clock_t;
+CONST clock_t CLOCKS_PER_SEC;
+TYPE (arith) time_t;
+FIELD struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

# 7.23.2.1

+FUNC clock_t clock(void);

# 7.23.2.2

+FUNC double difftime(time_t, time_t);

# 7.23.2.3

+FUNC time_t mktime(struct tm *);

# 7.23.2.4

+FUNC time_t time(time_t *);

# 7.23.3.1

+FUNC char *asctime(const struct tm *);

# 7.23.3.2

+FUNC char *ctime(const time_t *);

# 7.23.3.3

+FUNC struct tm *gmtime(const time_t *);

# 7.23.3.4

+FUNC struct tm *localtime(const time_t *);

# 7.23.3.5

+FUNC size_t strftime(char * restrict, size_t, const char * restrict,
		      const struct tm * restrict);
