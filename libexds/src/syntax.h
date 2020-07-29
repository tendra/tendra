/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * syntax.h - Character classification.
 *
 * This file specifies the interface to a number of syntax table manipulation
 * functions.  I ought to be able to use <ctype.h> for this, but I can't
 * because it doesn't have routines to get the numeric value for alphabetic
 * characters (amongst other omissions).
 *
 * It is assumed elsewhere (in association with the input stream facility
 * specified in the file "istream.h") that the null and newline characters are
 * white space, and have no digit value.
 */

#ifndef H_SYNTAX
#define H_SYNTAX

/*
 * This value is returned by the syntax_value function for characters that
 * do not have a digit value.
 *
 */
#define SYNTAX_NO_VALUE	(-1)

/*
 * This function returns the positive integer digit value that the specified
 * character should have, or SYNTAX_NO_VALUE if it has no value.
 */
int
syntax_value(char);

#endif /* !defined (H_SYNTAX) */
