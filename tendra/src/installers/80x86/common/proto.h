/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
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


/* 80x86/proto.h */

/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/


#ifndef PROTO_INCLUDED
#define PROTO_INCLUDED

#ifdef HAVE_PROTOTYPES

#define 
PROTO_Z ()			(void)
#define 
    PROTO_N ((v1)		(t1 v1 ))
    PROTO_T (t1 v1)		(t1 v1 )
#define 
    PROTO_N ((t2, t2 v2 ))
    PROTO_T (t1, v1 t2 X v2)	(t1 v1 t2 v2 )
#define 
    PROTO_N ((v1, v2, v3 ))
    PROTO_T (t1 v1 X t2 v2 X t3 v3 )\
(t1 v1, t2 v2, t3 v3)
#define 
    PROTO_N ((v1, v2, v3, v4 ))
    PROTO_T (t1 v1 X t2 v2 X t3 v3 X t4 v4 )\
(t1 v1, t2 v2, t3 v3, t4 v4)
#define 
    PROTO_N ((v1, v2, v3, v4, v5 ))
    PROTO_T (t1 v1 X t2 v2 X t3 v3 X t4 v4 X t5 v5 )\
(t1 v1, t2 v2, t3 v3, t4 v4, t5 v5)
	
#else /* HAVE_PROTOTYPES */
	
#define 
    PROTO_Z ()			()
#define 
    PROTO_N ((v1)		(v1 ))
    PROTO_T (t1 v1)		(v1 ) t1 v1;
#define 
    PROTO_N ((t2, v2 ))
    PROTO_T (t1, v1 t2 X v2)	(v1 v2 ) t1 v1 ; t2 v2;
#define 
    PROTO_N ((v1, v2, v3 ))
    PROTO_T (t1 v1 X t2 v2 X t3 v3 )\
	(v1, v2, v3) t1 v1 ; t2 v2 ; t3 v3;
#define 
PROTO_N ((v1, v2, v3, v4 ))
    PROTO_T (t1 v1 X t2 v2 X t3 v3 X t4 v4 )\
(v1, v2, v3, v4)\
t1 v1 ; t2 v2 ; t3 v3 ; t4 v4;
#define 
PROTO_N ((v1, v2, v3, v4, v5 ))
    PROTO_T (t1 v1 X t2 v2 X t3 v3 X t4 v4 X t5 v5 )\
(v1, v2, v3, v4, v5)\
t1 v1 ; t2 v2 ; t3 v3 ; t4 v4 ; t5 v5;

#endif /* HAVE_PROTOTYPES */

#endif
