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
$Date: 1998/02/04 15:48:57 $
$Revision: 1.2 $
$Log: maxminmacs.h,v $
 * Revision 1.2  1998/02/04  15:48:57  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:02:31  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#ifndef MAXMINMACS_H
#define MAXMINMACS_H

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#define max(a,b)	(((a)>=(b)) ? (a) : (b))
#define min(a,b)	(((a)<=(b)) ? (a) : (b))
#define absval(a)	(((a)<0) ? -(a) : (a))

#endif /* maxminmacs.h */
