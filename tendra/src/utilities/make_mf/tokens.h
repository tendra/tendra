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


#ifndef TOKENS_INCLUDED
#define TOKENS_INCLUDED


/*
    LEXICAL TOKEN NUMBERS

    These values gives the numbers associated with the various lexical
    tokens.
*/

#define lex_identifier		0
#define lex_number		1
#define lex_char		2
#define lex_wchar		3
#define lex_string		4
#define lex_wstring		5
#define lex_astring		6

#define lex_eof			7
#define lex_newline		8
#define lex_unknown		9

#define lex_hash		10
#define lex_hash_hash		11
#define lex_include		12


#endif
