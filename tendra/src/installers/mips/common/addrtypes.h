/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/
/***************************************************************** 
 *
 *		addressingtypes.h
 *
 *	Types for usable addressing modes are defined here :-
 *baseoff, instore, freg, ans, where

*****************************************************************/



#ifndef addressingtkey
#define addressingtkey 1

#include "common_types.h"


struct makeansst {
	int   lab;
	int   regmove;
};
typedef struct makeansst  makeans;

#define NOREG 100

struct baseofft {
	int   base;			/* base register for addressing */
	long  offset;			/* offset in words */
};
typedef struct baseofft baseoff;

struct instoret {
	baseoff b;
	bool adval;			/* if true then b is itself an address
						 *				   value i.e not a pointer to a value */
};
typedef struct instoret instore;

struct fregt {
	int   fr;			/* floating point reg (actually fr*2) */
	bool dble;		/* double precision */
};
typedef struct fregt  freg;

struct somefregt {
	int  *fr;
	bool dble;
};
typedef struct somefregt  somefreg;

struct someregt {
	int  *r;
};				/* extra struct is to get over bug in MIPS
				 *				   cc */
typedef struct someregt somereg;


union anstu {
	int   regans;			/* register number */
	freg fregans;
	instore instoreans;
	somefreg somefregans;		
	somereg someregans;
};

enum ansdiscrim {
	inreg, infreg, notinreg, insomereg, insomefreg
};
/* use to discriminate the above union type */

struct anst {
	enum ansdiscrim discrim;
	union anstu val;
};
typedef struct anst ans;	/* this type used as union of a fixpnt
							 *				   reg, 				
							 *				   a float reg and an instore value */

struct wheret {
	ans answhere;			/* reg or store position */
	ash ashwhere;			/* size and alignment, see ashtypes.h */
};

typedef struct wheret where;

struct mmt {
	long  maxi;
	long  mini;
	char *fmt;
};
typedef struct mmt  mm;

/******************************************************************
 *macros for ease of use of unions, allow 'hiding' of discriminator.
 ******************************************************************/

#define regalt(x) (x).val.regans
#define fregalt(x) (x).val.fregans
#define insalt(x) (x).val.instoreans
#define someregalt(x) (x).val.someregans.r;
#define somefregalt(x) (x).val.somefregans;

/* assign to field of union, discriminator set as appropriate */
#define setregalt(x,y) (x).discrim = inreg; (x).val.regans = y
#define setfregalt(x,y) (x).discrim = infreg; (x).val.fregans = y
#define setinsalt(x,y) (x).discrim = notinreg; (x).val.instoreans =y
#define setsomeregalt(x,y) (x).discrim = insomereg; (x).val.someregans.r =y
#define setsomefregalt(x,y) (x).discrim = insomefreg; (x).val.somefregans=y

#endif
