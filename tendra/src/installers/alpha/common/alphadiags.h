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


/*   alphadgdecs.h   - definitions in alphadgdecs.c  */

/*
$Log: alphadiags.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:58  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/05/23  10:52:12  john
 * Minor cosmetic change
 *
 * Revision 1.1.1.1  1995/03/23  10:39:31  john
 * Entered into CVS
 *
 * Revision 1.3  1995/01/31  14:23:47  john
 * Changed some declaration to use int rather than long
 *
 * Revision 1.2  1995/01/26  13:36:00  john
 * Changed prototypes
 *
*/

#include "exptypes.h"
#include "diagtypes.h"
extern int nofds;
extern int *file_dnos;		/* dense nos for files */
extern void collect_files PROTO_S ((filename f));
extern current_file;		/* dense no of current source file */
extern void stab_file PROTO_S ((int i));	/* symtab entry for file 
					   source file i */
extern void stabd PROTO_S ((int findex, int lno));/*.. entry for linenos */
extern void diagbr_open PROTO_S ((int findex));/* .. entry for open scope */
extern void diagbr_close PROTO_S ((int findex));/* entry for close scope */
extern void stab_local PROTO_S((char *nm,diag_type dt,exp id,int disp,
			      int findex));
 /* entry for local */
extern void stab_types PROTO_S ((void)); /* aux entries for types */
extern int currentlno;
extern int find_file PROTO_S ((filename));

extern int find_aux PROTO_S ((diag_type s /* struct or union shape */ ));
extern void symnosforfiles PROTO_S ((void));
