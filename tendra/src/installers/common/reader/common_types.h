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
$Date: 1998/01/17 15:55:45 $
$Revision: 1.1.1.1 $
$Log: common_types.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1998/01/11  18:43:35  pwe
 * consistent new/old diags
 *
 * Revision 1.2  1997/08/23  13:30:13  pwe
 * no invert order, and initial ANDF-DE
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
***********************************************************************/
#ifndef common_types_key
#define common_types_key 1



/* a collection of all the type defining header files */

#include "codetypes.h"

#include "dg_first.h"

#include "diaginfo.h"
#include "exptypes.h"
#include "installtypes.h"
#include "dg_types.h"		/* NEW DIAGS */
#include "diagtypes.h"		/* OLD DIAGS */
#include "toktypes.h"
#include "localtypes.h"
#include "li_types.h"

#include "diag_config.h"

#endif
