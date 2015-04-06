/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <shared/error.h>
#include <shared/string.h>

#define calculus_IO_ROUTINES
#include "calculus.h"
#include "common.h"
#include "pretty.h"

/*
 * AUTOMATICALLY GENERATED PRETTY PRINTING ROUTINES
 *
 * The main pretty printing routines are automatically generated.  The
 * various macros are used to customise these routines.
 */

#define OUTPUT_int(A, B)	fprintf((A), "%d",(B))
#define OUTPUT_number(A, B)	fprintf((A), "%lu",(B))
#define OUTPUT_string(A, B)	fprintf((A), "\"%s\"",(B))

#ifdef NDEBUG
#define BAD_PRINT_OP 0
#define PRINT_alg(A, B, C, D)            assert(BAD_PRINT_OP)
#define PRINT_list_ptr_en(A, B, C, D)    assert(BAD_PRINT_OP)
#define PRINT_list_ptr_ident(A, B, C, D) assert(BAD_PRINT_OP)
#define PRINT_list_ptr_prim(A, B, C, D)  assert(BAD_PRINT_OP)
#define PRINT_list_ptr_str(A, B, C, D)   assert(BAD_PRINT_OP)
#define PRINT_list_ptr_un(A, B, C, D)    assert(BAD_PRINT_OP)
#define PRINT_ptr_int(A, B, C, D)        assert(BAD_PRINT_OP)
#define PRINT_ptr_number(A, B, C, D)     assert(BAD_PRINT_OP)
#define PRINT_ptr_ptr_cid(A, B, C, D)    assert(BAD_PRINT_OP)
#define PRINT_ptr_ptr_type(A, B, C, D)   assert(BAD_PRINT_OP)
#define PRINT_ptr_string(A, B, C, D)     assert(BAD_PRINT_OP)
#endif

#include "print_def.h"

/*
 * PRETTY PRINT AN ALGEBRA
 *
 * This routine pretty prints the entire algebra type list into the
 * file named nm.
 */
void
pretty_file(char *nm)
{
	int old_indent_step;
	int old_ptr_depth;
	int old_list_expand;
	FILE *f;

	/* Open file */
	if (streq(nm, ".")) {
		f = stdout;
	} else {
		f = fopen(nm, "w");
		if (f == NULL) {
			error(ERR_SERIOUS, "Can't open output file, '%s'", nm);
			return;
		}
	}

	/* Save values */
	old_indent_step = print_indent_step;
	old_ptr_depth = print_ptr_depth;
	old_list_expand = print_list_expand;
	print_indent_step = 2;
	print_ptr_depth = 10000;
	print_list_expand = 1;

	/* Print the algebra */
	PRINT_string(f, algebra->name, "name", 0);
	PRINT_int(f, algebra->major_no, "major_no", 0);
	PRINT_int(f, algebra->minor_no, "minor_no", 0);
	fputc('\n', f);
	PRINT_list_ptr_type(f, algebra->types, "types", 0);

	/* Restore values */
	clear_calculus_alias();
	print_indent_step = old_indent_step;
	print_ptr_depth = old_ptr_depth;
	print_list_expand = old_list_expand;

	/* Close file */
	if (f != stdout) {
		fclose(f);
	}
}

