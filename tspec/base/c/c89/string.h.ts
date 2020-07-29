# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c89", "stddef.h.ts", "null"   (!?);
+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" (!?);

# 4.11.2.n Copying functions
+IFNDEF __JUST_POSIX
+FUNC void *memcpy(void * ~restrict, const void * ~restrict, size_t);
+IFNDEF __JUST_XPG3
+FUNC void *memmove(void *, const void *, size_t);
+ENDIF
+FUNC char *strcpy(char * ~restrict, const char * ~restrict);
+ENDIF
+FUNC char *strncpy(char *, const char *, size_t);

# 4.11.3.n Concatenation functions
+FUNC char *strcat(char * ~restrict, const char * ~restrict);
+FUNC char *strncat(char * ~restrict, const char * ~restrict, size_t);

# 4.11.4.n Comparison functions
+IFNDEF __JUST_POSIX
+FUNC int memcmp(const void *, const void *, size_t);
+FUNC int strcoll(const char *, const char *);
+FUNC size_t strxfrm(char * ~restrict, const char * ~restrict, size_t);
+ENDIF
+FUNC int strcmp(const char *, const char *);
+FUNC int strncmp(const char *, const char *, size_t);

# 4.11.5.n Search functions
+IFNDEF ~protect("cpp", "cstring")
# These are overloaded in C++
+FUNC char *strchr(const char *, int);
+FUNC char *strpbrk(const char *, const char *);
+FUNC char *strrchr(const char *, int);
+FUNC char *strstr(const char *, const char *);
+IFNDEF __JUST_POSIX
+FUNC void *memchr(const void *, int, size_t);
+ENDIF
+ENDIF
+FUNC size_t strcspn(const char *, const char *);
+FUNC size_t strspn(const char *, const char *);
+FUNC char *strtok(char * ~restrict, const char * ~restrict);

# 4.11.6.n Miscellaneous functions
+IFNDEF __JUST_POSIX
+FUNC void *memset(void *, int, size_t);
+FUNC char *strerror(int);
+ENDIF
+FUNC size_t strlen(const char *);

