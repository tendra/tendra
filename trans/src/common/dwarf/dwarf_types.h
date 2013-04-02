/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef dwarf_types_key
#define dwarf_types_key

#define DWARF_LAB_LEN	15

typedef char H_dwarf_lab[DWARF_LAB_LEN + 1]; /* reserve 1 flag byte */

typedef H_dwarf_lab dwarf_type_label; /* used to fill in type refs without
				       making sibling stuff too complex */


typedef struct {
	H_dwarf_lab	beg;
	H_dwarf_lab	end;
} dwarf_label;

typedef struct {
	diag_descriptor	*desc;
	dwarf_label	lab;
} dwarf_global;

#define OUT_FLAG(x)	((x)[DWARF_LAB_LEN])
#define LAB2CHAR(x)	(&((x)[0]))
#endif
