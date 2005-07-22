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

# 7.17

+SUBSET "_ptrdiff_t" := {
    +IFNDEF ~building_libs
    +TYPE (signed) ~ptrdiff_t.1 | ptrdiff_t.1;
    +TYPEDEF ~promote(~ptrdiff_t) __promoted_ptrdiff_t.1;
    +ELSE
    +TYPE (signed) ptrdiff_t.2 | ptrdiff_t.2;
    +TYPEDEF ~promote(ptrdiff_t) __promoted_ptrdiff_t.2;
    +ENDIF
};
+IFNDEF ~building_libs
+TYPEDEF ~ptrdiff_t ptrdiff_t;
+ENDIF

+SUBSET "_size_t" := {
    +IFNDEF ~building_libs
    +TYPE (unsigned) ~size_t.1 | size_t.1;
    +TYPEDEF ~promote(~size_t) __promoted_size_t.1;
    +ELSE
    +TYPE (unsigned) size_t.2 | size_t.2;
    +TYPEDEF ~promote(size_t) __promoted_size_t.2;
    +ENDIF
};
+SUBSET "size_t" := {
    +USE "iso99", "stddef.h", "_size_t";
    +IFNDEF ~building_libs
    +TYPEDEF ~size_t size_t;
    +ENDIF
};

+SUBSET "_wchar_t" := {
    +IFNDEF ~building_libs
    +TYPE (int) ~wchar_t.1 | "wchar_t";
    +TYPEDEF ~promote(~wchar_t) __promoted_wchar_t.1;
    +ELSE
    +TYPE (int) wchar_t.2 | wchar_t.2;
    +TYPEDEF wchar_t ~wchar_t.2;
    +TYPEDEF ~promote(~wchar_t) __promoted_wchar_t.2;
    +ENDIF
};
+SUBSET "wchar_t" := {
    +USE "iso99", "stddef.h", "_wchar_t";
    +IFNDEF ~building_libs
    +TYPEDEF ~wchar_t wchar_t;
    +ENDIF
};

+SUBSET "null" := {
    $PROTECT = "";
    +IFNDEF NULL
    +DEFINE NULL 0;
    +ENDIF
};

+TOKEN offsetof # This is tricky
%% PROC { STRUCT s, TYPE t, MEMBER t : s : m |\
    TYPE s, MEMBER s : m } EXP const : size_t : %%;
