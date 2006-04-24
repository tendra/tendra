/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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


/* 	$Id$	 */

/*
   out_badecs.h
*/

/*
$Log: out_ba.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:00  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/05/23  13:24:09  john
 * Change for 64 bit support
 *
 * Revision 1.2  1995/04/10  14:13:34  john
 * Minor changes
 *
 * Revision 1.1.1.1  1995/03/23  10:39:33  john
 * Entered into CVS
 *
 * Revision 1.2  1995/03/23  10:10:12  john
 * Changed prototypes (part of change to support scheduler).
 *
*/

#include "ibinasm.h"
#include "cross.h"

extern char *out_common(asmsym,unsigned);
extern char *out_ent(asmsym,unsigned,unsigned);
extern char *out_frame(asmsym,unsigned,asmint,asmreg,asmreg);
extern char *out_mask(asmsym,unsigned,unsigned,asmint);
extern char *out_verstamp(int,int);
extern void out_loc(int,unsigned);
extern char *out_chars(asmsym,unsigned,asmint,unsigned short);
extern char *out_option(int,int);
extern char *out_value(asmsym,unsigned,INT64,unsigned);
extern void out_alias(asmsym,unsigned,asmreg,asmreg);
extern char *out_rinst(asmsym,int,asmreg,asmreg,asmformat,asmreg);
extern char *out_linst(asmsym,int,asmreg,asmreg,asmformat,asmint);
extern char *out_data(char *,int);
extern char *out_iinst PROTO_S((asmsym,int,asmreg,asmreg,asmformat,
			      unsigned int, int));
extern char *out_biinst PROTO_S((asmsym,int,asmreg,asmreg,asmformat,
			      unsigned int, INT64));
extern  FILE * ba_file;


