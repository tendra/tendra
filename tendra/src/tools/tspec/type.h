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


#ifndef TYPE_INCLUDED
#define TYPE_INCLUDED


/*
 *    TYPE REPRESENTING A C TYPE
 *
 *    A type consists of a type identifier followed by a union of different
 *    information, depending on the identifier.
 */

typedef struct type_tag {
    int id;
    union {
		object *obj;
		struct type_tag *subtype;
    } u;
    union {
		int no;
		char *str;
		object *obj2;
		struct type_tag *next;
    } v;
    boolean state;
} type;


/*
 *    TYPE REPRESENTING A STRUCTURE OR UNION FIELD
 *
 *    A field of a structure or union consists of an object, giving the
 *    corresponding token, a field name, a field type, and the parent
 *    structure or union type.
 */

typedef struct field_tag {
    object *obj;
    char *fname;
    type *ftype;
    type *stype;
} field;


/*
 *    TYPE IDENTIFIERS
 *
 *    These are the valid type identifiers.  The first set consists of the
 *    base types, the second of the compound type constructors.
 */

#define TYPE_VOID		0
#define TYPE_INT		1
#define TYPE_SIGNED		2
#define TYPE_UNSIGNED		3
#define TYPE_FLOAT		4
#define TYPE_ARITH		5
#define TYPE_SCALAR		6
#define TYPE_STRUCT		7
#define TYPE_STRUCT_TAG		8
#define TYPE_UNION		9
#define TYPE_UNION_TAG		10
#define TYPE_ENUM		11
#define TYPE_ENUM_TAG		12
#define TYPE_GENERIC		13
#define TYPE_DEFINED		14

#define TYPE_ARRAY		15
#define TYPE_BITFIELD		16
#define TYPE_LIST		17
#define TYPE_LVALUE		18
#define TYPE_PROC		19
#define TYPE_PROMOTE		20
#define TYPE_PTR		21
#define TYPE_QUALIFIER		22
#define TYPE_RVALUE		23



/*
 *    BASE TYPE SPECIFIERS
 *
 *    The basic type specifiers are represented as combinations of these
 *    values.
 */

#define BTYPE_CHAR		((unsigned) 0x0001)
#define BTYPE_SHORT		((unsigned) 0x0002)
#define BTYPE_INT		((unsigned) 0x0004)
#define BTYPE_LONG		((unsigned) 0x0008)
#define BTYPE_LLONG		((unsigned) 0x0010)
#define BTYPE_SIGNED		((unsigned) 0x0020)
#define BTYPE_UNSIGNED		((unsigned) 0x0040)
#define BTYPE_FLOAT		((unsigned) 0x0080)
#define BTYPE_DOUBLE		((unsigned) 0x0100)
#define BTYPE_VOID		((unsigned) 0x0200)
#define BTYPE_ERROR		((unsigned) 0x0400)


/*
 *    FUNDAMENTAL TYPES
 *
 *    These types represent the basic C types.
 */

#define BUILTIN(TYPE, NAME, VERS, ID)	extern type *TYPE
#include "builtin.h"


/*
 *    PROCEDURE DECLARATIONS
 *
 *    These routines are concerned with creating and manipulating types.
 */

extern type *basic_type(unsigned);
extern type *make_type(char *, int, int);
extern type *find_type(char *, int, int, int);
extern type *make_subtype(type *, int);
extern type *inject_type(type *, type *);
extern type *check_type(type *, int);
extern type *expand_type(type *);
extern field *make_field(char *, int, type *, type *);
extern type *special_type(char *);
extern void init_types(void);


#endif
