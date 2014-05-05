# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# 4.7 SIGNAL HANDLING <signal.h>
+CONST void (*SIG_DFL)(int);
+CONST void (*SIG_ERR)(int);
+CONST void (*SIG_IGN)(int);

# 4.7 SIGNAL HANDLING <signal.h>
+CONST int SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM;

# 4.7.1.1 The signal function
+IFNDEF __JUST_POSIX
+FUNC void (*signal(int, void (*)(int)))(int);
+IFNDEF __JUST_XPG3
+TYPE (int) sig_atomic_t;
+FUNC int raise(int);
+ENDIF
+ENDIF

