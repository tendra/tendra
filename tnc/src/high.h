/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef HIGH_H
#define HIGH_H


/*
    TYPE REPRESENTING HIGH LEVEL SORTS

    A high level sort consists of a name and a dummy sort number, id.
    These are associated with a sort number, giving the result sort,
    and an array of sort numbers, giving the argument sorts.
*/

typedef struct {
	char *name;
	sortname id;
	sortname res;
	int no_args;
	sortname *args;
} high_sort;


/*
    STARTING POINT FOR HIGH LEVEL SORTS

    To distinguish them from the normal TDF sorts, high level sorts
    are assigned sort numbers starting at high_start.  The macro
    is_high is used to test whether a sort number corresponds to a
    high level sort, and high_no is used to transform a high level
    sort number into an offset in the table high_sorts.
*/

#define high_start	100
#define is_high(s)	((s) >= high_start)
#define high_no(n)	((int)((n) - high_start))


/*
    ROUTINES FOR MANIPULATING HIGH LEVEL SORTS
*/

extern high_sort *high_sorts;
extern int crt_high_sort;

high_sort *new_high_sort(high_sort *);
void set_high_sort(char *, tok_info *);
high_sort *unique_high_sort(high_sort *);
sortname find_high_sort(char *);
char *find_decode_string(high_sort *);
char *find_sortname(char *, sortname *);

#define sprint_high_sort(p, s)\
	(void)sprintf(p, "T%d#", high_no(s))


#endif /* HIGH_H */
