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
$Author: release $
$Date: 1998/01/17 15:55:48 $
$Revision: 1.1.1.1 $
$Log: dwarf_out.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/09/28  12:39:52  pwe
 * dwarf.h via import, and type changes for tcc checks
 *
 * Revision 1.1.1.1  1995/08/14  14:30:23  pwe
 * transferred from DJCH
 *
**********************************************************************/

extern void dwarf4(const char *t);
extern void dwarf4n(int x);
extern void dwarf2(char *c);
extern void out_dwarf_thing(int t,char *cmt);
extern void out_dwarfone(int t,char *cmt);

extern void enter_dwarf_blk(int four,int excl, dwarf_label *lb);
extern void new_dwarf_blk2(void);
extern void new_dwarf_blk4(void);
extern void leave_dwarf_blk1(int leave);

extern void out_diagnose_prelude(void);
extern void out_diagnose_postlude(void);

extern void enter_dwarf_comp_unit(void);
extern void leave_dwarf_comp_unit(void);

extern void next_dwarf_lab(dwarf_label *p);
extern dwarf_type_label *next_dwarf_type_lab(void);
extern char *current_label_name(void);

#include "dwarf_gbl.h"
extern void out_dwarf_name_attr(const char * const s);
#define TDFSTRING2CHAR(x)	(&(((x).ints.chars)[0]))
extern void out_dwarf_string(const char * const s);
extern void out_dwarf_sourcemark(const sourcemark * const x);

extern void out_dwarf_bytesize_attr(shape t);

#define OUT_DWARF_LOC_BLK(x)		out_dwarf_thing((int)x, "loc blk")

#define OUT_DWARF_TAG(x)		out_dwarf_thing(x, #x)
#define OUT_DWARF_TAG_NAMED(x, y)	out_dwarf_thing(x, y)
#define OUT_DWARF_ATTR(x)		out_dwarf_thing(x, #x)
#define dwarf2c(x)			out_dwarf_thing(x, #x)
#define dwarf1(x)			out_dwarfone(x, #x)

#define enter_dwarf_entry(lb)		enter_dwarf_blk(1, 0, lb)
#define leave_dwarf_blk()		leave_dwarf_blk1(1)
#define leave_dwarf_blk2()		leave_dwarf_blk1(0)
#define leave_dwarf_blk4()		leave_dwarf_blk1(1)

extern void start_sib_chain1(int d_tag, char *tag_name);
extern void cont_sib_chain1(int d_tag, char *tag_name);
extern void end_sib_chain(void);
extern void make_next_new_chain(void);

#define start_sib_chain(x)	start_sib_chain1(x, #x)
#define cont_sib_chain(x)	cont_sib_chain1(x, #x)


extern void out_dwarf_lab(H_dwarf_lab *l);
#ifdef mips
#define OUT_DWARF_BEG(x)	out_dwarf_lab((H_dwarf_lab *)&(((x)->beg)[0]))
#define OUT_DWARF_END(x)	out_dwarf_lab((H_dwarf_lab *)&(((x)->end)[0]))
#else
#define OUT_DWARF_BEG(x)	out_dwarf_lab(&((x)->beg))
#define OUT_DWARF_END(x)	out_dwarf_lab(&((x)->end))
#endif
