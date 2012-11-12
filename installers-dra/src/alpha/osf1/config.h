/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef config_key
#define config_key 1

#ifndef FS_64_BIT
#define FS_64_BIT		1
#endif

#define only_lengthen_ops 1

#define replace_compound 1
#define no_bitfield_ops 0
#define dont_unpad_apply 0

#define target_dbl_maxexp 308

#define has64bits 1

#define temp_mips 0

/* settings for foralls optimisations */
#define remove_unused_counters 1
#define remove_unused_index_counters 0
#define good_index_factor(f) 0
#define good_pointer_factor(f) 1


#define substitute_complex 1

#define value_of_null 0

#ifndef DO_SCHEDULE
#define DO_SCHEDULE 0
#endif

#define diagnose_registers 1

#endif
