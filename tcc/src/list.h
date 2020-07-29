/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef LIST_H
#define LIST_H


/*
 * TYPE REPRESENTING A LIST OF STRINGS
 *
 * A list consists of a list of strings linked via their next field.
 */
typedef struct list_t {
	const char *s;
	struct list_t *next;
} list;


list *add_list(list *, list *);
list *add_item(list *, const char *);
list *insert_item(const char *, list *);
list *make_list(const char *);
void free_list(list *);


#endif /* LIST_H */
