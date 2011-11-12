/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

    
    
    
    
    


/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:48:45 $
$Revision: 1.2 $
$Log: exptypes.h,v $
 * Revision 1.2  1998/02/04  15:48:45  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:00:43  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef exptypes_key
#define exptypes_key 1

#include "config.h"

#include "codetypes.h"

#include "dg_first.h"
#include "diaginfo.h"



typedef unsigned short prop;


struct dec_t;

struct exp_t
{
  union expno_u
  {
    struct exp_t *e;
    char *str;
    int l;
    unsigned int ui;
    float f;
    struct dec_t *glob;
    diag_info *d;
    struct aldef_t *ald;
    
  }       brof;
  union expno_u numf;
  union expno_u ptf;
  union expno_u sonf;
  struct exp_t *shf;
  prop propsf;
  unsigned char namef;
  unsigned int lastf:1;
  unsigned int park:1;
};
typedef struct exp_t *exp;

typedef union expno_u expno;


#endif
