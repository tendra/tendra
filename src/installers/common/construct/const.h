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
$Date: 1998/01/17 15:55:46 $
$Revision: 1.1.1.1 $
$Log: const.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/


/************************************************************************
 *                         constdecs.h
 *  This file declares the routines which detect constant expressions and
 *  extract them from loops.
 *
 *  The type maxconst returns information about the expression under
 *  consideration. The field self is true if the expression as a whole is
 *  constant within the program fragment under consideration. If the
 *  entire expression is not constant (self is false) then the field cont
 *  is a list of the sub-expressions which are constant within the
 *  specified region.
 *
 *  The type maxconst is defined in consttypes.h
 *
 *  The principal procedures declared here are mc_list and repeat_const.
 *  They are decribed in const.c
 *
 ************************************************************************/

#include "consttypes.h"

extern  void repeat_consts PROTO_S ((void));
extern  void return_repeats PROTO_S ((void));
extern  int intnl_to PROTO_S ((exp whole, exp part));
extern  exp get_repeats PROTO_S ((void));
