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
$Date: 1998/03/15 16:00:17 $
$Revision: 1.1 $
$Log: dw2_extra.h,v $
 * Revision 1.1  1998/03/15  16:00:17  pwe
 * regtrack dwarf dagnostics added
 *
**********************************************************************/

	/* Sparc specific declarations are listed here.
	   Declarations visible to common/dwarf2 are in dw2_config.h */


#ifndef dw2_extra_key
#define dw2_extra_key 1

#ifdef NEWDWARF

extern long dw2_start_fde PROTO_S ((long proc_start, long fblab));
extern void dw2_fde_entry PROTO_S ((long dwl0, long dwl1, long dwl2, 
		long dwl3, long dwl4, long dwl8, int space));
extern void dw2_untidy_return PROTO_S ((void));
extern long dw2_prep_fde_restore_args PROTO_S ((int untidy));
extern void dw2_fde_restore_args PROTO_S ((long dwl0, long dwl1, long dwl2, 
		long dwl3, long dwl4, int space));
extern void dw2_after_fde_exit PROTO_S ((long here));
extern void dw2_track_push PROTO_S ((void));
extern void dw2_track_pop PROTO_S ((void));
extern void dw2_track_sp PROTO_S ((void));
extern void dw2_complete_fde PROTO_S ((void));

extern void dw2_start_extra_bit PROTO_S ((exp body));
extern void dw2_end_extra_bit PROTO_S ((exp body));


extern int dw_ignore_used_regassn;
extern void dw_init_regassn PROTO_S ((int reg, int x));
extern void dw_used_regassn PROTO_S ((int reg, int x));
extern void dw_close_regassn PROTO_S ((int reg, int x));


#endif
#endif
