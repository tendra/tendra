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


/* sco/diag_config.h */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:51 $
$Revision: 1.1.1.1 $
$Log: diag_config.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/10/23  17:34:40  pwe
 * dynamic initialisation PIC, and sco diags
 *
 * Revision 1.3  1995/01/30  12:57:19  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.2  1994/07/13  07:57:06  jmf
 * Added Log
 *
**********************************************************************/

#ifndef diag_config_key
#define diag_config_key



typedef diag_descriptor diag_global;		/* used in installtypes.h */
typedef int OUTPUT_REC;
#define NEW_DIAG_GLOBAL(x) x

extern void OUTPUT_GLOBALS_TAB PROTO_S ((void));
extern void OUTPUT_DIAG_TAGS PROTO_S ((void));
extern void INSPECT_FILENAME PROTO_S ((filename fn));

#endif
