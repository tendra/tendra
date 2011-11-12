/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
**  version.c
**  ---------
**
**    "libtdf.a" always contains a version number and
**    release identier.  These are defined to be global
**    strings, and their definitions are found in this file.
**
**    It is always compiled as part of the build for
**    "libtdf.a", and so "libtdf.a" is never empty.
*/

#ifndef VERSION
#define VERSION "libtdf version 4.17"
#endif /* !defined (VERSION) */

#ifndef RELEASE
#define RELEASE "LOCAL"
#endif /* !defined (RELEASE) */

char __libtdf_versionid [] = VERSION;
char __libtdf_releaseid [] = RELEASE;
