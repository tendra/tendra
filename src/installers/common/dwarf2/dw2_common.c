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
$Author: pwe $
$Date: 1998/03/11 11:03:40 $
$Revision: 1.2 $
$Log: dw2_common.c,v $
 * Revision 1.2  1998/03/11  11:03:40  pwe
 * DWARF optimisation info
 *
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/12/04  19:42:02  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.3  1997/11/06  09:22:39  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.2  1997/10/23  09:28:05  pwe
 * ANDF-DE v1.7, extra diags
 *
 * Revision 1.1  1997/10/10  18:19:06  pwe
 * prep ANDF-DE revision
 *
**********************************************************************/

#include "config.h"
#include "common_types.h"
#include "basicread.h"
#include "install_fns.h"
#include "xalloc.h"
#include "dg_aux.h"
#include "externs.h"
#include "dg_globs.h"
#include "shapemacs.h"
#include "dw2_common.h"


static dg_name_list capnames;
static int cni = 0;

static void make_bastype
    PROTO_N ( (s, t) )
    PROTO_T ( char * s X dg_type t )
{
  dg_name this_name;
  dg_tag ans = (dgtag_struct *) xmalloc (sizeof(dgtag_struct));
  init_dgtag (ans);
  ans->outref.k = LAB_STR;
  ans->outref.u.s = s;
  this_name = f_dg_tag_name (ans, f_dg_type_name (
	no_dg_idname_option,
	f_dg_null_sourcepos,
	no_dg_accessibility_option,
	yes_dg_type_option (t),
	f_false,
	no_bool_option,
	no_dg_constraint_list_option));
  capnames = add_dg_name_list (capnames, this_name, cni++);
}


static dg_idname m_id
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  dg_idname ans;
  ans.id_key = DG_ID_SRC;
  ans.idd.nam = s;
  return ans;
}


static void make_basic_types
    PROTO_Z ()
{
  make_bastype ("__D_void_star", f_dg_address_type (
		m_id ("void *"), f_pointer (f_alignment (scharsh))));
  make_bastype ("__D_signed_char", f_dg_char_type (
		m_id ("signed char"), scharsh));
  make_bastype ("__D_unsigned_char", f_dg_char_type (
		m_id ("unsigned char"), ucharsh));
  make_bastype ("__D_short", f_dg_integer_type (
		m_id ("short"), swordsh));
  make_bastype ("__D_unsigned_short", f_dg_integer_type (
		m_id ("unsigned short"), uwordsh));
  make_bastype ("__D_int", f_dg_integer_type (
		m_id ("int"), slongsh));
  make_bastype ("__D_unsigned_int", f_dg_integer_type (
		m_id ("unsigned int"), ulongsh));
  make_bastype ("__D_long", f_dg_integer_type (
		m_id ("long"), slongsh));
  make_bastype ("__D_unsigned_long", f_dg_integer_type (
		m_id ("unsigned long"), ulongsh));
  make_bastype ("__D_long_long", f_dg_integer_type (
		m_id ("long long"), s64sh));
  make_bastype ("__D_unsigned_long_long", f_dg_integer_type (
		m_id ("unsigned long long"), u64sh));
  make_bastype ("__D_float", f_dg_float_type (
		m_id ("float"), shrealfv));
  make_bastype ("__D_double", f_dg_float_type (
		m_id ("double"), realfv));
  make_bastype ("__D_long_double", f_dg_float_type (
		m_id ("long double"), doublefv));
  make_bastype ("__D_complex", f_dg_complex_float_type (
		m_id ("complex"), shcomplexfv));
  make_bastype ("__D_double_complex", f_dg_complex_float_type (
		m_id ("double complex"), complexfv));
  make_bastype ("__D_long_double_complex", f_dg_complex_float_type (
		m_id ("long double complex"), complexdoublefv));
}


void make_dwarf_common
    PROTO_Z ()
{
  dg_compilation ans;
  capnames = new_dg_name_list (15);
  make_basic_types ();
  ans = (dg_compilation) xmalloc (sizeof (struct dg_comp_t));
  ans->prim_file = get_filename ((long)0, "", "", "");
  ans->comp_deps = new_string_list (0);
  ans->date = 0;
  ans->language = 1;	/* assume ANSI C */
  ans->id_case = 0;	/* case sensitive */
  ans->producer = "TenDRA";
  ans->comp_dir = get_filename ((long)0, "", "", "");
  ans->options = new_string_list (0);
  ans->dn_list = capnames;
  ans->macros = new_dg_macro_list (0);
  ans->another = (dg_compilation)0;
  all_comp_units = ans;
}
