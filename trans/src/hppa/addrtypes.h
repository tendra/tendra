/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef ADDRTYPES_INCLUDED
#define ADDRTYPES_INCLUDED

#include <local/ash.h>

#include <construct/installtypes.h>

#include "proctypes.h"

#define NOREG	100


/*
    TYPE DEFINITIONS
*/

typedef struct {
    int lab ;
    int regmove ;
} makeans ;

typedef struct {
    int base ;
    long offset ;
} baseoff ;

typedef struct {
    baseoff b ;
    bool adval ;
} instore ;

typedef struct {
    int fr ;
    bool dble ;
} freg ;

typedef struct {
    int *fr ;
    bool dble ;
} somefreg ;

typedef struct {
    int *r ;
} somereg ;

typedef struct {
    enum ansdiscrim {
	inreg,
	infreg,
	notinreg,
	bitad,
	insomereg,
	insomefreg
    } d ;
    union {
	int regans ;
	freg fregans ;
	instore instoreans ;
	instore bitadans ;
	somefreg somefregans ;
	somereg someregans ;
    } val ;
} ans ;

typedef struct {
    ans answhere ;
    ash ashwhere ;
} where ;

typedef struct {
    long maxi ;
    long mini ;
    char *fmt ;
} mm ;

struct regcell_t {int regcell_key;
			/* 0 - indetermined
			   1 - has first_dest, not second
			   2 - has second_dest, not first
			   3 - has first_dest and second_dest
			   4 - overdetermined
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
    MACROS FOR SETTING AND ADDRESSING THE COMPONENTS OF AN ANS
*/

#define discrim( x )		( x ).d
#define regalt( x )		( x ).val.regans
#define fregalt( x )		( x ).val.fregans
#define insalt( x )		( x ).val.instoreans
#define bitadalt( x )		( x ).val.bitadans
#define someregalt( x )		( x ).val.someregans.r
#define somefregalt( x )	( x ).val.somefregans

#define setregalt( x, y )	( x ).d = inreg ; regalt ( x ) = ( y )
#define setfregalt( x, y )	( x ).d = infreg ; fregalt ( x ) = ( y )
#define setinsalt( x, y )	( x ).d = notinreg ; insalt ( x ) = ( y )
#define setbitadalt( x, y )	( x ).d = bitad ; bitadalt ( x ) = ( y )
#define setsomeregalt( x, y )	( x ).d = insomereg ; someregalt ( x ) = ( y )
#define setsomefregalt( x, y )	( x ).d = insomefreg ; somefregalt ( x ) = ( y )



#endif





