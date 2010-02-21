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

#include "exptypes.h"
#include "diagtypes.h"
extern int nofds;
extern int *file_dnos;		/* dense nos for files */
extern void collect_files(filename f);
extern current_file;		/* dense no of current source file */
extern void stab_file PROTO_S ((int i));	/* symtab entry for file
					   source file i */
extern void stabd PROTO_S ((int findex, int lno));/*.. entry for linenos */
extern void diagbr_open PROTO_S ((int findex));/* .. entry for open scope */
extern void diagbr_close PROTO_S ((int findex));/* entry for close scope */
extern void stab_local PROTO_S((char *nm,diag_type dt,exp id,int disp,
			      int findex));
 /* entry for local */
extern void stab_types PROTO_S ((void)); /* aux entries for types */
extern int currentlno;
extern int find_file(filename);

extern int find_aux PROTO_S ((diag_type s /* struct or union shape */ ));
extern void symnosforfiles(void);
