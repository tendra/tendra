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


/**********************************************************************
$Author: pwe $
$Date: 1998/03/15 16:00:17 $
$Revision: 1.1 $
$Log: dw2_extra.h,v $
 * Revision 1.1  1998/03/15  16:00:17  pwe
 * regtrack dwarf dagnostics added
 *
**********************************************************************/

	/* Sparc specific declarations are listed here.
	   Declarations visible to common/dwarf2 are in dw2_config.h */


#ifndef dw2_extra_key
#define dw2_extra_key 1

#ifdef NEWDWARF

extern long dw2_start_fde(long proc_start, long fblab);
extern void dw2_fde_entry PROTO_S((long dwl0, long dwl1, long dwl2,
		long dwl3, long dwl4, long dwl8, int space));
extern void dw2_untidy_return(void);
extern long dw2_prep_fde_restore_args(int untidy);
extern void dw2_fde_restore_args PROTO_S((long dwl0, long dwl1, long dwl2,
		long dwl3, long dwl4, int space));
extern void dw2_after_fde_exit(long here);
extern void dw2_track_push(void);
extern void dw2_track_pop(void);
extern void dw2_track_sp(void);
extern void dw2_complete_fde(void);

extern void dw2_start_extra_bit(exp body);
extern void dw2_end_extra_bit(exp body);


extern int dw_ignore_used_regassn;
extern void dw_init_regassn(int reg, int x);
extern void dw_used_regassn(int reg, int x);
extern void dw_close_regassn(int reg, int x);


#endif
#endif
