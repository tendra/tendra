/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/**/


#ifndef COMMENT_INCLUDED
#define COMMENT_INCLUDED

#include "exptypes.h"
#include "codetypes.h"
#include "installtypes.h"


extern bool do_comment;
extern void fail(char *) ;


#ifdef DO_COMMENT

/* Commenting routines */
extern void comment(char *) ;
extern void comment1(char *, long) ;
extern void comment2(char *, long, long) ;
extern void comment3(char *, long, long, long) ;
extern void comment4(char *, long, long, long, long) ;

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
#define FULLCOMMENT(s)		comment (s)
#define FULLCOMMENT1(s, a)		comment1 (s, a)
#define FULLCOMMENT2(s, a, b)		comment2 (s, a, b)
#define FULLCOMMENT3(s, a, b, c)	comment3 (s, a, b, c)
#define FULLCOMMENT4(s, a, b, c, d)	comment4 (s, a, b, c, d)

#ifdef DO_PRTDF

/* TDF printing routines */
#define EXP_NUM(x)			(int) (x)
#define SH_NAME(x)			sh_name (x)
#define TAG_NAME(x)			tag_name (x)
#define ANSDISCRIM_NAME(x)		ansdiscrim_name (x)
#define PRTDF(s, e)			prtdf (s, e)

#else /* DO_PRTDF */

/* Dummy TDF printing macros */
#define EXP_NUM(x)			(int) (x)
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
