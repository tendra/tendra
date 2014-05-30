/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "fail.h"

#ifndef expmacs_key
#define expmacs_key 1

#ifdef __STDC__
#define Assert(x) if(!(x)) failer(#x)
#else
#define Assert(x) if(!(x)) failer("x")	/* might work, if not, who cares */
#endif
/* main components of exp */

#define son(x) ((x)->sonf.e)
#define bro(x) ((x)->brof.e)
#define last(x) (x)->lastf
#define name(x) (x)->namef
#define sh(x) (x)->shf
#define pt(x) ((x)->ptf.e)
#define props(x) (x)->propsf
#define no(x) ((x)->numf.l)
#define parked(x) ((x)->park)

/* alternative components of exp */

#define brog(x) ((x)->brof.glob)
#define nostr(x) ((x)->numf.str)
#define ptno(x) ((x) ->ptf.l)
#define sonno(x) ((x) ->sonf.l)
#define fno(x) ((x) -> numf.f)
#define dno(x) ((x) -> numf.d)
#define uno(x) ((x) -> numf.ui)

/* ntests */
#define test_number(x) (ntest)((x)->propsf & 0x1f)
#define settest_number(x, t) props(x) = (t)

/* rounding */
#define round_number(x) ((x)->propsf >> 3)
#define setround_number(x,r) (x)->propsf=(((x)->propsf & 0x7) | (r << 3))

/* error handling macros */
#define errhandle(x) ((x)->propsf & 0x7)
#define optop(x) ((int)errhandle(x) <= 2) 
#define seterrhandle(x,e) (x)->propsf= ((x)->propsf & 0xf8) | (e)

/* properties of constructions with EXCEPTIONS */
#define setjmp_dest(r,d) {(r)->ptf.e = (d); ++no(son(d));}
#define isov(x) (errhandle(x) == 0x4)

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
#define shape_align(x) ((unsigned long)((x)->brof.ald->al.al_val.al))
#define align_of(x) ((x)->brof.ald)
#define al1(x) ((unsigned long)((x)->sonf.ald->al.al_val.al))
#define al1_of(x) ((x)->sonf.ald)
#define al2(x) ((unsigned long)((x)->ptf.ald->al.al_val.al))
#define al2_of(x) ((x)->ptf.ald)
#define is_signed(x) (x)->lastf


/* properties of IDENT */


#define setvar(e) props(e) |= 0x01
  /* sets the property of a declaration to isvar (is a variable)*/
#define clearvar(e) props(e) &= ~0x01
  /* sets the property of a declaration to !isvar */
#define setid(e) props(e) &= ~0x01
  /* sets the property of a declaration to !isvar */
#define isvar(e) (props(e)&0x01)
  /* tests the property of a declaration as above */

#define setvis(e) props(e) |= 0x02
  /* sets the property of a declaration to in memory */
#define isvis(e) (props(e)&0x02)
  /* tests if a declaration is to be in memory */

#define setenvoff(e) props(e) |= 0x04
  /* sets the property of a declaration to visible */
#define isenvoff(e) (props(e)&0x04)
  /* tests if a declaration is to be visible */

#define setcaonly(e) props(e) |= 0x08
  /* sets the property of a variable declaration to show that it is only
     operated on by contents and assign operations */
#define clearcaonly(e) props(e) = (prop)(props(e) & ~0x08)
#define iscaonly(e) (props(e)&0x08)
  /* tests the above property */

#define setusereg(e) props(e) |= 0x10
  /* sets the property of a declaration to recommend the use of
     a register */
#define isusereg(e) (props(e)&0x10)
  /* tests a declaration for a register recommendation */
#define clearusereg(e) props(e) &= ~0x10

#define setparam(x) props(x) |= 0x20
#define clearparam(x) props(x) &= ~0x20
#define isparam(x) (props(x) & 0x20)

#define setglob(e) props(e) |= 0x40
  /* sets property of declaration to be global, in this case
     bro(e) will be the index of the declaration */
#define clearglob(e) props(e) &= ~0x40
#define isglob(e) (props(e)&0x40)
  /* tests the above property */

#define setcopy(e) props(e) |= 0x80
  /* set a flag used during copy */
#define clearcopy(e) props(e) &= ~0x80
  /* clear a flag used during copy */
#define copying(e) (props(e)&0x80)
  /* test the flag used during copying */

#define setinlined(x) props(x) = (prop)(props(x) | 0x200)
#define isinlined(x) (props(x) & 0x200)
#define clearinlined(x) props(x) &= ~0x200

#define setoutpar(x) props(x) |= 0x8000
#define isoutpar(x) ((props(x) & 0x8000) != 0)
#define clearoutpar(x) props(x) &= ~0x8000

/* Set in weights and used in coder. At this time no copying */
#define set_intnl_call(x) props(x) |= 0x80
#define has_intnl_call(x) (props(x) & 0x80)

/* properties of MAKE_PROC construction */

#define set_struct_res(x) props(x) |= 0x1
#define has_struct_res(x) (props(x) & 0x1)

#define set_loc_address(x) props(x) |= 0x2
#define loc_address(x) (props(x) & 0x2)

#define set_proc_has_setjmp(x) props(x) |= 0x4
#define proc_has_setjmp(x) (props(x) & 0x4)

#define set_proc_has_alloca(x) props(x) |= 0x8
#define proc_has_alloca(x) (props(x) & 0x8)

#define set_proc_has_lv(x) props(x) |= 0x10
#define proc_has_lv(x) (props(x) & 0x10)

#define isrecursive(x) (props(x) & 0x20)
#define setrecursive(x) props(x) |= 0x20

#define set_proc_uses_crt_env(x) props(x) |= 0x40
#define proc_uses_crt_env(x) (props(x) & 0x40)

#define set_proc_uses_external(x) props(x) |= 0x80
#define proc_uses_external(x) (props(x) & 0x80)

#define set_proc_has_float(x) props(x) |= 0x100
#define proc_has_float(x) (props(x) & 0x100)

/*set property of SOLVE construction */
#define setcrtsolve(x) props(x)=1

/* properties of pt of REP and SOLVE during copy */
#define set_copying_solve(x) props(x) |= 1
#define clear_copying_solve(x) props(x) &= ~0x01

/* properties of MOVE_SOME construction */
#define setnooverlap(x) props(x) |= 0x01
#define isnooverlap(x) (props(x) & 0x01)

/* properties of CONT construction */
#define set_propagate(x) props(x) |= 0x1
#define to_propagate(x) (props(x) & 0x1)
#define clear_propagate(x) props(x) &= ~0x01

/* various properties of LABST construction are used in exp.c */
#define set_loaded_lv(x) props(x) |= 0x10
#define is_loaded_lv(x) (props(x) & 0x10)
#define setunroll(x) props(x) = (prop)(props(x) | 0x04)
#define clearunroll(x)  props(x) = (prop)(props(x) & ~0x04)
#define isunroll(x) (props(x) & 0x04)

/* properties of NAME construction */
#define setlastuse(x) props(x) |= 0x01
#define islastuse(x) (props(x) & 0x01)

#define setloadparam(x) props(x) |= 0x02
#define isloadparam(x) (props(x) & 0x02)

#define setreallyass(x) props(x) |= 0x04
#define isreallyass(x) (props(x) & 0x04)

#define set_vararg(x)	props(x)|=0x08
#define is_vararg(x)    (props(x) & 0x08)

/* properties of STRING construction */
#define string_char_size(e) props(e)

/* properties of VAL construction */
#define setbigval(x)  props(x) |=  0x01
#define clearbigval(x) props(x) &= ~0x01
#define isbigval(x) (props(x) & 0x01)
#define setconstovf(x) props(x) |= 0x02
#define constovf(x) (props(x) & 0x02)

/* properties of REP construction */
#define setunrolled(x)  props(x) = (prop)(props(x) | 0x01)
#define isunrolled(x) (props(x) & 0x01)

/* properties of APPLY construction */
#define settoinline(x)  props(x) = (prop)(props(x) | 0x01)
#define istoinline(x) (props(x) & 0x01)

/* properties of jump record */
#define fstack_pos_of(x) (x)->propsf

#if 0
#define proc_has_gen_call(e) (props(e) & 0x4000)
#define set_proc_has_gen_call(e) props(e) |= 0x4000
#endif
#define set_has_c_vararg(x)	props(x)|=0x400
#define clear_has_c_vararg(x) props(x) &= ~0x400
#define has_c_vararg(x)		(props(x)&0x400)
#define set_has_machine_division(x) props(x)|=0x2000
#define has_machine_division(x) (props(x)&0x2000)
#define has_float(x)	(props(x)&0x1000)
#define set_has_float(x) props(x)|=0x1000

#define frame_al_of_ptr(x) (x)->sonf.ald->al.al_val.al_frame
#define frame_al1_of_offset(x) (x)->sonf.ald->al.al_val.al_frame
#define includes_vcallees(x) ((x & 16) != 0)
#define l_or_cees(x) ((x &25) !=0)

/* rounding for alignment */

#define rounder(n,a) (((n)+(a)-1)/(a))*(a)

#define align64	((unsigned long) 64)
#define align32 ((unsigned long) 32)
#define align16 ((unsigned long) 16)
#define align8 ((unsigned long) 8)
#define align1 ((unsigned long) 1)

#define size64 ((long) 64)
#define size32 ((long) 32)
#define size16 ((long) 16)
#define size8 ((long) 8)
#define Z (long)0

#define set_callee(id)	setname(son(id), formal_callee_tag)
#define set_make_procprops(e, p) props(e) |= ((p)<<8)
#define proc_has_vcallees(e) ((props(e) & 0x200)!=0)
#define postlude_has_call(e) (props(e) & 1)
#define call_has_vcallees(e) ((props(e) & 2) != 0)
#define call_has_vcallers(e) ((props(e) & 1) != 0)
#define proc_has_checkstack(e) ((props(e) & 0x800)!=0)
#define proc_has_vcallers(e) ((props(e) & 0x100) != 0)
#define proc_has_nolongj(e) ((props(e) & 0x1000) !=0)
#define call_is_untidy(e) ((props(e) & 4) != 0)

#define set_checkalloc(x) props(x) |= 1
#define checkalloc(x) (props(x) & 1)
#endif


