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
$Date: 1998/03/15 16:00:33 $
$Revision: 1.3 $
$Log: dw2_basic.h,v $
 * Revision 1.3  1998/03/15  16:00:33  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.2  1998/03/11  11:03:38  pwe
 * DWARF optimisation info
 *
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.8  1997/12/04  19:41:14  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.7  1997/11/06  09:22:00  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.6  1997/10/10  18:18:23  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.5  1997/08/23  13:36:34  pwe
 * initial ANDF-DE
 *
 * Revision 1.4  1997/04/17  11:50:14  pwe
 * Sparc and 80x86 support
 *
 * Revision 1.3  1997/04/01  17:19:35  pwe
 * diagnose pl_tests and locate -> platform specific
 *
 * Revision 1.2  1997/03/24  11:10:20  pwe
 * struct bitfields
 *
 * Revision 1.1  1997/03/20  16:09:02  pwe
 * first version
 *
**********************************************************************/

#ifndef dw2_basic_key
#define dw2_basic_key

extern void uleb128(unsigned long value);
extern void sleb128(long value);
extern int uleb128_length(unsigned long value);
extern int sleb128_length(long value);
extern void set_attribute(int name, int form);
extern void do_compunit_header(void);
extern void close_compunit_info(void);
extern void dw_sibling_end(void);
extern void dw_at_address(long lab);
extern void dw_at_ext_lab(ext_lab lab);
extern void dw_set_ext_lab(ext_lab lab);
extern void dw_at_ext_address(dg_tag tg);
extern void set_ext_address(dg_tag tg);
extern void dw_at_abstract_lab(dg_tag tg);
extern void set_abstract_lab(dg_tag tg);
extern void dw_at_string(char* s);
extern void dw_at_form(int f);
extern void dw_at_data(int n, long d);
extern void dw_at_udata(unsigned long n);
extern void dw_at_sdata(long n);
extern void dw_at_flag(int x);
extern void dw_at_decl(short_sourcepos p);
extern void dw_no_locate(void);
extern void dw_locate_offset(int n);
extern void dw_locate_reloffset(exp e);
extern void dw_at_distance(long lo, long hi);
extern long set_dw_text_label(void);
extern void out_text_label(long n);
extern void out_loc_range(long start, long end, int inclusive);

extern long last_text_label;


#endif
