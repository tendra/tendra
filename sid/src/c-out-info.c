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


/*** c-out-info.c --- Output control ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the SID output information routines.
 *
 *** Change Log:
 * $Log: c-out-info.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:43  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1996/03/01  09:53:14  smf
 * c-code.c, c-out-info.c, c-out-info.h, c-output.c:
 * 	- improved unreachable code analysis;
 * 	- improved some output formatting;
 * 	- added support for comment or macro to mark unreachable code.
 *
 * Revision 1.2  1994/12/15  09:56:27  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:18  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "c-out-info.h"
#include "c-code.h"

/*--------------------------------------------------------------------------*/

void
c_out_info_init(COutputInfoP info, OutputInfoP out_info)
{
    info->info        = out_info;
    info->header1     = NIL(CCodeP);
    info->header2     = NIL(CCodeP);
    info->trailer1    = NIL(CCodeP);
    info->trailer2    = NIL(CCodeP);
    nstring_copy_cstring(c_out_info_type_prefix(info), "ZT");
    nstring_copy_cstring(c_out_info_fn_prefix(info), "ZR");
    nstring_copy_cstring(c_out_info_in_prefix(info), "ZI");
    nstring_copy_cstring(c_out_info_out_prefix(info), "ZO");
    nstring_copy_cstring(c_out_info_label_prefix(info), "ZL");
    nstring_copy_cstring(c_out_info_terminal_prefix(info), "ZB");
    info->prototypes  = FALSE;
    info->numeric_ids = FALSE;
    info->casts       = FALSE;
    info->unreachable = FALSE;
    info->lines       = TRUE;
    info->split       = 0;
}

OutputInfoP
c_out_info_info(COutputInfoP info)
{
    return(info->info);
}

OStreamP
c_out_info_ostream(COutputInfoP info)
{
    return(out_info_get_current_ostream(info->info));
}

CStringP
c_out_info_program_name(COutputInfoP info)
{
    return(out_info_get_prog_name(info->info));
}

CStringP
c_out_info_source_name(COutputInfoP info)
{
    return(out_info_get_infile_name(info->info, (unsigned)0));
}

CStringP
c_out_info_c_source_name(COutputInfoP info)
{
    return(out_info_get_infile_name(info->info, (unsigned)1));
}

CCodeP
c_out_info_get_header1(COutputInfoP info)
{
    return(info->header1);
}

void
c_out_info_set_header1(COutputInfoP info, CCodeP code)
{
    info->header1 = code;
}

CCodeP
c_out_info_get_header2(COutputInfoP info)
{
    return(info->header2);
}

void
c_out_info_set_header2(COutputInfoP info, CCodeP code)
{
    info->header2 = code;
}

CCodeP
c_out_info_get_trailer1(COutputInfoP info)
{
    return(info->trailer1);
}

void
c_out_info_set_trailer1(COutputInfoP info, CCodeP code)
{
    info->trailer1 = code;
}

CCodeP
c_out_info_get_trailer2(COutputInfoP info)
{
    return(info->trailer2);
}

void
c_out_info_set_trailer2(COutputInfoP info, CCodeP code)
{
    info->trailer2 = code;
}

NStringP
c_out_info_type_prefix(COutputInfoP info)
{
    return(&(info->prefixes[CPFX_TYPE]));
}

NStringP
c_out_info_fn_prefix(COutputInfoP info)
{
    return(&(info->prefixes[CPFX_FN]));
}

NStringP
c_out_info_in_prefix(COutputInfoP info)
{
    return(&(info->prefixes[CPFX_IN]));
}

NStringP
c_out_info_out_prefix(COutputInfoP info)
{
    return(&(info->prefixes[CPFX_OUT]));
}

NStringP
c_out_info_label_prefix(COutputInfoP info)
{
    return(&(info->prefixes[CPFX_LABEL]));
}

NStringP
c_out_info_terminal_prefix(COutputInfoP info)
{
    return(&(info->prefixes[CPFX_TERMINAL]));
}

NStringP
c_out_info_prefix(COutputInfoP info, CPrefixT prefix)
{
    return(&(info->prefixes[prefix]));
}

BoolT
c_out_info_get_prototypes(COutputInfoP info)
{
    return(info->prototypes);
}

void
c_out_info_set_prototypes(COutputInfoP info, BoolT prototypes)
{
    info->prototypes = prototypes;
}

BoolT
c_out_info_get_numeric_ids(COutputInfoP info)
{
    return(info->numeric_ids);
}

void
c_out_info_set_numeric_ids(COutputInfoP info, BoolT numeric_ids)
{
    info->numeric_ids = numeric_ids;
}

BoolT
c_out_info_get_casts(COutputInfoP info)
{
    return(info->casts);
}

void
c_out_info_set_casts(COutputInfoP info, BoolT casts)
{
    info->casts = casts;
}

BoolT
c_out_info_get_unreachable(COutputInfoP info)
{
    return(info->unreachable);
}

void
c_out_info_set_unreachable(COutputInfoP info, BoolT unreachable)
{
    info->unreachable = unreachable;
}

BoolT
c_out_info_get_lines(COutputInfoP info)
{
    return(info->lines);
}

void
c_out_info_set_lines(COutputInfoP info, BoolT lines)
{
    info->lines = lines;
}

unsigned
c_out_info_get_split(COutputInfoP info)
{
    return(info->split);
}

void
c_out_info_set_split(COutputInfoP info, unsigned split)
{
    info->split = split;
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../output" "../generated")
 * end:
**/
