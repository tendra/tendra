/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
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
 *    		 Crown Copyright (c) 1996
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
/*
 *			    VERSION INFORMATION
 *			    ===================
 *
 *--------------------------------------------------------------------------
 *$Header$
 *--------------------------------------------------------------------------*/


#ifndef EXPTYPES_INCLUDED
#define EXPTYPES_INCLUDED


/*
 *    STRUCTURE REPRESENTING EXPRESSION PROPERTIES
 *
 *    This is basically a bitfield, with different bits representing
 *    different properties.  See expmacs.h for details.
 */

typedef unsigned short prop;


/*
 *    UNION REPRESENTING A EXPRESSION CONSTITUENT
 *
 *    An expression constituent can be another expression, a string, a
 *    numerical value, a floating-point value or an external declaration.
 */

typedef union {
#ifndef tdf3
	long l;
	unsigned long ui;
#else
    int l;
    unsigned int ui;
#endif
    float fp;
    char *str;
    struct exp_t *expr;
    struct dec_t *glob;
    diag_info *d;
    struct aldef_t *ald;
} expno ; 


/*
 *    STRUCTURE REPRESENTING EXPRESSIONS
 *
 *    An expression has a number of constituents given by the sonf, brof,
 *    ptrf and numf fields, a shape (which is another expression), a
 *    name representing the expression type, a properties field, and a
 *    single byte as an end marker.
 */

struct exp_t {
    unsigned char namef;
    unsigned char lastf;
    unsigned char park;
    prop propsf;
    expno sonf;
    expno brof;
    expno ptf;
    expno numf;
    struct exp_t *shf;
};


/*
 *    THE EXPRESSION TYPE
 *
 *    The type exp is a pointer to the structure given above.  Access to the
 *    fields of the structure is by means of the macros given in expmacs.h.
 */

typedef struct exp_t *exp;

#endif




