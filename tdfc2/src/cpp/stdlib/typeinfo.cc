/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "implement.h"
#include "interface.h"

#include <cstdio>
#include <cstring>
#include <typeinfo>

#include <shared/string.h>

using namespace std;

/*
 * Return true if the types represented by t and s are equal.
 */
static int
is_equal_type(TYPE_INFO *t, TYPE_INFO *s)
{
	int c;

	if (t == s) {
		return 1;
	}

	c = t->code;
	if (c != s->code) {
		return 0;
	}

	// Type categories match
	switch(c) {
	case RTTI_ptr:
	case RTTI_ref:
	case RTTI_ptr_mem:
	case RTTI_array:
	case RTTI_bitfield:
	case RTTI_func:
	case RTTI_c_func: {
		// Examine sub-types
		BASE_INFO *bt = t->base;
		BASE_INFO *bs = s->base;

		while (bt && bs) {
			if (bt->access != bs->access) {
				return 0;
			}

			if (bt->virt != bs->virt) {
				return 0;
			}

			t = bt->rtti;
			s = bs->rtti;
			if (!is_equal_type(t, s)) {
				return 0;
			}

			bt = bt->next;
			bs = bs->next;
		}

		if (bt || bs) {
			return 0;
		}

		return 1;
	}

	case RTTI_class:
	case RTTI_union:
	case RTTI_enum:
		// Examine type names
		if (streq(t->name, s->name)) {
			return 1;
		}
		break;

	default:
		// Built-in types have unique representative
		break;
	}

	return 0;
}

/*
 * Check for a base class
 *
 * This routine returns 1 if the type represented by s is a base class
 * of the type represented by t and 2 if the two types are actually
 * equal.
 */
static int
is_base_class(TYPE_INFO *t, TYPE_INFO *s)
{
	if (is_equal_type(t, s)) {
		return 2;
	}

	if (t->code == RTTI_class) {
		for (BASE_INFO *b = t->base; b; b = b->next) {
			// Check base classes
			if (is_base_class(b->rtti, s)) {
				return 1;
			}
		}
	}

	return 0;
}

/*
 * The following unique pointers are used in do_base_cast.
 */
/* XXX: these should probably be arranged to segfault if dereferenced */
static void *error_ptr = (void *) &error_ptr;
static void *null_ptr  = (void *) &null_ptr;

/*
 * Perform a base class conversion
 *
 * This routine converts the pointer p from the type represented by t
 * to the type represented by s.  The error pointer is returned for
 * ambiguous conversions while a keeps track of the base class access.
 */
static void *
do_base_cast(void *p, TYPE_INFO *t, TYPE_INFO *s, int &a)
{
	void *r = NULL;
	int acc = 0;

	if (is_equal_type(t, s)) {
		r = p;
	} else {
		// Check base classes
		for (BASE_INFO *b = t->base; b; b = b->next) {
			int c = b->access;
			void *q = p;

			if (q != null_ptr) {
				q = (void *) ((char *) p + b->off);
				if (b->virt) {
					q = *((void **) q);
				}
			}

			q = do_base_cast(q, b->rtti, s, c);
			if (!q) {
				continue;
			}

			if (r == NULL) {
				// First successful conversion
				r = q;
				acc = c;
			} else if (r == q) {
				// Select most accessible successful conversion
				if (c < acc) {
					acc = c;
				}
			} else {
				// Ambiguous conversion
				r = error_ptr;
				return r;
			}
		}
	}

	a += acc;
	return r;
}

/*
 * Perform an unambiguous base class conversion
 *
 * This routine is identical to do_base_cast except that it returns the
 * null pointer for ambiguous or inaccessible conversions.
 */
static void *
do_valid_base_cast(void *p, TYPE_INFO *t, TYPE_INFO *s)
{
	int acc = INFO_public;

	p = do_base_cast(p, t, s, acc);
	if (p == error_ptr || acc != INFO_public) {
		p = NULL;
	}

	return p;
}

/*
 * Perform a dynamic cast
 *
 * This routine is used to implement the dynamic cast construct.  p gives
 * a pointer to the virtual function table pointer for the construct
 * operand and s gives the type information for the target type.
 */
void *
__TCPPLUS_dynamic_cast(VTABLE **p, TYPE_INFO *s)
{
	TYPE_INFO *t;
	VTABLE *vptr;
	void *r;
	int c;

	r = NULL;
	vptr = *p;
	t = vptr->extra.rtti;

	c = is_base_class(t, s);
	if (c) {
		// Perform the base class conversion
		r = (void *) p;
		r = (void *) (((char *) r) + vptr->extra.off);
		if (c == 1) {
			r = do_valid_base_cast(r, t, s);
		}
	}

	return r;
}

/*
 * Perform an exception catch conversion
 *
 * This routine checks whether an exception of type t can be caught
 * by a handler of type s.  If so it applies any necessary conversions
 * to the exception value p and returns the value.  Otherwise the
 * null pointer is returned.  Note that any reference components will
 * have been removed from s.  cn is true if all the qualifiers in
 * a qualification conversion contain 'const'.  dpt keeps track of
 * the depth of pointer conversions.
 */
void *
__TCPPLUS_catch_cast(void *p, TYPE_INFO *t, TYPE_INFO *s, int cn, int dpt)
{
	int c;

	if (!p) {
		return NULL
	}

	if (is_equal_type(t, s)) {
		// Exact match
		return p;
	}

	c = t->code;
	if (c != s->code) {
		return NULL;
	}

	switch (c) {
	case RTTI_ptr:
	case RTTI_ref: {
		// Check for pointer conversions
		BASE_INFO *bt = t->base;
		BASE_INFO *bs = s->base;

		int at = bt->access;
		int as = bs->access;

		if (at == as ||(cn && !(at & ~as))) {
			// Qualifiers are alright
			t = bt->rtti;
			s = bs->rtti;

			if (dpt == 0) {
				if (s->code == RTTI_void && c == RTTI_ptr) {
					switch(t->code) {
					case RTTI_func:
					case RTTI_c_func:
						// Can't convert function to 'void *'
						break;

					default:
						// Can convert 't *' to 'void *'
						return p;
					}
				}

				switch (is_base_class(t, s)) {
				case 2:
					// Exact base class conversion
					return p;

				case 1:
					// Base class conversion
					void *q = *((void **) p);
					if (q == NULL) {
						q = null_ptr;
					}

					void *r = do_valid_base_cast(q, t, s);
					if (r) {
						static void *buf = NULL;
						if (q == r) {
							return p;
						}

						buf = r;
						return (void *) &buf;
					}
					break;
				}
			}

			if (!(at & INFO_const)) {
				cn = 0;
			}

			p = __TCPPLUS_catch_cast(p, t, s, cn, dpt + 1);
			return p;
		}

		break;
	}

	case RTTI_ptr_mem: {
		// Check for pointer to member conversion
		BASE_INFO *bt = t->base;
		BASE_INFO *bs = s->base;

		if (is_equal_type(bt->rtti, bs->rtti)) {
			// Classes match
			bt = bt->next;
			bs = bs->next;

			int at = bt->access;
			int as = bs->access;

			if (at == as ||(cn && !(at & ~as))) {
				// Qualifiers are alright
				t = bt->rtti;
				s = bs->rtti;

				if (!(at & INFO_const)) {
					cn = 0;
				}

				p = __TCPPLUS_catch_cast(p, t, s, cn, dpt + 1);
				return p;
			}
		}

		break;
	}

	case RTTI_class:
		// Check for base class conversions
		if (dpt == 0) {
			switch (is_base_class(t, s)) {
			case 2:
				return p;

			case 1:
				return do_valid_base_cast(p, t, s);
			}
		}

		break;
	}

	return NULL;
}

/*
 * Print run-time type information
 *
 * This routine prints the run-time type information t with access a
 * and virtual qualifier v at an indentation of i.
 */
static void
print_type_info(TYPE_INFO *t, char *a, char *v, int i)
{
	for (int j = 0; j < i; j++) {
		fputc(' ', stdout);
	}

	printf("%s%s%s", a, v, t->name);

	BASE_INFO *b = t->base;
	if (b && t->code == RTTI_class) {
		printf(" = {\n");

		for ( ; b; b = b->next) {
			switch(b->access) {
			case INFO_public:    a = "public ";    break;
			case INFO_protected: a = "protected "; break;
			case INFO_private:   a = "private ";   break;
			}

			v = const_cast <char *> (b->virt ? "virtual " : "");
			print_type_info(b->rtti, a, v, i + 4);
		}

		for (int j = 0; j < i; j++) {
			fputc(' ', stdout);
		}

		fputc('}', stdout);
	}

	printf(" ;\n");
	return;
}

/*
 * Print run-time type information for an object
 *
 * This routine prints the run-time type information for an object given
 * a pointer to its virtual function table.
 */
void
__TCPPLUS_type_info(VTABLE *p)
{
	if (p) {
		TYPE_INFO *t = p->extra.rtti;
		print_type_info(t, "", "", 0);
	}

	return;
}

/*
 * Member functions for type_info class
 *
 * These routines give the member functions for the type_info class.  They
 * exploit the layout equivalent of a type_info and a TYPE_INFO.
 */
type_info::type_info(const type_info &rhs)
{
	__code = rhs.__code;
	__name = rhs.__name;
	__base = rhs.__base;

	return;
}

type_info
&type_info::operator = (const type_info &rhs)
{
	__code = rhs.__code;
	__name = rhs.__name;
	__base = rhs.__base;

	return *this;
}

type_info::~type_info()
{
	return;
}

bool
type_info::operator == (const type_info &rhs) const
{
	return is_equal_type((TYPE_INFO *) this, (TYPE_INFO *) &rhs);
}

bool
type_info::operator != (const type_info &rhs) const
{
	return *this != rhs;
}

bool
type_info::before(const type_info &rhs) const
{
	return strcmp(__name, rhs.__name) < 0;
}

const char *
type_info::name() const
{
	return __name;
}

