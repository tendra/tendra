/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CATALOG_INCLUDED
#define CATALOG_INCLUDED

/*
    ERROR CATALOGUE

    The macros and types defined in this module describe the error catalogue.
    Note that the main component of the catalogue is in the automatically
    generated file errors1.h.
*/

#define ERR_GEN		make_error

typedef DECL_SPEC ACCESS;
typedef IDENTIFIER LONG_ID;
typedef int LEX;
typedef PTR(LOCATION) PTR_LOC;
typedef int cint;
typedef const char *cstring;
typedef unsigned long ucint;
typedef unsigned plural;

#if c_class_SPECIFICATION
#define ERR_CHECK	1
#endif

#ifndef ERR_HEADER_OFF
#include <utility/errors1.h>
#endif

extern void set_error_sev(int, int);
extern int find_error_no(STRING, int);
extern void init_catalog(void);
extern void term_catalog(void);
extern string find_vocab(int);
extern unsigned catalog_size;


#endif
