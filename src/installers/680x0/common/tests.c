/*
    		 Crown Copyright (c) 1996

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/
/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/tests.c,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: tests.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.2  1997/11/09 14:15:09  ma
Removed issigned. Use is_signed instead.

Revision 1.1.1.1  1997/10/13 12:42:59  ma
First version.

Revision 1.5  1997/10/13 08:50:11  ma
Made all pl_tests for general proc & exception handling pass.

Revision 1.4  1997/09/25 06:45:35  ma
All general_proc tests passed

Revision 1.3  1997/04/20 11:30:39  ma
Introduced gcproc.c & general_proc.[ch].
Added cases for apply_general_proc next to apply_proc in all files.

Revision 1.2  1997/03/20 12:46:24  ma
Now tag ids are kept in unsigned chars (MAX tag id > 127).

Revision 1.1.1.1  1997/03/14 07:50:18  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:59  john
 *
 * Revision 1.2  1996/07/05  14:26:52  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:17  john
 *
 * Revision 1.3  94/02/21  16:04:20  16:04:20  ra (Robert Andrews)
 * A number of values which were previously bool are now int.
 *
 * Revision 1.2  93/05/24  16:00:03  16:00:03  ra (Robert Andrews)
 * The optimisation which check_anyway is designed to test for has
 * returned.  Some tuning is required.
 *
 * Revision 1.1  93/02/22  17:16:44  17:16:44  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#include "config.h"
#include "common_types.h"
#include "assembler.h"
#include "exp.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "tags.h"
#include "tests.h"
#include "is_worth.h"
#ifndef tdf3
#include "68k_globals.h"
#endif


/*
    CC CONVENTIONS

    HP cc has different conventions to gcc on certain points, most
    noticably on the alignment of bitfields.  Both conventions are
    supported, but the cc conventions are default on the HP.  NeXT
    cc is gcc.
*/

#ifdef hp_cc_conventions
int cc_conventions = 1 ;
#else
int cc_conventions = 0 ;
#endif

bool reused_parameter
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
   bool reused = 0 ;
   exp def, ident_exp ;
   def = son ( e ) ;
   if ( name ( def ) == name_tag ) {
      ident_exp = son ( def ) ;
      if ( ! isvar ( ident_exp ) ) {
         /* This an obtain_tag of a parameter */
         if ( name( son( ident_exp ) ) == formal_callee_tag) {
            reused = cur_proc_use_same_callees ;
         }
         else {
            /* caller parameter */
            reused = cur_proc_has_tail_call ;
         }
      }
   }
   return reused ;
}

/*
    CAN THE VALUE OF AN EXPRESSION BE PUT INTO A REGISTER?

    This routine returns 1 if the expression e can be put into a register.
    It has to have its visible flag false, and to be of a suitable shape.
*/

bool regable
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
    shape sha ;
    char n ;
    long sz ;

    if ( isvis ( e ) ) return ( 0 ) ;

    sha = sh ( son ( e ) ) ;
    n = name ( sha ) ;
    if ( n == realhd || n == doublehd ) return ( 1 ) ;

    sz = shape_size ( sha ) ;

    return ( n != cpdhd && n != nofhd && sz <= 32 ) ;
}


/*
    DOES AN EXP HAVE NO SIDE EFFECTS?

    This routine returns 1 if e has no side effects.
*/

bool no_side
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
    int n = name ( e ) ;
    if ( n == ident_tag ) {
	return ( no_side ( son ( e ) ) && (no_side ( bro ( son ( e ) ) ) ) ) ;
    }
    return ( is_a ( n ) || n == test_tag ||
	     n == ass_tag || n == testbit_tag ) ;
}

    char n ;

/*
    IS AN EXP A PUSHABLE PROCEDURE ARGUMENT?

    Can the expression e be pushed directly onto the stack when it is
    the parameter of a procedure?
*/

bool push_arg
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
    unsigned char n = name ( e ) ;

    if ( is_a ( n ) ) return ( 1 ) ;
    if ( n == apply_tag || n == apply_general_tag ) return ( reg_result ( sh ( e ) ) ) ;
    if ( n == ident_tag ) {
	return ( push_arg ( son ( e ) ) && push_arg ( bro ( son ( e ) ) ) ) ;
    }
    return ( 0 ) ;
}


#if 0

/*
    IS A UNION ACTUALLY POINTER VOID?

    No longer used.
*/


#ifndef PTR_VOID_MIN
#define PTR_VOID_MIN	10
#endif

bool is_ptr_void
    PROTO_N ( ( sha ) )
    PROTO_T ( shape sha )
{
    bool go ;
    int ptrs = 0 ;
    exp t = son ( sha ) ;
    if ( t == nilexp ) return ( 0 ) ;
    do {
	go = ( last ( t ) ? 0 : 1 ) ;
	if ( name ( sh ( t ) ) != ptrhd ) return ( 0 ) ;
	ptrs++ ;
	t = bro ( t ) ;
    } while ( go ) ;
    if ( ptrs < PTR_VOID_MIN ) return ( 0 ) ;
#ifdef PTR_VOID_MAX
    if ( ptrs > PTR_VOID_MAX ) return ( 0 ) ;
#endif
    return ( 1 ) ;
}

#endif


/*
    IS A SHAPE COMPOUND?

    This routine is designed to test whether a given shape is compound,
    and thus likely to cause problems when it is the parameter of a
    procedure.
*/

bool cpd_param
    PROTO_N ( ( sha ) )
    PROTO_T ( shape sha )
{
    char n = name ( sha ) ;
    if ( !cc_conventions || n == bitfhd ) {
	long sz = shape_size ( sha ) ;
	if ( sz <= 32 ) return ( 0 ) ;
    }
    return ( n == cpdhd || n == nofhd || n == bitfhd

            || n == s64hd || n == u64hd

            ) ;
}


/*
    DOES A PROCEDURE RETURN A RESULT OF A GIVEN SHAPE IN A REGISTER?

    cc has two ways of getting results from procedures.  Firstly in the
    register D0 (or D0 and D1 in certain cases) and secondly in a section
    of memory the address of which is passed in at the start of the
    procedure in the A1 register and returned at the end in the D0
    register.  This routine works out whether or not a procedure
    delivering a result of shape sha will use the first method.
*/


int reg_result
    PROTO_N ( ( sha ) )
    PROTO_T ( shape sha )
{
    char n = name ( sha ) ;
    if ( cc_conventions ) {
	/* HP cc doesn't return any tuples, unions etc in a register */
	return ( n != cpdhd && n != nofhd ) ;
    } else {
	/* Return anything of size <= 32 or 64 in a register */
	long sz = shape_size ( sha ) ;
	return ( sz <= 32 || sz == 64 ) ;
    }
}


/*
    IS A SHAPE OF VARIABLE SIZE?

    This routine returns 1 if sha involves an array.
*/

bool varsize
    PROTO_N ( ( sha ) )
    PROTO_T ( shape sha )
{
    return ( name ( sha ) == nofhd ? 1 : 0 ) ;
}

#if 0
Use is_signed macro instead

/*
    IS A SHAPE SIGNED?

    This routine returns 1 if the integer variety shape sha is signed
    and 0 otherwise.
*/

bool issigned
    PROTO_N ( ( sha ) )
    PROTO_T ( shape sha )
{
    char n = name ( sha ) ;
    if ( n == ucharhd || n == uwordhd || n == ulonghd ) return ( 0 ) ;
    return ( 1 ) ;
}
#endif

/*
    CHECK ON DECLARATION FOR PARAMETER SUBSTITUTION

    This routine checks if the declaration e should be substituted
    for all its uses or not.
*/

int do_sub_params = 1 ;

int check_anyway
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
#ifndef tdf3
   return 0 ;
#else
    if ( do_sub_params ) {
	setmarked ( e ) ;
	if ( no ( e ) > 2 ) return ( 1 ) ;
    }
    return ( 0 ) ;
#endif
}


/*
    IS IT WORTH EXTRACTING A CONSTANT?
*/

int is_worth
    PROTO_N ( ( c ) )
    PROTO_T ( exp c )
{
  unsigned char cnam = name ( c ) ;
  return ( ( !is_o ( cnam ) && cnam != clear_tag ) ||
      /* ignore simple things unless ... */
      ( cnam == cont_tag && name ( son ( c ) ) == cont_tag &&
	name ( son ( son ( c ) ) )  == name_tag ) ||
      ( cnam == name_tag && isparam ( son ( c ) ) && !isvar ( son ( c ) ) &&
	shape_size ( sh ( c ) ) <= 32 && name ( sh ( c ) ) != shrealhd ) ) ;
}
