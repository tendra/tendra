/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
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


#ifndef CLASS_INCLUDED
#define CLASS_INCLUDED


/*
 *    CLASS AND ENUMERATION TYPE DECLARATIONS
 *
 *    The routines in this module are concerned with the construction of class
 *    and enumeration types.
 */

extern IDENTIFIER begin_class_defn(IDENTIFIER, BASE_TYPE, CLASS_INFO, TYPE);
extern IDENTIFIER end_class_defn(IDENTIFIER);
extern IDENTIFIER find_elaborate_type(IDENTIFIER, BASE_TYPE, TYPE, DECL_SPEC);
extern IDENTIFIER make_class(NAMESPACE, HASHID, BASE_TYPE, DECL_SPEC, TYPE, TYPE);
extern CLASS_TYPE parent_class(IDENTIFIER);
extern CLASS_TYPE namespace_class(NAMESPACE);
extern void copy_members(CLASS_TYPE, CLASS_TYPE, CLASS_INFO, int);
extern TYPE copy_class(TYPE, DECL_SPEC);
extern IDENTIFIER find_copied(IDENTIFIER, IDENTIFIER, int);
extern ERROR class_info(CLASS_TYPE, CLASS_INFO, int);
extern ERROR check_trivial_class(CLASS_TYPE);
extern CLASS_INFO check_member_type(CLASS_TYPE, CLASS_INFO, TYPE, int);
extern CLASS_INFO check_class_info(CLASS_INFO, CLASS_INFO, int, DECL_SPEC);
extern BASE_TYPE find_class_key(CLASS_TYPE);
extern int equal_key(BASE_TYPE, BASE_TYPE);
extern TYPE make_dummy_class(IDENTIFIER, LIST (TOKEN), BASE_TYPE);
extern int is_defined(IDENTIFIER, TYPE *, int);
extern int is_local_nspace(NAMESPACE);
extern CLASS_TYPE find_class(IDENTIFIER);
extern TYPE make_class_type(CLASS_TYPE);
extern int is_empty_class(TYPE);

extern IDENTIFIER begin_enum_defn(IDENTIFIER, TYPE);
extern IDENTIFIER make_enumerator(IDENTIFIER, IDENTIFIER, EXP);
extern IDENTIFIER find_enumerator(ENUM_TYPE, NAT);
extern IDENTIFIER end_enum_defn(IDENTIFIER);
extern IDENTIFIER make_typedef(NAMESPACE, HASHID, TYPE, DECL_SPEC);
extern IDENTIFIER constr_name(NAMESPACE, IDENTIFIER);
extern int defining_class(CLASS_TYPE);
extern void push_class(CLASS_TYPE);
extern void pop_class(void);
extern int found_elaborate_type;
extern CLASS_TYPE crt_class;


#endif
