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


#ifndef SUFFIX_INCLUDED
#define SUFFIX_INCLUDED


/*
    FILE PREFIXES AND SUFFIXES

    These macros give the prefixes and suffixes for the various output
    files.
*/

#define MAIN_PREFIX	algebra->name
#define READ_PREFIX	"read"
#define WRITE_PREFIX	"write"
#define PRINT_PREFIX	"print"
#define IGNORE_PREFIX	"ignore"
#define ASSERT_PREFIX	"assert"
#define SWITCH_PREFIX	"switch"

#define MAIN_SUFFIX	".h"
#define OPS_SUFFIX	"_ops.h"
#define MAP_SUFFIX	"_map.h"
#define HDR_SUFFIX	"_hdr.h"
#define DEF_SUFFIX	"_def.h"
#define SED_SUFFIX	".sed"


#endif
