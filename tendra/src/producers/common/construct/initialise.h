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


#ifndef INITIALISE_INCLUDED
#define INITIALISE_INCLUDED


/*
    INITIALISATION ROUTINES

    The routines in this module are concerned with the initialisation of
    variables.
*/

extern EXP init_empty(TYPE, CV_SPEC, int, ERROR *);
extern EXP init_assign(TYPE, CV_SPEC, EXP, ERROR *);
extern EXP init_constr(TYPE, LIST(EXP), ERROR *);
extern EXP init_direct(TYPE, EXP, ERROR *);
extern EXP init_ref_lvalue(TYPE, EXP, ERROR *);
extern EXP init_array(TYPE, CV_SPEC, EXP, int, ERROR *);
extern EXP init_aggregate(TYPE, EXP, IDENTIFIER, ERROR *);
extern EXP init_general(TYPE, EXP, IDENTIFIER, int);
extern EXP dynamic_init(IDENTIFIER, string, EXP);
extern EXP destroy_general(TYPE, IDENTIFIER);
extern ERROR init_error(ERROR, int);
extern void init_initialise(void);
extern BUFFER field_buff;

extern MEMBER next_data_member(MEMBER, int);
extern EXP make_ref_init(TYPE, EXP);
extern EXP make_null_exp(TYPE);
extern EXP make_unit_exp(TYPE);
extern int is_null_exp(EXP);
extern EXP check_init(EXP);
extern unsigned long member_no;

extern EXP make_temporary(TYPE, EXP, EXP, int, ERROR *);
extern EXP remove_temporary(EXP, EXP);
extern IDENTIFIER made_temporary;
extern int keep_temporary;

extern int init_object(IDENTIFIER, EXP);
extern int init_member(IDENTIFIER, EXP);
extern void init_param(IDENTIFIER, EXP);
extern void allow_initialiser(IDENTIFIER);
extern int init_ref_force;


#endif
