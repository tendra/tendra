/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


/**/


#ifndef ADDRTYPES_INCLUDED
#define ADDRTYPES_INCLUDED

#include "common_types.h"
#include "proctypes.h"

#define NOREG	100


/*
 *    TYPE DEFINITIONS
 */

typedef struct {
    int lab;
    int regmove;
} makeans;

typedef struct {
    int base;
    long offset;
} baseoff;

typedef struct {
    baseoff b;
    bool adval;
} instore;

typedef struct {
    int fr;
    bool dble;
} freg;

typedef struct {
    int *fr;
    bool dble;
} somefreg;

typedef struct {
    int *r;
} somereg;

typedef struct {
    enum ansdiscrim {
		inreg,
		infreg,
		notinreg,
		bitad,
		insomereg,
		insomefreg
    } d;
    union {
		int regans;
		freg fregans;
		instore instoreans;
		instore bitadans;
		somefreg somefregans;
		somereg someregans;
    } val;
} ans;

typedef struct {
    ans answhere;
    ash ashwhere;
} where;

typedef struct {
    long maxi;
    long mini;
    char *fmt;
} mm;

struct regcell_t {int regcell_key;
	/* 0 - indetermined
	 *			   1 - has first_dest, not second
	 *			   2 - has second_dest, not first
	 *			   3 - has first_dest and second_dest
	 *			   4 - overdetermined
	 */
	exp first_dest;
	int first_size;
	exp second_dest;
	int second_size;
};

typedef struct regcell_t regcell;

typedef regcell reg_record[7];

typedef struct outofline_t {
	struct outofline_t * next;
	where dest;
	exp body;
	int labno;
	int repeat_level;
	space sp;
	exp jr;
} outofline;


#define BITS2BYTES(x) 	((x) >> 3)
#define BYTES2BITS(x) 	((x) << 3)





/*
 *    MACROS FOR SETTING AND ADDRESSING THE COMPONENTS OF AN ANS
 */

#define discrim(x)		(x).d
#define regalt(x)		(x).val.regans
#define fregalt(x)		(x).val.fregans
#define insalt(x)		(x).val.instoreans
#define bitadalt(x)		(x).val.bitadans
#define someregalt(x)		(x).val.someregans.r
#define somefregalt(x)	(x).val.somefregans

#define setregalt(x, y)	(x).d = inreg ; regalt (x) = (y)
#define setfregalt(x, y)	(x).d = infreg ; fregalt (x) = (y)
#define setinsalt(x, y)	(x).d = notinreg ; insalt (x) = (y)
#define setbitadalt(x, y)	(x).d = bitad ; bitadalt (x) = (y)
#define setsomeregalt(x, y)	(x).d = insomereg ; someregalt (x) = (y)
#define setsomefregalt(x, y)	(x).d = insomefreg ; somefregalt (x) = (y)



#endif





