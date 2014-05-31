/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/error.h>
#include <shared/xalloc.h>

#include <time.h>
#include <string.h>

#include "object.h"
#include "hash.h"
#include "type.h"
#include "utility.h"

/*
 * FUNDAMENTAL TYPES
 *
 * These types represent the fundamental C types.
 */
#define BUILTIN(TYPE, NAME, VERS, ID) type *TYPE
#include "builtin.h"

/*
 * INITIALISE THE FUNDAMENTAL TYPES
 *
 * This routine initialises the fundamental C types.
 */
void
init_types(void)
{
#define BUILTIN(TYPE, NAME, VERS, ID) TYPE = make_type(NAME, VERS, ID)
#include "builtin.h"
}

/*
 * FIND THE NAMESPACE FOR A TYPE IDENTIFIER
 *
 * This routine returns the hash table for types with identifier id.  In
 * most cases this is types, but it can be tags.  If flds is true the
 * corresponding field hash table is returned.
 */
static hash_table *
find_namespace(int id, int fld)
{
	switch (id) {
	case TYPE_STRUCT_TAG:
	case TYPE_UNION_TAG:
	case TYPE_ENUM_TAG:
		return fld ? tag_fields : tags;

	default:
		return fld ? type_fields : types;
	}
}

/*
 * ALLOCATE A NEW TYPE
 *
 * This routine allocates space for a new type.
 */
static type *
new_type(void)
{
	type *t;

	t = xmalloc(sizeof *t);
	t->state = TYPE_IMMEDIATE;

	return t;
}

/*
 * FIND A BASIC TYPE
 *
 * This routine maps the combination of basic type specifiers n to a
 * type.
 */
type *
basic_type(unsigned n)
{
	switch (n) {
	case BTYPE_CHAR:
		return type_char;

	case BTYPE_SIGNED | BTYPE_CHAR:
		return type_schar;

	case BTYPE_UNSIGNED | BTYPE_CHAR:
		return type_uchar;

	case BTYPE_SHORT:
	case BTYPE_SHORT | BTYPE_INT:
		return type_short;

	case BTYPE_SIGNED | BTYPE_SHORT:
	case BTYPE_SIGNED | BTYPE_SHORT | BTYPE_INT:
		return type_sshort;

	case BTYPE_UNSIGNED | BTYPE_SHORT:
	case BTYPE_UNSIGNED | BTYPE_SHORT | BTYPE_INT:
		return type_ushort;

	case BTYPE_INT:
		return type_int;

	case BTYPE_SIGNED:
	case BTYPE_SIGNED | BTYPE_INT:
		return type_sint;

	case BTYPE_UNSIGNED:
	case BTYPE_UNSIGNED | BTYPE_INT:
		return type_uint;

	case BTYPE_LONG:
	case BTYPE_LONG | BTYPE_INT:
		return type_long;

	case BTYPE_SIGNED | BTYPE_LONG:
	case BTYPE_SIGNED | BTYPE_LONG | BTYPE_INT:
		return type_slong;

	case BTYPE_UNSIGNED | BTYPE_LONG:
	case BTYPE_UNSIGNED | BTYPE_LONG | BTYPE_INT:
		return type_ulong;

	case BTYPE_LONG | BTYPE_LLONG:
	case BTYPE_LONG | BTYPE_LLONG | BTYPE_INT:
		return type_llong;

	case BTYPE_SIGNED | BTYPE_LONG | BTYPE_LLONG:
	case BTYPE_SIGNED | BTYPE_LONG | BTYPE_LLONG | BTYPE_INT:
		return type_sllong;

	case BTYPE_UNSIGNED | BTYPE_LONG | BTYPE_LLONG:
	case BTYPE_UNSIGNED | BTYPE_LONG | BTYPE_LLONG | BTYPE_INT:
		return type_ullong;

	case BTYPE_FLOAT:
		return type_float;

	case BTYPE_DOUBLE:
		return type_double;

	case BTYPE_LONG | BTYPE_DOUBLE:
		return type_ldouble;

	case BTYPE_VOID:
		return type_void;

	default:
		error(ERROR_SERIOUS, "Invalid type specifier");
		return type_int;
	}
}

/*
 * FIND A SPECIAL TYPE NAME
 *
 * This routine returns the special type described by the string s.
 */
type *
special_type(char *s)
{
	if (0 == strcmp(s, "bottom")) {
		return type_bottom;
	}

	if (0 == strcmp(s, "printf")) {
		return type_printf;
	}

	if (0 == strcmp(s, "scanf")) {
		return type_scanf;
	}

	error(ERROR_SERIOUS, "Unknown special type '%s'", s);
	return type_int;
}

/*
 * MAKE A NEW TYPE
 *
 * This routine creates a type called nm (version vers) with identifier id.
 */
type *
make_type(char *nm, int vers, int id)
{
	type *t = new_type();
	object *p = make_object(nm, OBJ_TYPE);

	p->u.u_type = t;
	t->id = id;
	t->u.obj = p;
	t->v.obj2 = NULL;
	p = add_hash(find_namespace(id, 0), p, vers);

	return p->u.u_type;
}

/*
 * FIND A TYPE
 *
 * This routine looks up a type called nm (version vers) with identifier
 * id.  If it does not exist then it creates one, also printing an error
 * if force is true.
 */
type *
find_type(char *nm, int vers, int id, int force)
{
	type *t;
	object *p;

	hash_table *h = find_namespace(id, 0);
	p = search_hash(h, nm, vers);
	if (p == NULL) {
		if (force == 0) {
			return NULL;
		}

		error(ERROR_SERIOUS, "%s '%s' not defined", h->name, nm);
		return make_type(nm, vers, id);
	}

	t = p->u.u_type;
	if (id != TYPE_GENERIC && id != t->id) {
		char *err = "%s '%s' used inconsistently (see %s, line %d)";
		error(ERROR_SERIOUS, err, h->name, nm, p->filename, p->line_no);
	}

	return t;
}

/*
 * CREATE A NEW COMPOUND TYPE
 *
 * This routine creates a compound type with identifier id and subtype t.
 */
type *
make_subtype(type *t, int id)
{
	type *s = new_type();

	s->id = id;
	s->u.subtype = t;
	s->v.obj2 = NULL;

	return s;
}

/*
 * FORM A QUALIFIED TYPE
 *
 * This type forms a type from the incomplete type qualifier s and
 * the type t.
 */
type *
inject_type(type *s, type *t)
{
	type *p = s;

	if (p == NULL) {
		return t;
	}

	if (t != NULL) {
		for ( ; p->u.subtype; p = p->u.subtype)
			;

		p->u.subtype = t;
	}

	return s;
}

/*
 * CONSTRUCT A FIELD
 *
 * This routine creates a field called nm (version vers) which is a field
 * of the structure of union s of type t.
 */
field *
make_field(char *nm, int vers, type *s, type *t)
{
	char *n;
	field *r;

	object *p;

	p = make_object(nm, OBJ_FIELD);

	r = xmalloc(sizeof *r);
	r->obj = p;
	r->stype = s;
	r->ftype = t;
	n = strchr(nm, '.');
	r->fname = n ? n + 1 : nm;
	p->u.u_field = r;
	p = add_hash(find_namespace(s->id, 1), p, vers);

	return p->u.u_field;
}

/*
 * EXPAND A TYPE
 *
 * This routine expands the type t by replacing any typedefs by their
 * definitions.
 */
type *
expand_type(type *t)
{
	for ( ; t != NULL && t->id == TYPE_DEFINED; t = t->v.next)
		;

	return t;
}

/*
 * AUXILIARY TYPE CHECKING ROUTINE
 *
 * This routine applies various checks to the type t.
 */
static type *
check_type_aux(type *t, int obj, int c, int ret)
{
	if (t == NULL) {
		return NULL;
	}

	switch (t->id) {
	case TYPE_VOID:
		if ((obj || c) && !ret) {
			error(ERROR_SERIOUS, "The type 'void' is incomplete");
		}
		break;

	case TYPE_ARRAY:
		if (c && t->v.str [0] == 0) {
			error(ERROR_SERIOUS, "Incomplete array type");
		}

		if (ret) {
			error(ERROR_SERIOUS, "A function can't return an array");
		}

		t->u.subtype = check_type_aux(t->u.subtype, 1, 1, 0);
		break;

	case TYPE_BITFIELD: {
		type *s = expand_type(t->u.subtype);

		if (s == NULL) {
			break;
		}

		switch (s->id) {
		case TYPE_INT:
		case TYPE_SIGNED:
		case TYPE_UNSIGNED:
			break;

		default:
			error(ERROR_SERIOUS, "Non-integral bitfield type");
			break;
		}
	}

	case TYPE_QUALIFIER:
		t->u.subtype = check_type_aux(t->u.subtype, obj, c, ret);
		break;

	case TYPE_LIST:
		t->u.subtype = check_type_aux(t->u.subtype, obj, c, ret);
		t->v.next = check_type_aux(t->v.next, obj, c, ret);
		break;

	case TYPE_LVALUE:
		t->u.subtype = check_type_aux(t->u.subtype, 1, 0, ret);
		break;

	case TYPE_RVALUE:
		t->u.subtype = check_type_aux(t->u.subtype, 1, 1, ret);
		break;

	case TYPE_PROC:
		if (obj) {
			error(ERROR_SERIOUS, "Object type expected");
		}

		t->u.subtype = check_type_aux(t->u.subtype, 1, 1, 1);
		if (t->v.next && t->v.next->v.next == NULL) {
			/* Check for '( void )' */
			type *s = t->v.next->u.subtype;
			if (s && s->id == TYPE_VOID) {
				break;
			}
		}

		t->v.next = check_type_aux(t->v.next, 1, 0, 0);
		break;

	case TYPE_PTR:
		t->u.subtype = check_type_aux(t->u.subtype, 0, 0, 0);
		break;

	case TYPE_DEFINED:
		t->v.next = check_type_aux(t->v.next, obj, c, ret);
		break;
	}

	return t;
}

/*
 * CHECK A TYPE
 *
 * This routine checks that the type t is a valid type for an object of
 * type id.  It returns an equivalent type.
 */
type *
check_type(type *t, int id)
{
	if (t == NULL) {
		return NULL;
	}

	switch (id) {
	case OBJ_EXP:
	case OBJ_EXTERN:
		t = check_type_aux(t, 1, 0, 0);
		break;

	case OBJ_CONST:
	case OBJ_FIELD:
		t = check_type_aux(t, 1, 1, 0);
		break;

	case OBJ_FUNC:
		if (t->id != TYPE_PROC) {
			error(ERROR_SERIOUS, "Function type expected");
		}

		t = check_type_aux(t, 0, 0, 0);
		break;

	case OBJ_TYPE:
	case OBJ_MACRO:
	case OBJ_STATEMENT:
		t = check_type_aux(t, 0, 0, 0);
		break;
	}

	return t;
}

