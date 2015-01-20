/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#if TRANS_X86
#define COMMENT_2(x, y)	x "#" y
#else
#if TRANS_SPARC
#define COMMENT_2(x, y)	x "!" y
#else
error what is the comment to eol char ?
#endif
#endif
