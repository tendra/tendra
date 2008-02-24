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


/*** library.h --- TDF library ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "library.c" for more information.
 *
 *** Change Log:
 * $Log: library.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/09/22  08:39:20  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.3  1995/07/07  15:32:28  smf
 * Updated to support TDF specification 4.0.
 *
 * Revision 1.2  1994/12/12  11:46:25  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:32  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_LIBRARY
#define H_LIBRARY

#include "os-interface.h"
#include "capsule.h"
#include "dalloc.h"
#include "shape-table.h"
#include "tdf-read.h"
#include "tdf-write.h"

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int LibraryTypeT, *LibraryTypeP;
#define LT_INPUT		(0)
#define LT_OUTPUT		(1)
#else
typedef enum {
    LT_INPUT,
    LT_OUTPUT
} LibraryTypeT, *LibraryTypeP;
#endif /* defined (FS_NO_ENUM) */

struct LibraryT;

typedef struct LibCapsuleT {
    struct LibraryT	       *library;
    char *			name;
    NStringT			contents;
    BoolT			loaded;
} LibCapsuleT, *LibCapsuleP;

typedef struct LibraryT {
    LibraryTypeT		type;
    union {
	TDFReaderT		reader;
	TDFWriterT		writer;
    } u;
    char *			name;
    unsigned			num_capsules;
    LibCapsuleP			capsules;
    unsigned			major;
    unsigned			minor;
    BoolT			complete;
} LibraryT, *LibraryP;

/*--------------------------------------------------------------------------*/

extern char *			lib_capsule_name
(LibCapsuleP);
extern char *			lib_capsule_full_name
(LibCapsuleP);
extern NStringP			lib_capsule_contents
(LibCapsuleP);
extern BoolT			lib_capsule_is_loaded
(LibCapsuleP);
extern void			lib_capsule_loaded
(LibCapsuleP);

extern void			write_lib_capsule_full_name
(OStreamP, LibCapsuleP);

extern LibraryP			library_create_stream_input
(char *);
extern LibraryP			library_create_stream_output
(char *);
extern char *			library_name
(LibraryP);
extern unsigned			library_num_capsules
(LibraryP);
extern LibCapsuleP		library_get_capsule
(LibraryP, unsigned);
extern unsigned			library_byte
(LibraryP);
extern void			library_content
(LibraryP, BoolT, BoolT, BoolT);
extern void			library_extract_all
(LibraryP, BoolT);
extern void			library_extract
(LibraryP, BoolT, BoolT, unsigned, char * *);
extern void			library_read
(LibraryP, ShapeTableP);
extern void			library_write
(LibraryP, ShapeTableP, unsigned, CapsuleP *);
extern void			library_close
(LibraryP);

#endif /* !defined (H_LIBRARY) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
