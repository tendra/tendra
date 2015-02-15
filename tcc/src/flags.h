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

extern bool api_checks;
extern bool checker;
extern bool dry_run;
extern bool env_dump;
extern bool link_specs;
extern bool make_up_names;
extern bool show_api;
extern bool show_errors;
extern bool suffix_overrides;
extern bool taciturn;
extern bool tidy_up;
extern bool tool_chain;
extern bool tool_chain_environ;
extern bool verbose;
extern bool warnings;


/*
 * COMPILATION CONTROL OPTIONS
 *
 * These variables control the overall flow of the compilation.
 */

extern bool make_archive;
extern bool make_complex;
extern bool make_preproc;
extern bool make_pretty;
extern bool make_tspec;
extern bool use_assembler;
extern bool use_binasm;
extern bool use_hp_linker;
extern bool use_sparc_cc;
extern bool use_system_cc;
extern bool use_dynlink;
extern bool allow_cpp;
extern bool allow_notation;
extern bool allow_pl_tdf;
extern bool allow_specs;



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

extern bool flag_diag;
extern bool flag_incl;
extern bool flag_keep_err;
extern bool flag_merge_all;
extern bool flag_nepc;
extern bool flag_no_files;
extern bool flag_optim;
extern bool flag_prof;
extern bool flag_startup;
extern bool flag_strip;


#endif /* FLAGS_H */
