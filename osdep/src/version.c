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
**    "libtsl.a" always contains a version number and
**    release identier.  These are defined to be global
**    strings, and their definitions are found in this file.
**
**    It is always compiled as part of the build for
**    "libtsl.a", and so "libtsl.a" is never empty.
*/

#ifndef VERSION
#define VERSION "libtsl version 4.17"
#endif /* !defined (VERSION) */

#ifndef RELEASE
#define RELEASE "LOCAL"
#endif /* !defined (RELEASE) */

char __libtsl_versionid [] = VERSION;
char __libtsl_releaseid [] = RELEASE;
