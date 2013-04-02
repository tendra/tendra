/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef SAVE_INCLUDED
#define SAVE_INCLUDED


/*
    SPEC VERSION NUMBER

    These macros give the major and minor version numbers for the spec
    files.  The minor number is increased for upwardly compatible changes
    and the major number for incompatible changes.
*/

#define SPEC_major	((unsigned long)(SPEC_VERSION / 100))
#define SPEC_minor	((unsigned long)(SPEC_VERSION % 100))


/*
    SPEC OUTPUT DECLARATIONS

    The routines in this module are concerned with spec writing.
*/

extern void begin_spec(void);
extern void end_spec(void);
extern BITSTREAM *save_id(BITSTREAM *, IDENTIFIER, NAMESPACE);
extern BITSTREAM *save_end(BITSTREAM *, NAMESPACE);
extern BITSTREAM *spec_unit;
extern int output_spec;


#endif
