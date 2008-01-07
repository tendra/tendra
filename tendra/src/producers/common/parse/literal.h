/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#ifndef LITERAL_INCLUDED
#define LITERAL_INCLUDED


/*
 *    LITERAL CONSTRUCTION DECLARATIONS
 *
 *    The routines in this module are concerned with the construction of
 *    integer, floating-point, character, string and boolean literal
 *    expressions.
 */

extern EXP make_literal_exp(string, int *, int);
extern EXP make_bool_exp(unsigned, unsigned);
extern EXP make_string_exp(STRING);

extern int is_zero_float(FLOAT);
extern int eq_float_lit(FLOAT, FLOAT);
extern int eq_string_lit(STRING, STRING);
extern unsigned test_bool_exp(EXP);
extern unsigned long eval_line_digits(string, unsigned *);
extern unsigned long get_multi_char(string, int *);
extern unsigned long get_string_char(STRING, int *);
extern void add_multi_char(string, unsigned long, int);
extern unsigned long eval_unicode(int, unsigned, int *, string *, ERROR *);
extern TYPE find_literal_type(NAT, int, int, string, int *);
extern TYPE find_char_type(NAT);
extern NAT round_float_lit(FLOAT, RMODE);
extern STRING new_string_lit(string, string, int);
extern STRING concat_string_lit(STRING, STRING);
extern STRING share_string_lit(STRING);
extern NAT eval_char_lit(STRING);
extern int get_char_value(EXP);
extern void begin_literal(int, int);
extern void add_range_literal(EXP, int);
extern void add_type_literal(TYPE);
extern void add_token_literal(IDENTIFIER, unsigned);
extern void set_string_qual(CV_SPEC);
extern void set_escape(EXP, EXP);
extern void set_char_lit(TYPE);
extern void init_literal(void);

extern unsigned char digit_values [];
extern unsigned char escape_sequences [];
extern RMODE crt_round_mode;
extern CV_SPEC cv_string;


/*
 *    STRING TYPES
 *
 *    The values STRING_* form a bitfield which is used to identify the
 *    various types of string literals.
 */

#define STRING_NONE		((unsigned) 0x00)
#define STRING_CHAR		((unsigned) 0x01)
#define STRING_WIDE		((unsigned) 0x02)
#define STRING_MULTI		((unsigned) 0x04)
#define STRING_FAT		((unsigned) 0x08)
#define MULTI_WIDTH		5


/*
 *    BOOLEAN VALUES
 *
 *    These values give the boolean values, true and false, plus a third
 *    value indicating an indeterminate boolean.  A fourth error value is
 *    also given.
 */

#define BOOL_FALSE		((unsigned) 0)
#define BOOL_TRUE		((unsigned) 1)
#define BOOL_UNKNOWN		((unsigned) 2)
#define BOOL_INVALID		((unsigned) 3)
#define BOOL_VALUE(C)		((C) ? BOOL_TRUE : BOOL_FALSE)
#define BOOL_NEGATE(C)	((C) ? BOOL_FALSE : BOOL_TRUE)


/*
 *    LITERAL BASE AND SUFFIX VALUES
 *
 *    These values are used to identify the various bases and suffixes for
 *    integer literals.
 */

#define BASE_DECIMAL		0
#define BASE_OCTAL		1
#define BASE_HEXADECIMAL	2
#define BASE_NO			3

#define SUFFIX_NONE		0
#define SUFFIX_U		1
#define SUFFIX_L		2
#define SUFFIX_UL		3
#define SUFFIX_LL		4
#define SUFFIX_ULL		5
#define SUFFIX_NO		6

#define SUFFIX(U, L)		(2 * (L) + (U))


#endif
