/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef NODE_H
#define NODE_H


/*
    PROCEDURES FOR MANIPULATING NODES
*/

extern bool dont_check;

node *new_node(void);
void free_node(node *);
node *completion(node *);
bool eq_node(node *, node *);


/*
    PROCEDURES FOR MANIPULATING CONSTRUCTS
*/

extern char *local_prefix;

construct *new_construct(void);
construct *make_construct(sortname);
void copy_construct(construct *);
void free_construct(construct **);
void set_token_sort(construct *, sortname, char *, node *);
void set_tag_type(construct *, int);
bool is_local_name(char *);
char *skip_text(char *);



/*
    MACRO FOR RENUMBERING TOKEN CONSTRUCTS
*/

#define adjust_token(X)\
    if ((X) ->encoding == -1) {\
	(X) ->encoding = (sort_count[SORT_token]) ++ ;\
    }


#endif /* NODE_H */
