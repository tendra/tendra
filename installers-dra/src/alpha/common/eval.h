/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
$Log: eval.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:58  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/08/21  08:44:22  john
 * Changed include files
 *
 * Revision 1.2  1995/05/16  10:47:43  john
 * Cosmetic changes
 *
 * Revision 1.1.1.1  1995/03/23  10:39:06  john
 * Entered into CVS
 *
 * Revision 1.2  1995/01/26  13:39:46  john
 * Minor changes to prototypes
 *
*/

#include "config.h"

#include "localtypes.h"
#include "addresstypes.h"
#include "flpttypes.h"
#include "cross.h"

extern int  next_data_lab(void);

extern int  next_dlab_sym(void);
extern int data_lab;

extern mm maxmin(shape);


extern instore evaluated(exp,int);

extern void  outfloat(exp,int,ash);


extern char fltrepr[];

