/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef ADDRTYPES_INCLUDED
#define ADDRTYPES_INCLUDED

#include <shared/check.h>

#include <local/localtypes.h>

#include <construct/installtypes.h>

#define NOREG	100

typedef int reg_num;		/* so we can distinguish regs */

/*
    TYPES REPRESENTING ADDRESSING MODES

    Each of these types represent a different way of representing data.
    The type ans is a discriminated union of these types.
*/

typedef struct {
    int lab ;
    reg_num regmove ;
} makeans ;

typedef struct {
    reg_num base ;
    long offset ;		/* in BYTES (bits/8) */
} baseoff ;

typedef struct {
    baseoff b ;
    bool adval ;		/*  */
} instore ;

typedef struct {
    reg_num base ;
    long offset_bits ;		/* in BITS */
} baseoff_bits ;

typedef struct {
    baseoff_bits b ;
    bool adval ;		/*  */
} instore_bits ;

typedef struct {
    reg_num fr ;
    bool dble ;
} freg ;

typedef struct {
    reg_num *fr ;
    bool dble ;
} somefreg ;

typedef struct {
    reg_num *r ;
} somereg ;

typedef struct {
    enum ansdiscrim {
	inreg,
	infreg,
	notinreg,
	insomereg,
	insomefreg
    } d ;
    union {
	reg_num regans ;
	freg fregans ;
	instore instoreans ;
	somereg someregans ;
	somefreg somefregans ;
    } val ;
} ans ;

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
				 offset is aligned 32 bits, and doubled, 
				 so that bottom6 are clear*/
#define REG_PART(x) 	((x) & 0x3f)
				/* value (bits) was doubled, so shift by 4,
				   and ensure bottom two are clear 
				   (cos the old code did this...) */
#define BYTE_OFFSET_PART(x) 	(((x) >> 4) & ~0x3)
				/* globals and locals use the part above
				 REG_PART */
#define ADDR_PART(x)	((x) >> 6)
/*
    TYPE REPRESENTING A STORED VALUE
*/

typedef struct {
    ans answhere ;
    ash ashwhere ;
} where ;


/*
    TYPE REPRESENTING A DATA STORAGE TYPE
*/

typedef struct {
    long maxi ;
    long mini ;
    char *fmt ;
} mm ;


/*
    MACROS FOR SETTING AND ADDRESSING THE COMPONENTS OF AN ANS
*/

#define discrim( x )		( x ).d
#define regalt( x )		( x ).val.regans
#define fregalt( x )		( x ).val.fregans
#define insalt( x )		( x ).val.instoreans
#define someregalt( x )		( x ).val.someregans.r
#define somefregalt( x )	( x ).val.somefregans

#define setregalt( x, y )	( x ).d = inreg ; regalt ( x ) = ( y )
#define setfregalt( x, y )	( x ).d = infreg ; fregalt ( x ) = ( y )
#define setinsalt( x, y )	( x ).d = notinreg ; insalt ( x ) = ( y )
#define setsomeregalt( x, y )	( x ).d = insomereg ; someregalt ( x ) = ( y )
#define setsomefregalt( x, y )	( x ).d = insomefreg ; somefregalt ( x ) = ( y )


#endif
