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


/* 80x86/c_arith_type.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:51 $
$Revision: 1.1.1.1 $
$Log: c_arith_type.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1996/03/15  10:37:06  pwe
 * correct built-in ~arith_type definition
 *
 * Revision 1.2  1995/01/30  12:55:56  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:08:02  jmf
 * Initial revision
 *
**********************************************************************/



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
 if(b==(t_long|t_unsigned))return b;
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
 switch(a) {
   case (t_char|t_none): return scharsh;
   case (t_char|t_signed): return scharsh;
   case (t_char|t_unsigned): return ucharsh;
   case (t_short|t_signed): return swordsh;
   case (t_short|t_unsigned): return uwordsh;

   case (t_int|t_signed): return slongsh;
   case (t_int|t_unsigned): return ulongsh;
   case (t_long|t_signed): return slongsh;
   case (t_long|t_unsigned): return ulongsh;
   }
   return slongsh;
 }
