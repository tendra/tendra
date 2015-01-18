/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef FLAGS_H
#define FLAGS_H

#include "table.h"
#include "list.h"

/*
 * PROCEDURE DECLARATIONS
 *
 * These routines are concerned with initialising and updating the values of
 * the various compilation options.
*/

extern void initialise_options(void);
extern void update_options(void);
extern void set_stage(enum filetype, int);


/*
 * STRING VARIABLES
 *
 * These variables give various compilation constants.
 */

extern const char *api_info;
extern const char *api_output;
extern const char *dump_opts;
extern const char *environ_dir;
extern const char *final_name;
extern const char *name_E_file;
extern const char *name_h_file;
extern const char *name_j_file;
extern const char *name_k_file;
extern const char *name_K_file;
extern const char *name_p_file;
extern const char *tokdef_output;
extern const char *version_flag;
extern const char *dev_null;
extern const char **env_paths;


/*
 * INTERNAL OPTIONS
 *
 * These variables control the behaviour of tcc.
 */

extern boolean api_checks;
extern boolean checker;
extern boolean dry_run;
extern boolean env_dump;
extern boolean link_specs;
extern boolean make_up_names;
extern boolean show_api;
extern boolean show_errors;
extern boolean suffix_overrides;
extern boolean taciturn;
extern boolean tidy_up;
extern boolean time_commands;
extern boolean tool_chain;
extern boolean tool_chain_environ;
extern boolean verbose;
extern boolean warnings;


/*
 * COMPILATION CONTROL OPTIONS
 *
 * These variables control the overall flow of the compilation.
 */

extern boolean make_archive;
extern boolean make_complex;
extern boolean make_preproc;
extern boolean make_pretty;
extern boolean make_tspec;
extern boolean use_assembler;
extern boolean use_binasm;
extern boolean use_hp_linker;
extern boolean use_sparc_cc;
extern boolean use_system_cc;
extern boolean use_dynlink;
extern boolean allow_cpp;
extern boolean allow_notation;
extern boolean allow_pl_tdf;
extern boolean allow_specs;



/*
 * PRESERVATION AND CONSTRUCTION FLAGS
 *
 * These identifiers are used by set_stage to set the keeps and stops options
 * for the various file types. STOP_STAGE means "stop and keep",
 * STOP_ONLY_STAGE means "stop", KEEP_STAGE means "keep" and DONT_KEEP_STAGE
 * means "don't keep".
 */
/* TODO enum */

#define STOP_STAGE		0
#define STOP_ONLY_STAGE		1
#define KEEP_STAGE		2
#define DONT_KEEP_STAGE		3


/*
 * INDIVIDUAL OPTIONS
 *
 * These flags control those individual executable options which are not easily
 * integrated into the main scheme of things.
 */

extern boolean flag_diag;
extern boolean flag_incl;
extern boolean flag_keep_err;
extern boolean flag_merge_all;
extern boolean flag_nepc;
extern boolean flag_no_files;
extern boolean flag_optim;
extern boolean flag_prof;
extern boolean flag_startup;
extern boolean flag_strip;


#endif /* FLAGS_H */
