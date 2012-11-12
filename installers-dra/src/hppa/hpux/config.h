/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

#define null			NULL


/* MAIN MACHINE CONFIGURATION */


/* CONFIGURATION OPTIONS */
#define dont_unpad_apply 	1
#define has64bits		0
#define keep_PIC_vars           1
#define no_bitfield_ops 	0
#define only_lengthen_ops	0
#define promote_pars            1
#define replace_compound 	1
#define substitute_complex      1
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


#endif /* CONFIG_INCLUDED */
