/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef STAB_CONF_INCLUDED
#define STAB_CONF_INCLUDED

typedef long OUTPUT_REC ;
typedef diag_descriptor diag_global ;

#define INSPECT_FILENAME( x )	stab_collect_files ( x )
#define NEW_DIAG_GLOBAL( x )	( x )
#define OUTPUT_DIAG_TAGS()	stab_tagdefs ()
#define OUTPUT_GLOBALS_TAB()	stab_typedefs ()

#endif /* STAB_CONF_INCLUDED */
