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
$Author: pwe $
$Date: 1998/03/15 16:00:33 $
$Revision: 1.3 $
$Log: dw2_basic.h,v $
 * Revision 1.3  1998/03/15  16:00:33  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.2  1998/03/11  11:03:38  pwe
 * DWARF optimisation info
 *
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.8  1997/12/04  19:41:14  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.7  1997/11/06  09:22:00  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.6  1997/10/10  18:18:23  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.5  1997/08/23  13:36:34  pwe
 * initial ANDF-DE
 *
 * Revision 1.4  1997/04/17  11:50:14  pwe
 * Sparc and 80x86 support
 *
 * Revision 1.3  1997/04/01  17:19:35  pwe
 * diagnose pl_tests and locate -> platform specific
 *
 * Revision 1.2  1997/03/24  11:10:20  pwe
 * struct bitfields
 *
 * Revision 1.1  1997/03/20  16:09:02  pwe
 * first version
 *
**********************************************************************/

#ifndef dw2_basic_key
#define dw2_basic_key

extern void uleb128 PROTO_S ((unsigned long value));
extern void sleb128 PROTO_S ((long value));
extern int uleb128_length PROTO_S ((unsigned long value));
extern int sleb128_length PROTO_S ((long value));
extern void set_attribute PROTO_S ((int name, int form));
extern void do_compunit_header PROTO_S ((void));
extern void close_compunit_info PROTO_S ((void));
extern void dw_sibling_end PROTO_S ((void));
extern void dw_at_address PROTO_S ((long lab));
extern void dw_at_ext_lab PROTO_S ((ext_lab lab));
extern void dw_set_ext_lab PROTO_S ((ext_lab lab));
extern void dw_at_ext_address PROTO_S ((dg_tag tg));
extern void set_ext_address PROTO_S ((dg_tag tg));
extern void dw_at_abstract_lab PROTO_S ((dg_tag tg));
extern void set_abstract_lab PROTO_S ((dg_tag tg));
extern void dw_at_string PROTO_S ((char* s));
extern void dw_at_form PROTO_S ((int f));
extern void dw_at_data PROTO_S ((int n, long d));
extern void dw_at_udata PROTO_S ((unsigned long n));
extern void dw_at_sdata PROTO_S ((long n));
extern void dw_at_flag PROTO_S ((int x));
extern void dw_at_decl PROTO_S ((short_sourcepos p));
extern void dw_no_locate PROTO_S ((void));
extern void dw_locate_offset PROTO_S ((int n));
extern void dw_locate_reloffset PROTO_S ((exp e));
extern void dw_at_distance PROTO_S ((long lo, long hi));
extern long set_dw_text_label PROTO_S ((void));
extern void out_text_label PROTO_S ((long n));
extern void out_loc_range PROTO_S ((long start, long end, int inclusive));

extern long last_text_label;


#endif
