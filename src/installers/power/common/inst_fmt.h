/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

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
$Date: 1998/02/04 15:48:51 $
$Revision: 1.2 $
$Log: inst_fmt.h,v $
 * Revision 1.2  1998/02/04  15:48:51  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:01:28  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef INST_FMTDECS_H
#define INST_FMTDECS_H

#include "addresstypes.h"	/* for baseoff */
#include "instruct.h"	/* for Instruction_P */


extern char *ext_name PROTO_S ((long));


extern void ld_ro_ins PROTO_S ((Instruction_P,baseoff,int));
extern void ld_rr_ins PROTO_S ((Instruction_P,int,int,int));
extern void ld_ins PROTO_S ((Instruction_P,baseoff,int));

extern void st_ro_ins PROTO_S ((Instruction_P,int,baseoff));
extern void st_rr_ins PROTO_S ((Instruction_P,int,int,int));
extern void st_ins PROTO_S ((Instruction_P,int,baseoff));

extern void rrr_ins PROTO_S ((Instruction_P,int,int,int));
extern void rir_ins PROTO_S ((Instruction_P,int,long,int));
extern void rr_ins PROTO_S ((Instruction_P,int,int));

extern void mov_rr_ins PROTO_S ((int,int));

extern void ld_const_ins PROTO_S ((long,int));

extern void mf_ins PROTO_S ((Instruction_P,int));
extern void mt_ins PROTO_S ((Instruction_P,int));

extern void set_ins PROTO_S ((baseoff,int));
extern void z_ins PROTO_S ((Instruction_P));
extern void unimp_ins PROTO_S ((long));

extern void cmp_rr_ins PROTO_S ((Instruction_P,int,int,int));
extern void cmp_ri_ins PROTO_S ((Instruction_P,int,long,int));

extern void bc_ins PROTO_S ((Instruction_P,int,int ,int));
extern void long_bc_ins PROTO_S ((Instruction_P,int,int ,int));
extern void uncond_ins PROTO_S ((Instruction_P,int));

extern void extj_ins PROTO_S ((Instruction_P,baseoff));
extern void extj_special_ins PROTO_S ((Instruction_P,char *));

extern void ldf_ro_ins PROTO_S ((Instruction_P,baseoff,int));
extern void ldf_rr_ins PROTO_S ((Instruction_P,int,int,int));
extern void ldf_ins PROTO_S ((Instruction_P,baseoff,int));
extern void stf_ro_ins PROTO_S ((Instruction_P,int,baseoff));
extern void stf_rr_ins PROTO_S ((Instruction_P,int,int,int));
extern void stf_ins PROTO_S ((Instruction_P,int,baseoff));

extern void rrf_ins PROTO_S ((Instruction_P,int,int));
extern void rrrf_ins PROTO_S ((Instruction_P,int,int,int));
extern void rrrrf_ins PROTO_S ((Instruction_P,int,int,int,int));
extern void rrf_cmp_ins PROTO_S ((Instruction_P,int,int,int));
extern void fbr_ins PROTO_S ((Instruction_P,int));
extern void rlinm_ins PROTO_S ((Instruction_P,int,int,unsigned int,int));
extern void mfspr_ins PROTO_S ((int,int));
extern void mtfsfi_ins PROTO_S ((int,int));
extern void mtfsb1_ins PROTO_S ((int));
extern void mtfsb0_ins PROTO_S ((int));
extern void mcrfs_ins PROTO_S ((int,int));
extern char *get_instruction PROTO_S ((Instruction_P));
extern void lsi_ins PROTO_S ((int,int,int));
extern void stsi_ins PROTO_S ((int,int,int));
extern void comment PROTO_S ((char *));
#define NIL (char *)0
/* for mtfsfi_ins */

#define BITS_0_to_3     0
#define BITS_4_to_7     1
#define BITS_8_to_11    2
#define BITS_12_to_15   3
#define BITS_16_to_19   4
#define BITS_20_to_23   5
#define BITS_24_to_27   6
#define BITS_28_to_31   7

/* for bc_ins */
#define LIKELY_TO_JUMP   0
#define UNLIKELY_TO_JUMP 1

#endif /* inst_fmtdecs.h */





