/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef COMMON_INCLUDED
#define COMMON_INCLUDED

extern ALGEBRA_DEFN *algebra;
extern void new_algebra(void);
extern ALGEBRA_DEFN *find_algebra(char *);
extern TYPE_P find_type(ALGEBRA_DEFN *, char *);
extern TYPE_P register_type(TYPE_P);
extern int is_identity_type(TYPE_P);
extern TYPE_P compound_type(unsigned, TYPE_P, int);
extern void check_types(void);
extern void import_type(char *, char *);
extern void import_algebra(char *);
extern int size_type(TYPE_P, int);
extern char *name_type(TYPE_P);
extern char *name_aux_type(TYPE_P);
extern int is_complex_type(TYPE_P);


/*
 * These constants give the sizes of the basic types.
 */

#define SIZE_PRIM	1
#define SIZE_ENUM	1
#define SIZE_UNION	1
#define SIZE_PTR	1
#define SIZE_LIST	1
#define SIZE_STACK	1
#define SIZE_VEC	3
#define SIZE_VEC_PTR	2


/*
 * MAXIMUM DEPTH OF TYPE CONSTRUCTORS
 *
 * This macro is used to limit the level of type constructors which can
 * be used.  In particular, it is used in the detection of cyclic types.
 */

#define MAX_TYPE_DEPTH	1000


#endif
