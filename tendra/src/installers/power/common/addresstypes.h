/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

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



/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:48:39 $
$Revision: 1.2 $
$Log: addresstypes.h,v $
 * Revision 1.2  1998/02/04  15:48:39  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  15:59:28  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "localtypes.h"

#ifndef addressingtkey
#define addressingtkey 1

struct makeansst
{
  int lab;
  int regmove;
};
typedef struct makeansst makeans;

#define NOREG 100

struct baseofft
{
  int base;			/* base register for addressing */
  long offset;			/* offset in words */
};
typedef struct baseofft baseoff;

struct instoret
{
  baseoff b;
  bool adval;			/* if true then b is itself an address value
				 * i.e not a pointer to a value */
};
typedef struct instoret instore;

struct fregt
{
  int fr;			/* floating point reg (actually fr*2) */
  bool dble;			/* double precision */
};
typedef struct fregt freg;

struct somefregt
{
  int *fr;
  bool dble;
};
typedef struct somefregt somefreg;

struct someregt
{
  int *r;
};
typedef struct someregt somereg;


union anstu
{
  int regans;			/* register number */
  freg fregans;
  instore instoreans;
  somefreg somefregans;		/* not yet used */
  somereg someregans;
};

enum ansdiscrim
{
  inreg, 
  infreg, 
  notinreg, 
  insomereg, 
  insomefreg
};

/* use to discriminate the above union type */
struct anst
{
  enum ansdiscrim discrim;
  union anstu val;
};
typedef struct anst ans;	/* this type used as union of a fixpnt reg,
				 *  float reg and an instore value */

struct wheret
{
  ans answhere;			/* reg or store position */
  ash ashwhere;			/* size and alignment */
};

typedef struct wheret where;

struct mmt
{
  long maxi;
  long mini;
  char *fmt;
};
typedef struct mmt mm;

/******************************************************************
macros for ease of use of unions, allow 'hiding' of discriminator.
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
