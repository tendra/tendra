/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EXPMACS_INCLUDED
#define EXPMACS_INCLUDED


/*
    THE MAIN CONSTITUENTS OF AN EXPRESSION
*/

#define  name(X)		((X)->namef)
#define  son(X)		((X)->sonf.e)
#define  bro(X)		((X)->brof.e)
#define  pt(X)		((X)->ptf.e)
#define  no(X)		((X)->numf.l)
#define  sh(X)		((X)->shf)
#define  last(X)		((X)->lastf)
#define  props(X)		((X)->propsf)
#define  parked(X)		((X)->park)


/*
    ALTERNATIVE CONSTITUENTS OF AN EXPRESSION
*/

#define  sonno(X)		((X)->sonf.l)
#define  brog(X)		((X)->brof.glob)
#define  ptno(X)		((X)->ptf.l)
#define  nostr(X)		((X)->numf.str)
#define  fno(X)		((X)->numf.f)
#define  dno(X)		((X)->numf.d)
#define  uno(X)		((X)->numf.ui)


/*
    CONSTITUENTS OF AN EXPRESSION FOR NTESTS
*/

#define  test_number(X)	((int) props (X))
#define  settest_number(X, Y)	props (X) = (Y)
#define  setntest(X, Y)	props (X) = (Y)


/*
    CONSTITUENTS OF AN EXPRESSION FOR ROUNDING MODES
*/

#define  round_number(X)	(props (X) >> 3)
#define  setround_number(X, Y)\
	    props (X) = ((props (X) & 7) | ((Y) << 3))


/*
    MACROS FOR SETTING CONSTITUENTS OF EXPRESSIONS
*/

#define  setname(X, Y)	name (X) = (Y)
#define  setson(X, Y)		son (X) = (Y)
#define  setbro(X, Y)		bro (X) = (Y)
#define  setpt(X, Y)		pt (X) = (Y)
#define  setno(X, Y)		no (X) = (Y)
#define  setsh(X, Y)		sh (X) = (Y)
#define  setlast(X)		last (X) = 1
#define  clearlast(X)		last (X) = 0
#define  setfather(X, Y)	bro (Y) = (X) ; last (Y) = 1


/*
    CONSTITUENTS OF SHAPES
*/

#define  is_signed(X)		((X)->lastf)
#define  shape_size(X)	((X)->numf.l)
#define  al2ul(X)		((unsigned long) ((X)->al.al_val.al))
#define  align_of(X)		((X)->brof.ald)
#define  shape_align(X)	al2ul (align_of (X))
#define  al1_of(X)		((X)->sonf.ald)
#define  al1(X)		al2ul (al1_of (X))
#define  al2_of(X)		((X)->ptf.ald)
#define  al2(X)		al2ul (al2_of (X))

#ifndef tdf3
#define frame_al_of_ptr(x) (x)->sonf.ald->al.al_val.al_frame
#define frame_al1_of_offset(x) (x)->sonf.ald->al.al_val.al_frame
#define al_includes_vcallees 16
#define al_includes_caller_args 6
#endif

/*
    PROPERTIES OF CONSTRUCTS WITH ERROR TREATMENTS
*/

#define  isov(X)		(props (X) == 0x4)
#define  seterr_code(X, Y)	props (X) = (Y)
#define  setjmp_dest(X, Y)	\
		{ pt (X) = (Y) ; no (son (Y))++ ; }



/*
    MACROS FOR ERROR HANDLING
*/

#define  errhandle(X)		(props (X) & 0x7)
#define  optop(X)		(errhandle (X) <= 2)
#define  seterrhandle(X, Y)	\
	    props (X) = ((props (X) & 0xfff8) | (Y))


/*
    PROPERTIES OF IDENTITY DECLARATIONS
*/

#define  setvar(X)		props (X) |= 0x01
#define  clearvar(X)		props (X) &= ~0x01
#define  setid(X)		props (X) &= ~0x01
#define  isvar(X)		(props (X) & 0x01)

#define  setvis(X)		props (X) |= 0x02
#define  clearvis(X)		props (X) &= ~0x02
#define  isvis(X)		(props (X) & 0x02)

#define  setenvoff(X)		props (X) |= 0x04
#define  clearenvoff(X)	props (X) &= ~0x04
#define  isenvoff(X)		(props (X) & 0x04)

#define  setcaonly(X)		props (X) |= 0x08
#define  clearcaonly(X)	props (X) &= ~0x08
#define  iscaonly(X)		(props (X) & 0x08)

#define  setusereg(X)		props (X) |= 0x10
#define  clearusereg(X)	props (X) &= ~0x10
#define  isusereg(X)		(props (X) & 0x10)

#define  setparam(X)		props (X) |= 0x20
#define  clearparam(X)	props (X) &= ~0x20
#define  isparam(X)		(props (X) & 0x20)

#define  setglob(X)		props (X) |= 0x40
#define  clearglob(X)		props (X) &= ~0x40
#define  isglob(X)		(props (X) & 0x40)

#define  setcopy(X)		props (X) |= 0x80
#define  clearcopy(X)		props (X) &= ~0x80
#define  copying(X)		(props (X) & 0x80)

#define  set_intnl_call(X)	props (X) |= 0x80
#define  has_intnl_call(X)	(props (X) & 0x80)

#define  setinlined(X)	props (X) |= 0x200
#define  clearinlined(X)	props (X) &= ~0x200
#define  isinlined(X)		(props (X) & 0x200)

#define  setismarked(X)       props (X) |= 0x100
#define  ismarked(X)		(props (X) & 0x100)

/*
    PROPERTIES OF MAKE_PROC CONSTRUCTS
*/

#define  set_struct_res(X)		props (X) |= 0x1
#define  has_struct_res(X)		(props (X) & 0x1)

#define  set_loc_address(X)		props (X) |= 0x2
#define  loc_address(X)		(props (X) & 0x2)

#define  set_proc_has_setjmp(X)	 props (X) |= 0x4
#define  proc_has_setjmp(X)		(props (X) & 0x4)

#define  set_proc_has_alloca(X)	 props (X) |= 0x8
#define  proc_has_alloca(X)		(props (X) & 0x8)

#define  set_proc_has_lv(X)		props (X) |= 0x10
#define  proc_has_lv(X)		(props (X) & 0x10)

#define  isrecursive(X)		(props (X) & 0x20)
#define  setrecursive(X)		props (X) |= 0x20

#define  set_proc_uses_crt_env(X)	props (X) |= 0x40
#define  proc_uses_crt_env(X)		(props (X) & 0x40)

#define  set_proc_uses_external(X)	props (X) |= 0x80
#define  proc_uses_external(X)	(props (X) & 0x80)


/*
    PROPERTIES OF SOLVE CONSTRUCTS
*/

#define  setcrtsolve(X)		props (X) = 1
#define  set_copying_solve(X)		props (X) |= 1
#define  clear_copying_solve(X)	props (X) &= ~0x01


/*
    PROPERTIES OF MOVE_SOME CONSTRUCT
*/

#define  setnooverlap(X)		props (X) |= 0x01


/*
    PROPERTIES OF CONTENTS CONSTRUCT
*/

#define  set_propagate(X)		props (X) |= 0x1
#define  to_propagate(X)		(props (X) & 0x1)
#define  clear_propagate(X)		props (X) &= ~0x01


/*
    PROPERTIES OF LABST CONSTRUCT
*/

#define  set_loaded_lv(X)		props (X) |= 0x10
#define  is_loaded_lv(X)		(props (X) & 0x10)
#define  setunroll(X)			props (X) |= 0x20
#define  clearunroll(X)		props (X) &= ~0x20
#define  isunroll(X)			(props (X) & 0x20)


/*
    PROPERTIES OF NAME CONSTRUCT
*/

#define  setlastuse(X)		props (X) |= 0x01
#define  islastuse(X)			(props (X) & 0x01)
#define  setloadparam(X)		props (X) |= 0x02
#define  isloadparam(X)		(props (X) & 0x02)
#define  setreallyass(X)		/* props (X) |= 0x04 */
#define  isreallyass(X)		(props (X) & 0x04)


/*
    PROPERTIES OF VAL CONSTRUCT
*/

#define  setbigval(X)			props (X) |= 0x01
#define  clearbigval(X)		props (X) &= ~0x01
#define  isbigval(X)			(props (X) & 0x01)
#define  setconstovf(X)               props(X) |= 0x02
#define  constovf(X)                  (props(X) & 0x02)
/*
    PROPERTIES OF REPEAT CONSTRUCT
*/

#define  setunrolled(X)		props (X) |= 0x01
#define  isunrolled(X)		(props (X) & 0x01)


/*
    PROPERTIES OF APPLY CONSTRUCT
*/

#define  settoinline(X)		props (X) |= 0x01
#define  istoinline(X)		(props (X) & 0x01)


/*
    ROUNDING FOR ALIGNMENT
*/

#define  rounder(X, Y)		\
	    ((((X) + (Y) - 1) / (Y)) * (Y))


/*
    BASIC ALIGNMENTS
*/

#define  align32			((unsigned long) 32)
#define  align16			((unsigned long) 16)
#define  align8				((unsigned long) 8)
#define  align1				((unsigned long) 1)

#define  size64				((long) 64)
#define  size32				((long) 32)
#define  size16				((long) 16)
#define  size8				((long) 8)
#define  Z				(long) 0


#define set_checkalloc(x) props(x) |= 1
#define checkalloc(x) (props(x) & 1)

#define set_callee(id)  setname(son(id), formal_callee_tag)
#define set_make_procprops(e, p) props(e) |= ((p)<<8)

#ifndef tdf3
/* parameter used for output (needs to be in memory for 68k) */
#define setoutpar(x) setvis(x)
#define isoutpar(x) isvis(x)
#define clearoutpar(x)
#else
#define setoutpar(x) props(x) |= 0x8000
#define isoutpar(x) ((props(x) & 0x8000) != 0)
#define clearoutpar(x) props(x) &= ~0x8000
#endif

#ifndef tdf3

/* from trans386 */

#define set_callee(id)  setname(son(id), formal_callee_tag)
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

#endif


#endif
