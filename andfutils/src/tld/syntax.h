/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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


/*
 * syntax.h - Character classification.
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
 */

#ifndef H_SYNTAX
#define H_SYNTAX

#include <exds/common.h>


/*
 * This value is returned by the ``syntax_value'' function for characters that
 * do not have a digit value.
 */
#define SYNTAX_NO_VALUE	(-1)

/*
 * This function returns the positive integer digit value that the specified
 * character should have, or ``SYNTAX_NO_VALUE'' if it has no value.
 */
extern int			syntax_value
(char);

/*
 * This function returns the upper case version of the specified character if
 * it has one, otherwise it just returns the character.
 */
extern char			syntax_upcase
(char);

/*
 * This function returns the lower case version of the specified character if
 * it has one, otherwise it just returns the character.
 */
extern char			syntax_downcase
(char);

/*
 * This function returns true if the specified character is a white space
 * character, and false otherwise.
 */
extern BoolT			syntax_is_white_space
(char);

/*
 * This function returns true if the specified character can be printed, and
 * false otherwise.
 */
extern BoolT			syntax_is_printable
(char);

/*
 * This function returns true if the specified character is a letter, and
 * false otherwise.
 */
extern BoolT			syntax_is_letter
(char);

/*
 * This function returns true if the specified character is a decimal digit,
 * and false otherwise.
 */
extern BoolT			syntax_is_digit
(char);

#endif /* !defined (H_SYNTAX) */
