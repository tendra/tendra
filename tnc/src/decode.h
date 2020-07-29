/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef DECODE_H
#define DECODE_H


/*
    SIMPLE DECODING ROUTINES
*/

long fetch_extn(int);
long tdf_int(void);
node *de_node(char *);
construct *de_token(node *, sortname);
node *de_var_sort(long);

#define tdf_bool()		fetch(1)
#define de_list_start()\
	if (fetch(1)) input_error("Illegal LIST value")


#endif /* DECODE_H */
