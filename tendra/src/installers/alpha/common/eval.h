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
   evaldecs.h
*/

/*
$Log: eval.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:58  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/08/21  08:44:22  john
 * Changed include files
 *
 * Revision 1.2  1995/05/16  10:47:43  john
 * Cosmetic changes
 *
 * Revision 1.1.1.1  1995/03/23  10:39:06  john
 * Entered into CVS
 *
 * Revision 1.2  1995/01/26  13:39:46  john
 * Minor changes to prototypes
 *
*/

#include "addresstypes.h"
#include "flpttypes.h"
#include "common_types.h"
#include "cross.h"

extern int  next_data_lab PROTO_S ((void));

extern int  next_dlab_sym PROTO_S ((void));
extern int data_lab;

extern mm maxmin PROTO_S ((shape));


extern instore evaluated PROTO_S ((exp,int));

extern void  outfloat PROTO_S ((exp,int,ash));


extern char fltrepr[];



