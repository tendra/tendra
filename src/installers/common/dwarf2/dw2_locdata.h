/*
    		 Crown Copyright (c) 1998
    
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
$Date: 1998/03/15 16:00:37 $
$Revision: 1.2 $
$Log: dw2_locdata.h,v $
 * Revision 1.2  1998/03/15  16:00:37  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.1  1998/03/11  11:03:47  pwe
 * DWARF optimisation info
 *
**********************************************************************/

#ifndef dw2_loc_key
#define dw2_loc_key

typedef struct obl
{
  dg_name	obj;
  int		islist;
  struct obl *	next;
} obj_list;

extern obj_list * local_objects;

extern void set_locdata PROTO_S ((obj_list this_obl));
extern void close_locdata PROTO_S ((obj_list this_obl));
extern void set_optim_objects PROTO_S ((dg_info optim, int start));
extern void set_remval_object PROTO_S ((dg_info rmv));
extern void set_obj_rets PROTO_S ((retrec * rec));
extern int decide_ll_type PROTO_S ((exp x));
extern void out_obj_loclist PROTO_S ((long l1, long l2, exp x));
extern void out_obj_extloclist PROTO_S ((long l1, long l2, exp x));
extern void out_obj_shared_set PROTO_S ((dg_name dn));

extern void * dw_new_regshare PROTO_S ((dg_name nm, int reg));
extern void dw_add_regshare PROTO_S ((void * w, dg_name nm, long start, long end));
extern dg_name find_equiv_object PROTO_S ((exp e, int isc));

extern void init_dw_locdata PROTO_S ((void));
extern void complete_dw_locdata PROTO_S ((void));


#endif
