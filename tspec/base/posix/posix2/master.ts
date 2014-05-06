# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# This is ISO/IEC 9945-2:1993, which is a ratification of
# IEEE 1003.2-1992 (aka POSIX.2 in its 1992 revision).
# As far as I know the texts are identical.
#
# But this doesn't make sense, because IEEE 1003.2-1992 (and therefore
# I presume also ISO/IEC 9945-2:1993) only defines the Shell and Utilities,
# not C headers.
# Though ISO/IEC 9945-2:1993 does apparently specify regexps, which is what
# we have here.
#
# TODO: is this really ISO/IEC 9945-2:1993 ? I can't imagine the DRA would
# have mis-claimed that.

$UNIQUE = 1 ;
$VERSION = "2.6" ;
+BASE_API ;

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
