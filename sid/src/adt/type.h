/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * type.h - Type ADT.
 *
 * See the file "type.c" for more information.
 */

#ifndef H_TYPE
#define H_TYPE

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>

/*
 * Types are stored in an EntryT whose union holds a TypeT.
 */
typedef struct TypeT {
	/*
	 * A type contains the assignment code defined in the %assignment%,
	 * %param-assignment% and %result-assignment% sections of the action file.
	 * The exact type should depend on the output language, e.g. for C, the
	 * void * will be cast to a CCodeT *.
	 */
    void *			assign_code;
    void *			param_assign_code;
    void *			result_assign_code;

	/*
	 * If a type is not used in the grammar, the .ignored field is set true.
	 * However, an ignored type may be used in places which are themselves
	 * ignored, such as terminal extraction or production definitions.
	 */
	bool			ignored;
} TypeT;

TypeT *		type_create(bool ignored);
void *		type_get_assign_code(TypeT *);
void		type_set_assign_code(TypeT *, void *);
void *		type_get_param_assign_code(TypeT *);
void		type_set_param_assign_code(TypeT *, void *);
void *		type_get_result_assign_code(TypeT *);
void		type_set_result_assign_code(TypeT *, void *);
bool		type_get_ignored(TypeT *);

#endif /* !defined (H_TYPE) */
