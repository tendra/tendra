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
 * capsule.h - TDF capsule ADT.
 *
 * See the file "capsule.c" for more information.
 */

#ifndef H_CAPSULE
#define H_CAPSULE

#include "../os-interface.h"
#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>
#include "shape-table.h"
#include "tdf-read.h"
#include "tdf-write.h"
#include "unit-table.h"

struct LibCapsuleT;

#ifdef FS_NO_ENUM
typedef int CapsuleTypeT, *CapsuleTypeT *
#define CT_INPUT		(0)
#define CT_OUTPUT		(1)
#else
typedef enum {
    CT_INPUT,
    CT_OUTPUT
} CapsuleTypeT;
#endif /* defined (FS_NO_ENUM) */

typedef struct CapsuleT {
    CapsuleTypeT		type;
    union {
	TDFReaderT		reader;
	TDFWriterT		writer;
    } u;
    NStringT			contents;
    unsigned			capsule_index;
    char *			name;
    BoolT			complete;
} CapsuleT;

extern void			capsule_read_unit_set_file
(char *);
extern CapsuleT *		capsule_create_stream_input
(char *);
extern CapsuleT *		capsule_create_string_input
(char *, NStringT *);
extern CapsuleT *		capsule_create_stream_output
(char *);
extern char *			capsule_name
(CapsuleT *);
extern unsigned			capsule_byte
(CapsuleT *);
extern void			capsule_read
(CapsuleT *, UnitTableT *, ShapeTableT *);
extern void			capsule_store_contents
(CapsuleT *);
extern NStringT *		capsule_contents
(CapsuleT *);
extern void			capsule_set_index
(CapsuleT *, unsigned);
extern unsigned			capsule_get_index
(CapsuleT *);
extern void			capsule_write
(CapsuleT *, UnitTableT *, ShapeTableT *);
extern void			capsule_close
(CapsuleT *);
extern unsigned			capsule_get_major_version
(void);
extern void			capsule_set_major_version
(unsigned);
extern unsigned			capsule_get_minor_version
(void);

#endif /* !defined (H_CAPSULE) */

