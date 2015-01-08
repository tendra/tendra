/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * A structure to implement a list of function pointers.
 */
Struct s (
	prc : proc,
	ptr : pointer(AL)
);

Al_tagdef AL = alignment(s);

/*
 * A variable to hold a list of function pointers, with external linkage.
 */
Var __PROM_init_list: Ptr s;

/*
 * Create a dummy variable which uses the 'inital_value' contruct to force
 * evaluation of the inlined procedure at "dynamic initialisation" time.
 *
 * The inlined procedure calls each of the functions in the pre-formed list
 * of functions, '__PROM_init_list', which perform assignments for variable
 * initialisations (for PROMs).
 */
Let x : top = initial_value(
	{
		? {
			*? ((* __PROM_init_list) != make_null_ptr(AL));
			Rep()
			{
				(* (proc) ((* __PROM_init_list) *+. .prc)) [top] ();
				__PROM_init_list = (* (pointer(AL)) ((* __PROM_init_list) *+. .ptr));
				*? ((* __PROM_init_list) == make_null_ptr(AL))
			}
		|
			make_top
		};
	}
);

Keep ( __PROM_init_list)

