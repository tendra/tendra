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


/**** syntax.h --- Character classification.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to a number of syntax table manipulation
 * functions.  I ought to be able to use <ctype.h> for this, but I can't
 * because it doesn't have routines to get the numeric value for alphabetic
 * characters (amongst other omissions).  As I need to do this here, I might
 * as well put in support for everything.
 *
 * It is assumed elsewhere (in association with the input stream facility
 * specified in the file "istream.h") that the null and newline characters are
 * white space, and have no digit value.
 *
 ***=== CONSTANTS ============================================================
 *
 ** Constant:	SYNTAX_NO_VALUE
 *
 * This value is returned by the ``syntax_value'' function for characters that
 * do not have a digit value.
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	int			syntax_value
 *			PROTO_S ((char c))
 ** Exceptions:
 *
 * This function returns the positive integer digit value that the specified
 * character should have, or ``SYNTAX_NO_VALUE'' if it has no value.
 *
 ** Function:	char			syntax_upcase
 *			PROTO_S ((char c))
 ** Exceptions:
 *
 * This function returns the upper case version of the specified character if
 * it has one, otherwise it just returns the character.
 *
 ** Function:	char			syntax_downcase
 *			PROTO_S ((char c))
 ** Exceptions:
 *
 * This function returns the lower case version of the specified character if
 * it has one, otherwise it just returns the character.
 *
 ** Function:	BoolT			syntax_is_white_space
 *			PROTO_S ((char c))
 *
 * This function returns true if the specified character is a white space
 * character, and false otherwise.
 *
 ** Function:	BoolT			syntax_is_printable
 *			PROTO_S ((char c))
 ** Exceptions:
 *
 * This function returns true if the specified character can be printed, and
 * false otherwise.
 *
 ** Function:	BoolT			syntax_is_letter
 *			PROTO_S ((char c))
 ** Exceptions:
 *
 * This function returns true if the specified character is a letter, and
 * false otherwise.
 *
 ** Function:	BoolT			syntax_is_digit
 *			PROTO_S ((char c))
 ** Exceptions:
 *
 * This function returns true if the specified character is a decimal digit,
 * and false otherwise.
 *
 **** Change Log:
 * $Log: syntax.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:45:54  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:13  smf
 * Initial import of os-interface shared files.
 *
**/

/****************************************************************************/

#ifndef H_SYNTAX
#define H_SYNTAX

#include "os-interface.h"

/*--------------------------------------------------------------------------*/

#define SYNTAX_NO_VALUE (-1)

/*--------------------------------------------------------------------------*/

extern int			syntax_value
	PROTO_S ((char));
extern char			syntax_upcase
	PROTO_S ((char));
extern char			syntax_downcase
	PROTO_S ((char));
extern BoolT			syntax_is_white_space
	PROTO_S ((char));
extern BoolT			syntax_is_printable
	PROTO_S ((char));
extern BoolT			syntax_is_letter
	PROTO_S ((char));
extern BoolT			syntax_is_digit
	PROTO_S ((char));

#endif /* !defined (H_SYNTAX) */
