/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/* 	$Id: output.h,v 1.1.1.1 1998/01/17 15:56:01 release Exp $	 */


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
