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
$Log: diaginfo.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1997/08/23  13:27:14  pwe
 * initial ANDF-DE
 *
 * Revision 1.4  1997/03/20  17:12:33  currie
 * small blunder
 *
Revision 1.3  1997/03/20 17:04:53  currie
Dwarf2 diags

Revision 1.2  1997/02/18 12:55:52  currie
NEW DIAG STRUCTURE

 * Revision 1.1  1995/04/06  10:42:55  currie
 * Initial revision
 *
***********************************************************************/

#ifndef NEWDIAGS

#ifndef diaginfo_key
#define diaginfo_key 1



typedef struct diag_info_t diag_info; /* let's break a type cycle */

#include "diagtypes1.h"	/* gets diag_descriptor */

#include "diag_config.h"

#else				/* been included at least once */

#ifdef diagtypes_key

#ifndef diaginfo_done_phase2
#define diaginfo_done_phase2
				/* phase 2  */
typedef enum
{
  DIAG_INFO_UNINIT,
  DIAG_INFO_SOURCE,
  DIAG_INFO_ID,
  DIAG_INFO_TYPE,
  DIAG_INFO_TAG
} diag_info_key;

struct diag_info_t 
{
  diag_info_key key;
  union
  {
    struct 
    {
      sourcemark beg;
      sourcemark end;
    } source;
    struct
    {
      tdfstring nme;
      exp access;
      diag_type typ;
    } id_scope;
    struct
    {
      tdfstring nme;
      diag_type typ;
    } type_scope;
    struct
    {
      tdfstring nme;
      diag_type typ;
    } tag_scope;
  } data ;
};

				/* end phase 2 */
#endif				/* done phase 2 */
#endif				/* diagtypes defined */
#endif

#endif
