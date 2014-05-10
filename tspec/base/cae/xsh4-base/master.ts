# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# This is the "BASE" Feature Group
# of XSH Issue 4, "System Interfaces and Headers",
# which constitutes the C headers part of XPG4.
# Specified by X/Open as part of CAE. Document number C202,
# ISBN: 1-872630-47-2 publushed July 1992.

$UNIQUE  = 1;
$VERSION = "2.6";
+BASE_API;

$INFO = "X/Open CAE XSH Issue 4 - System Interfaces and Headers";

+IMPLEMENT "cae/xsh4-base", "sys/ipc.h.ts";
+IMPLEMENT "cae/xsh4-base", "sys/msg.h.ts";
+IMPLEMENT "cae/xsh4-base", "sys/sem.h.ts";
+IMPLEMENT "cae/xsh4-base", "sys/stat.h.ts";
+IMPLEMENT "cae/xsh4-base", "sys/times.h.ts";
+IMPLEMENT "cae/xsh4-base", "sys/types.h.ts";
+IMPLEMENT "cae/xsh4-base", "sys/utsname.h.ts";
+IMPLEMENT "cae/xsh4-base", "sys/wait.h.ts";

+IMPLEMENT "cae/xsh4-base", "assert.h.ts";
+IMPLEMENT "cae/xsh4-base", "cpio.h.ts";
+IMPLEMENT "cae/xsh4-base", "ctype.h.ts";
+IMPLEMENT "cae/xsh4-base", "dirent.h.ts";
+IMPLEMENT "cae/xsh4-base", "errno.h.ts";
+IMPLEMENT "cae/xsh4-base", "fcntl.h.ts";
+IMPLEMENT "cae/xsh4-base", "float.h.ts";
+IMPLEMENT "cae/xsh4-base", "ftw.h.ts";
+IMPLEMENT "cae/xsh4-base", "grp.h.ts";
+IMPLEMENT "cae/xsh4-base", "iconv.h.ts";
+IMPLEMENT "cae/xsh4-base", "iso646.h.ts";
+IMPLEMENT "cae/xsh4-base", "langinfo.h.ts";
+IMPLEMENT "cae/xsh4-base", "limits.h.ts";
+IMPLEMENT "cae/xsh4-base", "locale.h.ts";
+IMPLEMENT "cae/xsh4-base", "math.h.ts";
+IMPLEMENT "cae/xsh4-base", "nl_types.h.ts";
+IMPLEMENT "cae/xsh4-base", "pwd.h.ts";
+IMPLEMENT "cae/xsh4-base", "regexp.h.ts";
+IMPLEMENT "cae/xsh4-base", "search.h.ts";
+IMPLEMENT "cae/xsh4-base", "setjmp.h.ts";
+IMPLEMENT "cae/xsh4-base", "signal.h.ts";
+IMPLEMENT "cae/xsh4-base", "stdarg.h.ts";
+IMPLEMENT "cae/xsh4-base", "stddef.h.ts";
+IMPLEMENT "cae/xsh4-base", "stdio.h.ts";
+IMPLEMENT "cae/xsh4-base", "stdlib.h.ts";
+IMPLEMENT "cae/xsh4-base", "string.h.ts";
+IMPLEMENT "cae/xsh4-base", "tar.h.ts";
+IMPLEMENT "cae/xsh4-base", "termios.h.ts";
+IMPLEMENT "cae/xsh4-base", "ulimit.h.ts";
+IMPLEMENT "cae/xsh4-base", "unistd.h.ts";
+IMPLEMENT "cae/xsh4-base", "utime.h.ts";
+IMPLEMENT "cae/xsh4-base", "varargs.h.ts";
+IMPLEMENT "cae/xsh4-base", "wchar.h.ts";
+IMPLEMENT "cae/xsh4-base", "xti.h.ts";

