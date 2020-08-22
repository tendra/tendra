/*
 * Copyright 2008-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCAL_EXP_H
#define LOCAL_EXP_H

#include <reader/exp.h>

#include <construct/installtypes.h>


/* properties of constructions with EXCEPTIONS */
#define istrap(x) (((x)->props & 0x3) == 0x3)


#define frame_al_of_ptr(x) (x)->child.ald->al.frame
#define frame_al1_of_offset(x) (x)->child.ald->al.frame
#define al_includes_vcallees 16
#define al_includes_caller_args 6


/* properties of IDENT_TAG */

/* Set in weights and used in coder. At this time no copying */
#define set_intnl_call(x) (x)->props = (prop)((x)->props | 0x80)
#define has_intnl_call(x) ((x)->props & 0x80)

/* variable has had the no-sign-extension opt. (x86 only) */
#define setse_opt(x) (x)->props = (prop)((x)->props | 0x400)
#define isse_opt(x) ((x)->props & 0x400)

/* variable is used both as byte and long (x86 only) */
#define setbyteuse(x) (x)->props = (prop)((x)->props | 0x800)
#define isbyteuse(x) ((x)->props & 0x800)

/* used for diags, after code production */
#define set_proc_has_fp(x) (x)->props = (prop)((x)->props | 0x100)
#define clear_proc_has_fp(x) (x)->props &= ~0x100
#define proc_has_fp(x) ((x)->props & 0x100)

/* see also setcopy */
#define set_dg_labmark(x) (x)->props = (prop)((x)->props | 0x800)
#define dg_labmark(x)((x)->props & 0x800)
#define clear_dg_labmark(x) (x)->props = (prop)((x)->props & ~0x800)

/* properties of STRING_TAG construction */
#define string_char_size(e) (e)->props

/* properties of APPLY_TAG construction */
#define setbuiltin(x)  (x)->props = (prop) ((x)->props | 0x8000)
#define builtinproc(x) ((x)->props & 0x8000)	/* trans386 special */

/* properties of ASM construction */
#define asm_string(x) ((x)->props & 0x01)
#define asm_in(x) ((x)->props & 0x02)
#define asm_out(x) ((x)->props & 0x04)
#define asm_ptr(x) ((x)->props & 0x08)
#define asm_var(x) ((x)->props & 0x0c)	/* out | ptr */

#define set_proc_needs_envsize(x) (x)->props = (prop)((x)->props | 0x8000)
#define proc_needs_envsize(x) ((x)->props & 0x8000)

#define call_has_checkstack(e) (next(child(e))->props & 8)

#endif

