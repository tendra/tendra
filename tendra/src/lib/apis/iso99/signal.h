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

# 7.14

+SUBSET "_sig_atomic_t" := {
    +IFNDEF ~building_libs
    +TYPE (int) ~sig_atomic_t.1 | sig_atomic_t.1;
    +TYPEDEF ~promote(~sig_atomic_t) __promoted_sig_atomic_t.1;
    +ELSE
    +TYPE (int) sig_atomic_t.2 | sig_atomic_t.2;
    +TYPEDEF ~promote(sig_atomic_t) __promoted_sig_atomic_t.2;
    +ENDIF
};
+IFNDEF ~building_libs
+TYPEDEF ~sig_atomic_t sig_atomic_t;
+ENDIF

+CONST void (*SIG_DFL)(int);
+CONST void (*SIG_ERR)(int);
+CONST void (*SIG_IGN)(int);

+CONST int SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM;

# 7.14.1.1

+FUNC void (*signal(int, void (*)(int)))(int);

# 7.14.2.1

+FUNC int raise(int);
