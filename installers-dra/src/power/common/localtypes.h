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
$Date: 1998/02/04 15:48:53 $
$Revision: 1.2 $
$Log: localtypes.h,v $
 * Revision 1.2  1998/02/04  15:48:53  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:01:49  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef localtypes_key
#define localtypes_key 1

#include "config.h"

#include "installtypes.h"
#include "exptypes.h"
#include "memtdf.h"


struct specit {
  bool is_special;
  exp special_exp;
};
typedef struct specit speci;



#endif
