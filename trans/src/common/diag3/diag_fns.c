/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <tdf/nat.h>
#include <tdf/shape.h>
#include <tdf/sort.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/readglob.h>
#include <reader/table_fns.h>
#include <reader/basicread.h>
#include <reader/main_reads.h>

#include <construct/install_fns.h>
#include <construct/aldefs.h>

#include <diag3/diagtypes.h>
#include <diag3/diag_reform.h>

#include "diag_fns.h"
#include "diagglob.h"

/*
 * This is a workaround for shared/xcalloc asserting count is non-zero, but the
 * code here possibly being able to do that. I'm unsure if it actually does or
 * not. However, I think most of these instances probably oughn't to use calloc
 * at all.
 */
static void *
dg_xcalloc(size_t count, size_t size)
{
	if (count == 0) {
		return NULL;
	}

	return xcalloc(count, size);
}

diag_descriptor_list unit_diagvar_tab;

int unit_no_of_diagtags;

diag_tagdef **unit_ind_diagtags;
diag_tagdef *unit_diag_tagdeftab;


/* All variables initialised */

diag_tq f_diag_tq_null;	/* no need to initialise. Not really used. */

struct diag_type_t f_diag_type_null_obj = { DIAG_TYPE_NULL };

diag_type f_diag_type_null = &f_diag_type_null_obj;

void
start_make_diagdef_unit(int toks, int tags, int als, int diagtags)
{
	int i;

	unit_no_of_tokens = toks;
	unit_ind_tokens   = dg_xcalloc(unit_no_of_tokens, sizeof(tok_define *));
	for (i = 0; i < unit_no_of_tokens; ++i) {
		unit_ind_tokens[i] = NULL;
	}

	unit_no_of_tags = tags;
	unit_ind_tags   = dg_xcalloc(unit_no_of_tags, sizeof(dec *));
	for (i = 0; i < unit_no_of_tags; ++i) {
		unit_ind_tags[i] = NULL;
	}

	unit_no_of_als = als;
	unit_ind_als   = dg_xcalloc(unit_no_of_als, sizeof(aldef *));
	for (i = 0; i < unit_no_of_als; ++i) {
		unit_ind_als[i] = NULL;
	}

	unit_no_of_diagtags = diagtags;
	unit_ind_diagtags  = dg_xcalloc(unit_no_of_diagtags, sizeof(diag_tagdef *));
	for (i = 0; i < unit_no_of_diagtags; ++i) {
		unit_ind_diagtags[i] = NULL;
	}
}

void
init_diag_unit(void)
{
}

diag_unit
f_build_diag_unit(tdfint labels, diag_descriptor_list descriptors)
{
	UNUSED(labels);
	UNUSED(descriptors);

	error(ERR_INTERNAL, "f_build_diag_unit isn't really here");
	exit(EXIT_FAILURE);
}

diag_type_unit
f_build_diagtype_unit(tdfint labels, diag_tagdef_list descriptors)
{
	UNUSED(labels);
	UNUSED(descriptors);

	error(ERR_INTERNAL, "f_build_diagtype_unit isn't really here");
	exit(EXIT_FAILURE);
}

void
f_make_diagdef_unit(void)
{
	int i;
	int j;
	int no_of_labels;

	for (i = 0, j = 0; i < unit_no_of_tokens; ++i) {
		if (unit_ind_tokens[i] == NULL) {
			unit_ind_tokens[i] = &unit_toktab[j++];
		}
	}

	for (i = 0, j = 0; i < unit_no_of_tags; ++i) {
		if (unit_ind_tags[i] == NULL) {
			unit_ind_tags[i] = &unit_tagtab[j++];
		}
	}

	for (i = 0, j = 0; i < unit_no_of_als; ++i) {
		if (unit_ind_als[i] == NULL) {
			unit_ind_als[i] = &unit_altab[j++];
		}
	}

	for (i = 0, j = 0; i < unit_no_of_diagtags; ++i) {
		if (unit_ind_diagtags[i] == NULL) {
			unit_ind_diagtags[i] = &unit_diag_tagdeftab[j++];
		}
	}

	start_bytestream();
	no_of_labels = small_dtdfint();
	unit_no_of_labels = no_of_labels;
	unit_labtab = dg_xcalloc(unit_no_of_labels, sizeof(exp));
	unit_diagvar_tab = d_diag_descriptor_list();
	end_bytestream();

	diag3_driver->OUTPUT_GLOBALS_TAB();
}

/*
 * XXX: hack
 * Since diag_descriptor is not a pointer type, we can't set
 * the diag_descriptor field easily, so we cheat via a global
 */
static diag_descriptor *last_diag_desc;

diag_descriptor
f_diag_desc_id(tdfstring n, sourcemark whence, exp acc, diag_type new_type)
{
	diag_descriptor new;

	if (acc->tag != name_tag) {
		error(ERR_INTERNAL, "No name in f_diag_desc_id");
	}

	new.key	= DIAG_ID_KEY;
	new.data.id.name     = n;
	new.data.id.whence   = whence;
	new.data.id.access   = acc;
	new.data.id.new_type = new_type;

	nextg(child(acc))->diag_info =
	    diag3_driver->NEW_DIAG_GLOBAL(last_diag_desc);

	return new;
}

diag_descriptor
f_diag_desc_struct(tdfstring n, sourcemark whence, diag_type new_type)
{
	diag_descriptor new;

	new.key                 = DIAG_STRUCT_KEY;
	new.data.struc.name     = n;
	new.data.struc.whence   = whence;
	new.data.struc.new_type = new_type;

	return new;
}

diag_descriptor
f_diag_desc_typedef(tdfstring n, sourcemark whence, diag_type new_type)
{
	diag_descriptor new;

	new.key                = DIAG_TYPEDEF_KEY;
	new.data.type.name     = n;
	new.data.type.whence   = whence;
	new.data.type.new_type = new_type;

	return new;
}

void
init_diag_descriptor(void)
{
}

diag_descriptor_list
new_diag_descriptor_list(int n)
{
	diag_descriptor_list new;

	new.len        = n;
	new.lastused   = 0;
	new.array      = dg_xcalloc(n, sizeof(diag_descriptor));
	last_diag_desc = new.array;

	return new;
}

diag_descriptor_list
add_diag_descriptor_list(diag_descriptor_list list, diag_descriptor elem,
                         int index)
{
	UNUSED(index);

	last_diag_desc++;
	list.array[list.lastused++] = elem;

	return list;
}

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

diag_type
f_diag_type_apply_token(token token_value, bitstream token_args)
{
	tokval v;

	v = apply_tok(token_value, token_args, SORT_DIAG_TYPE, NULL);

	return v.tk_diag_type;
}

diag_type
f_diag_array(diag_type element_type, exp stride, exp lower_bound,
             exp upper_bound, diag_type index_type)
{
	diag_type new = xcalloc(1, sizeof(struct diag_type_t));

	new->key        = DIAG_TYPE_ARRAY;
	new->been_outed = 0;

	new->data.array.element_type = element_type;
	new->data.array.stride       = stride;
	new->data.array.lower_b      = lower_bound;
	new->data.array.upper_b      = upper_bound;
	new->data.array.index_type   = index_type;

	return new;
}

diag_type
f_diag_bitfield(diag_type type, nat number_of_bits)
{
	diag_type new = xcalloc(1, sizeof(struct diag_type_t));

	new->key        = DIAG_TYPE_BITFIELD;
	new->been_outed = 0;

	new->data.bitfield.result_type = type;
	new->data.bitfield.no_of_bits  = number_of_bits;

	return new;
}

diag_type
f_diag_enum(diag_type base_type, tdfstring enum_name, enum_values_list values)
{
	diag_type new = xcalloc(1, sizeof(struct diag_type_t));

	new->key        = DIAG_TYPE_ENUM;
	new->been_outed = 0;

	new->data.t_enum.base_type = base_type;
	new->data.t_enum.name      = enum_name;
	new->data.t_enum.values    = values;

	return new;
}

diag_type
f_diag_floating_variety(floating_variety var)
{
	diag_type new = xcalloc(1, sizeof(struct diag_type_t));

	new->key        = DIAG_TYPE_FLOAT;
	new->been_outed = 0;

	new->data.f_var	= var;

	return new;
}

diag_type
f_diag_loc(diag_type object, diag_tq qualifier)
{
	diag_type new = xcalloc(1, sizeof(struct diag_type_t));

	new->key        = DIAG_TYPE_LOC;
	new->been_outed = 0;

	new->data.loc.object    = object;
	new->data.loc.qualifier = qualifier;

	return new;
}

diag_type
f_diag_proc(diag_type_list params, bool optional_args, diag_type result_type)
{
	diag_type new = xcalloc(1, sizeof(struct diag_type_t));

	new->key        = DIAG_TYPE_PROC;
	new->been_outed = 0;

	new->data.proc.params      = params;
	new->data.proc.opt_args    = optional_args;
	new->data.proc.result_type = result_type;

	return new;
}

diag_type
f_diag_ptr(diag_type object, diag_tq qualifier)
{
	diag_type new = xcalloc(1, sizeof(struct diag_type_t));

	new->key        = DIAG_TYPE_PTR;
	new->been_outed = 0;

	new->data.ptr.object    = object;
	new->data.ptr.qualifier	= qualifier;

	return new;
}

diag_type
f_diag_struct(shape tdf_shape, tdfstring n, diag_field_list fields)
{
	diag_type new = xcalloc(1, sizeof(struct diag_type_t));

	new->key        = DIAG_TYPE_STRUCT;
	new->been_outed = 0;

	new->data.t_struct.tdf_shape = tdf_shape;
	new->data.t_struct.name      = n;
	new->data.t_struct.fields    = fields;

	return new;
}

diag_type
f_diag_union(shape tdf_shape, tdfstring n, diag_field_list fields)
{
	diag_type new = xcalloc(1, sizeof(struct diag_type_t));

	new->key        = DIAG_TYPE_UNION;
	new->been_outed = 0;

	new->data.t_union.tdf_shape = tdf_shape;
	new->data.t_union.name      = n;
	new->data.t_union.fields    = fields;

	return new;
}

diag_type
f_diag_variety(variety var)
{
	diag_type new = xcalloc(1, sizeof(struct diag_type_t));

	new->key        = DIAG_TYPE_VARIETY;
	new->been_outed = 0;

	new->data.var = var;

	return new;
}

void
init_diag_type(void)
{
}

enum_values
f_make_enum_values(exp value, tdfstring n)
{
	enum_values new = xcalloc(1, sizeof(struct enum_values_t));

	new->val  = value;
	new->name = n;

	return new;
}

void
init_enum_values(void)
{
}

enum_values_list
new_enum_values_list(int n)
{
	enum_values_list new = xcalloc(1, sizeof(struct enum_values_list_t));

	new->len      = n;
	new->lastused = 0;
	new->array    = dg_xcalloc(n, sizeof(enum_values));

	return new;
}

enum_values_list
add_enum_values_list(enum_values_list list, enum_values elem, int index)
{
	UNUSED(index);

	list->array[list->lastused++] = elem;

	return list;
}

diag_field
f_make_diag_field(tdfstring field_name, exp wh, diag_type field_type)
{
	diag_field new = xcalloc(1, sizeof(struct diag_field_t));

	new->field_name = field_name;
	new->where      = wh;
	new->field_type = field_type;

	return new;
}

void
init_diag_field(void)
{
}

diag_field_list
new_diag_field_list(int n)
{
	diag_field_list new = xcalloc(1, sizeof(struct diag_field_list_t));

	new->len      = n;
	new->lastused = 0;
	new->array    = dg_xcalloc(n, sizeof(diag_field));

	return new;
}

diag_field_list
add_diag_field_list(diag_field_list list, diag_field elem, int index)
{
	UNUSED(index);

	list->array[list->lastused++] = elem;

	return list;
}

diag_type_list
new_diag_type_list(int n)
{
	diag_type_list new = xcalloc(1, sizeof(struct diag_type_list_t));

	new->len      = n;
	new->lastused = 0;
	new->array    = dg_xcalloc(n, sizeof(diag_type));

	return new;
}

diag_type_list
add_diag_type_list(diag_type_list list, diag_type elem, int index)
{
	UNUSED(index);
	list->array[list->lastused++] = elem;
	return list;
}

sourcemark
f_make_sourcemark(filename file, nat line_no, nat char_offset)
{
	sourcemark new;

	new.file     = file;
	new.line_no  = line_no;
	new.char_off = char_offset;

	return new;
}

void
init_sourcemark(void)
{
}

filename
f_make_filename(nat date, tdfstring machine, tdfstring file)
{
	filename new;

	new = xcalloc(1, sizeof(struct filename_t));
	new->date    = date;
	new->machine = machine;
	new->file    = file;

	diag3_driver->INSPECT_FILENAME(new);

	return new;
}

filename
f_filename_apply_token(token token_value, bitstream token_args)
{
	tokval v;

	v = apply_tok(token_value, token_args, SORT_FILENAME, NULL);

	return v.tk_filename;
}

void
init_diag_tag(void)
{
}

diag_tag
f_make_diag_tag(tdfint num)
{
	return num;
}

void
init_diag_tagdef(void)
{
}

diag_tagdef
f_make_diag_tagdef(tdfint t, diag_type dtype)
{
	diag_tagdef new;

	new.d_tag  = t;
	new.d_type = dtype;

	return new;
}

void
init_capsule_diagtags(void)
{
	int i;

	/* the space has been calloced in read_fns */
	for (i = 0; i < capsule_no_of_diagtags; ++i) {
		diag_tagdef *tp = &capsule_diag_tagtab[i];
		tp->d_type = (diag_type)xcalloc(1, sizeof(struct diag_type_t));
		tp->d_type->key = DIAG_TYPE_INITED;
	}
}

void
start_make_diagtype_unit(int toks, int tags, int als, int diags)
{
	int i;

	unit_no_of_tokens = toks;
	unit_ind_tokens = dg_xcalloc(unit_no_of_tokens, sizeof(tok_define *));
	for (i = 0; i < unit_no_of_tokens; ++i) {
		unit_ind_tokens[i] = NULL;
	}

	unit_no_of_tags = tags;
	unit_ind_tags = dg_xcalloc(unit_no_of_tags, sizeof(dec *));
	for (i = 0; i < unit_no_of_tags; ++i) {
		unit_ind_tags[i] = NULL;
	}

	unit_no_of_als = als;
	unit_ind_als = dg_xcalloc(unit_no_of_als, sizeof(aldef *));
	for (i = 0; i < unit_no_of_als; ++i) {
		unit_ind_als[i] = NULL;
	}

	unit_no_of_diagtags = diags;
	unit_ind_diagtags = dg_xcalloc(unit_no_of_diagtags, sizeof(diag_tagdef *));
	for (i = 0; i < unit_no_of_diagtags; ++i) {
		unit_ind_diagtags[i] = NULL;
	}
}

void
init_unit_diagtags(int n)
{
	int i;

	unit_diag_tagdeftab = dg_xcalloc(unit_no_of_diagtags - n, sizeof(diag_tagdef));

	for (i = 0; i < unit_no_of_diagtags - n; ++i) {
		diag_tagdef *tp = &unit_diag_tagdeftab[i];
		tp->d_type = (diag_type)xcalloc(1, sizeof(struct diag_type_t));
		tp->d_type->key = DIAG_TYPE_INITED;
	}
}

diag_type_unit
f_make_diagtype_unit(void)
{
	int i;
	int j;
	int no_of_labels;

	for (i = 0, j = 0; i < unit_no_of_tokens; ++i) {
		if (unit_ind_tokens[i] == NULL) {
			unit_ind_tokens[i] = &unit_toktab[j++];
		}
	}

	for (i = 0, j = 0; i < unit_no_of_tags; ++i) {
		if (unit_ind_tags[i] == NULL) {
			unit_ind_tags[i] = &unit_tagtab[j++];
		}
	}

	for (i = 0, j = 0; i < unit_no_of_als; ++i) {
		if (unit_ind_als[i] == NULL) {
			unit_ind_als[i] = &unit_altab[j++];
		}
	}

	for (i = 0, j = 0; i < unit_no_of_diagtags; ++i) {
		if (unit_ind_diagtags[i] == NULL) {
			unit_ind_diagtags[i] = &unit_diag_tagdeftab[j++];
		}
	}

	start_bytestream();
	no_of_labels = small_dtdfint();
	unit_no_of_labels = no_of_labels;
	unit_labtab = dg_xcalloc(unit_no_of_labels, sizeof(exp));
	IGNORE d_diag_tagdef_list();
	end_bytestream();
	diag3_driver->OUTPUT_DIAG_TAGS();

	return 0;
}

diag_tagdef_list
new_diag_tagdef_list(int n)
{
	UNUSED(n);

	return 0;
}

diag_tagdef_list
add_diag_tagdef_list(diag_tagdef_list list, diag_tagdef elem, int index)
{
	diag_tagdef *new = unit_ind_diagtags[natint(elem.d_tag)];

	UNUSED(list);
	UNUSED(index);

	new->d_tag = elem.d_tag;
	new->ext_name = elem.ext_name;
	IGNORE memcpy(new->d_type, elem.d_type, sizeof(struct diag_type_t));

	return 0;
}

linkextern
f_make_diagtagextern(tdfint internal, external ext)
{
	diag_tagdef *dp = &capsule_diag_tagtab[natint(internal)];
	char *name;
	int namel = (int)strlen(ext.ex.id.ints.chars);
	int j;

	/* copy it  in case we need to vandalize it sometime */
	name = xcalloc((namel + 1), sizeof(char));
	name[namel] = 0;

	for (j = 0; j < namel; ++j) {
		name[j] = ext.ex.id.ints.chars[j];
	}

	dp->ext_name = name;

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
	unit_ind_diagtags[natint(i)] = &capsule_diag_tagtab[natint(ext)];
}

diag_descriptor f_dummy_diag_descriptor;
diag_tag f_dummy_diag_tag;
diag_tagdef f_dummy_diag_tagdef;
diag_type f_dummy_diag_type;
diag_tq f_dummy_diag_tq;
filename f_dummy_filename;
sourcemark f_dummy_sourcemark;

void
init_diag_tq(void)
{
}

void
init_filename(void)
{
}

void
init_diag_type_unit(void)
{
}

void
init_linkinfo_props(void)
{
}

