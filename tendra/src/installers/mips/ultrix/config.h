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
$Date: 1998/03/16 11:25:34 $
$Revision: 1.2 $
$Log: config.h,v $
 * Revision 1.2  1998/03/16  11:25:34  release
 * Modifications prior to version 4.1.2.
 *
 * Revision 1.1.1.1  1998/01/17  15:56:04  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/09/20  08:26:49  currie
 * isAlpha
 *
 * Revision 1.3  1995/06/22  09:33:03  currie
 * Added has_rotate
 *
 * Revision 1.2  1995/05/18  16:29:54  currie
 * Introduced has_bitfield_ops
 *
 * Revision 1.1  1995/04/13  09:33:41  currie
 * Initial revision
 *
***********************************************************************/


#ifndef config_key
#define config_key 1

#include "ossg_api.h"
#include "ossg.h"

#ifndef FS_LITTLE_ENDIAN
#define FS_LITTLE_ENDIAN 1
#endif

#define isvax 0
#define ismips 1
#define is68000 0
#define is80x86 0
#define ispower 0
#define issparc 0
#define isirix 0
#define isAlpha 0

#define issco 0
#define has64bits 0

#define has_setcc 0
#define little_end 1
#define has_byte_regs 0
#define has_byte_ops 0
#define only_lengthen_ops 1
#define has_neg_shift 0
#define regable_union 0
#define substitute_params 1
#define special_fns 1
#define shift_is_byte 1
#define only_inline_static 0
#define has_bitfield_ops 0

#define remove_zero_offsets 1
#define replace_compound 1
#define no_bitfield_ops 0
#define dont_unpad_apply 0

#define target_dbl_maxexp 308

#define check_shape 1

#define remove_unused_counters 1
#define remove_unused_index_counters 1
#define good_index_factor(f) 0
#define good_pointer_factor(f) 1

#define div0_implemented 1
#define do_case_transforms 0
/* Parameters for TDF->TDF case_optimisation */

#define jump_table_density 10        /* between 0 and 100 */

/* jump_table density is the percentage of entries which must be filled 
 * in a jump table in order for it to be created
 * So 0 would try to make everything into a jump table whereas 100
 * would mean only full jump tables could be put out
 */

#define non_default_entries 4      /* a positive integer */

/* non_default_entries is the minimum number of non default entries a
 * jump table can contain
 */

#define non_default_destinations 2  /* a positive integer */

/* non_default_destinations is the minimum number of non default destinations
 * a jump table can contain
 */
#define substitute_complex 1
#define temp_mips 0
#define value_of_null 0
#define has_rotate 0

#define HAS_MAGIC

#endif
