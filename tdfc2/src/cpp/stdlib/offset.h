/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef OFFSET_INCLUDED
#define OFFSET_INCLUDED


/*
    SPECIFICATION OF OFFSET INTERFACE

    These tokens describe the basic operations on offsets.  They are
    defined in ptr_mem.p.
*/

#pragma token TYPE OFFSET # ~cpp.offset.type
#pragma token PROC ( EXP : OFFSET : ) EXP : int : offset # ~cpp.offset.div
#pragma interface OFFSET offset


#endif
