/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header$
--------------------------------------------------------------------------*/


#ifndef STAB_CONF_INCLUDED
#define STAB_CONF_INCLUDED

#include "config.h"

typedef long OUTPUT_REC ;

#ifdef NEWDIAGS

extern int dwarf2;
extern void dw2_proc_start PROTO_S ((exp p, dg_name d));
extern void dw2_proc_end PROTO_S ((exp p));
extern void dw2_code_info PROTO_S ((dg_info d, void (*mcode)(void *), void * args));
extern void dw2_start_basic_block PROTO_S ((void));


#define DIAG_VAL_BEGIN(d,g,c,s,e)	if (!dwarf2) \
				  stab_global (d, e, s, g);

#define DIAG_VAL_END(d)		

#define DIAG_PROC_BEGIN(d,g,c,s,e) if (dwarf2) \
				  dw2_proc_start (e, d);\
				else \
				  stab_proc (d, e, s, g);

#define DIAG_PROC_END(e)	if (dwarf2) \
				  dw2_proc_end (e);\
				else \
				  stab_proc_end ();

#define CODE_DIAG_INFO(d,n,x,a)	if (dwarf2) \
				  dw2_code_info (d, x, a);\
				else \
				  code_diag_info (d, x, a);


#define START_BB()		if (dwarf2) \
				  dw2_start_basic_block ();


#else

#define DIAG_VAL_BEGIN(d,g,c,s,e)	stab_global (d, e, s, g);

#define DIAG_VAL_END(d)		;

#define DIAG_PROC_BEGIN(d,g,c,s,e)	stab_proc (d, e, s, g);

#define DIAG_PROC_END(e)	;


#define INSPECT_FILENAME( x )	stab_collect_files ( x )
#define NEW_DIAG_GLOBAL( x )	( x )
#define OUTPUT_DIAG_TAGS()	stab_tagdefs ()
#define OUTPUT_GLOBALS_TAB()	stab_typedefs ()

#endif


#endif /* STAB_CONF_INCLUDED */

