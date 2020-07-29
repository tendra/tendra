/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TYPE_H
#define TYPE_H

#include <shared/bool.h>

#ifndef OBJECT_H
#include "object.h"
#endif

/*
 * These are silly names.
 */
enum type_state {
	TYPE_IMMEDIATE,
	TYPE_ELSEWHERE,
	TYPE_EARLIER,
	TYPE_ANOTHER
};

/*
 * TYPE REPRESENTING A C TYPE
 *
 * A type consists of a type identifier followed by a union of different
 * information, depending on the identifier.
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

	enum type_state state;
} type;

/*
 * TYPE REPRESENTING A STRUCTURE OR UNION FIELD
 *
 * A field of a structure or union consists of an object, giving the
 * corresponding token, a field name, a field type, and the parent
 * structure or union type.
 */
typedef struct field_tag {
	object *obj;
	char *fname;
	type *ftype;
	type *stype;
} field;

/*
 * TYPE IDENTIFIERS
 *
 * These are the valid type identifiers.  The first set consists of the
 * base types, the second of the compound type constructors.
 */
#define TYPE_VOID        0
#define TYPE_INT         1
#define TYPE_SIGNED      2
#define TYPE_UNSIGNED    3
#define TYPE_FLOAT       4
#define TYPE_ARITH       5
#define TYPE_SCALAR      6
#define TYPE_STRUCT      7
#define TYPE_STRUCT_TAG  8
#define TYPE_UNION       9
#define TYPE_UNION_TAG  10
#define TYPE_ENUM       11
#define TYPE_ENUM_TAG   12
#define TYPE_GENERIC    13
#define TYPE_DEFINED    14

#define TYPE_ARRAY      15
#define TYPE_BITFIELD   16
#define TYPE_LIST       17
#define TYPE_LVALUE     18
#define TYPE_PROC       19
#define TYPE_PROMOTE    20
#define TYPE_PTR        21
#define TYPE_QUALIFIER  22
#define TYPE_RVALUE     23

/*
 * BASE TYPE SPECIFIERS
 *
 * The basic type specifiers are represented as combinations of these
 * values.
 */
#define BTYPE_CHAR     0x0001U
#define BTYPE_SHORT    0x0002U
#define BTYPE_INT      0x0004U
#define BTYPE_LONG     0x0008U
#define BTYPE_LLONG    0x0010U
#define BTYPE_SIGNED   0x0020U
#define BTYPE_UNSIGNED 0x0040U
#define BTYPE_FLOAT    0x0080U
#define BTYPE_DOUBLE   0x0100U
#define BTYPE_VOID     0x0200U
#define BTYPE_ERROR    0x0400U

/*
 * FUNDAMENTAL TYPES
 *
 * These types represent the basic C types.
 */
#define BUILTIN(TYPE, NAME, VERS, ID) extern type *TYPE
#include "builtin.h"

/*
 * PROCEDURE DECLARATIONS
 *
 * These routines are concerned with creating and manipulating types.
 */
type *basic_type(unsigned);
type *make_type(char *, int, int);
type *find_type(char *, int, int, int);
type *make_subtype(type *, int);
type *inject_type(type *, type *);
type *check_type(type *, int);
type *expand_type(type *);
field *make_field(char *, int, type *, type *);
type *special_type(char *);
void init_types(void);

#endif

