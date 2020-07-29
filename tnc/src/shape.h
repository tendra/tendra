/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef SHAPE_H
#define SHAPE_H


/*
    BASIC SHAPE CONSTRUCTION ROUTINES
*/

extern node *sh_bottom;
extern node *sh_proc;
extern node *sh_top;

node *sh_bitfield(node *);
node *sh_compound(node *);
node *sh_floating(node *);
node *sh_integer(node *);
node *sh_nof(node *, node *);
node *sh_offset(node *, node *);
node *sh_pointer(node *);
void init_shapes(void);
node *string_length(node *);
node *copy_node(node *);


/*
    BASIC SHAPE CHECKING ROUTINES
*/

node *check_shapes(node *, node *, int);
node *lub(node *, node *);
node *check1(int, node *);
node *check2(int, node *, node *);
node *checkn(int, node *, int);
node *normalize(node *);


/*
    TOKEN EXPANSION ROUTINES
*/

node *expand_tok(node *);
node *expand_fully(node *);
node *set_token_args(construct **, node *, int);
void expand_all(void);


#endif /* SHAPE_H */
