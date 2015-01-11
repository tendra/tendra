/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_SEARCH_INCLUDED
#define __HACKED_SEARCH_INCLUDED

#ifdef __BUILDING_LIBS
#define twalk		__wrong_twalk
#endif

#include_next <search.h>

#ifdef __BUILDING_LIBS
#undef twalk
#endif

#endif
