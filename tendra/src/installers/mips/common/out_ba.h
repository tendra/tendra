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
$Date: 1998/01/17 15:56:06 $
$Revision: 1.1.1.1 $
$Log: out_ba.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* out_badecs.h */
#include "ibinasm.h"
extern void out_common PROTO_S ((asmsym symno, unsigned asmtype));
extern void out_ent PROTO_S ((asmsym symno, unsigned asmtype, unsigned lexlev));
extern void out_frame PROTO_S((asmsym symno, unsigned asmtype, asmint frameoffset,
          asmreg framereg, asmreg pcreg));
extern void out_mask PROTO_S((asmsym symno, unsigned asmtype, unsigned regmask,
          asmint regoffsset));
extern void out_verstamp PROTO_S((int majornumber, int minornumber));
extern void out_loc PROTO_S ((unsigned filenumber, unsigned linenumber));
extern void out_chars PROTO_S((asmsym symno, unsigned asmtype, asmint expression,
          unsigned short repeat));
extern void out_option PROTO_S ((int x, int y));
extern void out_value PROTO_S((asmsym symno, unsigned asmtype, asmint expression,
          unsigned long repeat));
extern void out_alias PROTO_S((asmsym symno, unsigned asmtype, asmreg basereg1,
          asmreg basereg2));
extern void out_rinst PROTO_S((asmsym symno, unsigned char opcode, asmreg reg1, asmreg reg2,
          asmformat form, asmreg reg3));
extern void out_iinst PROTO_S((asmsym symno, unsigned char opcode, asmreg reg1, asmreg reg2,
          asmformat form, asmint immediate));

extern void out_data PROTO_S ((char *data, int size));

extern void out_cpload PROTO_S ((asmsym symno, asmreg reg));

extern  FILE * ba_file;


