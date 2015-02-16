/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EXPMACS_INCLUDED
#define EXPMACS_INCLUDED

#include "bitsmacs.h"

#define setse_opt(x) props(x) = (prop)(props(x) | 0x400)
#define isse_opt(x) (props(x) & 0x400)

#define setbyteuse(x)                   props(x) = (prop)(props(x) | 0x800)

#define frame_al_of_ptr(x) (x)->son.ald->al.al_val.al_frame
#define frame_al1_of_offset(x) (x)->son.ald->al.al_val.al_frame
#define includes_vcallees(x) ((x & 16) != 0)
#define l_or_cees(x) ((x &25) !=0)


/*
 * PROPERTIES OF IDENT CONSTRUCTS
*/

#define set_intnl_call( x )		pset ( x, 0x80 )
#define has_intnl_call( x )		ptst ( x, 0x80 )

#define is_fn_glob(e) ( name(e)==name_tag && name(son(e))==ident_tag\
	&& ( son(son(e))==NULL || name(son(son(e)))==proc_tag ||\
         name(son(son(e)))==general_proc_tag ) )
#define IS_A_PROC(e) ( name(e)==proc_tag || name(e)==general_proc_tag )


#endif /* EXPMACS_INCLUDED */


