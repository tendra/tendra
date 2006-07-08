/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
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


/**** debug.h --- Debugging routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * See the file "debug.c" for more information.
 *
 **** Change Log:
 * $Log: debug.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/07/07  15:32:23  smf
 * Updated to support TDF specification 4.0.
 *
 * Revision 1.2  1994/12/12  11:46:21  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:31  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_DEBUG
#define H_DEBUG

#include "os-interface.h"
#include "cstring.h"
#include "dstring.h"
#include "name-key.h"
#include "ostream.h"

/*--------------------------------------------------------------------------*/

extern void			debug_set_file
(OStreamP);

extern void			debug_info_u_name
(NStringP);

extern void			debug_info_r_start_capsule
(CStringP);
extern void			debug_info_r_versions
(unsigned, unsigned);
extern void			debug_info_r_start_unit_decs
(unsigned);
extern void			debug_info_r_unit_dec
(NStringP);
extern void			debug_info_r_start_shapes
(unsigned);
extern void			debug_info_r_shape
(NStringP, unsigned);
extern void			debug_info_r_start_names
(unsigned);
extern void			debug_info_r_start_shape_names
(NStringP, unsigned);
extern void			debug_info_r_name
(NameKeyP, unsigned, unsigned, NameKeyP);
extern void			debug_info_r_start_unit_sets
(unsigned);
extern void			debug_info_r_start_units
(NStringP, unsigned);
extern void			debug_info_r_start_unit
(NStringP, unsigned, unsigned);
extern void			debug_info_r_start_counts
(unsigned);
extern void			debug_info_r_count
(unsigned, NStringP);
extern void			debug_info_r_start_maps
(unsigned);
extern void			debug_info_r_start_shape_maps
(NStringP, unsigned);
extern void			debug_info_r_map
(unsigned, unsigned, unsigned);
extern void			debug_info_r_unit_body
(unsigned);
extern void			debug_info_r_tld_version
(unsigned);
extern void			debug_info_r_start_usages
(NStringP, unsigned);
extern void			debug_info_r_usage
(unsigned, unsigned, NameKeyP);
extern void			debug_info_r_end_capsule
(void);
extern void			debug_info_r_abort_capsule
(void);

extern void			debug_info_w_start_capsule
(CStringP);
extern void			debug_info_w_versions
(unsigned, unsigned);
extern void			debug_info_w_start_unit_decs
(unsigned);
extern void			debug_info_w_unit_dec
(NStringP);
extern void			debug_info_w_start_shapes
(unsigned);
extern void			debug_info_w_shape
(NStringP, unsigned);
extern void			debug_info_w_start_names
(unsigned);
extern void			debug_info_w_start_shape_names
(NStringP, unsigned);
extern void			debug_info_w_name
(NameKeyP, unsigned);
extern void			debug_info_w_start_unit_sets
(unsigned);
extern void			debug_info_w_start_units
(NStringP, unsigned);
extern void			debug_info_w_start_unit
(NStringP, unsigned, unsigned);
extern void			debug_info_w_start_counts
(unsigned);
extern void			debug_info_w_count
(unsigned, NStringP);
extern void			debug_info_w_start_maps
(unsigned);
extern void			debug_info_w_start_shape_maps
(NStringP, unsigned);
extern void			debug_info_w_map
(unsigned, unsigned);
extern void			debug_info_w_unit_body
(unsigned);
extern void			debug_info_w_tld_version
(unsigned);
extern void			debug_info_w_start_usages
(NStringP);
extern void			debug_info_w_usage
(unsigned, NameKeyP);
extern void			debug_info_w_end_capsule
(void);

extern void			debug_info_r_start_library
(CStringP);
extern void			debug_info_r_lib_versions
(unsigned, unsigned);
extern void			debug_info_r_library_version
(unsigned);
extern void			debug_info_r_start_capsules
(unsigned);
extern void			debug_info_r_capsule
(NStringP, unsigned);
extern void			debug_info_r_start_index
(unsigned);
extern void			debug_info_r_start_shape_index
(NStringP, unsigned);
extern void			debug_info_r_index_entry
(NameKeyP, unsigned, unsigned, NameKeyP, CStringP);
extern void			debug_info_r_end_library
(void);
extern void			debug_info_r_abort_library
(void);

extern void			debug_info_w_start_library
(CStringP);
extern void			debug_info_w_lib_versions
(unsigned, unsigned);
extern void			debug_info_w_library_version
(unsigned);
extern void			debug_info_w_start_capsules
(unsigned);
extern void			debug_info_w_capsule
(CStringP, unsigned);
extern void			debug_info_w_start_index
(unsigned);
extern void			debug_info_w_start_shape_index
(NStringP, unsigned);
extern void			debug_info_w_index_entry
(NameKeyP, unsigned, CStringP, unsigned);
extern void			debug_info_w_end_library
(void);

extern void			debug_info_l_not_needed
(NameKeyP, NStringP, unsigned);
extern void			debug_info_l_not_found
(NameKeyP, NStringP, unsigned);
extern void			debug_info_l_found
(NameKeyP, NStringP, unsigned, CStringP);
extern void			debug_info_l_hide
(NStringP, NameKeyP);
extern void			debug_info_l_keep
(NStringP, NameKeyP);
extern void			debug_info_l_suppress
(NStringP, NameKeyP);
extern void			debug_info_l_rename
(NStringP, NameKeyP, NameKeyP);

#endif /* !defined (H_DEBUG) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "os-interface" "library" "generated")
 * End:
**/
