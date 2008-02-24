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


/*
 * debug.h - Debugging routines.
 *
 * See the file "debug.c" for more information.
 */

#ifndef H_DEBUG
#define H_DEBUG

#include "os-interface.h"
#include <exds/common.h>
#include <exds/exception.h>
#include <exds/cstring.h>
#include <exds/dstring.h>
#include "adt/name-key.h"
#include <exds/ostream.h>

extern void			debug_set_file
(OStreamT *);

extern void			debug_info_u_name
(NStringT *);

extern void			debug_info_r_start_capsule
(char *);
extern void			debug_info_r_versions
(unsigned, unsigned);
extern void			debug_info_r_start_unit_decs
(unsigned);
extern void			debug_info_r_unit_dec
(NStringT *);
extern void			debug_info_r_start_shapes
(unsigned);
extern void			debug_info_r_shape
(NStringT *, unsigned);
extern void			debug_info_r_start_names
(unsigned);
extern void			debug_info_r_start_shape_names
(NStringT *, unsigned);
extern void			debug_info_r_name
(NameKeyT *, unsigned, unsigned, NameKeyT *);
extern void			debug_info_r_start_unit_sets
(unsigned);
extern void			debug_info_r_start_units
(NStringT *, unsigned);
extern void			debug_info_r_start_unit
(NStringT *, unsigned, unsigned);
extern void			debug_info_r_start_counts
(unsigned);
extern void			debug_info_r_count
(unsigned, NStringT *);
extern void			debug_info_r_start_maps
(unsigned);
extern void			debug_info_r_start_shape_maps
(NStringT *, unsigned);
extern void			debug_info_r_map
(unsigned, unsigned, unsigned);
extern void			debug_info_r_unit_body
(unsigned);
extern void			debug_info_r_tld_version
(unsigned);
extern void			debug_info_r_start_usages
(NStringT *, unsigned);
extern void			debug_info_r_usage
(unsigned, unsigned, NameKeyT *);
extern void			debug_info_r_end_capsule
(void);
extern void			debug_info_r_abort_capsule
(void);

extern void			debug_info_w_start_capsule
(char *);
extern void			debug_info_w_versions
(unsigned, unsigned);
extern void			debug_info_w_start_unit_decs
(unsigned);
extern void			debug_info_w_unit_dec
(NStringT *);
extern void			debug_info_w_start_shapes
(unsigned);
extern void			debug_info_w_shape
(NStringT *, unsigned);
extern void			debug_info_w_start_names
(unsigned);
extern void			debug_info_w_start_shape_names
(NStringT *, unsigned);
extern void			debug_info_w_name
(NameKeyT *, unsigned);
extern void			debug_info_w_start_unit_sets
(unsigned);
extern void			debug_info_w_start_units
(NStringT *, unsigned);
extern void			debug_info_w_start_unit
(NStringT *, unsigned, unsigned);
extern void			debug_info_w_start_counts
(unsigned);
extern void			debug_info_w_count
(unsigned, NStringT *);
extern void			debug_info_w_start_maps
(unsigned);
extern void			debug_info_w_start_shape_maps
(NStringT *, unsigned);
extern void			debug_info_w_map
(unsigned, unsigned);
extern void			debug_info_w_unit_body
(unsigned);
extern void			debug_info_w_tld_version
(unsigned);
extern void			debug_info_w_start_usages
(NStringT *);
extern void			debug_info_w_usage
(unsigned, NameKeyT *);
extern void			debug_info_w_end_capsule
(void);

extern void			debug_info_r_start_library
(char *);
extern void			debug_info_r_lib_versions
(unsigned, unsigned);
extern void			debug_info_r_library_version
(unsigned);
extern void			debug_info_r_start_capsules
(unsigned);
extern void			debug_info_r_capsule
(NStringT *, unsigned);
extern void			debug_info_r_start_index
(unsigned);
extern void			debug_info_r_start_shape_index
(NStringT *, unsigned);
extern void			debug_info_r_index_entry
(NameKeyT *, unsigned, unsigned, NameKeyT *, char *);
extern void			debug_info_r_end_library
(void);
extern void			debug_info_r_abort_library
(void);

extern void			debug_info_w_start_library
(char *);
extern void			debug_info_w_lib_versions
(unsigned, unsigned);
extern void			debug_info_w_library_version
(unsigned);
extern void			debug_info_w_start_capsules
(unsigned);
extern void			debug_info_w_capsule
(char *, unsigned);
extern void			debug_info_w_start_index
(unsigned);
extern void			debug_info_w_start_shape_index
(NStringT *, unsigned);
extern void			debug_info_w_index_entry
(NameKeyT *, unsigned, char *, unsigned);
extern void			debug_info_w_end_library
(void);

extern void			debug_info_l_not_needed
(NameKeyT *, NStringT *, unsigned);
extern void			debug_info_l_not_found
(NameKeyT *, NStringT *, unsigned);
extern void			debug_info_l_found
(NameKeyT *, NStringT *, unsigned, char *);
extern void			debug_info_l_hide
(NStringT *, NameKeyT *);
extern void			debug_info_l_keep
(NStringT *, NameKeyT *);
extern void			debug_info_l_suppress
(NStringT *, NameKeyT *);
extern void			debug_info_l_rename
(NStringT *, NameKeyT *, NameKeyT *);

#endif /* !defined (H_DEBUG) */

