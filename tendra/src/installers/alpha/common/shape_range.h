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


/* 	$Id$	 */

/**/
#ifndef SHAPE_RANGE_H
#define SHAPE_RANGE_H
#include "cross.h"
#if FS_64_BIT
#define scmm_max 127L
#define scmm_min -128L
#define uscmm_max 255L
#define uscmm_min 0L

#define shmm_max 32767L
#define shmm_min -32768L
#define ushmm_max 65535L
#define ushmm_min 0L

#define swmm_max 0x7fffffffL
#define swmm_min 0xffffffff80000000L
#define uswmm_max 0x00000000ffffffffL
#define uswmm_min 0L

#define s64mm_max 0x7fffffffffffffffL
#define s64mm_min 0x8000000000000000L
#define u64mm_max 0xffffffffffffffffL
#define u64mm_min 0L
#else
#define scmm_max {0,127}
#define scmm_min {0,0}
#define uscmm_max {0,255U}
#define uscmm_min {0,0}

#define shmm_max {0,0x0000ffff}
#define shmm_min {0xffffffff,0xffff8000}
#define ushmm_max {0,0x0000ffff}
#define ushmm_min {0,0}


#define swmm_max {0,0x7fffffff}
#define swmm_min {0xffffffff,0x80000000}
#define uswmm_max {0,0xffffffff}
#define uswmm_min {0,0}

#define s64mm_max {0x7fffffff,0xfffffff}
#define s64mm_min {0x80000000,0x0000000}
#define u64mm_max {0xffffffff,0xffffffff}
#define u64mm_min {0,0}
#endif /* ifdef alpha */
#endif
