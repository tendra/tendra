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


#ifndef TREE_INCLUDED
#define TREE_INCLUDED


/*
    STRUCTURE DEFINITION : WORD

    The structure word is used to record the layout of the pretty
    printed TDF tree.  It consists of a layout type (see below
    for details), a string of characters, together with the length
    of this string, and pointers to the "son" and "brother" words.
*/


typedef struct s_word {
    char type ;
    int length ;
    char *text ;
    struct s_word *son ;
    struct s_word *bro ;
} word ;


/*
    WORD LAYOUT TYPES

    The available layout types are :

	SIMPLE - representing a simple word,
	HORIZ_NONE - a word with a number of arguments listed horizontally,
	HORIZ_BRACKETS - a word with arguments listed horizontally in brackets,
	VERT_NONE - a word with arguments listed vertically,
	VERT_BRACKETS - a word with arguments listed vertically in brackets.
*/

#define SIMPLE			0
#define HORIZ_BRACKETS		1
#define VERT_BRACKETS		2
#define HORIZ_NONE		3
#define VERT_NONE		4


/*
    TDF TREE MANIPULATION

    The layout of the pretty-printed TDF tree is recorded in the
    structure word. The routine new_word allocates a new word of
    a given type.  The macro end_word is used to indicate the end
    of a complex word.  The routine format combines these with
    decode to provide a convenient way of decoding a word with a
    number of arguments of given sorts.
*/

#define blank_line()		( void ) new_word ( SIMPLE )
#define end_word( X )		word_ptr = ( X ) ; word_ptr->bro = null

extern int length ;
extern word word1 ;
extern word *word_ptr ;

extern void initialize_tree PROTO_S ( ( void ) ) ;
extern word *new_word PROTO_S ( ( int ) ) ;
extern void out_char PROTO_S ( ( int ) ) ;
extern void out_string PROTO_S ( ( char * ) ) ;
extern void out PROTO_S ( ( char * ) ) ;
extern void out_int PROTO_S ( ( long ) ) ;
extern void out_signed PROTO_S ( ( char *, int ) ) ;
extern void out_unique PROTO_S ( ( unique ) ) ;
extern void format PROTO_S ( ( int, char *, char * ) ) ;


#endif
