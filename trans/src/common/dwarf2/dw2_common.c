/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/xalloc.h>

#include <reader/basicread.h>
#include <reader/externs.h>

#include <tdf/shape.h>

#include <construct/install_fns.h>

#ifdef TDF_DIAG3
#include <diag3/dg_aux.h>
#include <diag3/diagglob.h>
#endif
#ifdef TDF_DIAG4
#include <diag4/dg_aux.h>
#include <diag4/diagglob.h>
#endif

#include <dwarf2/dw2_common.h>


static dg_name_list capnames;
static int cni = 0;

static void
make_bastype(char *s, dg_type t)
{
	dg_name this_name;
	dg_tag ans = xmalloc(sizeof(dgtag_struct));
	init_dgtag(ans);
	ans->outref.k = LAB_STR;
	ans->outref.u.s = s;
	this_name = f_dg_tag_name(ans,
				  f_dg_type_name(no_dg_idname_option,
						 f_dg_null_sourcepos,
						 no_dg_accessibility_option,
						 yes_dg_type_option(t), f_false,
						 no_bool_option,
						 no_dg_constraint_list_option));
	capnames = add_dg_name_list(capnames, this_name, cni++);
}


static dg_idname
m_id(char *s)
{
	dg_idname ans;
	ans.id_key = DG_ID_SRC;
	ans.idd.name = s;
	return ans;
}


static void
make_basic_types(void)
{
	make_bastype("__D_void_star",
		     f_dg_address_type(m_id("void *"),
				       f_pointer(f_alignment(scharsh))));
	make_bastype("__D_signed_char", f_dg_char_type(m_id("signed char"),
						       scharsh));
	make_bastype("__D_unsigned_char", f_dg_char_type(m_id("unsigned char"),
							 ucharsh));
	make_bastype("__D_short", f_dg_integer_type(m_id("short"), swordsh));
	make_bastype("__D_unsigned_short",
		     f_dg_integer_type(m_id("unsigned short"), uwordsh));
	make_bastype("__D_int", f_dg_integer_type(m_id("int"), slongsh));
	make_bastype("__D_unsigned_int", f_dg_integer_type(m_id("unsigned int"),
							   ulongsh));
	make_bastype("__D_long", f_dg_integer_type(m_id("long"), slongsh));
	make_bastype("__D_unsigned_long",
		     f_dg_integer_type(m_id("unsigned long"), ulongsh));
	make_bastype("__D_long_long", f_dg_integer_type(m_id("long long"),
							s64sh));
	make_bastype("__D_unsigned_long_long",
		     f_dg_integer_type(m_id("unsigned long long"), u64sh));
	make_bastype("__D_float", f_dg_float_type(m_id("float"), shrealfv));
	make_bastype("__D_double", f_dg_float_type(m_id("double"), realfv));
	make_bastype("__D_long_double", f_dg_float_type(m_id("long double"),
							doublefv));
	make_bastype("__D_complex", f_dg_complex_float_type(m_id("complex"),
							    shcomplexfv));
	make_bastype("__D_double_complex",
		     f_dg_complex_float_type(m_id("double complex"),
					     complexfv));
	make_bastype("__D_long_double_complex",
		     f_dg_complex_float_type(m_id("long double complex"),
					     complexdoublefv));
}


void
make_dwarf_common(void)
{
	dg_compilation ans;
	capnames = new_dg_name_list(15);
	make_basic_types();
	ans = (dg_compilation)xmalloc(sizeof(struct dg_comp_t));
	ans->prim_file = get_filename(0, "", "", "");
	ans->comp_deps = new_string_list(0);
	ans->date = 0;
	ans->language = 1;	/* assume ANSI C */
	ans->id_case = 0;	/* case sensitive */
	ans->producer = "TenDRA";
	ans->comp_dir = get_filename(0, "", "", "");
	ans->options = new_string_list(0);
	ans->dn_list = capnames;
	ans->macros = new_dg_macro_list(0);
	ans->another = NULL;
	all_comp_units = ans;
}
