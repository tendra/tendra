/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef FILENAME_H
#define FILENAME_H


/* TODO comment on keeping in sync with the table and vice-versa */
enum filetype {
	/* TODO prefix FT_ */
	C_SOURCE       =  0,
	PREPROC_C      =  1,
	CPP_SOURCE     =  2,
	PREPROC_CPP    =  3,
	INDEP_TDF      =  4,
	DEP_TDF        =  5,
	AS_SOURCE      =  6,
	BINARY_OBJ     =  7,
	EXECUTABLE     =  8,
	PRETTY_TDF     =  9,
	PL_TDF         = 10,
	TDF_ARCHIVE    = 11,
	BINASM_G_FILE  = 12,
	BINASM_T_FILE  = 13,
	C_SPEC         = 14,
	CPP_SPEC       = 15,
	STARTUP_FILE   = 16,

	/* Things which aren't really types */
	UNKNOWN_TYPE   = 17,
	ALL_TYPES      = 31,
	DEFAULT_TYPE   = BINARY_OBJ,  /* TODO what is this used for? */

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
 * FILE STORAGE TYPES
 *
 * The files handled by tcc may be of three basic types, input files, permanent
 * output files and temporary output files. The first type may also contain
 * input options which are treated like input files (for example, system
 * libraries). The second type includes the preserved intermediate files. In
 * fact PRESERVED_FILE is only used as the input to make_filename.
 */

enum file_storage {
	INPUT_FILE,
	INPUT_OPTION,
	OUTPUT_FILE,
	PRESERVED_FILE,
	TEMP_FILE
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
	enum file_storage storage;
	bool final;
	struct filename_t *aux;
	struct filename_t *next;
} filename;

#define no_filename	(NULL)


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

extern bool case_insensitive;
extern bool option_next;
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
extern filename *make_filename(filename *, enum filetype, enum file_storage);
extern enum filetype find_type_suffix(char);
extern enum filetype find_type_stage(char);
extern enum file_storage where(enum filetype);


#endif /* FILENAME_H */
