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
$Date: 1998/02/04 15:48:39 $
$Revision: 1.2 $
$Log: ash.c,v $
 * Revision 1.2  1998/02/04  15:48:39  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  15:59:33  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "config.h"
#include "ash.h"

/*
 * ash.c:
 * ashof is for historical compatibility, from before 
 * shape_size() & shape_align() 
 */
ash ashof(shape s)
{
  ash a;

  a.ashsize = shape_size(s);
  a.ashalign = shape_align(s);
  return a;
}
