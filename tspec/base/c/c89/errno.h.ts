# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

# 4.1.3 Errors <errno.h>

+FUNC (extern) int *__errno_location(void);
+DEFINE errno %% (*__errno_location ()) %%;

+SUBSET "enums" := {
	+CONST int EDOM, ERANGE;
};

