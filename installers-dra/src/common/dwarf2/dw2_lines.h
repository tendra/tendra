/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:48 $
$Revision: 1.1.1.1 $
$Log: dw2_lines.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/10/28  10:14:33  pwe
 * local location corrections
 *
 * Revision 1.2  1997/08/23  13:36:53  pwe
 * initial ANDF-DE
 *
 * Revision 1.1  1997/03/20  16:09:27  pwe
 * first version
 *
**********************************************************************/

#ifndef dw2_lines_key
#define dw2_lines_key

extern void do_statprog_prologue(long l_start, long l_end);
extern void dw2_source_mark(short_sourcepos pos, int is_stmt);
extern void dw2_start_basic_block(void);
extern void close_statprog(long l_end);

#endif
