/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.ten15.org/>
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


/*** c-out-info.c --- Output control ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the SID output information routines.
 */

#include "c-out-info.h"
#include "c-code.h"

/*--------------------------------------------------------------------------*/

void
c_out_info_init(COutputInfoP info, OutputInfoP out_info)
{
	info->info        = out_info;
	info->header1     = NIL (CCodeP);
	info->header2     = NIL (CCodeP);
	info->trailer1    = NIL (CCodeP);
	info->trailer2    = NIL (CCodeP);
	nstring_copy_cstring (c_out_info_type_prefix (info), "ZT");
	nstring_copy_cstring (c_out_info_fn_prefix (info), "ZR");
	nstring_copy_cstring (c_out_info_in_prefix (info), "ZI");
	nstring_copy_cstring (c_out_info_out_prefix (info), "ZO");
	nstring_copy_cstring (c_out_info_label_prefix (info), "ZL");
	nstring_copy_cstring (c_out_info_terminal_prefix (info), "ZB");
	info->prototypes  = FALSE;
	info->ossg        = FALSE;
	info->numeric_ids = FALSE;
	info->casts       = FALSE;
	info->unreachable = FALSE;
	info->lines       = TRUE;
	info->split       = 0;
}

#ifdef FS_FAST
#undef c_out_info_info
#endif /* defined (FS_FAST) */
OutputInfoP
c_out_info_info(COutputInfoP info)
{
	return (info->info);
}
#ifdef FS_FAST
#define c_out_info_info(o) ((o)->info)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_ostream
#endif /* defined (FS_FAST) */
OStreamP
c_out_info_ostream(COutputInfoP info)
{
	return (out_info_get_current_ostream (info->info));
}
#ifdef FS_FAST
#define c_out_info_ostream(o) (out_info_get_current_ostream ((o)->info))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_program_name
#endif /* defined (FS_FAST) */
CStringP
c_out_info_program_name(COutputInfoP info)
{
	return (out_info_get_prog_name (info->info));
}
#ifdef FS_FAST
#define c_out_info_program_name(o) (out_info_get_prog_name ((o)->info))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_source_name
#endif /* defined (FS_FAST) */
CStringP
c_out_info_source_name(COutputInfoP info)
{
	return (out_info_get_infile_name (info->info, (unsigned) 0));
}
#ifdef FS_FAST
#define c_out_info_source_name(o) \
(out_info_get_infile_name ((o)->info, (unsigned) 0))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_c_source_name
#endif /* defined (FS_FAST) */
CStringP
c_out_info_c_source_name(COutputInfoP info)
{
	return (out_info_get_infile_name (info->info, (unsigned) 1));
}
#ifdef FS_FAST
#define c_out_info_c_source_name(o) \
(out_info_get_infile_name ((o)->info, (unsigned) 1))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_get_header1
#endif /* defined (FS_FAST) */
CCodeP
c_out_info_get_header1(COutputInfoP info)
{
	return (info->header1);
}
#ifdef FS_FAST
#define c_out_info_get_header1(o) ((o)->header1)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_set_header1
#endif /* defined (FS_FAST) */
void
c_out_info_set_header1(COutputInfoP info,
					   CCodeP code)
{
	info->header1 = code;
}
#ifdef FS_FAST
#define c_out_info_set_header1(o, c) ((o)->header1 = (c))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_get_header2
#endif /* defined (FS_FAST) */
CCodeP
c_out_info_get_header2(COutputInfoP info)
{
	return (info->header2);
}
#ifdef FS_FAST
#define c_out_info_get_header2(o) ((o)->header2)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_set_header2
#endif /* defined (FS_FAST) */
void
c_out_info_set_header2(COutputInfoP info, CCodeP code)
{
	info->header2 = code;
}
#ifdef FS_FAST
#define c_out_info_set_header2(o, c) ((o)->header2 = (c))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_get_trailer1
#endif /* defined (FS_FAST) */
CCodeP
c_out_info_get_trailer1(COutputInfoP info)
{
	return (info->trailer1);
}
#ifdef FS_FAST
#define c_out_info_get_trailer1(o) ((o)->trailer1)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_set_trailer1
#endif /* defined (FS_FAST) */
void
c_out_info_set_trailer1(COutputInfoP info, CCodeP code)
{
	info->trailer1 = code;
}
#ifdef FS_FAST
#define c_out_info_set_trailer1(o, c) ((o)->trailer1 = (c))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_get_trailer2
#endif /* defined (FS_FAST) */
CCodeP
c_out_info_get_trailer2(COutputInfoP info)
{
	return (info->trailer2);
}
#ifdef FS_FAST
#define c_out_info_get_trailer2(o) ((o)->trailer2)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_set_trailer2
#endif /* defined (FS_FAST) */
void
c_out_info_set_trailer2(COutputInfoP info, CCodeP code)
{
	info->trailer2 = code;
}
#ifdef FS_FAST
#define c_out_info_set_trailer2(o, c) ((o)->trailer2 = (c))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_type_prefix
#endif /* defined (FS_FAST) */
NStringP
c_out_info_type_prefix(COutputInfoP info)
{
	return (&(info->prefixes [CPFX_TYPE]));
}
#ifdef FS_FAST
#define c_out_info_type_prefix(o) (&((o)->prefixes [CPFX_TYPE]))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_fn_prefix
#endif /* defined (FS_FAST) */
NStringP
c_out_info_fn_prefix(COutputInfoP info)
{
	return (&(info->prefixes [CPFX_FN]));
}
#ifdef FS_FAST
#define c_out_info_fn_prefix(o) (&((o)->prefixes [CPFX_FN]))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_in_prefix
#endif /* defined (FS_FAST) */
NStringP
c_out_info_in_prefix(COutputInfoP info)
{
	return (&(info->prefixes [CPFX_IN]));
}
#ifdef FS_FAST
#define c_out_info_in_prefix(o) (&((o)->prefixes [CPFX_IN]))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_out_prefix
#endif /* defined (FS_FAST) */
NStringP
c_out_info_out_prefix(COutputInfoP info)
{
	return (&(info->prefixes [CPFX_OUT]));
}
#ifdef FS_FAST
#define c_out_info_out_prefix(o) (&((o)->prefixes [CPFX_OUT]))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_label_prefix
#endif /* defined (FS_FAST) */
NStringP
c_out_info_label_prefix(COutputInfoP info)
{
	return (&(info->prefixes [CPFX_LABEL]));
}
#ifdef FS_FAST
#define c_out_info_label_prefix(o) (&((o)->prefixes [CPFX_LABEL]))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_terminal_prefix
#endif /* defined (FS_FAST) */
NStringP
c_out_info_terminal_prefix(COutputInfoP info)
{
	return (&(info->prefixes [CPFX_TERMINAL]));
}
#ifdef FS_FAST
#define c_out_info_terminal_prefix(o) (&((o)->prefixes [CPFX_TERMINAL]))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_prefix
#endif /* defined (FS_FAST) */
NStringP
c_out_info_prefix(COutputInfoP info, CPrefixT prefix)
{
	return (&(info->prefixes [prefix]));
}
#ifdef FS_FAST
#define c_out_info_prefix(o, i) (&((o)->prefixes [i]))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_get_prototypes
#endif /* defined (FS_FAST) */
BoolT
c_out_info_get_prototypes(COutputInfoP info)
{
	return (info->prototypes);
}
#ifdef FS_FAST
#define c_out_info_get_prototypes(o) ((o)->prototypes)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_set_prototypes
#endif /* defined (FS_FAST) */
void
c_out_info_set_prototypes(COutputInfoP info,
						  BoolT prototypes)
{
	info->prototypes = prototypes;
}
#ifdef FS_FAST
#define c_out_info_set_prototypes(o, b) ((o)->prototypes = (b))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_get_ossg
#endif /* defined (FS_FAST) */
BoolT
c_out_info_get_ossg(COutputInfoP info)
{
	return (info->ossg);
}
#ifdef FS_FAST
#define c_out_info_get_ossg(o) ((o)->ossg)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_set_ossg
#endif /* defined (FS_FAST) */
void
c_out_info_set_ossg(COutputInfoP info, BoolT ossg)
{
	info->ossg = ossg;
}
#ifdef FS_FAST
#define c_out_info_set_ossg(o, b) ((o)->ossg = (b))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_get_numeric_ids
#endif /* defined (FS_FAST) */
BoolT
c_out_info_get_numeric_ids(COutputInfoP info)
{
	return (info->numeric_ids);
}
#ifdef FS_FAST
#define c_out_info_get_numeric_ids(o) ((o)->numeric_ids)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_set_numeric_ids
#endif /* defined (FS_FAST) */
void
c_out_info_set_numeric_ids(COutputInfoP info,
						   BoolT numeric_ids)
{
	info->numeric_ids = numeric_ids;
}
#ifdef FS_FAST
#define c_out_info_set_numeric_ids(o, b) ((o)->numeric_ids = (b))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_get_casts
#endif /* defined (FS_FAST) */
BoolT
c_out_info_get_casts(COutputInfoP info)
{
	return (info->casts);
}
#ifdef FS_FAST
#define c_out_info_get_casts(o) ((o)->casts)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_set_casts
#endif /* defined (FS_FAST) */
void
c_out_info_set_casts(COutputInfoP info, BoolT casts)
{
	info->casts = casts;
}
#ifdef FS_FAST
#define c_out_info_set_casts(o, b) ((o)->casts = (b))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_get_unreachable
#endif /* defined (FS_FAST) */
BoolT
c_out_info_get_unreachable(COutputInfoP info)
{
	return (info->unreachable);
}
#ifdef FS_FAST
#define c_out_info_get_unreachable(o) ((o)->unreachable)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_set_unreachable
#endif /* defined (FS_FAST) */
void
c_out_info_set_unreachable(COutputInfoP info, BoolT unreachable)
{
	info->unreachable = unreachable;
}
#ifdef FS_FAST
#define c_out_info_set_unreachable(o, b) ((o)->unreachable = (b))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_get_lines
#endif /* defined (FS_FAST) */
BoolT
c_out_info_get_lines(COutputInfoP info)
{
	return (info->lines);
}
#ifdef FS_FAST
#define c_out_info_get_lines(o) ((o)->lines)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_set_lines
#endif /* defined (FS_FAST) */
void
c_out_info_set_lines(COutputInfoP info, BoolT lines)
{
	info->lines = lines;
}
#ifdef FS_FAST
#define c_out_info_set_lines(o, b) ((o)->lines = (b))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_get_split
#endif /* defined (FS_FAST) */
unsigned
c_out_info_get_split(COutputInfoP info)
{
	return (info->split);
}
#ifdef FS_FAST
#define c_out_info_get_split(o) ((o)->split)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef c_out_info_set_split
#endif /* defined (FS_FAST) */
void
c_out_info_set_split(COutputInfoP info, unsigned split)
{
	info->split = split;
}
#ifdef FS_FAST
#define c_out_info_set_split(o, n) ((o)->split = (n))
#endif /* defined (FS_FAST) */
