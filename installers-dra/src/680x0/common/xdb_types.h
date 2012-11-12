/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef XDB_TYPES_INCLUDED
#define XDB_TYPES_INCLUDED

#include <stdio.h>

/*
    TYPE REPRESENTING POSITIONS IN THE DIAGNOSTICS NAME TABLE
*/

typedef unsigned long posn_t;

typedef struct {
    int is_lab;
    posn_t posn;
    long size;
} table_posn;


/*
    TYPE REPRESENTING DIAGNOSTIC SCOPES
*/

typedef struct {
    posn_t posn;
    int dscope_type;
} dscope;


/*
    STANDARD TABLE POSITIONS
*/

#define  NULL_POSN		((posn_t)0xffffffff)
#define  NULL_POSN_STR		"0xffffffff"
#define  CHAR_POSN		((posn_t)0xc2000000)
#define  SIGNED_POSN		((posn_t)0xc3000000)
#define  UNSIGNED_POSN		((posn_t)0xc4000000)
#define  FLOATING_POSN		((posn_t)0xc5000000)
#define  LOCAL_POSN		((posn_t)0x80000000)
#define  GLOBL_POSN		((posn_t)0xa0000000)


extern posn_t out_dd(FILE *, int, int);
extern void out_posn(FILE *, table_posn *, int);
extern void fill_gap(FILE *, long, posn_t);
extern table_posn * analyse_diag_type(FILE *, diag_type, int);

extern void push_dscope(posn_t, int);
extern dscope * pop_dscope(void);

#endif
