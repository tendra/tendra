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
$Date: 1998/01/17 15:55:48 $
$Revision: 1.1.1.1 $
$Log: dwarf_out.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/09/28  12:39:52  pwe
 * dwarf.h via import, and type changes for tcc checks
 *
 * Revision 1.1.1.1  1995/08/14  14:30:23  pwe
 * transferred from DJCH
 *
**********************************************************************/

extern void 	dwarf4 PROTO_S ((CONST char *t));
extern void 	dwarf4n PROTO_S ((int x));
extern void 	dwarf2 PROTO_S ((char *c));
extern void 	out_dwarf_thing PROTO_S ((int t,char *cmt));
extern void 	out_dwarfone PROTO_S ((int t,char *cmt));

extern void	enter_dwarf_blk PROTO_S ((int four,int excl, dwarf_label *lb));
extern void	new_dwarf_blk2 PROTO_S ((void));
extern void	new_dwarf_blk4 PROTO_S ((void));
extern void	leave_dwarf_blk1 PROTO_S ((int leave));

extern void out_diagnose_prelude PROTO_S ((void));
extern void out_diagnose_postlude PROTO_S ((void));

extern void enter_dwarf_comp_unit PROTO_S ((void));
extern void leave_dwarf_comp_unit PROTO_S ((void));

extern void 			next_dwarf_lab PROTO_S ((dwarf_label *p));
extern dwarf_type_label * 	next_dwarf_type_lab PROTO_S ((void));
extern char * 			current_label_name PROTO_S ((void));

#include "dwarf_gbl.h"
extern void 	out_dwarf_name_attr PROTO_S ((CONST char * CONST s));
#define 	TDFSTRING2CHAR(x) (&(((x).ints.chars)[0]))
extern void 	out_dwarf_string PROTO_S ((CONST char * CONST s));
extern void 	out_dwarf_sourcemark PROTO_S ((CONST sourcemark * CONST x));

extern void 	out_dwarf_bytesize_attr PROTO_S ((shape t));

#define OUT_DWARF_LOC_BLK(x) 	out_dwarf_thing((int)x, "loc blk")

#if FS_STDC_HASH
#define OUT_DWARF_TAG(x)	out_dwarf_thing(x,#x)
#define OUT_DWARF_TAG_NAMED(x,y)	out_dwarf_thing(x,y)
#define OUT_DWARF_ATTR(x)	out_dwarf_thing(x,#x)
#define dwarf2c(x)		out_dwarf_thing(x,#x)
#define dwarf1(x)		out_dwarfone(x,#x)
#else
#define OUT_DWARF_TAG(x)	out_dwarf_thing(x,"x")
#define OUT_DWARF_TAG_NAMED(x,y)	out_dwarf_thing(x,y)
#define OUT_DWARF_ATTR(x)	out_dwarf_thing(x,"x")
#define dwarf2c(x)		out_dwarf_thing(x,"x")
#define dwarf1(x)		out_dwarfone(x,"x")
#endif

#define enter_dwarf_entry(lb) enter_dwarf_blk(1,0,lb)
#define leave_dwarf_blk() leave_dwarf_blk1(1)
#define leave_dwarf_blk2() leave_dwarf_blk1(0)
#define leave_dwarf_blk4() leave_dwarf_blk1(1)

extern void start_sib_chain1 PROTO_S ((int d_tag, char *tag_name));
extern void cont_sib_chain1 PROTO_S ((int d_tag, char *tag_name));
extern void end_sib_chain PROTO_S ((void));
extern void make_next_new_chain PROTO_S ((void));

#if FS_STDC_HASH
#define start_sib_chain(x) start_sib_chain1(x,#x)
#define cont_sib_chain(x) cont_sib_chain1(x,#x)
#else
#define start_sib_chain(x) start_sib_chain1(x,"x")
#define cont_sib_chain(x) cont_sib_chain1(x,"x")
#endif


extern void out_dwarf_lab PROTO_S ((H_dwarf_lab *l));
#ifdef mips
#define OUT_DWARF_BEG(x) out_dwarf_lab((H_dwarf_lab *)&(((x)->beg)[0]))
#define OUT_DWARF_END(x) out_dwarf_lab((H_dwarf_lab *)&(((x)->end)[0]))
#else
#define OUT_DWARF_BEG(x) out_dwarf_lab(&((x)->beg))
#define OUT_DWARF_END(x) out_dwarf_lab(&((x)->end))
#endif
