# $Id: assert.h.ts 3158 2014-05-05 23:40:27Z kate $

# Copyright 2015, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c89", "stdio.h.ts";

# 7.19.6.n snprintf
+FUNC int snprintf(char * restrict, size_t, ~printf_string restrict, ...);
+FUNC int vsnprintf(char * restrict, size_t, ~printf_string restrict, ~va_list);

# 7.19.6.n vscanf
+FUNC int vfscanf(FILE * restrict, ~scanf_string restrict, ~va_list);
+FUNC int vscanf(~scanf_string restrict, ~va_list);
+FUNC int vsscanf(~scanf_string restrict, ~scanf_string restrict, ~va_list);

