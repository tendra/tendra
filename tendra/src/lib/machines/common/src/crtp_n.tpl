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


/*
    Define a structure to implement a list of function pointers.
*/

Struct s (prc:proc, ptr:pointer(AL));
Al_tagdef AL = alignment(s) ;


/*
    Create a variable to hold a list of function pointers, with
    external linkage.
*/

Var __PROM_init_list: Ptr s;


/*
    Create a dummy variable which uses the 'inital_value' contruct to force
    evaluation of the inlined procedure at "dynamic initialisation" time.
    The inlined procedure calls each of the functions in the pre-formed list
    of functions, '__PROM_init_list', which perform assignments for variable
    initialisations (for PROMs).
*/

Let x : top = initial_value (
{
    ? { *? ((* __PROM_init_list) != make_null_ptr(AL));
	Rep ()
	{
	    (*(proc) ((* __PROM_init_list) *+. .prc)) [top] ();
	    __PROM_init_list = (*(pointer(AL)) ((* __PROM_init_list) *+. .ptr));
	    *? ((* __PROM_init_list) == make_null_ptr(AL))
	}
      |
	make_top
    };
});

Keep (__PROM_init_list)
