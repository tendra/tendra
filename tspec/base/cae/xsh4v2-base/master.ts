# $Id$

# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

$UNIQUE = 1 ;
$VERSION = "2.7" ;
+BASE_API ;

$INFO = "X/Open Single UNIX Specification";

# XXX: networking (-ar, -socket etc?) and curses need to go elsewhere

+IMPLEMENT "cae/xsh4v2-base", "sys/ipc.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "sys/msg.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "sys/sem.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "sys/socket.h.ts" ;		# Networking
+IMPLEMENT "cae/xsh4v2-base", "sys/stat.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "sys/times.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "sys/types.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "sys/un.h.ts" ;		# Networking
+IMPLEMENT "cae/xsh4v2-base", "sys/utsname.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "sys/wait.h.ts" ;

+IMPLEMENT "cae/xsh4v2-base", "arpa/inet.h.ts" ;		# Networking
+IMPLEMENT "cae/xsh4v2-base", "assert.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "cpio.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "ctype.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "curses.h.ts" ;		# Curses
+IMPLEMENT "cae/xsh4v2-base", "dirent.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "errno.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "fcntl.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "float.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "ftw.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "grp.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "iconv.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "langinfo.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "limits.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "locale.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "math.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "netdb.h.ts" ;		# Networking
+IMPLEMENT "cae/xsh4v2-base", "netinet/in.h.ts" ;		# Networking
+IMPLEMENT "cae/xsh4v2-base", "nl_types.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "pwd.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "regexp.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "search.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "setjmp.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "signal.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "stdarg.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "stddef.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "stdio.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "stdlib.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "string.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "tar.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "term.h.ts" ;			# Curses
+IMPLEMENT "cae/xsh4v2-base", "termios.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "time.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "ulimit.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "unctrl.h.ts" ;		# Curses
+IMPLEMENT "cae/xsh4v2-base", "unistd.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "utime.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "varargs.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "wchar.h.ts" ;
+IMPLEMENT "cae/xsh4v2-base", "xti.h.ts" ;			# Networking

