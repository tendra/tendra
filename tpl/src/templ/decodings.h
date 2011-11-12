/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef DECODINGS_INCLUDED
#define DECODINGS_INCLUDED

@use all
@loop sort
@if !sort.builtin
extern unsigned int d_%SN(int);
@endif
@end

#endif
