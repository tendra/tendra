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
 * arg-data.h - Command line argument data ADT.
 *
 * See the file "arg-data.c" for more information.
 */

#ifndef H_ARG_DATA
#define H_ARG_DATA

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/cstring.h>
#include <exds/cstring-list.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>
#include "name-key.h"
#include <exds/ostream.h>

typedef struct ShapeControlEntryT {
    struct ShapeControlEntryT  *next;
    NStringT			shape;
    BoolT			all;
    NameKeyListT		names;
} ShapeControlEntryT;

typedef struct ShapeControlT {
    ShapeControlEntryT *	head;
} ShapeControlT;

typedef struct RenameControlEntryT {
    struct RenameControlEntryT *next;
    NStringT			shape;
    NameKeyPairListT		names;
} RenameControlEntryT;

typedef struct RenameControlT {
    RenameControlEntryT *	head;
} RenameControlT;

typedef struct ArgDataT {
    BoolT			all_hide_defined;
    BoolT			suppress_mult;
    ShapeControlT		hides;
    ShapeControlT		keeps;
    ShapeControlT		suppresses;
    RenameControlT		renames;
    BoolT			extract_all;
    BoolT			extract_basename;
    BoolT			extract_match_base;
    BoolT			content_index;
    BoolT			content_size;
    BoolT			content_version;
    BoolT			missing_definitions;
    OStreamT			debug_file;
    char *			default_output_file;
    char *			output_file;
    unsigned			num_library_files;
    unsigned			num_library_paths;
    union {
	struct {
	    CStringListT	file;
	    CStringListT	path;
	} list;
	struct {
	    const char *       *file;
	    const char *       *path;
	} vector;
    } library;
    char *			unit_file;
    unsigned			num_files;
    char *		       *files;
} ArgDataT;

extern void			shape_control_iter
	(ShapeControlT *, void(*)(NStringT *, BoolT, NameKeyListT *,
					   void *), void *);
extern void			rename_control_iter
	(RenameControlT *, void(*)(NStringT *, NameKeyPairListT *,
					    void *), void *);

extern void			arg_data_init
(ArgDataT *, char *);
extern void			arg_data_set_all_hide_defd
(ArgDataT *, BoolT);
extern BoolT			arg_data_get_all_hide_defd
(ArgDataT *);
extern void			arg_data_set_suppress_mult
(ArgDataT *, BoolT);
extern BoolT			arg_data_get_suppress_mult
(ArgDataT *);
extern void			arg_data_add_hide
(ArgDataT *, char *, char *);
extern void			arg_data_add_hide_defined
(ArgDataT *, char *);
extern ShapeControlT *	arg_data_get_hides
(ArgDataT *);
extern void			arg_data_add_keep
(ArgDataT *, char *, char *);
extern void			arg_data_add_keep_all
(ArgDataT *, char *);
extern ShapeControlT *	arg_data_get_keeps
(ArgDataT *);
extern void			arg_data_add_suppress
(ArgDataT *, char *, char *);
extern void			arg_data_add_suppress_all
(ArgDataT *, char *);
extern ShapeControlT *	arg_data_get_suppresses
(ArgDataT *);
extern void			arg_data_add_rename
(ArgDataT *, NStringT *, NameKeyT *, NameKeyT *);
extern void			arg_data_parse_rename
(ArgDataT *, char *, char *, char *);
extern RenameControlT *	arg_data_get_renames
(ArgDataT *);
extern void			arg_data_set_extract_all
(ArgDataT *, BoolT);
extern BoolT			arg_data_get_extract_all
(ArgDataT *);
extern void			arg_data_set_extract_basename
(ArgDataT *, BoolT);
extern BoolT			arg_data_get_extract_basename
(ArgDataT *);
extern void			arg_data_set_extract_match_base
(ArgDataT *, BoolT);
extern BoolT			arg_data_get_extract_match_base
(ArgDataT *);
extern void			arg_data_set_content_index
(ArgDataT *, BoolT);
extern BoolT			arg_data_get_content_index
(ArgDataT *);
extern void			arg_data_set_content_size
(ArgDataT *, BoolT);
extern BoolT			arg_data_get_content_size
(ArgDataT *);
extern void			arg_data_set_content_version
(ArgDataT *, BoolT);
extern BoolT			arg_data_get_content_version
(ArgDataT *);
extern void			arg_data_set_missing_definitions
(ArgDataT *, BoolT);
extern BoolT			arg_data_get_missing_definitions
(ArgDataT *);
extern void			arg_data_set_debug_file
(ArgDataT *, char *);
extern OStreamT *		arg_data_get_debug_file
(ArgDataT *);
extern void			arg_data_set_output_file
(ArgDataT *, char *);
extern char *			arg_data_get_output_file
(ArgDataT *);
extern void			arg_data_add_library_file
(ArgDataT *, char *);
extern void			arg_data_add_library_path
(ArgDataT *, char *);
extern void			arg_data_vector_libraries
(ArgDataT *);
extern unsigned			arg_data_num_library_files
(ArgDataT *);
extern unsigned			arg_data_num_library_paths
(ArgDataT *);
extern const char *	       *arg_data_library_files
(ArgDataT *);
extern const char *	       *arg_data_library_paths
(ArgDataT *);
extern void			arg_data_set_unit_file
(ArgDataT *, char *);
extern void			arg_data_set_files
(ArgDataT *, int, char * *);
extern unsigned			arg_data_get_num_files
(ArgDataT *);
extern char *		       *arg_data_get_files
(ArgDataT *);

#endif /* !defined (H_ARG_DATA) */

