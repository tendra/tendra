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
$Log: c_arith_type.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:10:57  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.1  1995/10/20  13:41:43  wfs
 * gcc compilation changes.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  09:11:24  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  09:11:24  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:25:46  16:25:46  wfs (William Simmonds)
 * Apr95 tape version.
 *
 * Revision 3.0  95/03/30  11:14:24  11:14:24  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 *
 * Revision 2.0  95/03/15  15:25:13  15:25:13  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 *
 * Revision 1.1  95/01/11  13:20:30  13:20:30  wfs (William Simmonds)
 * Initial revision
 *
*/


/*
^^^	20/08/93  jmf	Altered arith_type to deliver signed int insead of
^^^			unsigned as the last return
*/

#include "config.h"
#include "common_types.h"
#include "install_fns.h"
#include "arith_codes.h"

/* PROCEDURES */

int arith_type
    PROTO_N ( (a,b) )
    PROTO_T ( int a X int b )
{
 if(a==(t_long|t_unsigned))return a;
 if(b==(t_long|t_unsigned))return a;
 if(a==(t_long|t_signed)){
   if(b==(t_int|t_unsigned))return (t_long|t_unsigned);
   return a;
   }
 if(b==(t_long|t_signed)){
   if(a==(t_int|t_unsigned))return (t_long|t_unsigned);
   return b;
   }
 if(a==(t_int|t_unsigned))return a;
 if(b==(t_int|t_unsigned))return b;
 return (t_int|t_signed);
}

int promote
    PROTO_N ( (a) )
    PROTO_T ( int a )
{
 if((a&variety_filter)<t_int)return(t_int|t_signed);
 return a;
}

int sign_promote
    PROTO_N ( (a) )
    PROTO_T ( int a )
{
 if((a&variety_filter)<t_int)a=((a&~variety_filter)|t_int);
 return a;
}

variety convert
    PROTO_N ( (a) )
    PROTO_T ( unsigned a )
{
 switch(a){
   case (t_char|t_none): return scharsh;
   case (t_char|t_signed): return scharsh;
   case (t_char|t_unsigned): return ucharsh;
   case (t_short|t_signed): return swordsh;
   case (t_short|t_unsigned): return uwordsh;

   case (t_int|t_signed): return slongsh;
   case (t_int|t_unsigned): return ulongsh;
   case (t_long|t_signed): return slongsh;
   case (t_long|t_unsigned): default: return ulongsh;
   }
 }
