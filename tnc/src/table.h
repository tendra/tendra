/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef TABLE_H
#define TABLE_H


#define hash_size 31


/*
    TABLES OF CONSTRUCTS
*/

extern construct **cons_table;
extern construct **var_table;
extern construct **cons_hash_tables;


/*
    TABLES OF SORT INFORMATION
*/

typedef node *(*decode_func)(void);
typedef node *(*read_func)(long);
extern long *sort_count;
extern char *sort_letters;
extern int *sort_encoding;
extern int *sort_extension;
extern long *sort_tokens;
extern long *sort_conds;
extern long *sort_removed;
extern decode_func *sort_decode;
extern read_func *sort_read;


/*
    SPECIAL CONSTRUCTS
*/

extern construct bytestream_cons;
extern construct false_cons;
extern construct optional_cons;
extern construct string_cons;
extern construct token_cons;
extern construct true_cons;
extern construct unknown_cons;
extern construct exp_shape;
extern construct shape_of;


/*
    OUTPUT FLAGS
*/

extern bool show_tokdecs;
extern bool show_tokdefs;
extern bool show_aldecs;
extern bool show_aldefs;
extern bool show_tagdecs;
extern bool show_tagdefs;


/*
    TABLE MANIPULATION ROUTINES
*/

void init_tables(void);
construct *add_to_cons_hash(construct *, sortname);
construct *search_cons_hash(char *, sortname);
construct *add_to_var_hash(construct *, sortname);
construct *search_var_hash(char *, sortname);
void remove_var_hash(char *, sortname);

extern construct *removals;


/*
    TABLE UTILITY ROUTINES
*/

extern bool order_names;

typedef void(*apply_func)(construct *);
char *sort_name(sortname);
void sort_table(construct **, sortname);
void sort_all(void);
void apply_to_all(apply_func, sortname);


/*
    AUXILLIARY TABLE ROUTINES
*/

void new_sort(sortname, int);
void new_cons(char *, sortname, int, char *);


/*
    MACRO FOR ACCESSING CONSTRUCTS
*/

#define cons_no(X, Y)		(cons_table[(X)] + (Y))


#endif /* TABLE_H */
