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


/* 	$Id: out_ba.h,v 1.1.1.1 1998/01/17 15:56:00 release Exp $	 */

/* 
   out_badecs.h 
*/

/*
$Log: out_ba.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:00  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/05/23  13:24:09  john
 * Change for 64 bit support
 *
 * Revision 1.2  1995/04/10  14:13:34  john
 * Minor changes
 *
 * Revision 1.1.1.1  1995/03/23  10:39:33  john
 * Entered into CVS
 *
 * Revision 1.2  1995/03/23  10:10:12  john
 * Changed prototypes (part of change to support scheduler).
 *
*/

#include "ibinasm.h"
#include "cross.h"

extern char *out_common PROTO_S ((asmsym,unsigned));
extern char *out_ent PROTO_S ((asmsym,unsigned,unsigned));
extern char *out_frame PROTO_S ((asmsym,unsigned,asmint,asmreg,asmreg));
extern char *out_mask PROTO_S ((asmsym,unsigned,unsigned,asmint));
extern char *out_verstamp PROTO_S ((int,int));
extern void out_loc PROTO_S ((int,unsigned));
extern char *out_chars PROTO_S ((asmsym,unsigned,asmint,unsigned short));
extern char *out_option PROTO_S ((int,int));
extern char *out_value PROTO_S ((asmsym,unsigned,INT64,unsigned));
extern void out_alias PROTO_S ((asmsym,unsigned,asmreg,asmreg));
extern char *out_rinst PROTO_S ((asmsym,int,asmreg,asmreg,asmformat,asmreg));
extern char *out_linst PROTO_S ((asmsym,int,asmreg,asmreg,asmformat,asmint));
extern char *out_data PROTO_S ((char *,int));
extern char *out_iinst PROTO_S((asmsym,int,asmreg,asmreg,asmformat,
			      unsigned int, int));
extern char *out_biinst PROTO_S((asmsym,int,asmreg,asmreg,asmformat,
			      unsigned int, INT64));
extern  FILE * ba_file;


