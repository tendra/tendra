/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

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

#define target_system "Solaris 10"

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
#define good_index_factor(f)	0
#define good_pointer_factor(f)	((f)!= 1 && (f)!= 2 && (f)!= 4 && (f)!= 8)

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
