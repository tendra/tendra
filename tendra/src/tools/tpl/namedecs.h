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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:57:25 $
$Revision: 1.1.1.1 $
$Log: namedecs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:25  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.3  1994/12/01  15:35:51  currie
 * Fixed common_tagdefs
 *
 * Revision 1.2  1994/07/21  10:36:27  currie
 * Added banner
 *
***********************************************************************/
#ifndef NAMEDECS_INCLUDED
#define NAMEDECS_INCLUDED

#include "units.h"


typedef struct{
	char *id;
	Name name;
} IdName;

typedef struct Sort_struct{
	int sort;
	struct Toksort_struct *toksort;
} Sort;
	/* sort of TOKEN is { token_sort , ptr to res and pars}
	   other sorts are  { X_sort, nil}
	 */


typedef struct Toksort_struct{
	Sort ressort;
	struct Tokpar_struct *pars;
} TokSort;
	/* if ressort is token then pars = nil */


typedef struct Tokpar_struct {
	Sort par;
	struct Tokpar_struct *next;
} Tokpar;


typedef struct Tokdec_struct {
	IdName idname;
	TokSort sort;
	struct Tokdec_struct *next;
	Bool isdeffed;
	Bool isused;
	Bool iskept;
	Bool isparam;
} Tokdec;

extern Tokdec *tokdecs;

typedef union {
	Name shtok;
	TDF tdfsh;
} Tagshape;

typedef struct Tagdec_struct {
	IdName idname;
	Bool isvar;
	Bool isdeffed;
	char hassh;
	Bool isused;
	Bool iskept;
	Bool iscommon;
	Tagshape sh;
	struct Tagdec_struct *next;
} Tagdec;

extern Tagdec *tagdecs;
extern Tagdec *localdecs;


typedef struct Al_tagdec_struct {
	IdName idname;
	struct Al_tagdec_struct *next;
	Bool isdeffed;
	Bool iskept;
	Bool isused;
} Al_tagdec;

extern Al_tagdec *al_tagdecs;

typedef struct Labdec_struct {
	IdName idname;
	Bool declared;
	struct Labdec_struct *next;
}  Labdec;

extern Labdec *labdecs;

extern Tokdec *find_tok(char *s);
extern Tagdec *find_tag(char *s);
extern Al_tagdec *find_al_tag(char *s);
extern Labdec *find_lab(char *s);

#define NEW_IDNAME(idn, s,ent)\
    (idn).id = s; (idn).name = next_name(ent);

#define LOCNAME(x)	(unsigned long)((x).name.unit_name)

#endif
