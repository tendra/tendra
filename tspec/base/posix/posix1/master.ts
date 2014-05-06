# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# This is ISO/IEC 9945-1:1990, which is a ratification of
# IEEE POSIX 1003.1-1990 (aka POSIX.1 in its 1990 revision).
# As far as I know the texts are identical.
#
# Entitled "Portable Operating System Interface (POSIX) -- Part 1:
# System Application Program Interface (API)"

$UNIQUE = 1 ;
$VERSION = "2.6" ;
+BASE_API ;

+IMPLEMENT "posix/posix1", "assert.h.ts" ;
+IMPLEMENT "posix/posix1", "ctype.h.ts" ;
+IMPLEMENT "posix/posix1", "dirent.h.ts" ;
+IMPLEMENT "posix/posix1", "errno.h.ts" ;
+IMPLEMENT "posix/posix1", "fcntl.h.ts" ;
+IMPLEMENT "posix/posix1", "float.h.ts" ;
+IMPLEMENT "posix/posix1", "grp.h.ts" ;
+IMPLEMENT "posix/posix1", "limits.h.ts" ;
+IMPLEMENT "posix/posix1", "locale.h.ts" ;
+IMPLEMENT "posix/posix1", "math.h.ts" ;
+IMPLEMENT "posix/posix1", "pwd.h.ts" ;
+IMPLEMENT "posix/posix1", "setjmp.h.ts" ;
+IMPLEMENT "posix/posix1", "signal.h.ts" ;
+IMPLEMENT "posix/posix1", "stdarg.h.ts" ;
+IMPLEMENT "posix/posix1", "stddef.h.ts" ;
+IMPLEMENT "posix/posix1", "stdio.h.ts" ;
+IMPLEMENT "posix/posix1", "stdlib.h.ts" ;
+IMPLEMENT "posix/posix1", "string.h.ts" ;
+IMPLEMENT "posix/posix1", "sys/stat.h.ts" ;
+IMPLEMENT "posix/posix1", "sys/times.h.ts" ;
+IMPLEMENT "posix/posix1", "sys/types.h.ts" ;
+IMPLEMENT "posix/posix1", "sys/utsname.h.ts" ;
+IMPLEMENT "posix/posix1", "sys/wait.h.ts" ;
+IMPLEMENT "posix/posix1", "termios.h.ts" ;
+IMPLEMENT "posix/posix1", "time.h.ts" ;
+IMPLEMENT "posix/posix1", "unistd.h.ts" ;
+IMPLEMENT "posix/posix1", "utime.h.ts" ;
