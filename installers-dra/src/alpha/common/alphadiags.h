/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*   alphadgdecs.h   - definitions in alphadgdecs.c  */

/*
$Log: alphadiags.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:58  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/05/23  10:52:12  john
 * Minor cosmetic change
 *
 * Revision 1.1.1.1  1995/03/23  10:39:31  john
 * Entered into CVS
 *
 * Revision 1.3  1995/01/31  14:23:47  john
 * Changed some declaration to use int rather than long
 *
 * Revision 1.2  1995/01/26  13:36:00  john
 * Changed prototypes
 *
*/

#include "config.h"
#include "exptypes.h"

#include "exptypes.h"
#include "diagtypes.h"
extern int nofds;
extern int *file_dnos;		/* dense nos for files */
extern void collect_files(filename f);
extern current_file;		/* dense no of current source file */
extern void stab_file(int i);	/* symtab entry for file source file i */
extern void stabd(int findex, int lno);/*.. entry for linenos */
extern void diagbr_open(int findex);/* .. entry for open scope */
extern void diagbr_close(int findex);/* entry for close scope */
extern void stab_local(char *nm, diag_type dt, exp id, int disp, int findex);
 /* entry for local */
extern void stab_types(void); /* aux entries for types */
extern int currentlno;
extern int find_file(filename);

extern int find_aux(diag_type s /* struct or union shape */ );
extern void symnosforfiles(void);
