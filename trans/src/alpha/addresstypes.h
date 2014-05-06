/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
   
  addresstypes.h

  Types for usable addressing modes are defined here :-
  baseoff, instore, freg, ans, where

*/



#ifndef addressingtkey
#define addressingtkey 1

#include <local/exptypes.h>
#include "cross.h"
#include <construct/installtypes.h>
#include <local/localtypes.h>


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

typedef struct source_t{
  bool reg;
  int value;
} source;



struct instoret {
  baseoff b;
  bool adval;	/* if true then b is itself an address
		   value i.e not a pointer to a value */
};

typedef struct instoret instore;

typedef enum {
  VAX_single,VAX_double,IEEE_single,IEEE_double
} float_reg_contents;


typedef struct fregt{
  int fr;
  float_reg_contents type;
} freg;


typedef struct somefregt {
  int  *fr;
  float_reg_contents type;
} somefreg;


struct someregt {
  int  *r;
};		
		
typedef struct someregt somereg;


union anstu {
  int   regans;			/* register number */
  freg fregans;
  instore instoreans;
  somefreg somefregans;		
  somereg someregans;
};

enum ansdiscrim {
  inreg, infreg, notinreg,insomereg, insomefreg
};
 /* use to discriminate the above union type */

struct anst {
  enum ansdiscrim discrim;
  union anstu val;
};
typedef struct anst ans;	/* this type used as union of a fixpnt
				   reg, a float reg and an instore 
				   value */

struct wheret {
  ans answhere;			/* reg or store position */
  ash ashwhere;			/* size and alignment, see ashtypes.h */
};

typedef struct wheret where;

struct mmt {
  INT64  maxi;
  INT64  mini;
  char *fmt;
};
typedef struct mmt  mm;

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


