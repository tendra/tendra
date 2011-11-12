/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef ACCESS_INCLUDED
#define ACCESS_INCLUDED


/*
    TYPE REPRESENTING LIST OF PENDING ACCESS CHECKS

    This type is used to represent a list of pending access checks.  These
    fall into two categories - member accesses and base class accesses.
*/

typedef struct {
	LIST(IDENTIFIER) ids;
	LIST(GRAPH) bases;
	LIST(int) info;
	int pending;
	int inherit;
} ACCESS_LIST;


/*
    ACCESS DECLARATIONS

    The routines in this module are concerned with class member access.
*/

extern IDENTIFIER access_decl(IDENTIFIER);
extern void friend_function(CLASS_TYPE, IDENTIFIER, int);
extern void friend_class(CLASS_TYPE, IDENTIFIER, int);
extern DECL_SPEC join_access(DECL_SPEC, DECL_SPEC);
extern void check_access(IDENTIFIER, DECL_SPEC);
extern void check_base_access(GRAPH);
extern void immediate_access(IDENTIFIER, IDENTIFIER);
extern int clear_access(IDENTIFIER, ACCESS_LIST *);
extern int report_access(IDENTIFIER);
extern void adjust_access(IDENTIFIER, DECL_SPEC, int);
extern void free_access(ACCESS_LIST *);
extern void save_access(ACCESS_LIST *);
extern int restore_access(IDENTIFIER, ACCESS_LIST *);
extern ACCESS_LIST crt_access_list;
extern int do_access_checks;
extern DECL_SPEC crt_access;
extern DECL_SPEC prev_access;
extern int have_access_decl;


/*
    SECONDARY ACCESS MACROS

    These macros are used for converting between primary and secondary
    access values.
*/

#define shadow_access(A)	(((A) & dspec_access) << 2)
#define unshadow_access(A)	(((A) & dspec_access2) >> 2)


#endif
