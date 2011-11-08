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


/*
$Log: comment.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:11:03  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.1  1995/09/15  13:29:28  wfs
 * Minor changes to stop the gcc compiler from complaining.
 *
 * Revision 5.0  1995/08/25  13:49:53  wfs
 * Preperation for August 95 Glue release
 *
 * Revision 4.0  1995/08/25  13:34:00  wfs
 * *** empty log message ***
 *
 * Revision 4.0  1995/08/25  13:34:00  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  10:49:24  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  10:49:24  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:25:58  16:25:58  wfs (William Simmonds)
 * Apr95 tape version.
 *
 * Revision 3.0  95/03/30  11:14:37  11:14:37  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 *
 * Revision 2.0  95/03/15  15:25:30  15:25:30  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 *
 * Revision 1.1  95/01/11  13:36:31  13:36:31  wfs (William Simmonds)
 * Initial revision
 *
*/


#ifndef COMMENT_INCLUDED
#define COMMENT_INCLUDED

#include "config.h"

#include "exptypes.h"
#include "codetypes.h"
#include "installtypes.h"


extern bool do_comment;
extern void fail(char *);


#ifdef DO_COMMENT

/* Commenting routines */
extern void comment(char *);
extern void comment1(char *, long);
extern void comment2(char *, long, long);
extern void comment3(char *, long, long, long);
extern void comment4(char *, long, long, long, long);

#else /* DO_COMMENT */

/* Dummy commenting macros */
#define comment(s)
#define comment1(s, a)
#define comment2(s, a, b)
#define comment3(s, a, b, c)
#define comment4(s, a, b, c, d)

#endif /* DO_COMMENT */


#ifdef DO_FULLCOMMENT

/* Full comments */
#define FULLCOMMENT(s)		comment(s)
#define FULLCOMMENT1(s, a)		comment1(s, a)
#define FULLCOMMENT2(s, a, b)		comment2(s, a, b)
#define FULLCOMMENT3(s, a, b, c)	comment3(s, a, b, c)
#define FULLCOMMENT4(s, a, b, c, d)	comment4(s, a, b, c, d)

#ifdef DO_PRTDF

/* TDF printing routines */
#define EXP_NUM(x)			(int)(x)
#define SH_NAME(x)			sh_name(x)
#define TAG_NAME(x)			tag_name(x)
#define ANSDISCRIM_NAME(x)		ansdiscrim_name(x)
#define PRTDF(s, e)			prtdf(s, e)

#else /* DO_PRTDF */

/* Dummy TDF printing macros */
#define EXP_NUM(x)			(int)(x)
#define SH_NAME(x)			(0)
#define TAG_NAME(x)			(0)
#define ANSDISCRIM_NAME(x)		(0)
#define PRTDF(s, e)			(0)

#endif /* DO_PRTDF */

#else /* DO_FULLCOMMENT */

/* Dummy full commenting macros */
#define FULLCOMMENT(s)
#define FULLCOMMENT1(s, a)
#define FULLCOMMENT2(s, a, b)
#define FULLCOMMENT3(s, a, b, c)
#define FULLCOMMENT4(s, a, b, c, d)
#define PRTDF(s, e)

#endif /* DO_FULLCOMMENT */

#endif /* COMMENT_INCLUDED */
