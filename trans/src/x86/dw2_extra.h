/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
 * Sparc specific declarations are listed here.
 * Declarations visible to common/dwarf2 are in dw2_config.h
 */


#ifndef DW2_EXTRA_H
#define DW2_EXTRA_H

long dw2_start_fde(long proc_start, long fblab);
void dw2_fde_entry (long dwl0, long dwl1, long dwl2, long dwl3, long dwl4, long dwl8, int space);
void dw2_untidy_return(void);
long dw2_prep_fde_restore_args(int untidy);
void dw2_fde_restore_args (long dwl0, long dwl1, long dwl2, long dwl3, long dwl4, int space);
void dw2_after_fde_exit(long here);
void dw2_track_push(void);
void dw2_track_pop(void);
void dw2_track_sp(void);
void dw2_complete_fde(void);

void dw2_start_extra_bit(exp body);
void dw2_end_extra_bit(exp body);


extern int dw_ignore_used_regassn;

void dw_init_regassn(int reg, int x);
void dw_used_regassn(int reg, int x);
void dw_close_regassn(int reg, int x);

#endif /* DW2_EXTRA_H */
