/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED


/*
 *    TABLES OF CONSTRUCTS
 */

extern construct **cons_table;
extern construct **var_table;
extern construct **cons_hash_tables;


/*
 *    TABLES OF SORT INFORMATION
 */

typedef node *(*decode_func)(void) ;
typedef node *(*read_func)(long) ;
extern long *sort_count;
extern char *sort_letters;
extern int *sort_encoding;
extern int *sort_extension;
extern long *sort_tokens;
extern long *sort_conds;
extern long *sort_removed;
extern decode_func *sort_decode;
extern read_func *sort_read;


/*
 *    SPECIAL CONSTRUCTS
 */

extern construct bytestream_cons;
extern construct false_cons;
extern construct optional_cons;
extern construct string_cons;
extern construct token_cons;
extern construct true_cons;
extern construct unknown_cons;
extern construct exp_shape;
extern construct shape_of;


/*
 *    OUTPUT FLAGS
 */

extern boolean show_tokdecs;
extern boolean show_tokdefs;
extern boolean show_aldecs;
extern boolean show_aldefs;
extern boolean show_tagdecs;
extern boolean show_tagdefs;


/*
 *    TABLE MANIPULATION ROUTINES
 */

extern void init_tables(void) ;
extern construct *add_to_cons_hash(construct *, sortname) ;
extern construct *search_cons_hash(char *, sortname) ;
extern construct *add_to_var_hash(construct *, sortname) ;
extern construct *search_var_hash(char *, sortname) ;
extern void remove_var_hash(char *, sortname) ;
extern construct *removals;


/*
 *    TABLE UTILITY ROUTINES
 */

extern BoolT order_names;
typedef void (*apply_func)(construct *) ;
extern char *sort_name(sortname) ;
extern void sort_table(construct **, sortname) ;
extern void sort_all(void) ;
extern void apply_to_all(apply_func, sortname) ;


/*
 *    AUXILIARY TABLE ROUTINES
 */

extern void new_sort(sortname, int) ;
extern void new_cons(char *, sortname, int, char *) ;


/*
 *    MACRO FOR ACCESSING CONSTRUCTS
 */

#define cons_no(X, Y)		(cons_table [ (X) ] + (Y))


#endif
