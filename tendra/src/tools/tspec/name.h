/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#ifndef NAME_INCLUDED
#define NAME_INCLUDED


/*
 *    INPUT AND OUTPUT DIRECTORIES
 *
 *    These macros give the standard input and output directories, and may
 *    vary between machines.
 */

#ifndef INPUT_DIR
#define INPUT_DIR		"/u/g/release/Source/src/lib/apis"
#endif

#ifndef INCLUDE_DIR
#define INCLUDE_DIR		"/u/g/release/Source/lib/include"
#endif

#ifndef SRC_DIR
#define SRC_DIR			"/u/g/release/Source/lib/building"
#endif


/*
 *    ENVIRONMENTAL VARIABLES
 *
 *    These macros give the names of the various environmental variables
 *    which are checked for input and output directories.
 */

#define INPUT_ENV		"TSPEC_INPUT"
#define OUTPUT_ENV		"TSPEC_OUTPUT"
#define INCLUDE_ENV		"TSPEC_INCL_OUTPUT"
#define SRC_ENV			"TSPEC_SRC_OUTPUT"


/*
 *    OUTPUT INCLUDE FILES
 *
 *    These macros are concerned with the include output files.
 */

#define OUTPUT_API		"%s/shared/%s.api/MASTER.h"
#define OUTPUT_FILE		"%s/%s.api/%s"
#define OUTPUT_SUBSET		"%s/shared/%s.api/%s.h"
#define OUTPUT_SUFFIX		".api"
#define OUTPUT_LENGTH		8


/*
 *    OUTPUT SOURCE FILES
 *
 *    These macros are concerned with the source output files.
 */

#define SOURCE_API		"%s/%s.api/MASTER.c"
#define SOURCE_FILE		"%s/%s.api/%s.c"
#define SOURCE_SUBSET		"%s/%s.api/%s.c"


/*
 *    OUTPUT MAKEFILES
 *
 *    These macros give the location of the output makefiles.
 */

#define MAKEFILE		"%s/%s.api/Makefile"
#define MAKEFILE_API		"%s/%s.api/M_%s"


/*
 *    MISCELLANEOUS FILES
 *
 *    These macros give certain standard file names.
 */

#define MASTER_FILE		"MASTER"
#define LOCAL_API		"LOCAL"


/*
 *    NAME CONSTANTS
 *
 *    These macros give various name prefixes and other standard names.
 */

#define HIDDEN_NAME		"__local_"
#define HIDDEN_LEN		sizeof (HIDDEN_NAME)
#define BUILDING_MACRO		"__BUILDING_LIBS"
#define PROTECT_PREFIX		"__TDF"
#define DEFINE_PREFIX		"__BUILDING_TDF"
#define WEAK_PROTO		"__WEAK_SPEC"
#define WRONG_PREFIX		"__WRONG"


/*
 *    PROCEDURE DECLARATIONS
 *
 *    These routines concerned with generating names of various sorts - file
 *    names, token names etc.
 */

extern char *basename(char *);
extern char *dirname(char *);
extern char *relative(char *, char *, int);
extern char *hack_name(char *, char *);
extern char *token_name(char *);
extern char *token_prefix(char *, char *, char *);
extern char *subset_name(char *, char *, char *);
extern char *include_name(char *, char *, char *, char *);
extern char *src_name(char *, char *, char *, char *);
extern char *macro_name(char *, char *, char *, char *);
extern char *block_name(char *, char *, char *);


/*
 *    STANDARD FLAGS
 *
 *    These are standard flags which are set by command line options.
 */

extern boolean allow_long_long;
extern boolean force_output;
extern boolean local_input;
extern boolean restrict_depth;
extern boolean restrict_use;
extern boolean unique_names;
extern int verbose;


/*
 *    INPUT AND OUTPUT DIRECTORIES
 *
 *    These variables give the input and output directories.
 */

extern char *input_dir;
extern char *output_incl_dir;
extern char *output_src_dir;
extern int output_incl_len;
extern int output_src_len;


#endif
