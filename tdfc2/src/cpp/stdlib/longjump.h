/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LONGJUMP_INCLUDED
#define LONGJUMP_INCLUDED

/*
 * The following tokens give the interface to the TDF long_jump construct.
 * The definitions are built into the compiler.
 */

#pragma token TYPE CODE_PTR # ~cpp.ptr.code
#pragma token TYPE FRAME_PTR # ~cpp.ptr.frame
#pragma token PROC ( EXP : FRAME_PTR :, EXP : CODE_PTR : ) \
	EXP : void : long_jump # ~cpp.except.jump

#pragma interface CODE_PTR FRAME_PTR
#pragma interface long_jump

#endif

