/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

/* API SPECIFICATION */
#include "ossg_api.h"
#include "ossg.h"

#ifndef FS_LITTLE_ENDIAN
#define FS_LITTLE_ENDIAN	0
#endif

#define null			NULL


#ifdef __GNUC__
#ifdef __sun__
/* SunOS 4.1.3 doesn't have these in stdio.h */
extern int fputs(const char *, FILE*);
extern int fputc(int , FILE*);
extern int fprintf(FILE*,const char*, ...);
extern size_t fread(void*, size_t, size_t, FILE*);
extern int fflush(FILE *);
extern int fclose(FILE *);
extern int fgetc(FILE *);
extern int remove(const char *);
extern void setbuf(FILE *, char *);
#endif
#endif


/* Settings for SunOS 4 and Solaris 1 */
#define SYSV_ABI		0
#define SYSV_AS			0
#define DWARF			0
#define target_system		"SunOS 4.1.3"
#define ADDUNDERSCORE		1


/* MACHINE IDENTIFIERS */
#define is68000			0
#define is80x86			0
#define ismips			0
#define ispower			0
#define issco			0
#define isAlpha                 0
#define issparc			1
#define isvax			0


/* CONFIGURATION OPTIONS */

#define GENCOMPAT		1


#define check_shape		1  /* interaction with parameter alignments is
				      now allowed for in install_fns */
#define dont_unpad_apply	1
#define has_byte_ops		0
#define has_byte_regs		0
#define has_neg_shift		0
#define has_setcc		0
#define has64bits		0
#define keep_PIC_vars		1
#define little_end		0
#define no_bitfield_ops		0
#define only_inline_static	0
#define only_lengthen_ops	0
#define regable_union		1
#define remove_zero_offsets	0
#define replace_compound	0
#define shift_is_byte		0
#define special_fns		0
#define substitute_params	0
#define substitute_complex	1
#define use_link_stuff		SYSV_AS
#define div0_implemented 	1

/* foralls config */
#define remove_unused_counters 0
#define remove_unused_index_counters 1

#define good_index_factor(f)0
#define good_pointer_factor(f)1

#if SYSV_ABI
#define target_dbl_maxexp	16384
#define use_long_double		1
#else
#define target_dbl_maxexp	308
#define use_long_double		0
#endif

#define do_case_transforms 0
#define jump_table_density 10
#define non_default_entries 4
#define non_default_destinations 2

#define value_of_null 0

#define has_bitfield_ops 0

#define has_rotate 0

/* This shouldn't really be solaris specific.  It depends on whether or not
   the processor correctly implements the sdivcc and udivcc instructions.
   These are part of the SPARC v8 architecture but their implementation
   (via software) on some implementations does not meet the specification
   with respect to overflow detection.
   */
#define DIV_SETS_CC 0

#define diagnose_registers 1

#define HAS_MAGIC 1

#define promote_pars 1

	/* condition for shape to be treated as a struct */
#define sparccpd(s)(name(s) == cpdhd || name(s) == nofhd || \
			name(s) == shcomplexhd || shape_size(s) >64 || \
			name(s) == u64hd || name(s) == s64hd)

#endif /* CONFIG_INCLUDED */

