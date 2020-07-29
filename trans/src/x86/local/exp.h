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
#define istrap(x) ((props(x) & 0x3) == 0x3)


#define frame_al_of_ptr(x) (x)->son.ald->al.frame
#define frame_al1_of_offset(x) (x)->son.ald->al.frame
#define al_includes_vcallees 16
#define al_includes_caller_args 6


/* properties of IDENT_TAG */

/* Set in weights and used in coder. At this time no copying */
#define set_intnl_call(x) props(x) = (prop)(props(x) | 0x80)
#define has_intnl_call(x) (props(x) & 0x80)

/* variable has had the no-sign-extension opt. (x86 only) */
#define setse_opt(x) props(x) = (prop)(props(x) | 0x400)
#define isse_opt(x) (props(x) & 0x400)

/* variable is used both as byte and long (x86 only) */
#define setbyteuse(x) props(x) = (prop)(props(x) | 0x800)
#define isbyteuse(x) (props(x) & 0x800)

/* used for diags, after code production */
#define set_proc_has_fp(x) props(x) = (prop)(props(x) | 0x100)
#define clear_proc_has_fp(x) props(x) &= ~0x100
#define proc_has_fp(x) (props(x) & 0x100)

/* see also setcopy */
#define set_dg_labmark(x) props(x) = (prop)(props(x) | 0x800)
#define dg_labmark(x)(props(x) & 0x800)
#define clear_dg_labmark(x) props(x) = (prop)(props(x) & ~0x800)

/* properties of STRING_TAG construction */
#define string_char_size(e) props(e)

/* properties of APPLY_TAG construction */
#define setbuiltin(x)  props(x) = (prop)(props(x) | 0x8000)
#define builtinproc(x) (props(x) & 0x8000)	/* trans386 special */

/* properties of ASM construction */
#define asm_string(x) (props(x) & 0x01)
#define asm_in(x) (props(x) & 0x02)
#define asm_out(x) (props(x) & 0x04)
#define asm_ptr(x) (props(x) & 0x08)
#define asm_var(x) (props(x) & 0x0c)	/* out | ptr */

#define set_proc_needs_envsize(x) props(x) = (prop)(props(x) | 0x8000)
#define proc_needs_envsize(x) (props(x) & 0x8000)

#define call_has_checkstack(e) (props(bro(son(e))) & 8)

#endif

