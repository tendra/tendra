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

/* 
   out_badecs.h 
*/

/**/

#include "ibinasm.h"
#include "cross.h"

extern char *out_common PROTO_S ((asmsym,unsigned));
extern char *out_ent PROTO_S ((asmsym,unsigned,unsigned));
extern char *out_frame PROTO_S ((asmsym,unsigned,asmint,asmreg,asmreg));
extern char *out_mask PROTO_S ((asmsym,unsigned,unsigned,asmint));
extern char *out_verstamp PROTO_S ((int,int));
extern void out_loc PROTO_S ((int,unsigned));
extern char *out_chars PROTO_S ((asmsym,unsigned,asmint,unsigned short));
extern char *out_option PROTO_S ((int,int));
extern char *out_value PROTO_S ((asmsym,unsigned,INT64,unsigned));
extern void out_alias PROTO_S ((asmsym,unsigned,asmreg,asmreg));
extern char *out_rinst PROTO_S ((asmsym,int,asmreg,asmreg,asmformat,asmreg));
extern char *out_linst PROTO_S ((asmsym,int,asmreg,asmreg,asmformat,asmint));
extern char *out_data PROTO_S ((char *,int));
extern char *out_iinst PROTO_S((asmsym,int,asmreg,asmreg,asmformat,
			      unsigned int, int));
extern char *out_biinst PROTO_S((asmsym,int,asmreg,asmreg,asmformat,
			      unsigned int, INT64));
extern  FILE * ba_file;


