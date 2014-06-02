/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef BASIC_INCLUDED
#define BASIC_INCLUDED


/*
 * BASIC TDF DECODING ROUTINES
 *
 * This file contains the basic decoding routines for TDF integers,
 * strings etc.
 */

extern external de_extern_name(void);
extern sortid de_sort_name(int);
extern string de_tdfstring(void);
extern string de_tdfstring_align(void);
extern unique de_unique(void);
extern long fetch_extn(int);
extern long tdf_int(void);
extern char *tdf_int_str(void);
extern string get_string(long, long);
extern void add_foreign_sort(char *, char *, int);
extern int tdf_int_digits;
extern sortid *foreign_sorts;
extern long no_foreign_sorts;
extern int do_foreign_sorts;

#define tdf_bool()	(fetch(1))

#define check_list()\
	if (fetch(1)) {\
	    out("<error>");\
	    input_error("Illegal LIST value");\
	}


/*
 * START OF EXTRA SORTS
 *
 * Normal TDF sorts are represented by small values (see tdf.h).  Foreign
 * sorts are represented by values starting at extra_sorts.
 */
#define extra_sorts     100


#endif
