/*
    		 Crown Copyright (c) 1997
    
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
$Log: proctypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:12:23  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:27:53  16:27:53  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:18:44  11:18:44  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:28:34  15:28:34  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:42:26  13:42:26  wfs (William Simmonds)
 * Initial revision
 * 
*/


#ifndef PROCTYPES_INCLUDED
#define PROCTYPES_INCLUDED

#include "exptypes.h"
#include "common_types.h"


typedef struct {
      int fixneeds  ;
      int floatneeds ;
      prop propsneeds ;
      int maxargs ;
      int builtin;
      long sz;
} needs ;

/*
    MACROS FOR MANIPULATING PROPERTIES OF NEEDS
*/

#define pnset( x, m )	( x ).propsneeds = ( prop ) ( ( x ).propsneeds | ( m ) )
#define pnclr( x, m )	( x ).propsneeds = ( prop ) ( ( x ).propsneeds & ~( m ) )
#define pntst( x, m )	( ( x ).propsneeds & ( m ) )


#define wfixno		25
#define wfloatno	16

typedef struct {
    float fix [ wfixno ] ;
    float floating [ wfloatno ] ;
} weights ;


typedef struct {
    int regadd ;
    long stackadd ;
    long forweights ;
} parpair ;


typedef struct {
    long fixdump ;
    long fltdump ;
    long stack ;
} spacereq ;


typedef struct {
    needs needsproc ;
    spacereq spacereqproc ;
    long locals_space;
    long locals_offset;
    long callees_offset;
    long params_offset;
    int frame_sz;
    int max_args;
    int fixdump;
    int floatdump;
    int dumpstart;
    int fldumpstart;
    int callee_sz;
    exp nameproc ;
    int tlrecstart ;
    int expproc ;
    bool Has_ll;
    bool Has_checkalloc;
    bool has_vcallees;
    bool has_no_vcallers;
    bool leaf;
    bool Has_alloca;  
} procrec ;


typedef struct {
    weights wp_weights ;
    long fix_break ;
    long float_break ;
} wp ;


typedef struct {
    long fixed ;
    long flt ;
} space  ;


#endif /* PROCTYPES_INCLUDED */










