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


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/




#include "config.h"
#include "common_types.h"
#include "readglob.h"
#include "table_fns.h"
#include "basicread.h"
#include "sortmacs.h"
#include "shapemacs.h"
#include "expmacs.h"
#include "tags.h"
#include "main_reads.h"
#include "natmacs.h"
#include "install_fns.h"
#include "diag_fns.h"
#include "xalloc.h"


#ifdef NEWDIAGS


/* allocate space in this file */
#define EXTERN_DIAG

#include "diagglob.h"
#include "dg_globs.h"
#include "dg_aux.h"
#include "externs.h"


diag_descriptor f_dummy_diag_descriptor;
diag_tag f_dummy_diag_tag;
diag_tagdef f_dummy_diag_tagdef;
diag_type f_dummy_diag_type;
diag_tq f_dummy_diag_tq;
filename f_dummy_filename;
sourcemark f_dummy_sourcemark;


#define DEBUG(x) x


static dg_filename primary_file = (dg_filename)0;

static nat zero_nat;


static dg_tag
dg_tag_void_star,
	dg_tag_signed_char, dg_tag_unsigned_char,
	dg_tag_short, dg_tag_unsigned_short,
	dg_tag_int, dg_tag_unsigned_int,
	dg_tag_long_long, dg_tag_unsigned_long_long,
	dg_tag_float, dg_tag_double, dg_tag_long_double,
	dg_tag_complex, dg_tag_double_complex, dg_tag_long_double_complex;


extern shape shcomplexsh;
extern shape complexsh;
extern shape complexdoublesh;

static dg_tag
make_bastype(char * s)
{
	dg_tag ans = (dgtag_struct *) xmalloc (sizeof(dgtag_struct));
	init_dgtag (ans);
	ans->outref.k = LAB_STR;
	ans->outref.u.s = s;
	return ans;
}

static int tags_initialised = 0;

static void
init_basic_diag_tags()
{
	dg_tag_void_star		= make_bastype ("__D_void_star");
	dg_tag_signed_char		= make_bastype ("__D_signed_char");
	dg_tag_unsigned_char		= make_bastype ("__D_unsigned_char");
	dg_tag_short			= make_bastype ("__D_short");
	dg_tag_unsigned_short		= make_bastype ("__D_unsigned_short");
	dg_tag_int			= make_bastype ("__D_int");
	dg_tag_unsigned_int		= make_bastype ("__D_unsigned_int");
	dg_tag_long_long		= make_bastype ("__D_long_long");
	dg_tag_unsigned_long_long	= make_bastype ("__D_unsigned_long_long");
	dg_tag_float			= make_bastype ("__D_float");
	dg_tag_double			= make_bastype ("__D_double");
	dg_tag_long_double		= make_bastype ("__D_long_double");
	dg_tag_complex		= make_bastype ("__D_complex");
	dg_tag_double_complex		= make_bastype ("__D_double_complex");
	dg_tag_long_double_complex	= make_bastype ("__D_long double_complex");
	tags_initialised = 1;
}

static shape
basic_tag_shape(dg_tag t)
{
	if (t == dg_tag_void_star)
		return f_pointer (f_alignment (scharsh));
	if (t == dg_tag_signed_char)
		return scharsh;
	if (t == dg_tag_unsigned_char)
		return ucharsh;
	if (t == dg_tag_short)
		return swordsh;
	if (t == dg_tag_unsigned_short)
		return uwordsh;
	if (t == dg_tag_int)
		return slongsh;
	if (t == dg_tag_unsigned_int)
		return ulongsh;
	if (t == dg_tag_long_long)
		return s64sh;
	if (t == dg_tag_unsigned_long_long)
		return u64sh;
	if (t == dg_tag_float)
		return shrealsh;
	if (t == dg_tag_double)
		return realsh;
	if (t == dg_tag_long_double)
		return doublesh;
	if (t == dg_tag_complex)
		return shcomplexsh;
	if (t == dg_tag_double_complex)
		return complexsh;
	if (t == dg_tag_long_double_complex)
		return complexdoublesh;
	failer ("unexpected bitfield type");
	return slongsh;
}





/*----------------------- diagdef and diag_descriptor  lists ----------------*/

void
start_make_diagdef_unit(int toks, int tags,
						int als, int diagtags)
{
	int i;
	
	if (!tags_initialised)
		init_basic_diag_tags ();
	
	unit_no_of_tokens = toks;
	unit_ind_tokens = (tok_define * *)xcalloc(unit_no_of_tokens,
											  sizeof(tok_define *));
	for (i = 0; i < unit_no_of_tokens; ++i)
		unit_ind_tokens[i] = (tok_define*)0;
	
	unit_no_of_tags = tags;
	unit_ind_tags = (dec * *)xcalloc(unit_no_of_tags,
									 sizeof(dec *));
	for (i = 0; i < unit_no_of_tags; ++i)
		unit_ind_tags[i] = (dec*)0;
	
	unit_no_of_als = als;
	unit_ind_als = (aldef * *)xcalloc(unit_no_of_als,
									  sizeof(aldef *));
	for (i = 0; i < unit_no_of_als; ++i)
		unit_ind_als[i] = (aldef*)0;
	
	unit_no_of_diagtags = diagtags;
	unit_ind_diagtags = (diag_tagdef * *)xcalloc(unit_no_of_diagtags,
												 sizeof(diag_tagdef *));
	for (i = 0; i < unit_no_of_diagtags; ++i)
		unit_ind_diagtags[i] = (diag_tagdef *)0;
	
	return;
}

void
init_diag_unit()
{
	return;
}

diag_unit
f_build_diag_unit(tdfint labels, diag_descriptor_list descriptors)
{
	UNUSED(labels); UNUSED(descriptors);
	failer("f_build_diag_unit isn't really here");
	exit(EXIT_FAILURE);
}

diag_type_unit
f_build_diagtype_unit(tdfint labels, diag_tagdef_list descriptors)
{
	UNUSED(labels); UNUSED(descriptors);
	failer("f_build_diagtype_unit isn't really here");
	exit(EXIT_FAILURE);
}


void
f_make_diagdef_unit()
{
	int i;
	int j = 0;
	int no_of_labels;
	int was_within_diags;
	
	for (i = 0; i < unit_no_of_tokens; ++i)
	{
		if (unit_ind_tokens[i] == (tok_define*)0)
			unit_ind_tokens[i] = &unit_toktab[j++];
	};
	
	j = 0;
	for (i = 0; i < unit_no_of_tags; ++i)
	{
		if (unit_ind_tags[i] == (dec*)0)
			unit_ind_tags[i] = &unit_tagtab[j++];
	};
	
	j = 0;
	for (i = 0; i < unit_no_of_als; ++i)
	{
		if (unit_ind_als[i] == (aldef*)0)
			unit_ind_als[i] = &unit_altab[j++];
	};
	
	j=0;
	for (i = 0; i < unit_no_of_diagtags; ++i)
	{
		if (unit_ind_diagtags[i] == (diag_tagdef *)0)
			unit_ind_diagtags[i] = &unit_diag_tagdeftab[j++];
	};
	
	was_within_diags = within_diags;
	within_diags = 1;
	{
		dg_compilation * comp_unit_ptr = &all_comp_units;
		dg_compilation ans;
		dg_name_list desc_list;
		while (* comp_unit_ptr)
			comp_unit_ptr = &(* comp_unit_ptr)->another;
		primary_file = (dg_filename)0;
		start_bytestream();
		no_of_labels = small_dtdfint();
		unit_no_of_labels = no_of_labels;
		unit_labtab = (exp*)xcalloc(unit_no_of_labels, sizeof(exp));
		desc_list = d_diag_descriptor_list();
		end_bytestream();
		if (!primary_file)
			primary_file = get_filename ((long)0, "", "", "no_source_file");
		(* comp_unit_ptr) = ans = (dg_compilation) xmalloc (sizeof (struct dg_comp_t));
		ans->prim_file = primary_file;
		ans->comp_deps = new_string_list (0);
		ans->date = 0;
		ans->language = 1;	/* assume ANSI C */
		ans->id_case = 0;	/* case sensitive */
		ans->producer = "TenDRA";
		ans->comp_dir = get_filename ((long)0, "", "unknown directory", "");
		ans->options = new_string_list (0);
		ans->dn_list = desc_list;
		ans->macros = new_dg_macro_list (0);
		ans->another = (dg_compilation)0;
	}
	within_diags = was_within_diags;
	return;
}


diag_descriptor
f_diag_desc_id(tdfstring n, sourcemark whence,
			   exp acc, diag_type new_type)
{
	dg_idname nid;
	if (brog(son(acc))->dec_u.dec_val.extnamed)
		nid = f_dg_external_idname (n);
	else
		nid = f_dg_sourcestring_idname (n);
	if (new_type->key == DGT_PROC && !isvar(son(acc)))
		return f_dg_proc_name (
			nid,
			whence,
			new_type,
			yes_exp_option (diag_locate (acc)),
			no_dg_accessibility_option,
			no_dg_virtuality_option,
			f_false,
			no_dg_type_list_option,
			no_dg_tag_option);
	else
		return f_dg_object_name (
			nid,
			whence,
			new_type,
			yes_exp_option (diag_locate (acc)),
			no_dg_accessibility_option);
}

diag_descriptor
f_diag_desc_struct(tdfstring n, sourcemark whence,
				   diag_type new_type)
{
	UNUSED (n);
	UNUSED (whence);
	UNUSED (new_type);
	failer ("diag_desc_struct is obsolete");
	return f_dummy_diag_descriptor;
}

diag_descriptor
f_diag_desc_typedef(tdfstring n, sourcemark whence,
					diag_type new_type)
{
	if (!new_type || (new_type->key == DGT_TAGGED &&
					  new_type->data.t_tag->key == DGK_NONE))
		return (dg_name)0;		/* no type definition for __va_list etc */
	return f_dg_type_name (
		f_dg_sourcestring_idname (n),
		whence,
		no_dg_accessibility_option,
		yes_dg_type_option (new_type),
		f_false,
		no_bool_option,
		no_dg_constraint_list_option);
}

void
init_diag_descriptor()
{
	return;
}

diag_descriptor_list
new_diag_descriptor_list(int n)
{
	return new_dg_name_list (n);
}

diag_descriptor_list
add_diag_descriptor_list(diag_descriptor_list list,
						 diag_descriptor elem,
						 int index)
{
	if (!elem)		/* no type definition for __va_list etc */
		return list;
	return add_dg_name_list (list, elem, index);
}

/*---------------------------- diag_tq--------------------------*/

diag_tq f_diag_tq_null = 0;

diag_tq
f_add_diag_const(diag_tq qual)
{
	return (qual | (1 << DG_CONST_T));
}

diag_tq
f_add_diag_volatile(diag_tq qual)
{
	return (qual | (1 << DG_VOL_T));
}

/*--------------------------diag_type -----------------------------*/

diag_type f_diag_type_null = (dg_type)0;

diag_type
f_diag_type_apply_token(token token_value,
						bitstream token_args)
{
	tokval v;
	v = apply_tok(token_value, token_args,  DIAG_TYPE_SORT, (tokval*)0);
	return v.tk_diag_type;
}

diag_type
f_diag_array(diag_type element_type, exp stride,
			 exp lower_bound, exp upper_bound,
			 diag_type index_type)
{
	return f_dg_array_type (
		element_type,
		stride,
		no_bool_option,
		add_dg_dim_list (new_dg_dim_list (1),
						 f_dg_bounds_dim (
							 f_dg_static_bound (lower_bound),
							 f_dg_static_bound (upper_bound),
							 index_type),
						 0));
}

diag_type
f_diag_bitfield(diag_type typ, nat number_of_bits)
{
	shape sha;
	if (typ->key == DGT_BASIC)
		sha = typ->data.t_bas.b_sh;
	else
		if (typ->key == DGT_ENUM)
			sha = typ->data.t_enum.sha;
		else
			if (typ->key == DGT_TAGGED && typ->data.t_tag->outref.k == LAB_STR)
				sha = basic_tag_shape (typ->data.t_tag);
			else {
				failer ("unexpected bitfield type");
				sha = slongsh;
			}
	return f_dg_bitfield_type (
		typ,
		f_bfvar_bits (((name(sha) & 1) ? 1 : 0), number_of_bits),
		sha);
}


diag_type
f_diag_enum(diag_type base_type, tdfstring enum_name,
			enum_values_list values)
{
	UNUSED (base_type);
	return f_dg_enum_type (
		values,
		yes_dg_idname_option (f_dg_sourcestring_idname (enum_name)),
		no_dg_sourcepos_option,
		sh(son(values.array->value)),
		f_false);
}


diag_type
f_diag_floating_variety(floating_variety var)
{
	switch (var) {
    case shrealfv:
		return (f_dg_named_type (dg_tag_float));
    case realfv:
		return (f_dg_named_type (dg_tag_double));
    case doublefv:
		return (f_dg_named_type (dg_tag_long_double));
    case shcomplexfv:
		return (f_dg_named_type (dg_tag_complex));
    case complexfv:
		return (f_dg_named_type (dg_tag_double_complex));
    case complexdoublefv:
		return (f_dg_named_type (dg_tag_long_double_complex));
	}
	failer ("bad variety");
	return f_dummy_diag_type;
}

diag_type
f_diag_loc(diag_type object, diag_tq qualifier)
{
	if (qualifier & (1 << DG_CONST_T))
		object = f_dg_qualified_type (DG_CONST_T, object);
	if (qualifier & (1 << DG_VOL_T))
		object = f_dg_qualified_type (DG_VOL_T, object);
	return object;
}

diag_type
f_diag_proc(diag_type_list params, bool optional_args,
			diag_type result_type)
{
	int i;
	dg_param_list plist;
	dg_param thispar;
	procprops_option prps = no_procprops_option;
	if (params.len == 1 && !params.array[0])
		params.len = 0;
	plist = new_dg_param_list (params.len);
	for (i=0; i<params.len; i++) {
		if (!params.array[i])
			failer ("dummy parameter?");
		thispar = f_dg_object_param (
			no_dg_idname_option,
			no_dg_sourcepos_option,
			no_dg_param_mode_option,
			params.array[i],
			no_dg_default_option);
		plist = add_dg_param_list (plist, thispar, i);
	}
	if (optional_args)
		prps = yes_procprops_option (f_var_callers);
	return f_dg_proc_type (plist, result_type, no_bool_option,
						   no_nat_option, no_nat_option, prps);
}


diag_type
f_diag_ptr(diag_type object, diag_tq qualifier)
{
	dg_type ptr = (object ? f_dg_pointer_type (object, no_bool_option)
				   : f_dg_named_type (dg_tag_void_star));
	return f_diag_loc (ptr, qualifier);
}

diag_type
f_diag_struct(shape tdf_shape, tdfstring n,
			  diag_field_list fields)
{
	return f_dg_struct_type (
		fields,
		yes_shape_option (tdf_shape),
		yes_dg_idname_option (f_dg_sourcestring_idname (n)),
		no_dg_sourcepos_option,
		no_dg_varpart_option,
		f_false,
		f_false);
}

diag_type
f_diag_union(shape tdf_shape, tdfstring n,
			 diag_field_list fields)
{
	return f_dg_struct_type (
		fields,
		yes_shape_option (tdf_shape),
		yes_dg_idname_option (f_dg_sourcestring_idname (n)),
		no_dg_sourcepos_option,
		no_dg_varpart_option,
		f_true,
		f_false);
}

diag_type
f_diag_variety(variety var)
{
	switch (name(var)) {
    case scharhd:
		return (f_dg_named_type (dg_tag_signed_char));
    case ucharhd:
		return (f_dg_named_type (dg_tag_unsigned_char));
    case swordhd:
		return (f_dg_named_type (dg_tag_short));
    case uwordhd:
		return (f_dg_named_type (dg_tag_unsigned_short));
    case slonghd:
		return (f_dg_named_type (dg_tag_int));
    case ulonghd:
		return (f_dg_named_type (dg_tag_unsigned_int));
    case s64hd:
		return (f_dg_named_type (dg_tag_long_long));
    case u64hd:
		return (f_dg_named_type (dg_tag_unsigned_long_long));
	}
	failer ("bad variety");
	return f_dummy_diag_type;
}

void
init_diag_type()
{
	zero_nat.nat_val.small_nat = 0;
	zero_nat.issmall = 1;
	return;
}

/*-------------------------- DIAG TYPE HELPERS ---------------------*/
/*---------------------------enum_values ---------------------------*/

enum_values
f_make_enum_values(exp value, tdfstring n)
{
	return f_make_dg_enum (
		value,
		f_dg_sourcestring_idname (n),
		f_dg_null_sourcepos);
}

void
init_enum_values()
{
	return;
}

enum_values_list
new_enum_values_list(int n)
{
	return new_dg_enum_list (n);
}

enum_values_list
add_enum_values_list(enum_values_list list,
					 enum_values elem, int index)
{
	return add_dg_enum_list (list, elem, index);
}

/*--------------------------struct fields-------------------------*/
diag_field
f_make_diag_field(tdfstring field_name, exp wh,
				  diag_type field_type)
{
	return f_dg_field_classmem (
		f_dg_sourcestring_idname (field_name),
		f_dg_null_sourcepos,
		wh,
		field_type,
		no_dg_accessibility_option,
		no_bool_option,
		no_dg_default_option);
}

void
init_diag_field()
{
	return;
}

diag_field_list
new_diag_field_list(int n)
{
	return new_dg_classmem_list (n);
}

diag_field_list
add_diag_field_list(diag_field_list list,
					diag_field elem, int index)
{
	return add_dg_classmem_list (list, elem, list.len - index - 1);
}

/*----------------------diag type list----------------------*/
diag_type_list
new_diag_type_list(int n)
{
	return new_dg_type_list (n);
}

diag_type_list
add_diag_type_list(diag_type_list list, diag_type elem,
				   int index)
{
	return add_dg_type_list (list, elem, index);
}
/*----------------------------END HELPERS------------------------------------*/

/*-------------------------- sourcemark ---------------------------------*/

sourcemark
f_make_sourcemark(filename file, nat line_no,
				  nat char_offset)
{
	return f_dg_mark_sourcepos (file, line_no, char_offset);
}

void
init_sourcemark()
{
	return;
}

/*------------------------------filename ------------------------*/

filename
f_make_filename(nat date, tdfstring machine,
				tdfstring file)
{
	filename f;
	tdfstring path;
	char * dot;
	path.size = 8;
	path.number = 0;
	path.ints.chars = "";
	f = f_make_dg_filename (date,  machine, path, file);
	if (!primary_file && (dot = strrchr (f->file_name, '.'), !dot || dot[1] != 'h'))
		primary_file = f;
	return f;
}


filename
f_filename_apply_token(token token_value,
					   bitstream token_args)
{
	tokval v;
	v = apply_tok(token_value, token_args, DIAG_FILENAME, (tokval*)0);
	return v.tk_filename;
}

/*----------------------------- diag tag ------------------------------*/


void
init_diag_tag()
{
	return;
}

diag_tag
f_make_diag_tag(tdfint num)
{
	int index = natint(num);
	if (index >= unit_no_of_diagtags)
		failer("make_dg_tag out of range");
	return unit_ind_diagtags[index];
}


/*---------------------------- diag_tagdef =diag_typeunit ------------------*/

static dg_name_list s_tags;

void
init_diag_tagdef()
{
	return;
}

diag_tagdef
f_make_diag_tagdef(tdfint t, diag_type dtype)
{
	dg_tag tg = f_make_diag_tag (t);
	IGNORE f_dg_tag_type (tg, dtype);
	if ((dtype->key == DGT_STRUCT && dtype->data.t_struct.idnam.id_key == DG_ID_SRC
		 && dtype->data.t_struct.idnam.idd.nam[0])
		|| (dtype->key == DGT_ENUM && dtype->data.t_enum.tnam[0])) {
		dg_name * nm = &s_tags;
		while (*nm) nm = &((*nm)->next);
		(*nm) = f_dg_type_name (
			no_dg_idname_option,
			f_dg_null_sourcepos,
			no_dg_accessibility_option,
			yes_dg_type_option (dtype),
			f_false,
			no_bool_option,
			no_dg_constraint_list_option);
	}
	return f_dummy_diag_tagdef;
}


void
init_capsule_diagtags()
{
	/* the space has been calloced in read_fns */
	
	int i;
	for (i = 0; i < capsule_no_of_diagtags; ++i)
	{
		init_dgtag (&capsule_diag_tagtab[i]);
	}
	return;
}

void
start_make_diagtype_unit(int toks, int tags,
						 int als, int diags)
{
	int i;
	
	if (!tags_initialised)
		init_basic_diag_tags ();
	
	unit_no_of_tokens = toks;
	unit_ind_tokens = (tok_define * *)xcalloc(unit_no_of_tokens,
											  sizeof(tok_define *));
	for (i = 0; i < unit_no_of_tokens; ++i)
		unit_ind_tokens[i] = (tok_define*)0;
	
	unit_no_of_tags = tags;
	unit_ind_tags = (dec * *)xcalloc(unit_no_of_tags,
									 sizeof(dec *));
	for (i = 0; i < unit_no_of_tags; ++i)
		unit_ind_tags[i] = (dec*)0;
	
	unit_no_of_als = als;
	unit_ind_als = (aldef * *)xcalloc(unit_no_of_als,
									  sizeof(aldef *));
	for (i = 0; i < unit_no_of_als; ++i)
		unit_ind_als[i] = (aldef*)0;
	
	unit_no_of_diagtags = diags;
	unit_ind_diagtags = (diag_tagdef * *)xcalloc(unit_no_of_diagtags,
												 sizeof(diag_tagdef *));
	for (i = 0; i < unit_no_of_diagtags; ++i)
		unit_ind_diagtags[i] = (diag_tagdef *)0;
	s_tags = (dg_name)0;
	return;
}

void
init_unit_diagtags(int n)
{
	
	int i;
	
	unit_diag_tagdeftab = (diag_tagdef *) xcalloc(unit_no_of_diagtags - n,
												  sizeof(diag_tagdef));
	
	for (i = 0; i < unit_no_of_diagtags - n; ++i)
	{
		init_dgtag (&unit_diag_tagdeftab[i]);
	}
	return;
}

diag_type_unit
f_make_diagtype_unit()
{
	int i;
	int j = 0;
	int no_of_labels;
	int was_within_diags;
	
	for (i = 0; i < unit_no_of_tokens; ++i)
	{
		if (unit_ind_tokens[i] == (tok_define*)0)
			unit_ind_tokens[i] = &unit_toktab[j++];
	};
	
	j = 0;
	for (i = 0; i < unit_no_of_tags; ++i)
	{
		if (unit_ind_tags[i] == (dec*)0)
			unit_ind_tags[i] = &unit_tagtab[j++];
	};
	
	j = 0;
	for (i = 0; i < unit_no_of_als; ++i)
	{
		if (unit_ind_als[i] == (aldef*)0)
			unit_ind_als[i] = &unit_altab[j++];
	};
	
	j=0;
	for (i = 0; i < unit_no_of_diagtags; ++i)
	{
		if (unit_ind_diagtags[i] == (diag_tagdef *)0)
			unit_ind_diagtags[i] = &unit_diag_tagdeftab[j++];
	};
	
	was_within_diags = within_diags;
	within_diags = 1;
	start_bytestream();
	no_of_labels = small_dtdfint();
	unit_no_of_labels = no_of_labels;
	unit_labtab = (exp*)xcalloc(unit_no_of_labels, sizeof(exp));
	IGNORE d_diag_tagdef_list();
	end_bytestream();
	if (s_tags) {
		dg_compilation * comp_unit_ptr = &all_comp_units;
		dg_compilation ans;
		while (* comp_unit_ptr)
			comp_unit_ptr = &(* comp_unit_ptr)->another;
		(* comp_unit_ptr) = ans = (dg_compilation) xmalloc (sizeof (struct dg_comp_t));
		ans->prim_file = get_filename ((long)0, "", "", "no_source_file");
		ans->comp_deps = new_string_list (0);
		ans->date = 0;
		ans->language = 1;	/* assume ANSI C */
		ans->id_case = 0;	/* case sensitive */
		ans->producer = "TenDRA";
		ans->comp_dir = get_filename ((long)0, "", "unknown directory", "");
		ans->options = new_string_list (0);
		ans->dn_list = s_tags;
		ans->macros = new_dg_macro_list (0);
		ans->another = (dg_compilation)0;
	}
	within_diags = was_within_diags;
	return 0;
}

diag_tagdef_list
new_diag_tagdef_list(int n)
{
	UNUSED(n);
	return 0;
}

diag_tagdef_list
add_diag_tagdef_list(diag_tagdef_list list,
					 diag_tagdef elem, int index)
{
	UNUSED(list); UNUSED(elem); UNUSED(index);
	return 0;
}

linkextern
f_make_diagtagextern(tdfint internal, external ext)
{
	dg_tag tg = &capsule_diag_tagtab[natint(internal)];
	tg->outref.k = NO_LAB;	/* old diag names are internal ! */
	tg->outref.u.s = external_to_string(ext);
	return 0;
}

diag_type
f_use_diag_tag(diag_tag t)
{
	return f_dg_named_type (t);
}


void
f_make_diagtaglink(tdfint i, tdfint ext)
{
	unit_ind_diagtags[natint(i)] =
		&capsule_diag_tagtab[natint(ext)];
	return;
}


void
init_diag_tq()
{
	return;
}

void
init_filename()
{
	return;
}

void
init_diag_type_unit()
{
	return;
}

void
init_linkinfo_props()
{
	return;
}



#else
/* !NEWDIAGS */

#if issparc
#include "sparcdiags.h"
#endif

#if is68000
#include "xdb_basics.h"
#endif

#if ishppa
#include "hppadiags.h"
#endif

#if isAlpha
#include "alphadiags.h"
#endif


/* allocate space in this file */
#define EXTERN_DIAG

#include "diagglob.h"

#define DEBUG(x) x

/* VARIABLES */
/* All variables initialised */

diag_tq f_diag_tq_null;	/* no need to initialise. Not really used. */

/* IDENTITIES */

struct diag_type_t f_diag_type_null_obj = { DIAG_TYPE_NULL };

diag_type f_diag_type_null = &f_diag_type_null_obj;


/* PROCEDURES */

/*----------------------- diagdef and diag_descriptor  lists ----------------*/

void
start_make_diagdef_unit(int toks, int tags,
						int als, int diagtags)
{
	int i;
	
	unit_no_of_tokens = toks;
	unit_ind_tokens = (tok_define * *)xcalloc(unit_no_of_tokens,
											  sizeof(tok_define *));
	for (i = 0; i < unit_no_of_tokens; ++i)
		unit_ind_tokens[i] = (tok_define*)0;
	
	unit_no_of_tags = tags;
	unit_ind_tags = (dec * *)xcalloc(unit_no_of_tags,
									 sizeof(dec *));
	for (i = 0; i < unit_no_of_tags; ++i)
		unit_ind_tags[i] = (dec*)0;
	
	unit_no_of_als = als;
	unit_ind_als = (aldef * *)xcalloc(unit_no_of_als,
									  sizeof(aldef *));
	for (i = 0; i < unit_no_of_als; ++i)
		unit_ind_als[i] = (aldef*)0;
	
	unit_no_of_diagtags = diagtags;
	unit_ind_diagtags = (diag_tagdef * *)xcalloc(unit_no_of_diagtags,
												 sizeof(diag_tagdef *));
	for (i = 0; i < unit_no_of_diagtags; ++i)
		unit_ind_diagtags[i] = (diag_tagdef *)0;
	
	return;
}

void
init_diag_unit()
{
	return;
}

diag_unit
f_build_diag_unit(tdfint labels, diag_descriptor_list descriptors)
{
	UNUSED(labels); UNUSED(descriptors);
	failer("f_build_diag_unit isn't really here");
	exit(EXIT_FAILURE);
}

diag_type_unit
f_build_diagtype_unit(tdfint labels, diag_tagdef_list descriptors)
{
	UNUSED(labels); UNUSED(descriptors);
	failer("f_build_diagtype_unit isn't really here");
	exit(EXIT_FAILURE);
}


void
f_make_diagdef_unit()
{
	int i;
	int j = 0;
	int no_of_labels;
	
	for (i = 0; i < unit_no_of_tokens; ++i)
	{
		if (unit_ind_tokens[i] == (tok_define*)0)
			unit_ind_tokens[i] = &unit_toktab[j++];
	};
	
	j = 0;
	for (i = 0; i < unit_no_of_tags; ++i)
	{
		if (unit_ind_tags[i] == (dec*)0)
			unit_ind_tags[i] = &unit_tagtab[j++];
	};
	
	j = 0;
	for (i = 0; i < unit_no_of_als; ++i)
	{
		if (unit_ind_als[i] == (aldef*)0)
			unit_ind_als[i] = &unit_altab[j++];
	};
	
	j=0;
	for (i = 0; i < unit_no_of_diagtags; ++i)
	{
		if (unit_ind_diagtags[i] == (diag_tagdef *)0)
			unit_ind_diagtags[i] = &unit_diag_tagdeftab[j++];
	};
	
	start_bytestream();
	no_of_labels = small_dtdfint();
	unit_no_of_labels = no_of_labels;
	unit_labtab = (exp*)xcalloc(unit_no_of_labels, sizeof(exp));
	unit_diagvar_tab = d_diag_descriptor_list();
	end_bytestream();
	OUTPUT_GLOBALS_TAB();
	return;
}

/*---------------------- diag_descriptor fns --------------------*/

/* HACK attack */
/* since diag_descriptor are not a pointer
 *				 type we cant set the diag_global field
 *				 easily, so we CHEAT via a global */

static diag_descriptor * last_diag_desc;

diag_descriptor
f_diag_desc_id(tdfstring n, sourcemark whence,
			   exp acc, diag_type new_type)
{
	diag_descriptor new;
	
	if (name(acc) != name_tag)
		failer("No name in f_diag_desc_id");
	
	new.key	 	= DIAG_ID_KEY;
	new.data.id.nme 	= n;
	new.data.id.whence	= whence;
	new.data.id.access	= acc;
	new.data.id.new_type	= new_type;
	
	brog(son(acc))->dec_u.dec_val.diag_info =
		NEW_DIAG_GLOBAL(last_diag_desc);
	
	return new;
}

diag_descriptor
f_diag_desc_struct(tdfstring n, sourcemark whence,
				   diag_type new_type)
{
	diag_descriptor new;
	
	new.key	 	= DIAG_STRUCT_KEY;
	new.data.struc.nme 	= n;
	new.data.struc.whence	= whence;
	new.data.struc.new_type	= new_type;
	
	return new;
}

diag_descriptor
f_diag_desc_typedef(tdfstring n, sourcemark whence,
					diag_type new_type)
{
	diag_descriptor new;
	
	new.key	 	= DIAG_TYPEDEF_KEY;
	new.data.typ.nme 	= n;
	new.data.typ.whence	= whence;
	new.data.typ.new_type	= new_type;
	
	return new;
}

void
init_diag_descriptor()
{
	return;
}

diag_descriptor_list
new_diag_descriptor_list(int n)
{
	diag_descriptor_list new;
	
	new.len = n;
	new.lastused = 0;
	new.array = (diag_descriptor *) xcalloc(n,sizeof(diag_descriptor));
	last_diag_desc = new.array;
	return new;
}

diag_descriptor_list
add_diag_descriptor_list(diag_descriptor_list list,
						 diag_descriptor elem,
						 int index)
{
	UNUSED(index);
	last_diag_desc++;
	list.array[list.lastused++] = elem;
	return list;
}

/*---------------------------- diag_tq--------------------------*/


diag_tq
f_add_diag_const(diag_tq qual)
{
	diag_tq new;
	new = qual;
	new.is_const = 1;
	return new;
}

diag_tq
f_add_diag_volatile(diag_tq qual)
{
	diag_tq new;
	new = qual;
	new.is_volatile = 1;
	return new;
}

/*--------------------------diag_type -----------------------------*/

diag_type
f_diag_type_apply_token(token token_value,
						bitstream token_args)
{
	tokval v;
	v = apply_tok(token_value, token_args,  DIAG_TYPE_SORT, (tokval*)0);
	return v.tk_diag_type;
}

#ifndef NULL
#define NULL ((OUTPUT_REC)0)
#endif

diag_type
f_diag_array(diag_type element_type, exp stride,
			 exp lower_bound, exp upper_bound,
			 diag_type index_type)
{
	diag_type new = (diag_type) xcalloc(1,sizeof(struct diag_type_t));
	
	new->key	= DIAG_TYPE_ARRAY;
	new->been_outed = 0;
	
	new->data.array.element_type	= element_type;
	new->data.array.stride	= stride;
	new->data.array.lower_b	= lower_bound;
	new->data.array.upper_b	= upper_bound;
	new->data.array.index_type	= index_type;
	
	return new;
}

diag_type
f_diag_bitfield(diag_type type, nat number_of_bits)
{
	diag_type new = (diag_type) xcalloc(1,sizeof(struct diag_type_t));
	
	new->key      = DIAG_TYPE_BITFIELD;
	new->been_outed = 0;
	
	new->data.bitfield.result_type	= type;
	new->data.bitfield.no_of_bits		= number_of_bits;
	
	return new;
}


diag_type
f_diag_enum(diag_type base_type, tdfstring enum_name,
			enum_values_list values)
{
	diag_type new = (diag_type) xcalloc(1,sizeof(struct diag_type_t));
	
	new->key      = DIAG_TYPE_ENUM;
	new->been_outed = 0;
	
	new->data.t_enum.base_type	= base_type;
	new->data.t_enum.nme		= enum_name;
	new->data.t_enum.values	= values;
	
	return new;
}


diag_type
f_diag_floating_variety(floating_variety var)
{
	diag_type new = (diag_type) xcalloc(1,sizeof(struct diag_type_t));
	
	new->key      = DIAG_TYPE_FLOAT;
	new->been_outed = 0;
	
	new->data.f_var	= var;
	
	return new;
}

diag_type
f_diag_loc(diag_type object, diag_tq qualifier)
{
	diag_type new = (diag_type) xcalloc(1,sizeof(struct diag_type_t));
	
	new->key      = DIAG_TYPE_LOC;
	new->been_outed = 0;
	
	new->data.loc.object		= object;
	new->data.loc.qualifier	= qualifier;
	
	return new;
}

diag_type
f_diag_proc(diag_type_list params, bool optional_args,
			diag_type result_type)
{
	diag_type new = (diag_type) xcalloc(1,sizeof(struct diag_type_t));
	
	new->key      = DIAG_TYPE_PROC;
	new->been_outed = 0;
	
	new->data.proc.params		= params;
	new->data.proc.opt_args	= optional_args;
	new->data.proc.result_type	= result_type;
	
	return new;
}


diag_type
f_diag_ptr(diag_type object, diag_tq qualifier)
{
	diag_type new = (diag_type) xcalloc(1,sizeof(struct diag_type_t));
	
	new->key      = DIAG_TYPE_PTR;
	new->been_outed = 0;
	
	new->data.ptr.object		= object;
	new->data.ptr.qualifier	= qualifier;
	
	return new;
}

diag_type
f_diag_struct(shape tdf_shape, tdfstring n,
			  diag_field_list fields)
{
	diag_type new = (diag_type) xcalloc(1,sizeof(struct diag_type_t));
	
	new->key      = DIAG_TYPE_STRUCT;
	new->been_outed = 0;
	
	new->data.t_struct.tdf_shape	= tdf_shape;
	new->data.t_struct.nme	= n;
	new->data.t_struct.fields	= fields;
	
	return new;
}

diag_type
f_diag_union(shape tdf_shape, tdfstring n,
			 diag_field_list fields)
{
	diag_type new = (diag_type) xcalloc(1,sizeof(struct diag_type_t));
	
	new->key      = DIAG_TYPE_UNION;
	new->been_outed = 0;
	
	new->data.t_union.tdf_shape	= tdf_shape;
	new->data.t_union.nme		= n;
	new->data.t_union.fields	= fields;
	
	return new;
}

diag_type
f_diag_variety(variety var)
{
	diag_type new = (diag_type) xcalloc(1,sizeof(struct diag_type_t));
	
	new->key      = DIAG_TYPE_VARIETY;
	new->been_outed = 0;
	
	new->data.var	= var;
	
	return new;
}

void
init_diag_type()
{
	return;
}

/*-------------------------- DIAG TYPE HELPERS ---------------------*/
/*---------------------------enum_values ---------------------------*/

enum_values
f_make_enum_values(exp value, tdfstring n)
{
	enum_values new = (enum_values) xcalloc(1,sizeof(struct enum_values_t));
	
	new->val	= value;
	new->nme 	= n;
	
	return new;
}

void
init_enum_values()
{
	return;
}

enum_values_list
new_enum_values_list(int n)
{
	enum_values_list new = (enum_values_list)
		xcalloc(1,sizeof(struct enum_values_list_t));
	
	new->len = n;
	new->lastused = 0;
	new->array = (enum_values *) xcalloc(n,sizeof(enum_values));
	return new;
}

enum_values_list
add_enum_values_list(enum_values_list list,
					 enum_values elem, int index)
{
	UNUSED(index);
	list->array[list->lastused++] = elem;
	return list;
}

/*--------------------------struct fields-------------------------*/
diag_field
f_make_diag_field(tdfstring field_name, exp wh,
				  diag_type field_type)
{
	diag_field new = (diag_field) xcalloc(1,sizeof(struct diag_field_t));
	
	new->field_name	= field_name;
	new->where		= wh;
	new->field_type	= field_type;
	
	return new;
	
}

void
init_diag_field()
{
	return;
}

diag_field_list
new_diag_field_list(int n)
{
	diag_field_list new = (diag_field_list)
		xcalloc(1,sizeof(struct diag_field_list_t));
	
	new->len = n;
	new->lastused = 0;
	new->array = (diag_field*) xcalloc(n,sizeof(diag_field));
	return new;
}

diag_field_list
add_diag_field_list(diag_field_list list,
					diag_field elem, int index)
{
	UNUSED(index);
	list->array[list->lastused++] = elem;
	return list;
}

/*----------------------diag type list----------------------*/
diag_type_list
new_diag_type_list(int n)
{
	diag_type_list new = (diag_type_list)
		xcalloc(1,sizeof(struct diag_type_list_t));
	
	new->len = n;
	new->lastused = 0;
	new->array = (diag_type *) xcalloc(n,sizeof(diag_type));
	return new;
}

diag_type_list
add_diag_type_list(diag_type_list list, diag_type elem,
				   int index)
{
	UNUSED(index);
	list->array[list->lastused++] = elem;
	return list;
}
/*----------------------------END HELPERS------------------------------------*/

/*-------------------------- sourcemark ---------------------------------*/

sourcemark
f_make_sourcemark(filename file, nat line_no,
				  nat char_offset)
{
	sourcemark new;
	new.file	= file;
	new.line_no	= line_no;
	new.char_off	= char_offset;
	
	return new;
}

void
init_sourcemark()
{
	return;
}

/*------------------------------filename ------------------------*/

filename
f_make_filename(nat date, tdfstring machine,
				tdfstring file)
{
	filename new;
	new 	= (filename) xcalloc(1,sizeof(struct filename_t));
	new->date 	= date;
	new->machine	= machine;
	new->file 	= file;
	
	INSPECT_FILENAME(new);
	return new;
}


filename
f_filename_apply_token(token token_value,
					   bitstream token_args)
{
	tokval v;
	v = apply_tok(token_value, token_args, DIAG_FILENAME, (tokval*)0);
	return v.tk_filename;
}

/*----------------------------- diag tag ------------------------------*/


void
init_diag_tag()
{
	return;
}

diag_tag
f_make_diag_tag(tdfint num)
{
	return num;
}


/*---------------------------- diag_tagdef =diag_typeunit ------------------*/

void
init_diag_tagdef()
{
	return;
}

diag_tagdef
f_make_diag_tagdef(tdfint t, diag_type dtype)
{
	diag_tagdef new;
	
	new.d_tag 	= t;
	new.d_type	= dtype;
	
	return new;
}


void
init_capsule_diagtags()
{
	/* the space has been calloced in read_fns */
	
	int i;
	for (i = 0; i < capsule_no_of_diagtags; ++i)
	{
		diag_tagdef * tp 	= &capsule_diag_tagtab[i];
		tp->d_type = (diag_type) xcalloc(1,sizeof(struct diag_type_t));
		tp->d_type->key = DIAG_TYPE_INITED;
	}
	return;
}

void
start_make_diagtype_unit(int toks, int tags,
						 int als, int diags)
{
	int i;
	
	unit_no_of_tokens = toks;
	unit_ind_tokens = (tok_define * *)xcalloc(unit_no_of_tokens,
											  sizeof(tok_define *));
	for (i = 0; i < unit_no_of_tokens; ++i)
		unit_ind_tokens[i] = (tok_define*)0;
	
	unit_no_of_tags = tags;
	unit_ind_tags = (dec * *)xcalloc(unit_no_of_tags,
									 sizeof(dec *));
	for (i = 0; i < unit_no_of_tags; ++i)
		unit_ind_tags[i] = (dec*)0;
	
	unit_no_of_als = als;
	unit_ind_als = (aldef * *)xcalloc(unit_no_of_als,
									  sizeof(aldef *));
	for (i = 0; i < unit_no_of_als; ++i)
		unit_ind_als[i] = (aldef*)0;
	
	unit_no_of_diagtags = diags;
	unit_ind_diagtags = (diag_tagdef * *)xcalloc(unit_no_of_diagtags,
												 sizeof(diag_tagdef *));
	for (i = 0; i < unit_no_of_diagtags; ++i)
		unit_ind_diagtags[i] = (diag_tagdef *)0;
	return;
}

void
init_unit_diagtags(int n)
{
	
	int i;
	
	unit_diag_tagdeftab = (diag_tagdef *) xcalloc(unit_no_of_diagtags - n,
												  sizeof(diag_tagdef));
	
	for (i = 0; i < unit_no_of_diagtags - n; ++i)
	{
		diag_tagdef * tp = &unit_diag_tagdeftab[i];
		tp->d_type = (diag_type) xcalloc(1,sizeof(struct diag_type_t));
		tp->d_type->key = DIAG_TYPE_INITED;
	}
	return;
}

diag_type_unit
f_make_diagtype_unit()
{
	int i;
	int j = 0;
	int no_of_labels;
	
	for (i = 0; i < unit_no_of_tokens; ++i)
	{
		if (unit_ind_tokens[i] == (tok_define*)0)
			unit_ind_tokens[i] = &unit_toktab[j++];
	};
	
	j = 0;
	for (i = 0; i < unit_no_of_tags; ++i)
	{
		if (unit_ind_tags[i] == (dec*)0)
			unit_ind_tags[i] = &unit_tagtab[j++];
	};
	
	j = 0;
	for (i = 0; i < unit_no_of_als; ++i)
	{
		if (unit_ind_als[i] == (aldef*)0)
			unit_ind_als[i] = &unit_altab[j++];
	};
	
	j=0;
	for (i = 0; i < unit_no_of_diagtags; ++i)
	{
		if (unit_ind_diagtags[i] == (diag_tagdef *)0)
			unit_ind_diagtags[i] = &unit_diag_tagdeftab[j++];
	};
	
	start_bytestream();
	no_of_labels = small_dtdfint();
	unit_no_of_labels = no_of_labels;
	unit_labtab = (exp*)xcalloc(unit_no_of_labels, sizeof(exp));
	IGNORE d_diag_tagdef_list();
	end_bytestream();
	OUTPUT_DIAG_TAGS();
	return 0;
}

diag_tagdef_list
new_diag_tagdef_list(int n)
{
	UNUSED(n);
	return 0;
}

diag_tagdef_list
add_diag_tagdef_list(diag_tagdef_list list,
					 diag_tagdef elem, int index)
{
	diag_tagdef * new = unit_ind_diagtags[natint(elem.d_tag)];
	UNUSED(list); UNUSED(index);
	
	new->d_tag 	= elem.d_tag;
	new->ext_name	= elem.ext_name;
	IGNORE memcpy(new->d_type,elem.d_type,sizeof(struct diag_type_t));
	
	return 0;
}

linkextern
f_make_diagtagextern(tdfint internal, external ext)
{
	diag_tagdef * dp = &capsule_diag_tagtab[natint(internal)];
	char *nm = ext.ex.id.ints.chars;
	char * id;
	int idl = (int)strlen(nm);
	int   j;
	
	/* copy it  in case we need to vandalize it sometime */
	
	id = (char *) xcalloc ((idl + 1), sizeof (char));
	id[idl] = 0;
	
	for (j = 0; j < idl; ++j)
		id[j] = nm[j];
	
	dp->ext_name = id;
	
	return 1;
}

diag_type
f_use_diag_tag(diag_tag t)
{
	return unit_ind_diagtags[natint(t)]->d_type;
}


void
f_make_diagtaglink(tdfint i, tdfint ext)
{
	unit_ind_diagtags[natint(i)] =
		&capsule_diag_tagtab[natint(ext)];
	return;
}

diag_descriptor f_dummy_diag_descriptor;
diag_tag f_dummy_diag_tag;
diag_tagdef f_dummy_diag_tagdef;
diag_type f_dummy_diag_type;
diag_tq f_dummy_diag_tq;
filename f_dummy_filename;
sourcemark f_dummy_sourcemark;

void
init_diag_tq()
{
	return;
}

void
init_filename()
{
	return;
}

void
init_diag_type_unit()
{
	return;
}

void
init_linkinfo_props()
{
	return;
}


#endif
