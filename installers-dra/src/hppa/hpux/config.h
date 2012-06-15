/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

#include "ossg_api.h"
#include "ossg.h"

#ifndef FS_LITTLE_ENDIAN
#define FS_LITTLE_ENDIAN	0
#endif


#define null			NULL


/* MAIN MACHINE CONFIGURATION */


/* MACHINE IDENTIFIERS */
#define is68000			0
#define is80x86			0
#define ismips			0
#define ispower			0
#define issparc			0
#define isvax			0
#define ishppa                  1
#define isAlpha                 0

/* CONFIGURATION OPTIONS */
#define dont_unpad_apply 	1
#define has_bitfield_ops        0
#define has_byte_ops		0
#define has_byte_regs		0
#define has_neg_shift 		0
#define has_rotate              0
#define has_setcc		0
#define has64bits		0
#define keep_PIC_vars           1
#define no_bitfield_ops 	0
#define only_inline_static 	0
#define only_lengthen_ops	0
#define promote_pars            1
#define regable_union 		0
#define remove_zero_offsets 	0
#define replace_compound 	1
#define shift_is_byte 		0
#define special_fns 		0
#define substitute_complex      1
#define substitute_params 	0
#define use_long_double         1
#define value_of_null		0
#define remove_unused_counters	1
#define remove_unused_index_counters 0
#define good_index_factor(f) 0
#if 0
#define good_pointer_factor(f) ( (f) != 1 && (f) != 2 && (f) != 4 && (f) != 8 )
#else
#define good_pointer_factor(f) 1
#endif

#if use_long_double
#define target_dbl_maxexp 	16384
#else
#define target_dbl_maxexp 	308
#endif


#define DO_INDEXED_LOADS 1
#define USE_BITAD 0
#define HAS_MAGIC


#endif /* CONFIG_INCLUDED */
