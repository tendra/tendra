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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:05 $
$Revision: 1.1.1.1 $
$Log: exptypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/

#ifndef exptypes_key
#define exptypes_key 1
#include "diaginfo.h"


typedef unsigned short prop;


struct dec_t; 
struct aldef_t;

struct exp_t
  {
    union expno_u {
      struct exp_t * e;
      char * str;
      int l;
      float f;
      struct dec_t * glob;
      diag_info * d;
      struct aldef_t * ald;
      unsigned int ui;
    } brof; 
    union expno_u numf;
    union expno_u ptf;
    union expno_u sonf;
    struct exp_t * shf;
    prop propsf;    
    unsigned char namef;
    unsigned int lastf : 1;
    unsigned int park : 1;
  };

typedef struct exp_t * exp;

typedef union expno_u expno;


#endif
