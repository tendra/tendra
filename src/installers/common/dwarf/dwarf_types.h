/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
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

typedef char H_dwarf_lab[DWARF_LAB_LEN+1]; /* reserve 1 flag byte */

typedef H_dwarf_lab dwarf_type_label; /* used to fill in type refs without
				       making sibling stuff too complex */


typedef struct 
{
  H_dwarf_lab	beg;
  H_dwarf_lab	end;
} dwarf_label;

typedef struct 
{
  diag_descriptor	*desc;
  dwarf_label		lab;
} dwarf_global;

#define OUT_FLAG(x) ((x)[DWARF_LAB_LEN])
#define LAB2CHAR(x) (&((x)[0]))
#endif
