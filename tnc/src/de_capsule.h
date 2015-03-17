/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef DE_CAPSULE_H
#define DE_CAPSULE_H


/*
    DECODING FLAGS
*/

extern bool in_skip_pass;
extern bool extract_tokdecs;


/*
    BINDING ROUTINES
*/

extern binding *crt_binding;
extern long al_tag_var, tag_var, tok_var;

construct *find_binding(binding *, long, long);


/*
    HIGH LEVEL DECODING ROUTINES
*/

void de_capsule(void);
void de_library(void);


#endif /* DE_CAPSULE_H */
