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


/**** syntax.c --- Character classification.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the syntax table facility specified in the file
 * "syntax.h". See that file for more details.
 *
 * This particular implementation assumes that the ASCII character set is
 * being used. It will need changing for other character sets.
 *
 **** Change Log:
 * $Log: syntax.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:45:52  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:12  smf
 * Initial import of os-interface shared files.
 *
**/

/****************************************************************************/

#include "syntax.h"

/*--------------------------------------------------------------------------*/

int
syntax_value PROTO_N ((c))
	     PROTO_T (char c)
{
    if ((c >= '0') && (c <= '9')) {
	return (c - '0');
    } else if ((c >= 'A') && (c <= 'Z')) {
	return (c - 'A' + 10);
    } else if ((c >= 'a') && (c <= 'z')) {
	return (c - 'a' + 10);
    }
    return (SYNTAX_NO_VALUE);
}

char
syntax_upcase PROTO_N ((c))
	      PROTO_T (char c)
{
    if ((c >= 'a') && (c <= 'z')) {
	return ((char) (c - 'a' + 'A'));
    }
    return (c);
}

char
syntax_downcase PROTO_N ((c))
		PROTO_T (char c)
{
    if ((c >= 'A') && (c <= 'Z')) {
	return ((char) (c - 'A' + 'a'));
    }
    return (c);
}

BoolT
syntax_is_white_space PROTO_N ((c))
		      PROTO_T (char c)
{
    return ((c < 33) || (c > 126));
}

BoolT
syntax_is_printable PROTO_N ((c))
		    PROTO_T (char c)
{
    return ((c > 31) && (c < 127));
}

BoolT
syntax_is_letter PROTO_N ((c))
		 PROTO_T (char c)
{
    return (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')));
}

BoolT
syntax_is_digit PROTO_N ((c))
		PROTO_T (char c)
{
    return ((c >= '0') && (c <= '9'));
}
