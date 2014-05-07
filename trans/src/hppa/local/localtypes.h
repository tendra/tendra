/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCALTYPES_INCLUDED
#define LOCALTYPES_INCLUDED

#include <local/exptypes.h>

#include <construct/installtypes.h>

typedef struct {
    long ashsize;
    long ashalign;
} ash;

extern ash ashof(shape);


typedef struct {
    bool is_special;
    exp special_exp;
} speci;


#endif /* LOCALTYPES_INCLUDED */
