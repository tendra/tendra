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
/*
 *			    VERSION INFORMATION
 *			    ===================
 *
 *--------------------------------------------------------------------------
 *$Header$
 *--------------------------------------------------------------------------*/


#include "config.h"
#include "common_types.h"
#include "exp.h"
#include "expmacs.h"
#include "exptypes.h"
#include "shapemacs.h"
#include "tags.h"
#include "install_fns.h"
#include "instrs.h"
#include "special_exps.h"
#include "utility.h"

/************************************************************************
 *  Make an exp representing the contents of an external tag with
 *  name n of shape s and variable if v.
 ************************************************************************/

exp
make_extn(char* n, shape s, int v)
{
	dec * g = alloc_nof (dec, 1);
	exp id = getexp (s, 0, 1, 0, 0, 0, 0, ident_tag);
	exp nme = getexp (s, 0, 1, id, 0, 0, 0, name_tag);
	setglob (id);
	if (v) {
		setvar(id);
	}
	brog(id) = g;
	g -> dec_u.dec_val.dec_exp = id;
	g -> dec_u.dec_val.dec_id = n;
	g -> dec_u.dec_val.extnamed = 1;
	return (nme);
}

/************************************************************************
 *  Make an exp representing a dummy double destination used to force a
 *  floating point overflow (if any) for expression with zero destination.
 ************************************************************************/
exp
get_dummy_double_dest()
{
	return (make_extn("___m68k_dummy_double", doublesh, 1));
}


/************************************************************************
 *  Make an exp representing the stack limit
 ************************************************************************/
exp
get_stack_limit()
{
	return make_extn ("___m68k_stack_limit", ulongsh, 1);
}

/************************************************************************
 *  Make an exp representing the error handler
 ************************************************************************/
exp
get_error_handler()
{
	return make_extn ("___m68k_errhandler", ulongsh, 1);
}
/************************************************************************
 *  Make an exp representing env_size
 ************************************************************************/
exp
get_env_size(dec *decl)
{
	/* allocate space for 10 digits 2 prefix characters and a null */
	char* lab_name = alloc_nof (char, 13);
	sprintf(lab_name, "#%c%lu", LPREFIX, (unsigned long) decl);
	return make_extn (lab_name, ulongsh, 1);
}

