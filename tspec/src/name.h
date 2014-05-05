/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef NAME_H
#define NAME_H

#include <shared/bool.h>

/*
 * ENVIRONMENTAL VARIABLES
 *
 * These macros give the names of the various environmental variables
 * which are checked for input and output directories.
 */
#define INPUT_ENV     "TSPEC_INPUT"
#define OUTPUT_ENV    "TSPEC_OUTPUT"
#define INCLUDE_ENV   "TSPEC_INCL_OUTPUT"
#define SRC_ENV       "TSPEC_SRC_OUTPUT"
#define COPYRIGHT_ENV "TSPEC_COPYRIGHT"

/*
 * OUTPUT INCLUDE FILES
 *
 * These macros are concerned with the include output files.
 */

#define OUTPUT_API    "%s/shared/%s.api/MASTER.h"
#define OUTPUT_FILE   "%s/%s.api/%s"
#define OUTPUT_SUBSET "%s/shared/%s.api/%s.h"
#define OUTPUT_SUFFIX ".api"
#define OUTPUT_LENGTH 8

/*
 * OUTPUT SOURCE FILES
 *
 * These macros are concerned with the source output files.
 */
#define SOURCE_API    "%s/%s.api/MASTER.c"
#define SOURCE_FILE	  "%s/%s.api/%s.c"
#define SOURCE_SUBSET "%s/%s.api/%s.c"

/*
 * MISCELLANEOUS FILES
 *
 * These macros give certain standard file names.
 */
#define MASTER_FILE "MASTER"
#define LOCAL_API   "LOCAL"

/*
 *  NAME CONSTANTS
 *
 * These macros give various name prefixes and other standard names.
 */
#define HIDDEN_NAME	   "__local_"
#define HIDDEN_LEN     (sizeof HIDDEN_NAME)
#define BUILDING_MACRO "__BUILDING_LIBS"
#define PROTECT_PREFIX "__TDF"
#define DEFINE_PREFIX  "__BUILDING_TDF"
#define WEAK_PROTO     "__WEAK_SPEC"
#define WRONG_PREFIX   "__WRONG"

/*
 * PROCEDURE DECLARATIONS
 *
 * These routines concerned with generating names of various sorts - file
 * names, token names etc.
 */
char *basename(char *);
char *strip_extension(char *);
char *dirname(char *);
char *relative(char *, char *, int);
char *hack_name(char *, char *);
char *token_name(char *);
char *token_prefix(char *, char *, char *);
char *subset_name(char *, char *, char *);
char *include_name(char *, char *, char *, char *);
char *src_name(char *, char *, char *, char *);
char *macro_name(char *, char *, char *, char *);
char *block_name(char *, char *, char *);

/*
 * STANDARD FLAGS
 *
 * These are standard flags which are set by command line options.
 */
extern bool basename_apis;
extern bool allow_long_long;
extern bool force_output;
extern bool local_input;
extern bool restrict_depth;
extern bool restrict_use;
extern bool unique_names;
extern int verbose;

/*
 * INPUT AND OUTPUT DIRECTORIES
 *
 * These variables give the input and output directories.
 */
extern char *input_dir;
extern char *output_incl_dir;
extern char *output_src_dir;
extern int output_incl_len;
extern int output_src_len;

#endif

