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
$Date: 1998/03/16 11:25:35 $
$Revision: 1.4 $
$Log: config.h,v $
 * Revision 1.4  1998/03/16  11:25:35  release
 * Modifications prior to version 4.1.2.
 *
 * Revision 1.3  1998/02/04  15:48:34  release
 * Added OSF copyright message.
 *
 * Revision 1.2  1998/02/04  10:43:51  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:58  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:00:03  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef CONFIG_H
#define CONFIG_H		1

/* The AIX cc compiler is weird */
#ifdef _AIX
#ifndef FS_STDC_HASH
#define FS_STDC_HASH		1
#endif
#endif

#include "ossg_api.h"
#include "ossg.h"

#ifndef FS_LITTLE_ENDIAN
#define FS_LITTLE_ENDIAN	0
#endif

#define	hasproto		1


/* define target */

#define ispower			1
#define isvax			0
#define ismips			0
#define is68000			0
#define is80x86			0
#define issparc			0

#define issco			0


#define istrans			1	/* to get sym_number field of dec_t in
					   "construct/installtypes.h" */


/* define compilation options (bools) */

					/* Meaning when option set (1) */
					/* =========================== */
#define check_shape		1	/* Check shape-correctness */
#define dont_unpad_apply	1	/* Careful with procedure results */
#define has_byte_ops		0	/* Have byte opertions */
#define has_byte_regs		0	/* Have byte registers */
#define has_neg_shift		0	/* Have negative shifts */
#define has_setcc		0	/* Use scc */
#define little_end		0	/* Little endian */
#define load_ptr_pars		0	/* Inline ptr parameters */
#define only_inline_static	0	/* Only inline static procedures */
#define only_lengthen_ops	0	/* Avoid byte registers */
#define remove_zero_offsets	1	/* Remove zero offsets */
#define replace_compound	1	/* Replace make_compound by assigns */
#define shift_is_byte		0	/* Shift count is 8-bit */
#define special_fns		1	/* Look for special functions */
#define substitute_params	1	/* Substitute parameters when inlining */
#define temp_mips		0	/* Need a mips hack */
#define has64bits               0

#define	target_dbl_maxexp	308	/* Maximum exp for floating_variety */

/* foralls config */
#define remove_unused_counters  0
#define remove_unused_index_counters 1

#define good_index_factor(f)    1
#define good_pointer_factor(f)  0

/* case opts config */

#define jump_table_density      60/* between 0 and 100 */
#define min_jump_table_size     10
#define max_jump_table_size     100
#define min_no_of_default_destinations 3
#if 0
#define non_default_entries     4
#define non_default_destinations 3
#endif
#define do_case_transforms      1
/* complex numbers */
#define substitute_complex      1
#define has_bitfield_ops        0
/* div 0 implemented */
#define div0_implemented        1

#define target_system           "RS6000 / POWERPC"

#define POWERPC_CODE            1
#define RS6000_CODE             2
#define COMMON_CODE             0
extern int architecture;

#define NO_ERROR_JUMP           0
#define value_of_null           0
#define has_rotate              0

#define no_trap_on_nil_contents 1

/* For a general proc 4 parameters are passed in t-regs R_3 -- R_6 */
#define GENERAL_PROC_PARAM_REGS 4
/* for a normal proc by ABI 8 params must be passed in t-regs R_3 -- R_10 */
#define PROC_PARAM_REGS         8

#define HAS_MAGIC               1


/* In an ideal world REGISTER_SAFETY_NUMBER would be zero */
/* It is a measure of how bad needscan is */
#define REGISTER_SAFETY_NUMBER 2
/* It represents the number of t-regs available if needscan gets it wrong */
#define promote_pars
#define DO_DYNAMIC_INITIALISATION
#endif
