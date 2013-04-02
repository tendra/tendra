/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <construct/shapemacs.h>
#include <construct/flags.h>

#include "expmacs.h"
#include "regable.h"


/*
    DOES A PROCEDURE RETURN THE GIVEN SHAPE IN A REGISTER?
*/

int 
reg_result ( shape sha )
{
    if ( valregable ( sha ) ) return 1;
    if ( is_floating ( name ( sha ) ) ) {
	if ( use_long_double && shape_size ( sha ) > 64 ) return 0;
	return 1;
    }
    return 0;
}
