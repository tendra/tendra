/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


#ifndef FILENAME_H
#define FILENAME_H

#include "config.h"


/* TODO comment on keeping in sync with the table and vice-versa */
enum filetype {
	/* TODO prefix FT_ */
	C_SOURCE     = 0,
	PREPROC_C    = 1,
	CPP_SOURCE   = 2,
	PREPROC_CPP  = 3,
	INDEP_TDF    = 4,
	DEP_TDF      = 5,
	AS_SOURCE    = 6,
	BINARY_OBJ   = 7,
	EXECUTABLE   = 8,
	PRETTY_TDF   = 9,
	PL_TDF       = 10,
	TDF_ARCHIVE  = 11,
	MIPS_G_FILE  = 12,
	MIPS_T_FILE  = 13,
	C_SPEC       = 14,
	CPP_SPEC     = 15,
	STARTUP_FILE = 16,

	/* Things which aren't really types */
	UNKNOWN_TYPE = 17,
	ALL_TYPES    = 31,
	DEFAULT_TYPE = BINARY_OBJ,  /* TODO what is this used for? */

	/*
	 * EXTRA FILE TYPES
	 *
	 * These dummy file types are in addition to those listed in filename.h. They
	 * are used in the keeps and stops arrays to resolve questions about, for
	 * example, TDF building, which in terms of file types maps :
	 *
	 *     INDEP_TDF x ... x INDEP_TDF -> INDEP_TDF
	 *
	 * By introducing a dummy type for the output we can refine the keeps and stops
	 * information to, for example, keep the output but not the input.
	 */
	INDEP_TDF_COMPLEX = UNKNOWN_TYPE + 1,
	C_SPEC_1          = UNKNOWN_TYPE + 2,
	C_SPEC_2          = UNKNOWN_TYPE + 3,
	CPP_SPEC_1        = UNKNOWN_TYPE + 4,
	CPP_SPEC_2        = UNKNOWN_TYPE + 5,
	INDEP_TDF_AUX     = UNKNOWN_TYPE + 6,
	BINARY_OBJ_AUX    = UNKNOWN_TYPE + 7
};


/*
 * TYPE REPRESENTING A FILE NAME
 *
 * The filename structure is used to represent a tcc input or output file. It
 * has an associated name (the full pathname), a basename (with the directory
 * and file suffix removed), a file type (see below) and a file storage type
 * (see below). Filenames are formed into lists using the next field. The may
 * also be associated into groups which are passed around as if they were a
 * single file using the aux field.
 */

typedef struct filename_t {
	const char *name;
	const char *bname;
	int uniq;
	enum filetype type;
	int storage;
	boolean final;
	struct filename_t *aux;
	struct filename_t *next;
} filename;

#define no_filename	(NULL)


/*
 * FILE STORAGE TYPES
 *
 * The files handled by tcc may be of three basic types, input files, permanent
 * output files and temporary output files. The first type may also contain
 * input options which are treated like input files (for example, system
 * libraries). The second type includes the preserved intermediate files. In
 * fact PRESERVED_FILE is only used as the input to make_filename.
 */
/* TODO enum */

#define INPUT_FILE	0
#define INPUT_OPTION	1
#define OUTPUT_FILE	2
#define PRESERVED_FILE	3
#define TEMP_FILE	4


/*
 * FILE STORAGE LOCATIONS
 *
 * Output files may be stored either in the temporary directory or the work
 * directory.
 */

extern const char *tempdir;
extern const char *workdir;


/*
 * INPUT FILE VARIABLES
 *
 * These variables are used to pass information to and from find_filename.
 */

extern boolean case_insensitive;
extern boolean option_next;
extern int no_input_files;


/*
 * PROCEDURE DECLARATIONS
 *
 * These routines are concerned with creating and manipulating filenames.
 */

extern const char *find_basename(const char *);
extern const char *find_fullname(const char *);
extern filename *add_filename(filename *, filename *);
extern filename *find_filename(const char *, enum filetype);
extern filename *make_filename(filename *, enum filetype, int);
extern enum filetype find_type_suffix(char);
extern enum filetype find_type_stage(char);
extern int where(enum filetype);


#endif /* FILENAME_H */
