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


/* sol86/config.h */

/**********************************************************************
$Author: release $
$Date: 1998/03/16 11:25:27 $
$Revision: 1.2 $
$Log: config.h,v $
 * Revision 1.2  1998/03/16  11:25:27  release
 * Modifications prior to version 4.1.2.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.25  1997/10/10  18:25:59  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.24  1997/04/02  10:33:37  pwe
 * diagnose pl_tests
 *
 * Revision 1.23  1997/03/20  16:24:30  pwe
 * dwarf2
 *
 * Revision 1.22  1996/05/20  14:31:07  pwe
 * improved 64-bit handling
 *
 * Revision 1.21  1996/02/20  14:45:38  pwe
 * linux/elf return struct
 *
 * Revision 1.20  1996/02/08  13:45:44  pwe
 * Linux elf v aout option
 *
 * Revision 1.19  1996/01/04  09:54:41  pwe
 * solaris remove no_trap_on_nil_contents
 *
 * Revision 1.18  1995/12/18  16:18:29  pwe
 * solaris traps on nil OK
 *
 * Revision 1.17  1995/12/01  11:54:27  pwe
 * solaris proc equality
 *
 * Revision 1.16  1995/10/09  15:14:43  pwe
 * dynamic initialisation etc
 *
 * Revision 1.15  1995/09/29  16:18:20  pwe
 * gcc_compatible default on Linux
 *
 * Revision 1.14  1995/09/20  12:00:44  pwe
 * svr4 and solaris initial_value, and solaris 64 bit correction
 *
 * Revision 1.13  1995/09/19  15:43:15  pwe
 * round, fp overflow etc
 *
 * Revision 1.12  1995/09/05  16:25:36  pwe
 * specials and exception changes
 *
 * Revision 1.11  1995/08/30  16:07:19  pwe
 * prepare exception trapping
 *
 * Revision 1.10  1995/07/07  15:22:35  pwe
 * prepare for 4.0, and correct PIC switch
 *
 * Revision 1.9  1995/01/30  14:43:55  pwe
 * defined value_of_null for CR95_032
 *
 * Revision 1.8  1995/01/30  12:57:34  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.7  1994/11/08  16:26:19  jmf
 * Added substitute_complex
 *
 * Revision 1.6  1994/10/27  14:12:30  jmf
 * set DWARF 0
 *
 * Revision 1.5  1994/09/27  16:17:36  jmf
 * added case parameters
 *
 * Revision 1.4  1994/09/27  15:19:48  jmf
 * added do_case_transforms
 *
 * Revision 1.3  1994/08/04  13:40:23  jmf
 * Added condassign_implemented
 *
 * Revision 1.2  1994/07/13  07:48:18  jmf
 * Added Log
 *
**********************************************************************/

#ifndef config_key
#define config_key 1


/* API SPECIFICATION */
#include "ossg_api.h"
#include "ossg.h"

#ifndef FS_LITTLE_ENDIAN
#define FS_LITTLE_ENDIAN	1
#endif

#define NEWDIAGS 1
#define NEWDWARF 1
#define SHARED_ABBREV 1
#define has_asm 1
#define as_comment_symbol '/'

#define isvax 0
#define ismips 0
#define is68000 0
#define is80x86 1
#define ispower 0
#define issparc 0
#define istrans 0
#define ishppa 0
#define isAlpha 0

#define issco 0
#define issol86 1
#define islinux 0
#define isfreebsd 0
#define remove_struct_ref 1

#define has_setcc 1
#define little_end 1
#define has_byte_regs 1
#define has_byte_ops 1
#define only_lengthen_ops 1
#define has_neg_shift 0
#define regable_union 0
#define substitute_params 1
#define special_fns 1
#define shift_is_byte 1
#define only_inline_static 0
#define remove_zero_offsets 1
#define replace_compound 1
#define no_bitfield_ops 1
#define dont_unpad_apply 0
#define diagnose_registers 1
#define DWARF 0
#define load_ptr_pars 1
#define use_long_double 1
#define has64bits 1
#define keep_PIC_vars 0
#define maxmin_implemented 1
#define target_dbl_maxexp 4932
#define div0_implemented 1
#define do_case_transforms 1
#define substitute_complex 1
#define has_rotate 1
#define GCC_STRUCTS 0

#define condassign_implemented 0
#define check_shape 1
#define value_of_null 0

#define prefix_length 0	/* strlen(name_prefix) */
#define normal_fpucon 0x37f

#define remove_unused_counters 0
#define remove_unused_index_counters 0
#define good_index_factor(f) 0
#define good_pointer_factor(f) ((f) != 1 && (f) != 2 && (f) != 4 && (f) != 8)

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


#define temp_mips 0

#endif
