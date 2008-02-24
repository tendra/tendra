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
 * library.h - TDF library ADT.
 *
 * See the file "library.c" for more information.
 */

#ifndef H_LIBRARY
#define H_LIBRARY

#include "capsule.h"
#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include "shape-table.h"
#include "tdf-read.h"
#include "tdf-write.h"

typedef enum {
    LT_INPUT,
    LT_OUTPUT
} LibraryTypeT;

struct LibraryT;

typedef struct LibCapsuleT {
    struct LibraryT	       *library;
    char *			name;
    NStringT			contents;
    BoolT			loaded;
} LibCapsuleT;

typedef struct LibraryT {
    LibraryTypeT		type;
    union {
	TDFReaderT		reader;
	TDFWriterT		writer;
    } u;
    char *			name;
    unsigned			num_capsules;
    LibCapsuleT *		capsules;
    unsigned			major;
    unsigned			minor;
    BoolT			complete;
} LibraryT;

extern char *			lib_capsule_name
(LibCapsuleT *);
extern char *			lib_capsule_full_name
(LibCapsuleT *);
extern NStringT *		lib_capsule_contents
(LibCapsuleT *);
extern BoolT			lib_capsule_is_loaded
(LibCapsuleT *);
extern void			lib_capsule_loaded
(LibCapsuleT *);

extern void			write_lib_capsule_full_name
(OStreamT *, LibCapsuleT *);

extern LibraryT *		library_create_stream_input
(char *);
extern LibraryT *		library_create_stream_output
(char *);
extern char *			library_name
(LibraryT *);
extern unsigned			library_num_capsules
(LibraryT *);
extern LibCapsuleT *	library_get_capsule
(LibraryT *, unsigned);
extern unsigned			library_byte
(LibraryT *);
extern void			library_content
(LibraryT *, BoolT, BoolT, BoolT);
extern void			library_extract_all
(LibraryT *, BoolT);
extern void			library_extract
(LibraryT *, BoolT, BoolT, unsigned, char * *);
extern void			library_read
(LibraryT *, ShapeTableT *);
extern void			library_write
(LibraryT *, ShapeTableT *, unsigned, CapsuleT **);
extern void			library_close
(LibraryT *);

#endif /* !defined (H_LIBRARY) */

