/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef MACRO_INCLUDED
#define MACRO_INCLUDED


/*
    TYPE REPRESENTING THE LOCATION OF A LIST OF TOKENS

    This type represents the location of a list of tokens and it used in
    expand_macro.  The toks field gives a pointer to this list, while the
    next field allows these locations to be formed into lists.
*/

typedef struct tok_loc_tag {
	PPTOKEN **toks;
	struct tok_loc_tag *next;
} TOKEN_LOC;


/*
    MACRO EXPANSION DECLARATIONS

    The routines in this module are concerned with the manipulation of
    lists of preprocessing tokens, including the expansion of macros.
*/

extern void init_macros(int, int);
extern void term_macros(void);
extern PPTOKEN *recognise_strings(PPTOKEN *, HASHID, int);
extern PPTOKEN *expand_macro(HASHID, TOKEN_LOC *, int);
extern PPTOKEN *read_line(int, int);
extern PPTOKEN *expand_tok_list(PPTOKEN *);
extern PPTOKEN *clean_tok_list(PPTOKEN *);
extern PPTOKEN *new_pptok(void);
extern void free_tok_list(PPTOKEN *);
extern int quote_tok_list(PPTOKEN *, int, int);
extern void token_parts(int, PPTOKEN *);


/*
    MACRO EXPANSION VARIABLES

    These variables are used in the macro expansion routines.
*/

extern NAMESPACE assert_namespace;
extern PPTOKEN *free_tokens;
extern TOKEN_LOC *file_loc;


/*
    BUILT-IN MACRO FLAG

    This flag is used as part of the storage field of a macro to indicate
    a built-in macro.
*/

#define dspec_builtin		dspec_static


#endif
