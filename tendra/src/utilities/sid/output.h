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


/**** output.h --- Target independent output routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * See the file "output.c" for more information.
 */

#ifndef H_OUTPUT
#define H_OUTPUT

#include "os-interface.h"
#include "cstring.h"
#include "istream.h"
#include "ostream.h"

/*--------------------------------------------------------------------------*/

typedef struct OutputInfoT {
	CStringP			prog_name;
	OStreamP			current_ostream;
	IStreamP			istreams;
	OStreamP			ostreams;
	CStringP		       *input_names;
	CStringP		       *output_names;
	unsigned			tab_width;
} OutputInfoT, *OutputInfoP;

/*--------------------------------------------------------------------------*/

void	out_info_init(OutputInfoP, CStringP);
CStringP out_info_get_prog_name(OutputInfoP);
void	out_info_set_current_ostream(OutputInfoP, unsigned);
OStreamP out_info_get_current_ostream(OutputInfoP);
void	out_info_set_num_input_files(OutputInfoP, unsigned);
void	out_info_set_num_output_files(OutputInfoP, unsigned);
IStreamP out_info_get_istream(OutputInfoP, unsigned);
OStreamP out_info_get_ostream(OutputInfoP, unsigned);
void	out_info_set_infile_name(OutputInfoP, unsigned, CStringP);
CStringP out_info_get_infile_name(OutputInfoP, unsigned);
void	out_info_set_outfile_name(OutputInfoP, unsigned, CStringP);
CStringP out_info_get_outfile_name(OutputInfoP, unsigned);
void	out_info_set_tab_width(OutputInfoP, unsigned);
void	output_indent(OutputInfoP, unsigned);

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define out_info_get_prog_name(o) ((o)->prog_name)
#define out_info_get_current_ostream(o) ((o)->current_ostream)
#define out_info_get_istream(o, i) (&((o)->istreams [(i)]))
#define out_info_get_ostream(o, i) (&((o)->ostreams [(i)]))
#define out_info_set_infile_name(o, i, s) ((o)->input_names [(i)] = (s))
#define out_info_get_infile_name(o, i) ((o)->input_names [(i)])
#define out_info_set_outfile_name(o, i, s) ((o)->output_names [(i)] = (s))
#define out_info_get_outfile_name(o, i) ((o)->output_names [(i)])
#define out_info_set_tab_width(o, w) ((o)->tab_width = (w))
#endif /* defined (FS_FAST) */

#endif /* !defined (H_OUTPUT) */
