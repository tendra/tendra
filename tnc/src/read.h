/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef READ_H
#define READ_H


/*
    BASIC READING ROUTINE
*/

extern bool allow_multibyte;
extern bool intro_visible;

node *read_node(char *);
node *read_var_sort(sortname);
void read_token(node *, sortname);
void read_seq_node(node *);

#define read_sequence(X, Y)		read_seq_node((X))
#define read_make_signed_nat(X, Y)	(X) ->son = read_node("j")


#endif /* READ_H */
