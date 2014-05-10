# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


$UNIQUE = 1 ;
$VERSION = "2.6" ;
+BASE_API ;

$INFO = "System V Interface Definition 3rd edition";

+IMPLEMENT "svid/svid3", "acl.h.ts" ;
+IMPLEMENT "svid/svid3", "assert.h.ts" ;
+IMPLEMENT "svid/svid3", "cpio.h.ts" ;
+IMPLEMENT "svid/svid3", "cs.h.ts" ;
+IMPLEMENT "svid/svid3", "ctype.h.ts" ;
+IMPLEMENT "svid/svid3", "curses.h.ts" ;
+IMPLEMENT "svid/svid3", "dirent.h.ts" ;
+IMPLEMENT "svid/svid3", "errno.h.ts" ;
+IMPLEMENT "svid/svid3", "eti.h.ts" ;
+IMPLEMENT "svid/svid3", "fcntl.h.ts" ;
+IMPLEMENT "svid/svid3", "float.h.ts" ;
+IMPLEMENT "svid/svid3", "fmtmsg.h.ts" ;
+IMPLEMENT "svid/svid3", "form.h.ts" ;
+IMPLEMENT "svid/svid3", "ftw.h.ts" ;
+IMPLEMENT "svid/svid3", "grp.h.ts" ;
+IMPLEMENT "svid/svid3", "langinfo.h.ts" ;
+IMPLEMENT "svid/svid3", "limits.h.ts" ;
+IMPLEMENT "svid/svid3", "locale.h.ts" ;
+IMPLEMENT "svid/svid3", "mac.h.ts" ;
+IMPLEMENT "svid/svid3", "malloc.h.ts" ;
+IMPLEMENT "svid/svid3", "math.h.ts" ;
+IMPLEMENT "svid/svid3", "menu.h.ts" ;
+IMPLEMENT "svid/svid3", "mon.h.ts" ;
+IMPLEMENT "svid/svid3", "netconfig.h.ts" ;
+IMPLEMENT "svid/svid3", "netdir.h.ts" ;
+IMPLEMENT "svid/svid3", "nl_types.h.ts" ;
+IMPLEMENT "svid/svid3", "nlist.h.ts" ;
+IMPLEMENT "svid/svid3", "panel.h.ts" ;
+IMPLEMENT "svid/svid3", "pfmt.h.ts" ;
+IMPLEMENT "svid/svid3", "pkginfo.h.ts" ;
+IMPLEMENT "svid/svid3", "poll.h.ts" ;
+IMPLEMENT "svid/svid3", "priv.h.ts" ;
+IMPLEMENT "svid/svid3", "prof.h.ts" ;
+IMPLEMENT "svid/svid3", "pwd.h.ts" ;
+IMPLEMENT "svid/svid3", "regexp.h.ts" ;
+IMPLEMENT "svid/svid3", "remop.h.ts" ;
+IMPLEMENT "svid/svid3", "rpc/key_prot.h.ts" ;
+IMPLEMENT "svid/svid3", "rpc/rpc.h.ts" ;
+IMPLEMENT "svid/svid3", "rpc/types.h.ts" ;
+IMPLEMENT "svid/svid3", "rpc/xdr.h.ts" ;
+IMPLEMENT "svid/svid3", "search.h.ts" ;
+IMPLEMENT "svid/svid3", "setjmp.h.ts" ;
+IMPLEMENT "svid/svid3", "siginfo.h.ts" ;
+IMPLEMENT "svid/svid3", "signal.h.ts" ;
+IMPLEMENT "svid/svid3", "stdarg.h.ts" ;
+IMPLEMENT "svid/svid3", "stddef.h.ts" ;
+IMPLEMENT "svid/svid3", "stdio.h.ts" ;
+IMPLEMENT "svid/svid3", "stdlib.h.ts" ;
+IMPLEMENT "svid/svid3", "string.h.ts" ;
+IMPLEMENT "svid/svid3", "stropts.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/acct.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/audit.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/ipc.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/lock.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/mman.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/mount.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/msg.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/priocntl.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/procset.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/resource.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/rtpriocntl.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/sem.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/shm.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/stat.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/statvfs.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/swap.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/termio.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/termios.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/termiox.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/time.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/times.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/tspriocntl.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/types.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/uio.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/utsname.h.ts" ;
+IMPLEMENT "svid/svid3", "sys/wait.h.ts" ;
+IMPLEMENT "svid/svid3", "tar.h.ts" ;
+IMPLEMENT "svid/svid3", "term.h.ts" ;
+IMPLEMENT "svid/svid3", "termio.h.ts" ;
+IMPLEMENT "svid/svid3", "termios.h.ts" ;
+IMPLEMENT "svid/svid3", "time.h.ts" ;
+IMPLEMENT "svid/svid3", "tiuser.h.ts" ;
+IMPLEMENT "svid/svid3", "ucontext.h.ts" ;
+IMPLEMENT "svid/svid3", "ulimit.h.ts" ;
+IMPLEMENT "svid/svid3", "unctrl.h.ts" ;
+IMPLEMENT "svid/svid3", "unistd.h.ts" ;
+IMPLEMENT "svid/svid3", "ustat.h.ts" ;
+IMPLEMENT "svid/svid3", "utime.h.ts" ;
+IMPLEMENT "svid/svid3", "utmp.h.ts" ;
+IMPLEMENT "svid/svid3", "varargs.h.ts" ;
+IMPLEMENT "svid/svid3", "wait.h.ts" ;

+SUBSET "config" := {
    /* System V configuration */
    +DEFINE __SYSV_KERNEL_EXTENSION 1 ;
    +DEFINE __SYSV_ADMINISTERED_SYSTEMS 1 ;
    +DEFINE __SYSV_SOFTWARE_DEVELOPMENT 1 ;
    +DEFINE __SYSV_TERMINAL_INTERFACE 1 ;
    +DEFINE __SYSV_REAL_TIME 1 ;
    +DEFINE __SYSV_REMOTE_SERVICES 1 ;
    +DEFINE __SYSV_WINDOW_SYSTEMS 0 ;
    +DEFINE __SYSV_UPDATE 1 ;
    +DEFINE __SYSV_ENHANCED_SECURITY 1 ;
    +DEFINE __SYSV_AUDITING_EXTENSION 1 ;
    +DEFINE __SYSV_REMOTE_ADMINISTRATION 1 ;
} ;
