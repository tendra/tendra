/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef ALIGNMENT_H
#define ALIGNMENT_H


/*
    ROUTINES FOR MANIPULATING ALIGNMENTS AND OFFSETS
*/

extern node *al_top;
extern node *al_code;
extern node *al_frame;
extern node *al_alloca;
extern node *al_var_param;

void init_alignments(void);
node *al_shape(node *);
void al_equals(node *, node *);
void al_includes(node *, node *);
node *al_union(node *, node *);
node *offset_from(node *);
node *offset_to(node *);
node *ptr_to(node *);

#endif /* ALIGNMENT_H */
