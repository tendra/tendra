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


/* 	$Id: operators.h,v 1.1.1.1 1998/01/17 15:56:01 release Exp $	 */



/* 
   operators.h
*/


#include "exptypes.h"
#include "addresstypes.h"
#include "instypes.h"





extern int  comm_op PROTO_S ((exp,space,where,instruction));
extern int  non_comm_op PROTO_S ((exp,space,where,instruction));
extern int  monop PROTO_S ((exp,space,where,instruction));
extern int  fop PROTO_S ((exp,space,where,instruction));
extern int  fmop PROTO_S ((exp,space,where,instruction));
extern void tidyshort PROTO_S ((int,shape));
  
