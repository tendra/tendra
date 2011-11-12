/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
   output.h

   This file provides a set of macros to output low-level data 
   (strings and integers) to the assembler file.
*/

/*
$Log: output.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:01  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/23  10:39:16  john
 * Entered into CVS
 *
 * Revision 1.3  1995/03/23  10:10:53  john
 * Added definition of outchar
 *
*/

#ifndef OUTPUT_H
#define OUTPUT_H
#define outhex(num)	fprintf(as_file,"0x%08x",num)
#define outhexlow(num)	fprintf(as_file,"%08x",num)
#define outhigh(num)	fprintf(as_file,"%08x",num)
#define outlong(num)	fprintf(as_file,"%ld",num)
#define outint(num)	fprintf(as_file,"%d",num)
#define outstring(str)	fprintf(as_file,"%s",str)
#define outchar(ch)	fputc(ch,as_file)
#endif 
