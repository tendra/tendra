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


#ifndef HIGH_INCLUDED
#define HIGH_INCLUDED


/*
    TYPE REPRESENTING HIGH LEVEL SORTS

    A high level sort consists of a name and a dummy sort number, id.
    These are associated with a sort number, giving the result sort,
    and an array of sort numbers, giving the argument sorts.
*/

typedef struct {
    char *name ;
    sortname id ;
    sortname res ;
    int no_args ;
    sortname *args ;
} high_sort ;


/*
    STARTING POINT FOR HIGH LEVEL SORTS

    To distinguish them from the normal TDF sorts, high level sorts
    are assigned sort numbers starting at high_start.  The macro
    is_high is used to test whether a sort number corresponds to a
    high level sort, and high_no is used to transform a high level
    sort number into an offset in the table high_sorts.
*/

#define high_start	100
#define is_high( s )	( ( s ) >= high_start )
#define high_no( n )	( ( int ) ( ( n ) - high_start ) )


/*
    ROUTINES FOR MANIPULATING HIGH LEVEL SORTS
*/

extern high_sort *high_sorts ;
extern int crt_high_sort ;
extern high_sort *new_high_sort PROTO_S ( ( high_sort * ) ) ;
extern void set_high_sort PROTO_S ( ( char *, tok_info * ) ) ;
extern high_sort *unique_high_sort PROTO_S ( ( high_sort * ) ) ;
extern sortname find_high_sort PROTO_S ( ( char * ) ) ;
extern char *find_decode_string PROTO_S ( ( high_sort * ) ) ;
extern char *find_sortname PROTO_S ( ( char *, sortname * ) ) ;
#define sprint_high_sort( p, s )\
	( void ) sprintf ( p, "T%d#", high_no ( s ) )


#endif
