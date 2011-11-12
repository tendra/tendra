/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
$Log: hppadiags.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:11:28  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.4  1995/10/20  13:51:54  wfs
 * Added the declaration of "output_DEBUG()" for gcc compilation.
 *
 * Revision 5.3  1995/10/09  13:08:17  wfs
 * Cosmetic changes.
 *
 * Revision 5.2  1995/09/25  11:21:40  wfs
 * *** empty log message ***
 *
 * Revision 5.1  1995/09/15  14:01:35  wfs
 * "extern void stab_end PROTO_S (( diag_info*, exp ))" added.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:26:42  16:26:42  wfs (William Simmonds)
 * Apr95 tape version.
 *
 * Revision 3.0  95/03/30  11:17:20  11:17:20  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 *
 * Revision 2.0  95/03/15  15:27:07  15:27:07  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 *
 * Revision 1.1  95/01/17  14:12:19  14:12:19  wfs (William Simmonds)
 * Initial revision
 *
*/


#ifndef HPPADDECS_INCLUDED
#define HPPADDECS_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "dg_first.h"
#include "diaginfo.h"
#include "exptypes.h"

extern void init_stab(void);
extern void init_stab_aux(void);
extern void stab_collect_files(filename);
extern void stab_tagdefs(void);
extern void stab_typedefs(void);
extern void stab_begin(diag_info *, int, exp);

extern void init_stab_aux(void);
extern void init_diag(void);
extern void stab_file(long, bool);
extern void stabn(long, long);
extern long diagbr_open(long);
extern void diagbr_close(long);
extern void stab_types(void);
extern void stab_global(shape, char *, bool);
extern void stab_proc(exp, char *, bool);
extern void stab_local(char *, diag_type, exp, long, long);
extern void close_function_scope(int);
extern long currentfile;
extern void stab_end(diag_info*, exp);
#ifdef _SYMTAB_INCLUDED
extern void output_DEBUG(void);
#endif
#endif /* HPPADDECS_INCLUDED */
