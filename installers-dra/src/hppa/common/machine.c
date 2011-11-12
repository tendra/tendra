/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
$Log: machine.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:11:50  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.1  1995/09/15  12:41:54  wfs
 * "regable.h" included.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  09:50:48  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  09:50:48  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:27:11  16:27:11  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:18:07  11:18:07  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:27:54  15:27:54  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:11:34  13:11:34  wfs (William Simmonds)
 * Initial revision
 * 
*/


#define HPPATRANS_CODE
#include "config.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "regable.h"

/*
    DOES A PROCEDURE RETURN THE GIVEN SHAPE IN A REGISTER?
*/

int
reg_result(shape sha)
{
    if ( valregable ( sha ) ) return 1;
    if ( is_floating ( name ( sha ) ) ) {
#if use_long_double
	if ( shape_size ( sha ) > 64 ) return 0;
#endif
	return 1;
    }
    return 0;
}


/*
    NAME PREFIXES
*/

char *local_prefix = "" ;
char *name_prefix = "" ;
