/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


#ifndef COMMON_INCLUDED
#define COMMON_INCLUDED


/*
    DECLARATIONS FOR TYPE MANIPULATION ROUTINES
*/

extern ALGEBRA_DEFN *algebra ;
extern void new_algebra PROTO_S ( ( void ) ) ;
extern ALGEBRA_DEFN *find_algebra PROTO_S ( ( char * ) ) ;
extern TYPE_P find_type PROTO_S ( ( ALGEBRA_DEFN *, char * ) ) ;
extern TYPE_P register_type PROTO_S ( ( TYPE_P ) ) ;
extern int is_identity_type PROTO_S ( ( TYPE_P ) ) ;
extern TYPE_P compound_type PROTO_S ( ( unsigned, TYPE_P, int ) ) ;
extern void check_types PROTO_S ( ( void ) ) ;
extern void import_type PROTO_S ( ( char *, char * ) ) ;
extern void import_algebra PROTO_S ( ( char * ) ) ;
extern int size_type PROTO_S ( ( TYPE_P, int ) ) ;
extern char *name_type PROTO_S ( ( TYPE_P ) ) ;
extern char *name_aux_type PROTO_S ( ( TYPE_P ) ) ;
extern int is_complex_type PROTO_S ( ( TYPE_P ) ) ;


/*
    MACROS FOR BASIC CLASS SIZES

    These macros give the sizes of the basic types.
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
    MAXIMUM DEPTH OF TYPE CONSTRUCTORS

    This macro is used to limit the level of type constructors which can
    be used.  In particular, it is used in the detection of cyclic types.
*/

#define MAX_TYPE_DEPTH	1000


#endif
