/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCALEXPMACS_H
#define LOCALEXPMACS_H

#define frame_al_of_ptr(x) (x)->son.ald->al.frame
#define frame_al1_of_offset(x) (x)->son.ald->al.frame
#define includes_vcallees(x) ((x & 16) != 0)
#define l_or_cees(x) ((x &25) !=0)

extern shape LISTsh;

#define isLIST(x) (x)==LISTsh

/* properties of IDENT */

/* Set in weights and used in coder. At this time no copying */
#define set_intnl_call(x) props(x) |= 0x80
#define has_intnl_call(x) (props(x) & 0x80)

/* properties of STRING construction */
#define string_char_size(e) props(e)

#endif
