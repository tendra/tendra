/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef BINDING_INCLUDED
#define BINDING_INCLUDED


/*
 * BASIC BINDING ROUTINES
 *
 * This file contains the basic routines for manipulating tokens, tags
 * and similar objects.
 */

extern object *new_object(long);
extern binding *new_binding_table(void);
extern void free_binding_table(binding *);
extern void set_binding_size(binding *, long, long);
extern void set_binding(binding *, long, long, object *);
extern void complete_binding(binding *);
extern object *find_binding(binding *, long, long);
extern void out_object(long, object *, long);
extern char *object_name(long, long);


#endif
