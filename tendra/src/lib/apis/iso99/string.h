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
+IMPLEMENT "ansi", "stddef.h", "null";
+IMPLEMENT "ansi", "stddef.h", "size_t";

# 7.21.2.1

+FUNC void *memcpy(void * restrict, const void * restrict, size_t);

# 7.21.2.2

+FUNC void *memmove(void *, const void *, size_t);

# 7.21.2.3

+FUNC char *strcpy(char * restrict, const char * restrict);

# 7.21.2.4

+FUNC char *strncpy(char * restrict, const char * restrict, size_t);

# 7.21.3.1

+FUNC char *strcat(char * restrict, const char * restrict);

# 7.21.3.2

+FUNC char *strncat(char * restrict, const char * restrict, size_t);

# 7.21.4.1

+FUNC int memcmp(const void *, const void *, size_t);

# 7.21.4.2

+FUNC int strcmp(const char *, const char *);

# 7.21.4.3

+FUNC int strcoll(const char *, const char *);

# 7.21.4.4

+FUNC int strncmp(const char *, const char *, size_t);

# 7.21.4.5

+FUNC size_t strxfrm(char * restrict, const char * restrict, size_t);

# 7.21.5.1

+FUNC void *memchr(const void *, int, size_t);

# 7.21.5.2

+FUNC char *strchr(const char *, int);

# 7.21.5.3

+FUNC size_t strcspn(const char *, const char *);

# 7.21.5.4

+FUNC char *strpbrk(const char *, const char *);

# 7.21.5.5

+FUNC char *strrchr(const char *, int);

# 7.21.5.6

+FUNC size_t strspn(const char *, const char *);

# 7.21.5.7

+FUNC char *strstr(const char *, const char *);

# 7.21.5.8

+FUNC char *strtok(char * restrict, const char * restrict);

# 7.21.6.1

+FUNC void *memset(void *, int, size_t);

# 7.21.6.2

+FUNC char *strerror(int);

# 7.21.6.3

+FUNC size_t strlen(const char *);
