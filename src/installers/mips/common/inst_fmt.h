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
$Date: 1998/01/17 15:56:05 $
$Revision: 1.1.1.1 $
$Log: inst_fmt.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/12  10:59:27  currie
 * gcc pedanttry
 *
 * Revision 1.2  1995/08/16  16:06:48  currie
 * Shortened some .h names
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* inst_fmtdecs.h
    procs for outputting various MIPS instruction formats to external files
    as_file and ba_file
*/

#include "addrtypes.h" 


extern void ls_ins PROTO_S ((char *ins, int reg, baseoff a));
extern void mon_ins PROTO_S ((char *ins, int dest, int src));
extern void rrr_ins PROTO_S ((char *ins, int dest, int src1, int src2));
extern void rri_ins PROTO_S ((char *ins, int dest, int src1, long imm));
extern void uncond_ins PROTO_S ((char *ins, int lab));
extern void condrr_ins PROTO_S ((char *ins, int src1, int src2, int lab));
extern void condri_ins PROTO_S ((char *ins, int src1, long imm, int lab));
extern void condr_ins PROTO_S ((char *ins, int src1, int lab));
extern void cop_ins PROTO_S ((char *ins, int gr, int fr));
extern void lsfp_ins PROTO_S ((char *ins, int reg, baseoff a));
extern void rrfp_ins PROTO_S ((char *ins, int dest, int src));
extern void rrfpcond_ins PROTO_S ((char *ins, int dest, int src));
extern void rrrfp_ins PROTO_S ((char *ins, int dest, int src1, int src2));
extern void ri_ins PROTO_S ((char *ins, int dest, long imm));
extern void br_ins PROTO_S ((char *ins, int dest));
extern void extj_ins PROTO_S ((char *ins, baseoff b));
extern void tround_ins PROTO_S ((char *ins, int dfr, int sfr, int gpr));
extern void multdiv_ins PROTO_S ((char *ins, int r1, int r2));
extern void hilo_ins PROTO_S ((char * ins, int dest));
