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




/*
 *			    VERSION INFORMATION
 *			    ===================
 *
 *--------------------------------------------------------------------------
 *$Header$
 *--------------------------------------------------------------------------*/


#ifndef ADDRTYPES_INCLUDED
#define ADDRTYPES_INCLUDED

#include "common_types.h"

#define NOREG	100

typedef int reg_num;		/* so we can distinguish regs */

/*
 *    TYPES REPRESENTING ADDRESSING MODES
 *
 *    Each of these types represent a different way of representing data.
 *    The type ans is a discriminated union of these types.
 */

typedef struct {
    int lab;
    reg_num regmove;
} makeans;

typedef struct {
    reg_num base;
    long offset ;		/* in BYTES (bits/8) */
} baseoff;

typedef struct {
    baseoff b;
    bool adval ;		/*  */
} instore;

typedef struct {
    reg_num base;
    long offset_bits ;		/* in BITS */
} baseoff_bits;

typedef struct {
    baseoff_bits b;
    bool adval ;		/*  */
} instore_bits;

typedef struct {
    reg_num fr;
    bool dble;
} freg;

typedef struct {
    reg_num *fr;
    bool dble;
} somefreg;

typedef struct {
    reg_num *r;
} somereg;

typedef struct {
    enum ansdiscrim {
		inreg,
		infreg,
		notinreg,
		insomereg,
		insomefreg
    } d;
    union {
		reg_num regans;
		freg fregans;
		instore instoreans;
		somereg someregans;
		somefreg somefregans;
    } val;
} ans;

#if __GNUC__
#define  CREATE_instore_bits(a,x) instore_bits a = {{(x).b.base, -1},(x).adval}
#else
#define  CREATE_instore_bits(a,x) instore_bits a;\
  a.b.base = (x).b.base;\
  a.b.offset_bits = -1;\
  a.adval = (x).adval
#endif

#define BITS2BYTES(x) 	((x) >> 3)
#define BYTES2BITS(x) 	((x) << 3)
/* bottom 6 bits are used for reg number,
 *				 offset is aligned 32 bits, and doubled, 
 *				 so that bottom6 are clear*/
#define REG_PART(x) 	((x) & 0x3f)
/* value (bits) was doubled, so shift by 4,
 *				   and ensure bottom two are clear 
 *				   (cos the old code did this...) */
#define BYTE_OFFSET_PART(x) 	(((x) >> 4) & ~0x3)
/* globals and locals use the part above
 *				 REG_PART */
#define ADDR_PART(x)	((x) >> 6)
/*
 *    TYPE REPRESENTING A STORED VALUE
 */

typedef struct {
    ans answhere;
    ash ashwhere;
} where;


/*
 *    TYPE REPRESENTING A DATA STORAGE TYPE
 */

typedef struct {
    long maxi;
    long mini;
    char *fmt;
} mm;


/*
 *    MACROS FOR SETTING AND ADDRESSING THE COMPONENTS OF AN ANS
 */

#define discrim(x)		(x).d
#define regalt(x)		(x).val.regans
#define fregalt(x)		(x).val.fregans
#define insalt(x)		(x).val.instoreans
#define someregalt(x)		(x).val.someregans.r
#define somefregalt(x)	(x).val.somefregans

#define setregalt(x, y)	(x).d = inreg ; regalt (x) = (y)
#define setfregalt(x, y)	(x).d = infreg ; fregalt (x) = (y)
#define setinsalt(x, y)	(x).d = notinreg ; insalt (x) = (y)
#define setsomeregalt(x, y)	(x).d = insomereg ; someregalt (x) = (y)
#define setsomefregalt(x, y)	(x).d = insomefreg ; somefregalt (x) = (y)


#endif
