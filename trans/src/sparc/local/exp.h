/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCAL_EXP_H
#define LOCAL_EXP_H

#include "bits.h"

/*
 * PROPERTIES OF IDENT CONSTRUCTS
 */

#define set_intnl_call( x )		pset ( x, 0x80 )
#define has_intnl_call( x )		ptst ( x, 0x80 )

/* properties of ASM construction */
#define asm_string(x)			ptst(x, 0x01)
#define asm_in(x)			ptst(x, 0x02)
#define asm_out(x)			ptst(x, 0x04)
#define asm_ptr(x)			ptst(x, 0x08)
#define asm_var(x)			ptst(x, 0x0c)	/* out | ptr */

/* New operations for spec 3.1 */
#define set_postlude_has_call(e) (props(e) |= 1)
#define clear_postlude_has_call(e) (props(e) &= ~1)
#define proc_may_have_callees(e) ((props(e) & 0x8000) != 0)
#define set_proc_may_have_callees(e) (props(e) |= 0x8000)

#define frame_al_of_ptr(e) (e)->son.ald->al.frame
#define frame_al1_of_offset(e) (e)->son.ald->al.frame
#define include_vcallees(e) (e & 16)
#define cees(e) (e & 24)
#define l_or_cees(e)	(e&25)

/* property of current_env */
#define setcallee_offset(x) (props(x) |= 1)
#define callee_offset(x) (props(x) & 1)

#endif

