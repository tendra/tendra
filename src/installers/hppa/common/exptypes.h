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
$Log: exptypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:11:13  wfs
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
 * Revision 3.3  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.3  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:26:10  16:26:10  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:16:56  11:16:56  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:25:46  15:25:46  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:37:47  13:37:47  wfs (William Simmonds)
 * Initial revision
 * 
*/


#ifndef EXPTYPES_INCLUDED
#define EXPTYPES_INCLUDED

#include "diaginfo.h"
struct dec_t ;


/*
    TYPE REPRESENTING EXPRESSION PROPERTIES
*/

typedef unsigned short prop ;


/*
    UNION REPRESENTING AN EXPRESSION CONSTITUENT
*/

typedef union {
    struct exp_t *e ;
    char *str ;
    int l ;
    unsigned int ui ;
    float f ;
    struct dec_t *glob ;
    diag_info *d ;
    struct aldef_t *ald ;
} expno ;


/*
    TYPE REPRESENTING AN EXPRESSION
*/

struct exp_t {
    expno brof ;
    expno numf ;
    expno ptf ;
    expno sonf ;
    struct exp_t *shf ;
    prop propsf ;
    unsigned char namef ;
    unsigned int lastf : 1 ;
    unsigned int park : 1 ;
    int commuted;
} ;

typedef struct exp_t *exp ;

struct labexp_t {
    exp e;
    int lab;
    struct labexp_t *next;
}  ;

typedef struct labexp_t *labexp;



#endif /* EXPTYPES_INCLUDED */














