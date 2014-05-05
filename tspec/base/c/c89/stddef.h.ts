# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# 4.1.5 Common definitions <stddef.h>

+SUBSET "null" := {
	$PROTECT = "";
	+IFNDEF NULL
	+DEFINE NULL 0;
	+ENDIF
};

+SUBSET "size_t" := {
	+TYPE (unsigned) size_t | "size_t";
	+TYPEDEF ~promote (size_t) __size_t  | "__size_t";
};

+SUBSET "wchar_t" := {
	+TYPE (int) wchar_t | "wchar_t";
};

+TYPE (signed) ptrdiff_t | "ptrdiff_t";

+TOKEN offsetof # This is tricky
%% PROC { STRUCT s, TYPE t, MEMBER t : s : m | \
   TYPE s, MEMBER s : m } EXP const : size_t : %%;

