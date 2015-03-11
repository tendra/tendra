/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef LEX_INCLUDED
#define LEX_INCLUDED


/*
    LEXICAL ANALYSIS DECLARATIONS

    The routines in this module are concerned with the lexical analysis
    of the input, including its decomposition into preprocessing tokens
    using the routine read_token.
*/

extern void init_lex(void);
extern void init_char(void);
extern void process_file(void);
extern IDENTIFIER make_keyword(HASHID, int, IDENTIFIER);
extern void init_keywords(void);
extern int read_token(void);
extern int read_string(int, int);
extern int peek_char(int, int *);
extern int skip_to_end(void);
extern unsigned long skip_white(int);
extern void patch_white(unsigned long);
extern int get_digraph(int);
extern int primary_form(int);
extern int is_white_char(unsigned long);
extern int is_alpha_char(unsigned long);
extern int is_legal_char(unsigned long);
extern void set_char_lookup(int, int);
extern void set_character(EXP, EXP);


/*
    LEXICAL TOKEN INFORMATION

    These variables are used by read_token to hold information about the
    current lexical token.
*/

extern BUFFER token_buff;
extern HASHID token_hashid;
extern const char *token_names[];


/*
    LEXICAL ANALYSIS OPTIONS

    These variables are used to configure the lexical analysis routines.
*/

extern int allow_trigraphs;
extern int allow_digraphs;
extern int allow_unicodes;
extern int allow_multibyte;
extern int allow_cpp_comments;
extern int allow_dos_newline;
extern int allow_extra_symbols;
extern int allow_iso_keywords;
extern int analyse_comments;
extern unsigned long max_id_length;


/*
    TOKEN NAME LOOK-UP

    The macro token_name is used to look up the name associated with the
    lexical token number T.
*/

#define token_name(T)		(ustrlit(token_names[(T)]))


/*
    WHITE-SPACE INDICATORS

    These macros are used by skip_white to indicate the form of the white-
    space characters skipped.
*/

enum {
	WHITE_SPACE       = 0x01UL,
	WHITE_NEWLINE     = 0x02UL,
	WHITE_ESC_NEWLINE = 0x04UL,
	WHITE_MASK        = (WHITE_SPACE | WHITE_NEWLINE)
};


#endif
