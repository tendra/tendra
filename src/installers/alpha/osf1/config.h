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


/* 	$Id: config.h,v 1.2 1998/03/16 11:25:30 release Exp $	 */
/*
$Log: config.h,v $
 * Revision 1.2  1998/03/16  11:25:30  release
 * Modifications prior to version 4.1.2.
 *
 * Revision 1.1.1.1  1998/01/17  15:56:01  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1995/09/20  10:46:48  john
 * Changes isAlpha macro
 *
 * Revision 1.6  1995/09/13  11:03:44  john
 * Added HAS_MAGIC flag
 *
 * Revision 1.5  1995/07/27  09:34:50  john
 * Set diagnose_registers macro
 *
 * Revision 1.4  1995/06/28  10:23:17  john
 * New option: has_rotate
 *
 * Revision 1.3  1995/06/13  13:59:54  john
 * Changed default value of DO_SCHEDULE
 *
 * Revision 1.2  1995/05/23  10:54:18  john
 * New configuration flag : has_bitfield_ops
 *
 * Revision 1.1.1.1  1995/03/23  10:39:04  john
 * Entered into CVS
 *
 * Revision 1.18  1995/03/23  10:02:34  john
 * Added DO_SCHEDULE macro
 *
 * Revision 1.17  1995/01/31  14:24:50  john
 * Moved some definitions into TenDRA.h
 *
 * Revision 1.16  1995/01/10  09:39:16  john
 * Added definition of value_of_null
 *
*/
#ifndef config_key
#define config_key 1

#include "ossg_api.h"
#include "ossg.h"

#ifndef FS_64_BIT
#define FS_64_BIT		1
#endif

#ifndef FS_LITTLE_ENDIAN
#define FS_LITTLE_ENDIAN	1
#endif

#define isvax 0
#define ismips 0
#define is68000 0
#define is80x86 0
#define ispower 0
#define issparc 0
#define isAlpha 1
#define is80586 0

#define issco 0

#define has_setcc 0
#define little_end 1
#define has_byte_regs 0
#define has_byte_ops 0
#define only_lengthen_ops 1
#define has_neg_shift 0
#define regable_union 0
#define substitute_params 1
#define special_fns 0
#define shift_is_byte 1
#define only_inline_static 0

#define remove_zero_offsets 1
#define replace_compound 1
#define no_bitfield_ops 0
#define dont_unpad_apply 0

#define target_dbl_maxexp 308

#define check_shape 1
#define has64bits 1
#define maxmin_implemented 0

#define temp_mips 0

/* settings for foralls optimisations */
#define remove_unused_counters 1
#define remove_unused_index_counters 0
#define good_index_factor(f) 0
#define good_pointer_factor(f) 1


#define div0_implemented 0

#define condassign_implemented 0

#define substitute_complex 1

#define do_case_transforms 0  /* This does not work on the alpha */
#define jump_table_density 10
#define non_default_entries 0 /* 4 */
#define non_default_destinations 2

#define value_of_null 0

#define has_bitfield_ops 0
#define has_rotate 0

#ifndef DO_SCHEDULE
#define DO_SCHEDULE 0
#endif

#define diagnose_registers 1

#define HAS_MAGIC 1

#endif
