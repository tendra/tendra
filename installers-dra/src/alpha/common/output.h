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
