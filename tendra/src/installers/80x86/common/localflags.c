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


/* 80x86/localflags.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: localflags.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1997/04/17  11:55:50  pwe
 * dwarf2 improvements
 *
 * Revision 1.4  1997/03/20  16:23:57  pwe
 * dwarf2
 *
 * Revision 1.3  1995/09/29  16:17:58  pwe
 * gcc_compatible default on Linux
 *
 * Revision 1.2  1995/01/30  12:56:30  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:36:14  jmf
 * Initial revision
 *
**********************************************************************/

#include "config.h"
#include "common_types.h"

#include "localflags.h"

/* VARIABLES */
/* All variables initialised */

int is80486;		/* compile for 80486 */
int is80586;		/* compile for 80586 */
int flush_before_tell = 0;	/* to cure a bug in DOS system */
int always_use_frame;
int gcc_compatible = GCC_STRUCTS;
int module_has_setjmp = 0;
int stack_aligned_8byte = 0;
int permit_8byte_align = 1;
int useful_double = 0;
int keep_short = 0;	/* init by cproc */

weak_cell * weak_list = (weak_cell*)0;

