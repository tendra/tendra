/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:48 $
$Revision: 1.1.1.1 $
$Log: dwarf_types.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/08/14  14:30:26  pwe
 * transferred from DJCH
 *
**********************************************************************/

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
