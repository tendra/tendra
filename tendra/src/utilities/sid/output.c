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


/**** output.c --- Target independent output routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements some generic output routines.
 *
 **** Change Log:*/

/****************************************************************************/

#include "output.h"

/*--------------------------------------------------------------------------*/

void
out_info_init PROTO_N ((info, prog))
	      PROTO_T (OutputInfoP info X
		       CStringP    prog)
{
    info->prog_name       = prog;
    info->current_ostream = NIL (OStreamP);
    info->istreams        = NIL (IStreamP);
    info->ostreams        = NIL (OStreamP);
    info->input_names     = NIL (CStringP *);
    info->output_names    = NIL (CStringP *);
    info->tab_width       = 8;
}

#ifdef FS_FAST
#undef out_info_get_prog_name
#endif /* defined (FS_FAST) */
CStringP
out_info_get_prog_name PROTO_N ((info))
		       PROTO_T (OutputInfoP info)
{
    return (info->prog_name);
}
#ifdef FS_FAST
#define out_info_get_prog_name(o) ((o)->prog_name)
#endif /* defined (FS_FAST) */

void
out_info_set_current_ostream PROTO_N ((info, i))
			     PROTO_T (OutputInfoP info X
				      unsigned    i)
{
    info->current_ostream = &(info->ostreams [i]);
}

#ifdef FS_FAST
#undef out_info_get_current_ostream
#endif /* defined (FS_FAST) */
OStreamP
out_info_get_current_ostream PROTO_N ((info))
			     PROTO_T (OutputInfoP info)
{
    return (info->current_ostream);
}
#ifdef FS_FAST
#define out_info_get_current_ostream(o) ((o)->current_ostream)
#endif /* defined (FS_FAST) */

void
out_info_set_num_input_files PROTO_N ((info, size))
			     PROTO_T (OutputInfoP info X
				      unsigned    size)
{
    info->istreams    = ALLOCATE_VECTOR (IStreamT, size);
    info->input_names = ALLOCATE_VECTOR (CStringP, size);
}

void
out_info_set_num_output_files PROTO_N ((info, size))
			      PROTO_T (OutputInfoP info X
				       unsigned    size)
{
    info->ostreams     = ALLOCATE_VECTOR (OStreamT, size);
    info->output_names = ALLOCATE_VECTOR (CStringP, size);
}

#ifdef FS_FAST
#undef out_info_get_istream
#endif /* defined (FS_FAST) */
IStreamP
out_info_get_istream PROTO_N ((info, i))
		     PROTO_T (OutputInfoP info X
			      unsigned    i)
{
    return (&(info->istreams [i]));
}
#ifdef FS_FAST
#define out_info_get_istream(o, i) (&((o)->istreams [(i)]))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef out_info_get_ostream
#endif /* defined (FS_FAST) */
OStreamP
out_info_get_ostream PROTO_N ((info, i))
		     PROTO_T (OutputInfoP info X
			      unsigned    i)
{
    return (&(info->ostreams [i]));
}
#ifdef FS_FAST
#define out_info_get_ostream(o, i) (&((o)->ostreams [(i)]))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef out_info_set_infile_name
#endif /* defined (FS_FAST) */
void
out_info_set_infile_name PROTO_N ((info, i, name))
			 PROTO_T (OutputInfoP info X
				  unsigned    i X
				  CStringP    name)
{
    info->input_names [i] = name;
}
#ifdef FS_FAST
#define out_info_set_infile_name(o, i, s) ((o)->input_names [(i)] = (s))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef out_info_get_infile_name
#endif /* defined (FS_FAST) */
CStringP
out_info_get_infile_name PROTO_N ((info, i))
			 PROTO_T (OutputInfoP info X
				  unsigned    i)
{
    return (info->input_names [i]);
}
#ifdef FS_FAST
#define out_info_get_infile_name(o, i) ((o)->input_names [(i)])
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef out_info_set_outfile_name
#endif /* defined (FS_FAST) */
void
out_info_set_outfile_name PROTO_N ((info, i, name))
			  PROTO_T (OutputInfoP info X
				   unsigned    i X
				   CStringP    name)
{
    info->output_names [i] = name;
}
#ifdef FS_FAST
#define out_info_set_outfile_name(o, i, s) ((o)->output_names [(i)] = (s))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef out_info_get_outfile_name
#endif /* defined (FS_FAST) */
CStringP
out_info_get_outfile_name PROTO_N ((info, i))
			  PROTO_T (OutputInfoP info X
				   unsigned    i)
{
    return (info->output_names [i]);
}
#ifdef FS_FAST
#define out_info_get_outfile_name(o, i) ((o)->output_names [(i)])
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef out_info_set_tab_width
#endif /* defined (FS_FAST) */
void
out_info_set_tab_width PROTO_N ((info, width))
		       PROTO_T (OutputInfoP info X
				unsigned    width)
{
    info->tab_width = width;
}
#ifdef FS_FAST
#define out_info_set_tab_width(o, w) ((o)->tab_width = (w))
#endif /* defined (FS_FAST) */

void
output_indent PROTO_N ((info, indent))
	      PROTO_T (OutputInfoP info X
		       unsigned    indent)
{
    OStreamP ostream    = out_info_get_current_ostream (info);
    unsigned tab_width  = info->tab_width;
    unsigned num_tabs   = (indent / tab_width);
    unsigned num_spaces = (indent % tab_width);

    while (num_tabs --) {
	write_tab (ostream);
    }
    while (num_spaces --) {
	write_char (ostream, ' ');
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../generated")
 * end:
**/
