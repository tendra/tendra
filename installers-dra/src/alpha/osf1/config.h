/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef config_key
#define config_key 1

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
