/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef SUFFIX_H
#define SUFFIX_H


/*
 * SINGLE CHARACTER KEYS FOR FILE TYPES - Table 2
 *
 * These are the special keys which do not correspond directly to a file type
 * present in table.h.
 *
 * TODO: is ALL_KEY actually used? (Perhaps only given by the user?)
 * TODO: can we merge the EXTRA_KEY information into table.h somehow?
 */
#define ALL_KEY				'a'
#define EXTRA_KEY			'+'


/*
 * OTHER FILE TYPE INFORMATION - Table 3
 *
 * Most of the file suffixes can be deduced from the table above. This table
 * gives a few other suffixes plus the default names for various output files.
 */
/* TODO possibly move to NULL-terminated array per type in table.c */
#define CPP_1_SUFFIX			"cc"
#define CPP_2_SUFFIX			"cpp"
#define PREPROC_CPP_1_SUFFIX		"ii"
#define PREPROC_CPP_2_SUFFIX		"ipp"
#define AS_2_SUFFIX			"asm"
#define CPP_SPEC_1_SUFFIX		"kk"
#define PL_TDF_SUFFIX			"tpl"
#define TDF_ARCHIVE_SUFFIX		"ta"
#define TDF_COMPLEX_NAME		"a.j"
#define TDF_ARCHIVE_NAME		"a.ta"
#define C_SPEC_COMPLEX_NAME		"a.k"
#define API_ANAL_NAME			"a.api"
#define EXECUTABLE_NAME			"a.out"
#define CPP_SPEC_COMPLEX_NAME		"a.K"

#define STARTUP_NAME			"tcc_startup.h"
#define ENDUP_NAME			"tcc_endup.h"
#define TOKDEF_NAME			"tcc_tokdef.p"
#define MADE_UP_NAME			"_tcc%04d"
#define TEMP_NAME			"_tcc"


/*
 * SINGLE CHARACTER KEYS FOR EXECUTABLES - Table 4
 *
 * Each executable has an associated identifying letter.
 *
 * Since these are used to construct strings in the options interpreter,
 * none of these may have the value '\0'.
 */
/* TODO: enum */
#define ARCHIVER_ID          'J'
#define ASSEMBLE_ID          'a'
#define ASSEMBLE_BINASM_ID   'A'
#define CAT_ID               'o'
#define CC_ID                'C'
#define CPP_PREPROC_ID       'g'
#define CPP_PRODUCE_ID       'x'
#define CPP_SPEC_LINK_ID     'S'
#define DUMP_ANAL_ID         'e'
#define DUMP_LINK_ID         'u'
#define DYNLINK_ID           'D'
#define INSTALL_ID           'I'
#define LINK_ID              'l'
#define MKDIR_ID             'm'
#define MOVE_ID              'v'
#define NOTATION_ID          'n'
#define PL_TDF_ID            'P'
#define PREPROC_ID           'p'
#define PRETTY_ID            'd'
#define PRODUCE_ID           'c'
#define RMDIR_ID             'R'
#define RMFILE_ID            'r'
#define SPEC_LINK_ID         's'
#define TDF_LINK_ID          'L'
#define TOUCH_ID             'T'
#define TRANSLATE_ID         't'


/*
 * OTHER MISCELLANEOUS INFORMATION
 *
 * This table contains miscellaneous configuration items.
 */
#define PROGNAME_TCC			"tcc"
#define TCCENV_VAR			"TCCENV"
#define TCCOPT_VAR			"TCCOPTS"
#define DIAG_ENV			"tcc_diag"
#define PREPROC_ENV			"tcc_pp"
#define PROF_ENV			"tcc_prof"
#define TNC_ENV				"tnc"


#endif /* SUFFIX_H */
