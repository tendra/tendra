# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# This is ISO/IEC 9945-2:1993, which is a ratification of
# IEEE 1003.2-1992 (aka POSIX.2 in its 1992 revision).
# As far as I know the texts are identical.
#
# ISO/IEC 9945-2:1993 defines the "Shell and Utilities", but also
# C headers in Appendix B. It is this appendix which is specified here.
#
# These headers expose functionality (such as globbing) which the
# shell uses, and is made available by a C interface for consistency
# of other programs to use.

$UNIQUE = 1 ;
$VERSION = "2.6" ;
+BASE_API ;

$INFO = "ISO/IEC 9945-2:1993";

+IMPLEMENT "posix/posix2", "assert.h.ts" ;
+IMPLEMENT "posix/posix2", "ctype.h.ts" ;
+IMPLEMENT "posix/posix2", "dirent.h.ts" ;
+IMPLEMENT "posix/posix2", "errno.h.ts" ;
+IMPLEMENT "posix/posix2", "fcntl.h.ts" ;
+IMPLEMENT "posix/posix2", "float.h.ts" ;
+IMPLEMENT "posix/posix2", "fnmatch.h.ts" ;
+IMPLEMENT "posix/posix2", "glob.h.ts" ;
+IMPLEMENT "posix/posix2", "grp.h.ts" ;
+IMPLEMENT "posix/posix2", "limits.h.ts" ;
+IMPLEMENT "posix/posix2", "locale.h.ts" ;
+IMPLEMENT "posix/posix2", "math.h.ts" ;
+IMPLEMENT "posix/posix2", "pwd.h.ts" ;
+IMPLEMENT "posix/posix2", "regex.h.ts" ;
+IMPLEMENT "posix/posix2", "setjmp.h.ts" ;
+IMPLEMENT "posix/posix2", "signal.h.ts" ;
+IMPLEMENT "posix/posix2", "stdarg.h.ts" ;
+IMPLEMENT "posix/posix2", "stddef.h.ts" ;
+IMPLEMENT "posix/posix2", "stdio.h.ts" ;
+IMPLEMENT "posix/posix2", "stdlib.h.ts" ;
+IMPLEMENT "posix/posix2", "string.h.ts" ;
+IMPLEMENT "posix/posix2", "sys/stat.h.ts" ;
+IMPLEMENT "posix/posix2", "sys/times.h.ts" ;
+IMPLEMENT "posix/posix2", "sys/types.h.ts" ;
+IMPLEMENT "posix/posix2", "sys/utsname.h.ts" ;
+IMPLEMENT "posix/posix2", "sys/wait.h.ts" ;
+IMPLEMENT "posix/posix2", "termios.h.ts" ;
+IMPLEMENT "posix/posix2", "time.h.ts" ;
+IMPLEMENT "posix/posix2", "unistd.h.ts" ;
+IMPLEMENT "posix/posix2", "utime.h.ts" ;
+IMPLEMENT "posix/posix2", "wordexp.h.ts" ;
