/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef PREPROC_INCLUDED
#define PREPROC_INCLUDED


/*
 * TYPE REPRESENTING A PREPROCESSING TOKEN
 *
 * This type represents a preprocessing token. This consists of a token value,
 * corresponding to the macros defined in syntax.h, plus any associated data.
 * In some instances the space field is used to indicate that the token is
 * preceded by a white-space. The next field points to the next token.
 */
typedef struct pptok_tag {
	int tok;
	struct pptok_tag *next;
	union {
		/* Associated data */
		int sint;
		string text;
		unsigned uint;
		character buff[8];
		EXP exp;
		NAT nat;
		FLOAT flt;
		NAMESPACE ns;
		STRING strlit;
		TYPE type;
		struct {
			/* Identifier */
			HASHID hash;
			IDENTIFIER use;
		} id;
		struct {
			/* String */
			string start;
			string end;
		} str;
		struct {
			/* Macro parameter */
			HASHID hash;
			unsigned long no;
		} par;
		struct {
			/* Location */
			unsigned long line;
			PTR(POSITION)posn;
		} loc;
		struct {
			/* Token application */
			IDENTIFIER id;
			struct pptok_tag *args;
		} tok;
	} pp_data;
	unsigned long pp_space;
	OPTIONS *pp_opts;
} PPTOKEN;


/*
 *  PREPROCESSING DECLARATIONS
 *
 * The routines in this module are concerned with the processing of
 * preprocessing directives.  They include preprocess_file which is the
 * stand-alone preprocessing action of the program.
 */
extern int read_preproc_dir(int, int);
extern void patch_preproc_dir(PPTOKEN *);
extern int read_include(int, int);
extern unsigned check_macro(HASHID, int);
extern IDENTIFIER make_assert(HASHID, int);
extern void read_ident(int);
extern void read_weak(int);
extern void preprocess_file(void);
extern void start_preproc_if (void);
extern int clear_preproc_if (void);
extern int patch_cond(int, int);


/*
 * PREPROCESSING VARIABLES
 *
 * These variables are used by the preprocessing routines.
 */
extern int preproc_only;
extern int preproc_space;
extern int pragma_number;
extern int in_preproc_dir;
extern int no_preproc_dir;
extern int in_pragma_dir;
extern int in_hash_if_exp;
extern EXP crt_hash_if_exp;
extern LOCATION preproc_loc;
extern IDENTIFIER token_macro;


/*
 * CONDITIONAL COMPILATION STATES
 *
 * These values are used to identify the various conditional compilation
 * states.  The condition may be true, false, being skipped, or unresolved.
 * In addition a conditional compilation may or may not have associated
 * '#else' and '#elif' statements.  There is a special value for indicating
 * the end of an individual file.
 */
enum {
	PP_FALSE      = 0x00U,
	PP_TRUE       = 0x01U,
	PP_PAST       = 0x02U,
	PP_SKIP       = 0x03U,
	PP_UNRESOLVED = 0x04U,
	PP_COND_MASK  = 0x0fU,
	PP_HAVE_ELSE  = 0x10U,
	PP_HAVE_ELIF  = 0x20U,
	PP_TOKEN      = 0x40U,
	PP_END        = 0xffU
};


#endif

