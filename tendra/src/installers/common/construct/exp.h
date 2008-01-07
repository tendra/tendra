/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#ifndef expdecs_key
#define expdecs_key 1

#include "exptypes.h"		/* for MD types */

/*
 * Rounding for the given alignment
 */
#define rounder(X, Y)		((((X) + (Y) - 1) / (Y)) * (Y))


/*
 * Basic alignments
 */
#define align32			32UL
#define align16			16UL
#define align8			8UL
#define align1			1UL

#define size64			64L
#define size32			32L
#define size16			16L
#define size8			8L


#ifndef EXP_MD_FIELDS
#define	EXP_MD_FIELDS
#endif

struct exp_t;
struct dec_t;
struct aldef_t;

#ifdef NEWDIAGS
struct dg_info_t;
typedef struct dg_info_t *_diaginfo;
#else
struct diag_info_t;
typedef struct diag_info_t *_diaginfo;
#endif

typedef int prop;

/*
 * expno represents an expression constituent
 */
typedef union expno_u {
	struct exp_t	*e;				/* another expression */
	char			*str;			/* string */
	long			l;				/* signed value */
	unsigned long	ui;				/* unsigned value */
	float			f;				/* floating-point value */
	struct dec_t	*glob;			/* external declaration */
	_diaginfo		d;
	struct aldef_t	*ald;
} expno;

/*
 * exp is a rather central type which represents various all possible
 * TDF constructs.
 */
typedef struct exp_t {
	union expno_u	sonf;			/* first argument or NULL */
	union expno_u	brof;			/* next argument or head exp */
	union expno_u	numf;			/* value of the expression */
	union expno_u	ptf;			/* destination labst or use list for declaration */
	struct exp_t	*shf;			/* shape of the expression */
#ifdef NEWDIAGS
	_diaginfo		diagf;
#endif
	prop			propsf;			/* various data, depends on e_name */
	unsigned char	e_name;			/* expression type */
	unsigned int	e_last:1;		/* is last argument */
	unsigned int	e_park:1;
	EXP_MD_FIELDS					/* machine dependent fields */
} *exp;

/*
 * Various macro to access exp properties
 */
#define	nilexp		NULL			/* deprecated, use NULL instead */

/*
 * main components of exp
 */
#define	son(x)		((x)->sonf.e)
#define	bro(x)		((x)->brof.e)
#define	last(x)		((x)->e_last)
#define	name(x)		((x)->e_name)
#define	sh(x)		((x)->shf)
#define	pt(x)		((x)->ptf.e)
#define	props(x)	((x)->propsf)
#define	no(x)		((x)->numf.l)
#define	parked(x)	((x)->e_park)
#define	dgf(x)		((x)->diagf)

/*
 * alternative components of exp
 */
#define	brog(x)		((x)->brof.glob)
#define	nostr(x)	((x)->numf.str)
#define	ptno(x)		((x)->ptf.l)
#define	sonno(x)	((x)->sonf.l)
#define	fno(x)		((x)->numf.f)
#ifndef NEWDIAGS
#define	dno(x)		((x)->numf.d)
#endif
#define	uno(x)		((x)->numf.ui)

/*
 * Setting macros for components of exp
 */
#define	setbro(x, b)	bro(x) = (b)
#define	setsh(x, b)		sh(x) = (b)
#define	setson(x ,b)	son(x) = (b)
#define	setpt(x, b)		pt(x) = (b)
#define	setlast(x)		last(x) = 1
#define	clearlast(x)	last(x) = 0
#define	setname(x, n)	name(x) = (n)
#define	setfather(f, s)	bro(s) = (f), setlast(s)

/*
 * Components of shapes
*/
#define	shape_size(x)	((x)->numf.l)
#define	shape_align(x)	((unsigned long)(x)->brof.ald->al)
#define	align_of(x)		((x)->brof.ald)
#define	al1(x)			((unsigned long)(x)->sonf.ald->al)
#define	al1_of(x)		((x)->sonf.ald)
#define	al2(x)			((unsigned long)(x)->ptf.ald->al)
#define	al2_of(x)		((x)->ptf.ald)
#define	is_signed(x)	(int)((x)->e_last)



/*
 * Alternative usage of propsf for ntests
 */
#define	test_number(x)			(ntest)((x)->propsf & 0x1f)
#define	settest_number(x, t)	((x)->propsf = (prop)(((x)->propsf & 0xe0) | (int)(t)))

/*
 * Alernative usage of props for rounding modes
 */
#define	round_number(x)			((x)->propsf >> 3)
#define	setround_number(x,r)	((x)->propsf = (prop)(((x)->propsf & 0x7) | (r << 3)))

/*
 * Error handling macros
 */
#define	errhandle(x)			((x)->propsf & 0x7)
#define	optop(x)				((int)errhandle(x) <= 2)
#define	seterrhandle(x,e)		((x)->propsf = (prop)(((x)->propsf & ~0x7) | (e)))

/*
 * Properties of constructions with EXCEPTIONS
 */
#define	setjmp_dest(r,d)		(pt(r) = (d), ++no(son(d)))
#define	isov(x)					(errhandle(x) == 0x4)
#define	istrap(x)				(((x)->propsf & 0x3) == 0x3)


/*
 * Macros for manipulating properties
 */
#define	pset(x, m)			props (x) |= (m)
#define	pclr(x, m)			props (x) &= ~(m)
#define	ptst(x, m)			(props (x) & (m))

/*
 * Pproperties of IDENT_TAG
 */

#define	setvar(x)			pset(x, 0x01)		/* is variable */
#define	clearvar(x)			pclr(x, 0x01)
#define isvar(x)			ptst(x, 0x01)
#define setid(x)			clearvar(x)

#define setvis(x)			pset(x, 0x02)		/* declaration is in memory */
#define clearvis(x)			pclr(x, 0x02)
#define isvis(x)			ptst(x, 0x02)

#define setenvoff(x)		pset(x, 0x04)
#define clearenvoff(x)		pclr(x, 0x04)
#define isenvoff(x)			ptst(x, 0x04)

/* operated only by  contents and assign operations */
#define setcaonly(x)		pset(x, 0x08)		
#define clearcaonly(x)		pclr(x, 0x08)
#define ClearCaonly(e)		clearcaonly(e)
#define iscaonly(x)			ptst(x, 0x08)

#define setusereg(x)		pset(x, 0x10)		/* possibly live in reg */
#define clearusereg(x)		pclr(x, 0x10)
#define isusereg(x)			ptst(x, 0x10)

#define setparam(x)			pset(x, 0x20)
#define clearparam(x)		pclr(x, 0x20)
#define isparam(x)			ptst(x, 0x20)

/* property of declaration to be global, in this case bro(e) will be the index of
 * the declaration */
#define setglob(x)			pset(x, 0x40)
#define clearglob(x)		pclr(x, 0x40)
#define isglob(x)			ptst(x, 0x40)

/* set a flag used during copy : also used for LABST_TAG */
#define setcopy(x)			pset(x, 0x80)
#define clearcopy(x)		pclr(x, 0x80)
#define copying(x)			ptst(x, 0x80)

/* Set in weights and used in coder. At this time no copying */
#define set_intnl_call(x)	pset(x, 0x80)
#define has_intnl_call(x)	ptst(x, 0x80)

#define subvar				0x100

#define setinlined(x)		pset(x, 0x200)
#define clearinlined(x)		pclr(x, 0x200)
#define isinlined(x)		ptst(x, 0x200)

#define	IDENT_TAG_BSPARE1	0x1000

/* parameter used for output */
#if is68000 ||is80x86
/*needs to be in memory */
#define setoutpar(x)		setvis(x)
#define isoutpar(x)			isvis(x)
#define clearoutpar(x)
#else
#define setoutpar(x)		pset(x, 0x8000)
#define clearoutpar(x)		pclr(x, 0x8000)
#define isoutpar(x)			ptst(x, 0x8000)
#endif

/*
 * Properties of PROC_TAG construction
 */
#define set_struct_res(x)			pset (x, 0x01)
#define has_struct_res(x)			ptst (x, 0x01)

#define set_loc_address(x)			pset (x, 0x02)
#define loc_address(x)				ptst (x, 0x02)

#define set_proc_has_setjmp(x)		pset (x, 0x04)
#define proc_has_setjmp(x)			ptst (x, 0x04)

#define set_proc_has_alloca(x)		pset (x, 0x08)
#define proc_has_alloca(x)			ptst (x, 0x08)

#define set_proc_has_lv(x)			pset (x, 0x10)
#define proc_has_lv(x)				ptst (x, 0x10)

#define isrecursive(x)				ptst (x, 0x20)
#define setrecursive(x)				pset (x, 0x20)

#define set_proc_uses_crt_env(x)	pset (x, 0x40)
#define proc_uses_crt_env(x)		ptst (x, 0x40)

#define set_proc_uses_external(x)	pset (x, 0x80)
#define proc_uses_external(x)		ptst (x, 0x80)

/* used for diags, after code production */
#define set_proc_has_fp(x)			pset(x, 0x100)
#define set_proc_has_float(x)		pset(x, 0x100)
#define clear_proc_has_fp(x)		pclr(x, 0x100)
#define proc_has_fp(x)				ptst(x, 0x100)
#define proc_has_float(x)			ptst(x, 0x100)

/*
 * Properties of SOLVE constructs
 */
/*set property of SOLVE_TAG construction */
#define setcrtsolve(x)				props(x) = 1

/* properties of pt of REP_TAG and SOLVE_TAG during copy */
#define set_copying_solve(x)		pset(x, 0x01)
#define clear_copying_solve(x)		pclr(x, 0x01)
#define is_copying_solve(x)			ptst(x, 0x01)

/*
 * Properties of MOVE_SOME construct
 */
#define setnooverlap(x)				pset(x, 0x01)
#define isnooverlap(x)				ptst(x, 0x01)

/*
 * Properties of CONTENTS construct
 */
#define set_propagate(x)			pset(x, 0x01)
#define clear_propagate(x)			pclr(x, 0x01)
#define to_propagate(x)				ptst(x, 0x01)

/*
 * Properties of LABST construct
 */
#define set_loaded_lv(x)			pset(x, 0x10)
#define is_loaded_lv(x)				ptst(x, 0x10)

#define setunroll(x) 				pset(x, 0x04)
#define clearunroll(x)  			pclr(x, 0x04)
#define isunroll(x) 				ptst(x, 0x04)

#define set_dg_labmark(e)			pset(e, 0x800)
#define dg_labmark(e)				ptst(e, 0x800)
#define clear_dg_labmark(e)			pclr(e, 0x800)

/*
 * Properties of NAME construct
 */
#define setlastuse(x)				pset(x, 0x01)
#define islastuse(x)				ptst(x, 0x01)

#define setloadparam(x)				pset(x, 0x02)
#define isloadparam(x)				ptst(x, 0x02)

#define setreallyass(x)				/* not used */
#define isreallyass(x)				(0)

#ifdef NEWDIAGS
#define setisdiaginfo(x)			pset(x, 0x08)
#define isdiaginfo(x)				ptst(x, 0x08)

#define setdiscarded(x)				pset(x, 0x10)
#define isdiscarded(x)				ptst(x, 0x10)
#endif

#define set_vararg(x)				pset(x, 0x20)
#define is_vararg(x)    			ptst(x, 0x20)

/* 
 * Properties of STRING construct
 */
#define string_char_size(x)			props(x)

/*
 * Properties of VAL construct
 */
#define setbigval(x)				pset(x, 0x01)
#define clearbigval(x)				pclr(x, 0x01)
#define isbigval(x)					ptst(x, 0x01)

#define setconstovf(x)				pset(x, 0x02)
#define constovf(x)					ptst(x, 0x02)

/*
 * Properties of REPEAT construct
 */
#define setunrolled(x)				pset(x, 0x01)
#define isunrolled(x)				ptst(x, 0x01)

#define setinnermost(x)				pset(x, 0x10)
#define isinnermost(x)				ptst(x, 0x10)
#define clearinnermost(x)			pclr(x, 0x10)

/*
 * Properties of APPLY construct
 */
#define settoinline(x)				pset(x, 0x01)
#define istoinline(x)				ptst(x, 0x01)

/*
 * Properties of ASM construct
 */
#define asm_string(x)				ptst(x, 0x01)
#define asm_in(x)					ptst(x, 0x02)
#define asm_out(x)					ptst(x, 0x04)
#define asm_ptr(x)					ptst(x, 0x08)
#define asm_var(x)					ptst(x, 0x0c)	/* out | ptr */

/*
 * Properties of ALLOCA construct
 */
#define set_checkalloc(x)			pset(x, 0x01)
#define checkalloc(x)				ptst(x, 0x01)

/*
 * Properties of jump record
 */
#define fstack_pos_of(x)			(x)->propsf

/*
 * Misc unsorted properties
 */
#define set_callee(id)				setname(son(id), formal_callee_tag)
#define set_make_procprops(e, p)	props(e) |= ((p) << 8)
#define proc_has_vcallees(e)		ptst(e, 0x200)

#define set_postlude_has_call(e)	pset(e, 0x01)
#define clear_postlude_has_call(e)	pclr(e, 0x01)
#define postlude_has_call(e)		ptst(e, 0x01)

#define call_has_vcallees(e)		ptst(e, 0x02)
#define proc_has_checkstack(e)		ptst(e, 0x800)
#define proc_has_vcallers(e)		ptst(e, 0x100)
#define proc_has_nolongj(e)			ptst(e, 0x1000)

#define set_proc_needs_envsize(x)	pset(x, 0x8000)
#define proc_needs_envsize(x)		ptst(x, 0x8000)

#if is80x86 || is68000
#define call_is_untidy(e)			ptst(bro(son(e)), 0x04)
#else
#define call_is_untidy(e)			ptst(e, 0x04)
#endif

#define call_has_checkstack(e)		ptst(bro(son(e)), 0x08)

#define IS_A_PROC(e)		(name(e) == proc_tag || name(e) == general_proc_tag)


/* These are used in TDF 3.1 for general_env_offset */
#define frame_al_of_ptr(x)			(x)->sonf.ald->al_frame
#define frame_al1_of_offset(x)		(x)->sonf.ald->al_frame
#define al_includes_vcallees		16
#define al_includes_caller_args		6
#define includes_vcallees(x)		(((x) & 16) != 0)
#define l_or_cees(x)				(((x) & 25) != 0)

#include "expmacs.h"		/* for MD macros */
#include "installtypes.h"

/*
 * MI functions
 */
extern exp getexp(shape s, exp b, int l, exp sn, exp p,
				  prop pr, int n, unsigned char tg);
extern exp getshape(int l, alignment sn, alignment p,
					alignment pr, int n, unsigned char tg);

extern shape lub_shape(shape a, shape b);
extern int next_lab(void);
extern int eq_shape(shape a, shape b);
extern char * intchars(int i);
extern void case_item(exp e);
extern void kill_exp(exp e, exp scope);
extern void altered(exp e, exp scope);
extern void replace(exp old, exp e, exp scope);
extern int internal_to(exp whole, exp part);
extern exp next_exp(void);
extern exp copy(exp e);
extern exp copy_res(exp e, exp var, exp lab);
extern exp copyexp(exp e);
extern exp father(exp e);
extern exp * refto(exp f, exp e);
extern void retcell(exp e);
extern int is_comm(exp e);
extern int crt_labno;

extern exp clean_labelled(exp starter, label_list placelabs_intro);

#endif
