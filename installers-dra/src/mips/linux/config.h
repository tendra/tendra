/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */




#ifndef config_key
#define config_key 1

#include <reader/ossg_api.h>
#include <reader/ossg.h>

#ifndef FS_LITTLE_ENDIAN
#define FS_LITTLE_ENDIAN 0
#endif

#define has64bits 0

#define has_setcc 0
#define only_lengthen_ops 1
#define has_neg_shift 0
#define substitute_params 1

#define remove_zero_offsets 1
#define replace_compound 1
#define no_bitfield_ops 0
#define dont_unpad_apply 0

#define target_dbl_maxexp 308

#define remove_unused_counters 1
#define remove_unused_index_counters 1
#define good_index_factor(f) 0
#define good_pointer_factor(f) 1

#define div0_implemented 1

#define keep_PIC_vars 1

#define substitute_complex 1

#define temp_mips 0
#define value_of_null 0

#define has_rotate 0

#define promote_pars 1

#endif
