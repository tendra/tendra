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


/* sol86/diag_config.h */

/**********************************************************************
$Author$
$Date$
$Revision$*/

#ifndef diag_config_key
#define diag_config_key


typedef long OUTPUT_REC ;

#ifdef NEWDIAGS

extern int dwarf2;
extern void dw2_proc_start PROTO_S ((exp p, dg_name d));
extern void dw2_proc_end PROTO_S ((exp p));
extern void dw2_code_info PROTO_S ((dg_info d, void (*mcode)(void *), void * args));
extern void dw2_start_basic_block PROTO_S ((void));

extern void code_diag_info PROTO_S ((diag_info * d, void (*mcode)(void *), void * args));
extern void out_diag_global PROTO_S ((dg_name di, int global, int cname, char* pname));
extern void diag_proc_begin PROTO_S ((dg_name di, int global, int cname, char* pname));
extern void diag_proc_end PROTO_S ((void));



#define DIAG_VAL_BEGIN(d,g,c,s)	if (!dwarf2) \
				  out_diag_global (d, g, c, s);

#define DIAG_VAL_END(d)	
	
#define DIAG_PROC_BEGIN(d,g,c,s,p) if (dwarf2) \
				  dw2_proc_start (p, d);\
				else \
				  diag_proc_begin (d, g, c, s);

#define DIAG_PROC_END(d,p)	if (dwarf2) \
				  dw2_proc_end (p);\
				else \
				  diag_proc_end ();

#define CODE_DIAG_INFO(d,n,x,a)	if (dwarf2) \
				  dw2_code_info (d, x, a);\
				else \
				  code_diag_info (d, x, a);


#define START_BB()		if (dwarf2) \
				  dw2_start_basic_block ();


#else

#define INSPECT_FILENAME( x )	stab_collect_files ( x )
#define NEW_DIAG_GLOBAL( x )	( x )
#define OUTPUT_DIAG_TAGS()	stab_tagdefs ()
#define OUTPUT_GLOBALS_TAB()	stab_typedefs ()

extern void stab_collect_files PROTO_S ((dg_filename f));
extern void stab_tagdefs PROTO_S((void));
extern void stab_typedefs PROTO_S((void));

#endif

#define STABS

extern void init_stab_aux PROTO_S((void));

#endif
