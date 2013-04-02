/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
  version.h

  This file contains the current version number of the alpha installer
*/

#ifndef VERSION_H
#define VERSION_H

/* installer version */
#define target_version 2
#define target_revision	4
#define target_patchlevel 11

#ifdef RELEASE
#define RELEASE_INFO RELEASE
#else
#define RELEASE_INFO "private"
#endif



#endif

