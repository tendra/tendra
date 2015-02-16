/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

	/* Sparc specific declarations are listed here.
	   Declarations visible to common/dwarf2 are in dw2_config.h */

#ifndef dw2_extra_key
#define dw2_extra_key 1

extern void dw2_start_fde(exp e);
extern void dw2_fde_save(void);
extern void dw2_fde_restore(void);
extern void dw2_complete_fde(void);


extern void dw_init_regassn(int reg);
extern void dw_used_regassn(int reg);
extern void dw_close_regassn(int reg);


#endif
