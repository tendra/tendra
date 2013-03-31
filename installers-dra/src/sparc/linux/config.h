/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

/* Settings for Solaris 2 */
#define SYSV_ABI		1
#define DWARF			0


/* CONFIGURATION OPTIONS */

#define GENCOMPAT		1
#define NEWDIAGS		1
#define NEWDWARF		1


/* foralls config */
#define remove_unused_counters 0
#define remove_unused_index_counters 1

#define good_index_factor(f) 0
#define good_pointer_factor(f) 1

	/* condition for shape to be treated as a struct */
#define sparccpd(s) (name(s) == cpdhd || name(s) == nofhd || \
			name(s) == shcomplexhd || shape_size(s)>64 || \
			name(s) == u64hd || name(s) == s64hd)

#endif /* CONFIG_INCLUDED */



