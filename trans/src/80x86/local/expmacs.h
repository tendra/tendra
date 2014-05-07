/* $Id$ */

/*
 * Copyright 2008-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EXPMACS_H
#define EXPMACS_H

#include <local/exptypes.h>

#include <construct/installtypes.h>

#define nilexp NULL

/* main components of exp */

#define son(x) ((x)->sonf.e)
#define bro(x) ((x)->brof.e)
#define last(x) (int)((x)->lastf)
#define name(x) (x)->namef
#define sh(x) (x)->shf
#define pt(x) ((x)->ptf.e)
#define props(x) (x)->propsf
#define no(x) ((x)->numf.l)
#define parked(x) ((x)->park)

#ifdef NEWDIAGS
#define dgf(x) ((x)->diagf)
#endif

/* alternative components of exp */

#define brog(x) ((x)->brof.glob)
#define nostr(x) ((x)->numf.str)
#define ptno(x) ((x) ->ptf.l)
#define sonno(x) ((x) ->sonf.l)
#define fno(x) ((x) -> numf.f)
#ifndef NEWDIAGS
#define dno(x) ((x) -> numf.d)
#endif
#define uno(x) ((x) -> numf.ui)

/* ntests */
#define test_number(x) (ntest)((x)->propsf & 0x1f)
#define settest_number(x, t) (x)->propsf= (prop)(((x)->propsf & 0xe0) | (int)(t))

/* rounding */
#define round_number(x) ((x)->propsf >> 3)
#define setround_number(x,r) (x)->propsf=(prop)(((x)->propsf & 0x7) | (r << 3))

/* error handling macros */
#define errhandle(x) ((x)->propsf & 0x7)
#define optop(x) ((int)errhandle(x) <= 2)
#define seterrhandle(x,e) (x)->propsf= (prop)(((x)->propsf & 0xf8) | (e))

/* properties of constructions with EXCEPTIONS */
#define setjmp_dest(r,d) {(r)->ptf.e = (d); ++no(son(d));}
#define isov(x) (errhandle(x) == 0x4)
#define istrap(x) (((x)->propsf & 0x3) == 0x3)

/* setting macros for components of exp */

#define setbro(x,b) (x)->brof.e = (b)
#define setsh(x,b) (x)->shf = (b)
#define setson(x,b) (x)->sonf.e = (b)
#define setpt(x,b) (x)->ptf.e = (b)
#define setlast(x) (x)->lastf = 1
#define clearlast(x) (x)->lastf = 0
#define setname(x,n) (x)->namef = (n)
#define setfather(f,s) (s)->brof.e = (f); (s)->lastf = 1

/* components of shapes */
#define shape_size(x) ((x)->numf.l)
#define shape_align(x) ((x)->brof.ald->al.al_val.al)
#define align_of(x) ((x)->brof.ald)
#define al1(x) ((x)->sonf.ald->al.al_val.al)
#define al1_of(x) ((x)->sonf.ald)
#define al2(x) ((x)->ptf.ald->al.al_val.al)
#define al2_of(x) ((x)->ptf.ald)
#define is_signed(x) (int)((x)->lastf)

#define frame_al_of_ptr(x) (x)->sonf.ald->al.al_val.al_frame
#define frame_al1_of_offset(x) (x)->sonf.ald->al.al_val.al_frame
#define al_includes_vcallees 16
#define al_includes_caller_args 6


/* properties of IDENT_TAG */


#define setvar(e) props(e) = (prop)(props(e) | 0x01)
  /* sets the property of a declaration to isvar (is a variable)*/
#define clearvar(e) props(e) = (prop)(props(e) & ~0x01)
  /* sets the property of a declaration to !isvar */
#define setid(e) props(e) = (prop)(props(e) & ~0x01)
  /* sets the property of a declaration to !isvar */
#define isvar(e) (props(e)&0x01)
  /* tests the property of a declaration as above */

#define setvis(e) props(e) = (prop)(props(e) | 0x02)
  /* sets the property of a declaration to in memory */
#define isvis(e) (props(e)&0x02)
  /* tests if a declaration is to be in memory */

#define setenvoff(e) props(e) = (prop)(props(e) | 0x04)
  /* sets the property of a declaration to visible */
#define isenvoff(e) (props(e)&0x04)
  /* tests if a declaration is to be visible */

#define setcaonly(e) props(e) = (prop)(props(e) | 0x08)
  /* sets the property of a variable declaration to show that it is only
     operated on by contents and assign operations */
#define clearcaonly(e) props(e) = (prop)(props(e) & ~0x08)
#define iscaonly(e) (props(e)&0x08)
  /* tests the above property */

#define setusereg(e) props(e) = (prop)(props(e) | 0x10)
  /* sets the property of a declaration to recommend the use of
     a register */
#define isusereg(e) (props(e)&0x10)
  /* tests a declaration for a register recommendation */
#define clearusereg(e) props(e) = (prop)(props(e) & ~0x10)

#define setparam(x) props(x) = (prop)(props(x) | 0x20)
#define clearparam(x) props(x) = (prop)(props(x) & ~0x20)
#define isparam(x) (props(x) & 0x20)

#define setglob(e) props(e) = (prop)(props(e) | 0x40)
  /* sets property of declaration to be global, in this case
     bro(e) will be the index of the declaration */
#define clearglob(e) props(e) &= ~0x40
#define isglob(e) (props(e)&0x40)
  /* tests the above property */

#define setcopy(e) props(e) = (prop)(props(e) | 0x80)
  /* set a flag used during copy : also used for LABST_TAG */
#define clearcopy(e) props(e) = (prop)(props(e) & ~0x80)
  /* clear a flag used during copy */
#define copying(e) (props(e)&0x80)
  /* test the flag used during copying */

/* Set in weights and used in coder. At this time no copying */
#define set_intnl_call(x) props(x) = (prop)(props(x) | 0x80)
#define has_intnl_call(x) (props(x) & 0x80)

/* variable has had the no-sign-extension opt. (80x86 only) */
#define setse_opt(x) props(x) = (prop)(props(x) | 0x400)
#define isse_opt(x) (props(x) & 0x400)

#define setinlined(x) props(x) = (prop)(props(x) | 0x200)
#define isinlined(x) (props(x) & 0x200)
#define clearinlined(x) props(x) &= ~0x200

/* variable is used both as byte and long (80x86 only) */
#define setbyteuse(x) props(x) = (prop)(props(x) | 0x800)
#define isbyteuse(x) (props(x) & 0x800)

/* parameter used for output (needs only to be in memory for 80x86) */
#define setoutpar(x) setvis(x)
#define isoutpar(x) isvis(x)
#define clearoutpar(x)

/* properties of PROC_TAG construction */

#define set_struct_res(x) props(x) = (prop)(props(x) | 0x1)
#define has_struct_res(x) (props(x) & 0x1)

#define set_loc_address(x) props(x) = (prop)(props(x) | 0x2)
#define loc_address(x) (props(x) & 0x2)

#define set_proc_has_setjmp(x) props(x) = (prop)(props(x) | 0x4)
#define proc_has_setjmp(x) (props(x) & 0x4)

#define set_proc_has_alloca(x) props(x) = (prop)(props(x) | 0x8)
#define proc_has_alloca(x) (props(x) & 0x8)

#define set_proc_has_lv(x) props(x) = (prop)(props(x) | 0x10)
#define proc_has_lv(x) (props(x) & 0x10)

#define isrecursive(x) (props(x) & 0x20)
#define setrecursive(x) props(x) = (prop)(props(x) | 0x20)

#define set_proc_uses_crt_env(x) props(x) = (prop)(props(x) | 0x40)
#define proc_uses_crt_env(x) (props(x) & 0x40)

#define set_proc_uses_external(x) props(x) = (prop)(props(x) | 0x80)
#define proc_uses_external(x) (props(x) & 0x80)

	/* used for diags, after code production */
#define set_proc_has_fp(x) props(x) = (prop)(props(x) | 0x100)
#define clear_proc_has_fp(x) props(x) &= ~0x100
#define proc_has_fp(x) (props(x) & 0x100)


/*set property of SOLVE_TAG construction */
#define setcrtsolve(x) props(x)=1

/* properties of pt of REP_TAG and SOLVE_TAG during copy */
#define set_copying_solve(x) props(x) = (prop)(props(x) | 1)
#define clear_copying_solve(x) props(x) = (prop)(props(x) & ~0x01)

/* properties of MOVECONT_TAG construction */
#define setnooverlap(x) props(x) = (prop)(props(x) | 0x01)
#define isnooverlap(x) (props(x) & 0x01)

/* properties of CONT_TAG construction */
#define set_propagate(x) props(x) = (prop)(props(x) | 0x1)
#define to_propagate(x) (props(x) & 0x1)
#define clear_propagate(x) props(x) = (prop)(props(x) & ~0x01)

/* various properties of LABST_TAG construction are used in exp.c */
#define set_loaded_lv(x) props(x) = (prop)(props(x) | 0x10)
#define is_loaded_lv(x) (props(x) & 0x10)
#define setunroll(x) props(x) = (prop)(props(x) | 0x04)
#define clearunroll(x)  props(x) = (prop)(props(x) & ~0x04)
#define isunroll(x) (props(x) & 0x04)
	/* see also setcopy */
#define set_dg_labmark(x) props(x) = (prop)(props(x) | 0x800)
#define dg_labmark(x)(props(x) & 0x800)
#define clear_dg_labmark(x) props(x) = (prop)(props(x) & ~0x800)

/* properties of NAME_TAG construction */
#define setlastuse(x) props(x) = (prop)(props(x) | 0x01)
#define islastuse(x) (props(x) & 0x01)

#define setloadparam(x) props(x) = (prop)(props(x) | 0x02)
#define isloadparam(x) (props(x) & 0x02)

#define setreallyass(x) props(x) = (prop)(props(x) | 0x04)
#define isreallyass(x) (props(x) & 0x04)

#ifdef NEWDIAGS
#define setisdiaginfo(x) props(x) = (prop)(props(x) | 0x08)
#define isdiaginfo(x) (props(x) & 0x08)

#define setdiscarded(x) props(x) = (prop)(props(x) | 0x10)
#define isdiscarded(x) (props(x) & 0x10)
#endif

/* properties of STRING_TAG construction */
#define string_char_size(e) props(e)

/* properties of VAL_TAG construction */
#define setbigval(x)  props(x) = (prop)(props(x) | 0x01)
#define clearbigval(x) props(x) = (prop)(props(x) & ~0x01)
#define isbigval(x) (props(x) & 0x01)

#define setconstovf(x)  props(x) = (prop)(props(x) | 0x02)
#define constovf(x) (props(x) & 0x02)

/* properties of REP_TAG construction */
#define setunrolled(x)  props(x) = (prop)(props(x) | 0x01)
#define isunrolled(x) (props(x) & 0x01)

/* properties of APPLY_TAG construction */
#define settoinline(x)  props(x) = (prop)(props(x) | 0x01)
#define istoinline(x) (props(x) & 0x01)

#define setbuiltin(x)  props(x) = (prop)(props(x) | 0x8000)
#define builtinproc(x) (props(x) & 0x8000)	/* trans386 special */

/* properties of ASM construction */
#define asm_string(x) (props(x) & 0x01)
#define asm_in(x) (props(x) & 0x02)
#define asm_out(x) (props(x) & 0x04)
#define asm_ptr(x) (props(x) & 0x08)
#define asm_var(x) (props(x) & 0x0c)	/* out | ptr */

/* properties of alloca constructions */
#define set_checkalloc(x) props(x) |= 1;
#define checkalloc(x) (props(x) & 1)


/* properties of jump record */

#define fstack_pos_of(x) (x)->propsf


#define set_callee(id)	setname(son(id), formal_callee_tag)
#define set_make_procprops(e, p) props(e) |= ((p)<<8)
#define proc_has_vcallees(e) (props(e) & 0x200)
#define postlude_has_call(e) (props(e) & 1)
#define call_has_vcallees(e) (props(e) & 2)
#define proc_has_checkstack(e) (props(e) & 0x800)
#define proc_has_vcallers(e) (props(e) & 0x100)
#define proc_has_nolongj(e) (props(e) & 0x1000)

#define set_proc_needs_envsize(x) props(x) = (prop)(props(x) | 0x8000)
#define proc_needs_envsize(x) (props(x) & 0x8000)

#define call_is_untidy(e) (props(bro(son(e))) & 4)
#define call_has_checkstack(e) (props(bro(son(e))) & 8)


/* rounding for alignment */

#define rounder(n,a) (((n)+(a)-1)/(a))*(a)

#define align32 ( 32)
#define align16 ( 16)
#define align8 ( 8)
#define align1 ( 1)

#define size64 ( 64)
#define size32 ( 32)
#define size16 ( 16)
#define size8 ( 8)

#endif /* EXPMACS_H */
