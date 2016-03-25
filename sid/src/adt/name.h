/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * name.h - Name ADT.
 *
 * See the file "name.c" for more information.
 */

#ifndef H_NAME
#define H_NAME

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>

typedef struct NameT {
    bool			clash;
    bool			used;
    bool			labelled;
    unsigned			label;
} NameT;

NameT *		name_create(void);
bool		name_test_and_set_clash(NameT *);
void		name_reset_clash(NameT *);
bool		name_is_used(NameT *);
void		name_used(NameT *);
void		name_not_used(NameT *);
unsigned		name_get_label(NameT *);
void		name_set_label(NameT *, unsigned);
void		name_reset_label(NameT *);
bool		name_has_label(NameT *);

#endif /* !defined (H_NAME) */
