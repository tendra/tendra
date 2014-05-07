# $Id$

# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+USE "cae/xsh2", "sys/types.h.ts", "mode_t" (!?);

+CONST int S_IFMT, S_IFSOCK;

+MACRO int S_ISSOCK(mode_t);

