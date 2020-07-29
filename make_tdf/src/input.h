/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef INPUT_INCLUDED
#define INPUT_INCLUDED


/*
    INPUT CONSTRUCTION DECLARATIONS
*/

extern SORT find_sort(string, int);
extern void compound_sort(SORT, string, unsigned, int);
extern void basic_sort(SORT, unsigned, unsigned, LIST(CONSTRUCT));
extern PARAMETER find_param(CONSTRUCT, unsigned);
extern CONSTRUCT make_construct(string, unsigned, SORT, LIST(PARAMETER));
extern CONSTRUCT find_construct(SORT, string);
extern LIST(LINKAGE) foreign_sorts(void);
extern LIST(SORT)check_sorts(void);
extern void mark_construct(CONSTRUCT, int);
extern void mark_sort(SORT, int);
extern void mark_all_sorts(int);
extern void set_special(SORT, string, unsigned);
extern CONSTRUCT get_special(SORT, unsigned);
extern string ends_in(string, string);
extern void builtin_sorts(void);
extern string to_capitals(string);


/*
    KINDS OF CONSTRUCT
*/

#define KIND_simple		((unsigned)0)
#define KIND_token		((unsigned)1)
#define KIND_cond		((unsigned)2)
#define KIND_edge		((unsigned)3)
#define KIND_foreign		((unsigned)4)
#define KIND_special		((unsigned)5)
#define KIND_dummy		((unsigned)6)


#endif
