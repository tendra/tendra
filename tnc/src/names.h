/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef NAMES_H
#define NAMES_H


/*
    MACROS GIVING CHARACTER TYPES

    These macros determine the character types for input text
*/

#include <ctype.h>

#define white_space(X)	((X) == ' ' || (X) == '\n' || (X) == '\t')
#define octal_digit(X)	((X) >= '0' && (X) <= '7')
#define dec_digit(X)	((X) >= '0' && (X) <= '9')
#define terminator(X)	(white_space(X) || (X) == '(' ||\
			 (X) == ')' || (X) == '#' || (X) == ',' ||\
			 (X) == EOF)
#define alpha(X)	(isalpha((X)) ||\
			 (X) == '_' || (X) == '~' || (X) == '.')
#define alphanum(X)	(alpha(X) || dec_digit(X))


/*
    BASIC CONSTRUCT NAMES

    These macros give the names of the basic constructs used in
    input text.
*/

#define MAKE_ALDEC		"make_al_tagdec"
#define MAKE_ALDEF		"make_al_tagdef"
#define MAKE_ID_TAGDEC		"make_id_tagdec"
#define MAKE_VAR_TAGDEC		"make_var_tagdec"
#define COMMON_TAGDEC		"common_tagdec"
#define MAKE_ID_TAGDEF		"make_id_tagdef"
#define MAKE_VAR_TAGDEF		"make_var_tagdef"
#define COMMON_TAGDEF		"common_tagdef"
#define MAKE_TOKDEC		"make_tokdec"
#define MAKE_TOKDEF		"make_tokdef"
#define MAKE_SORT		"make_token_sort"


/*
    INCLUDE CONSTRUCT NAMES

    These macros give the names of the constructs used to include
    code in input text.
*/

#define INCLUDE_CODE		"code"
#define INCLUDE_LIB		"lib"
#define INCLUDE_TEXT		"include"
#define USE_CODE		"use_code"
#define USE_LIB			"use_lib"


/*
    OTHER NAMES

    These macros gives other names used in input text.
*/

#define LOCAL_DECL		"local"
#define MAKE_STRING_EXTERN	"string_extern"
#define MAKE_UNIQUE_EXTERN	"unique_extern"
#define MAKE_CHAIN_EXTERN	"chain_extern"
#define MAKE_STRING		"multi_string"


#endif /* NAMES_H */
