/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */
    
/*
    TRANSLATIONS BETWEEN OLD SPECIFICATION AND NEW
*/

#define  botsh			f_bottom
#define  topsh			f_top
#define  proksh			f_proc
#define  ptr_shape(X)		f_pointer(f_alignment(X))

#if 1

#define  is_offset(X)\
	(name(sh(X)) == offsethd && al2(sh(X)) != 1)
#else

#define is_offset(X)\
        (name(sh(X)) == offsethd && \
	 (((al2(sh(son(X))) == 1) && (al2(sh(bro(son(X))))!=1)) || \
	  ((al2(sh(son(X)))!=1) && (al2(sh(bro(son(X)))) == 1))))
#endif

#define  simple_exp(X)\
	getexp(botsh, NULL, 0, NULL, NULL, 0, 0L, X)
