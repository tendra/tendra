/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONFIG_H
#define CONFIG_H		1

#define	hasproto		1


/* define compilation options (bools) */

					/* Meaning when option set (1) */
					/* =========================== */

#define	target_dbl_maxexp	308	/* Maximum exp for floating_variety */

/* foralls config */
#define remove_unused_counters  0
#define remove_unused_index_counters 1

#define good_index_factor(f)    1
#define good_pointer_factor(f)  0

#define POWERPC_CODE            1
#define RS6000_CODE             2
#define COMMON_CODE             0
extern int architecture;

#define NO_ERROR_JUMP           0
#define value_of_null           0

#define no_trap_on_nil_contents 1

/* For a general proc 4 parameters are passed in t-regs R_3 -- R_6 */
#define GENERAL_PROC_PARAM_REGS 4
/* for a normal proc by ABI 8 params must be passed in t-regs R_3 -- R_10 */
#define PROC_PARAM_REGS         8


/* In an ideal world REGISTER_SAFETY_NUMBER would be zero */
/* It is a measure of how bad needscan is */
#define REGISTER_SAFETY_NUMBER 2
/* It represents the number of t-regs available if needscan gets it wrong */
#define DO_DYNAMIC_INITIALISATION
#endif
