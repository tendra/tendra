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


#ifndef NAMESPACE_INCLUDED
#define NAMESPACE_INCLUDED


/*
    NAMESPACE DECLARATIONS

    The routines in this module are concerned with the construction and
    manipulation of namespaces.
*/

extern void begin_declarator(IDENTIFIER, QUALIFIER, NAMESPACE, int);
extern void end_declarator(IDENTIFIER, int);
extern void begin_namespace(IDENTIFIER, int);
extern void end_namespace(int);
extern void alias_namespace(IDENTIFIER, NAMESPACE);
extern void using_namespace(NAMESPACE);
extern int use_namespace(NAMESPACE, NAMESPACE, NAMESPACE);
extern void target_decl(int, EXP);
extern void begin_decl_block(IDENTIFIER);
extern int end_decl_block(IDENTIFIER, int);
extern void clear_decl_blocks(void);
extern NAMESPACE find_namespace(IDENTIFIER);
extern NAMESPACE find_nspace_id(IDENTIFIER);
extern int has_linkage(IDENTIFIER);

extern NAMESPACE make_namespace(IDENTIFIER, unsigned, int);
extern NAMESPACE make_global_nspace(const char *, int);
extern void uncache_namespace(NAMESPACE, int);
extern void add_namespace(NAMESPACE);
extern void remove_namespace(void);
extern void push_namespace(NAMESPACE);
extern void store_namespace(NAMESPACE);
extern NAMESPACE pop_namespace(void);
extern NAMESPACE restore_namespace(void);
extern int add_nested_nspace(NAMESPACE);
extern int remove_nested_nspace(NAMESPACE);
extern int is_subnspace(NAMESPACE, NAMESPACE);
extern void update_namespace(void);
extern void check_hiding(IDENTIFIER);
extern void init_namespace(void);

extern MEMBER search_member(NAMESPACE, HASHID, int);
extern IDENTIFIER search_id(NAMESPACE, HASHID, int, int);
extern IDENTIFIER find_id(HASHID);
extern IDENTIFIER find_type_id(HASHID, int);
extern IDENTIFIER find_qual_id(NAMESPACE, HASHID, int, int);
extern IDENTIFIER find_extern_id(HASHID, NAMESPACE, int);
extern IDENTIFIER check_id(NAMESPACE, IDENTIFIER, int);
extern IDENTIFIER type_member(MEMBER, int);
extern MEMBER update_member(NAMESPACE, MEMBER);
extern void set_type_member(MEMBER, IDENTIFIER);
extern void set_member(MEMBER, IDENTIFIER);
extern void clear_member(NAMESPACE, HASHID);
extern IDENTIFIER find_op_id(HASHID);
extern void remove_id(IDENTIFIER);

extern STACK(NAMESPACE) local_nspace_stack;
extern STACK(NAMESPACE) crt_nspace_stack;
extern STACK(NAMESPACE) namespace_stack;
extern NAMESPACE nonblock_namespace;
extern NAMESPACE nonclass_namespace;
extern NAMESPACE global_namespace;
extern NAMESPACE token_namespace;
extern NAMESPACE last_namespace;
extern NAMESPACE qual_namespace;
extern NAMESPACE crt_namespace;
extern NAMESPACE c_namespace;
extern int old_cache_lookup;
extern int cache_lookup;


#endif
