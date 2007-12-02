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


/*** solve-cycles.h --- Include all header files in the TDF directory.
 *
 ** Author: Steve Folkes <smf@rivers.dra.hmg.gb>
 *
 *** Commentary:
 *
 * This file is an attempt to get around the structure mismatch errors that
 * "tcc" gives out when linking files together.
 *
 *** Change Log:
 * $Log: solve-cycles.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:20  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/09/22  08:39:35  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
**/

#include "capsule.h"
#include "debug.h"
#include "library.h"
#include "map-entry.h"
#include "map-table.h"
#include "name-entry.h"
#include "name-key.h"
#include "name-table.h"
#include "shape-entry.h"
#include "shape-table.h"
#include "tdf-read.h"
#include "tdf-write.h"
#include "tdf.h"
#include "unit-entry.h"
#include "unit-table.h"
