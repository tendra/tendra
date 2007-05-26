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


#ifndef COMMON_INCLUDED
#define COMMON_INCLUDED

/*
 * DECLARATIONS FOR TYPE MANIPULATION ROUTINES
 */

extern ALGEBRA_DEFN *algebra;
extern void new_algebra(void);
extern ALGEBRA_DEFN *find_algebra(char *);
extern TYPE_P find_type(ALGEBRA_DEFN *, char *);
extern TYPE_P register_type(TYPE_P);
extern int is_identity_type(TYPE_P);
extern TYPE_P compound_type(unsigned, TYPE_P, int);
extern void check_types(void);
extern void import_type(char *, char *);
extern void import_algebra(char *);
extern int size_type(TYPE_P, int);
extern char *name_type(TYPE_P);
extern char *name_aux_type(TYPE_P);
extern int is_complex_type(TYPE_P);


/*
 * MACROS FOR BASIC CLASS SIZES
 *
 * These macros give the sizes of the basic types.
 */

#define SIZE_PRIM	1
#define SIZE_ENUM	1
#define SIZE_UNION	1
#define SIZE_PTR	1
#define SIZE_LIST	1
#define SIZE_STACK	1
#define SIZE_VEC	3
#define SIZE_VEC_PTR	2


/*
 * MAXIMUM DEPTH OF TYPE CONSTRUCTORS
 *
 * This macro is used to limit the level of type constructors which can
 * be used.  In particular, it is used in the detection of cyclic types.
 */

#define MAX_TYPE_DEPTH	1000


#endif
