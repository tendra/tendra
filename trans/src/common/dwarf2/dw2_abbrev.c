/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>
#include <shared/error.h>

#include <local/dw2_config.h>

#include <reader/readglob.h>

#include <main/driver.h>
#include <main/print.h>

#include <dwarf2/dw2_basic.h>
#include <dwarf2/dw2_abbrev.h>
#include <dwarf2/dw2_abbrev_vn.h>
#include <dwarf2/dw2_codes.h>
#include <dwarf2/dw2_entries.h>

static void
set_abbrev_tag(abbrev_entry *en, int c, int tag_code, int has_children)
{
	if (!en->index && !c) {
		error(ERR_SERIOUS, "abbreviation index unset: %s\n", en->aname);
	}
	out8();
	uleb128((unsigned long)(en->index + c));
	asm_printf(", ");
	uleb128((unsigned long)tag_code);
	asm_printf(", ");
	asm_printf("%d", has_children ? DW_CHILDREN_yes : DW_CHILDREN_no);
	asm_comment("%s %d", en->aname, c);
}


static void
set_decl_attributes(void)
{
	set_attribute(DW_AT_decl_file, DW_FORM_udata);
	set_attribute(DW_AT_decl_line, DW_FORM_udata);
	set_attribute(DW_AT_decl_column, DW_FORM_udata);
}


static void
obj_abbrev(abbrev_entry *en, int tag_code)
{
	int c = 0;
	do {
		long attr = (en->attr)[c];
		set_abbrev_tag(en, c, tag_code, 0);
		if (attr & H_AO) {
			set_attribute(DW_AT_abstract_origin, DW_FORM_ref_addr);
		}
		if (attr & H_SP) {
			set_attribute(DW_AT_specification, DW_FORM_ref_addr);
		}
		if (attr & H_DC) {
			set_attribute(DW_AT_declaration, DW_FORM_flag);
		}
		if (attr & H_NM) {
			set_attribute(DW_AT_name, DW_FORM_string);
		}
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_EX) {
			set_attribute(DW_AT_external, DW_FORM_flag);
		}
		if (attr & H_AT) {
			set_attribute(DW_AT_artificial, DW_FORM_flag);
		}
		if (attr & H_AC) {
			set_attribute(DW_AT_accessibility, DW_FORM_data1);
		}
		if (attr & H_TP) {
			set_attribute(DW_AT_type, DW_FORM_ref_addr);
		}
		if (attr & H_VP) {
			set_attribute(DW_AT_variable_parameter, DW_FORM_flag);
		}
#ifdef H_DX
		if (attr & H_DX) {
			set_attribute(DW_AT_DD_computed_default, DW_FORM_flag);
		}
#endif
		if (attr & H_DF) {
			set_attribute(DW_AT_default_value, DW_FORM_indirect);
		}
		if (attr & H_SS) {
			set_attribute(DW_AT_start_scope, DW_FORM_data2);
		}
		if (attr & H_CV) {
			set_attribute(DW_AT_const_value, DW_FORM_indirect);
		}
		if (attr & H_LC) {
			set_attribute(DW_AT_location, DW_FORM_block1);
		}
		if (attr & H_LL) {
			set_attribute(DW_AT_location, DW_FORM_ref_addr);
		}
		if (attr & H_LE) {
			set_attribute(DW_AT_DD_ext_location, DW_FORM_ref_addr);
		}
		if (attr & H_RP) {
			set_attribute(DW_AT_DD_repn, DW_FORM_indirect);
		}
		set_attribute(0, 0);
		c++;
	} while ((en->attr)[c]);
}


static void
module_abbrev(abbrev_entry *en, int tag_code)
{
	int c = 0;
	do {
		long attr = (en->attr)[c];
		set_abbrev_tag(en, c, tag_code, 1);
		if (attr & H_AO) {
			set_attribute(DW_AT_abstract_origin, DW_FORM_ref_addr);
		}
		if (attr & H_SP) {
			set_attribute(DW_AT_specification, DW_FORM_ref_addr);
		}
		if (attr & H_DC) {
			set_attribute(DW_AT_declaration, DW_FORM_flag);
		}
		if (attr & H_NM) {
			set_attribute(DW_AT_name, DW_FORM_string);
		}
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_AT) {
			set_attribute(DW_AT_artificial, DW_FORM_flag);
		}
		if (attr & H_AC) {
			set_attribute(DW_AT_accessibility, DW_FORM_data1);
		}
		if (attr & H_PC) {
			set_attribute(DW_AT_low_pc, DW_FORM_addr);
			set_attribute(DW_AT_high_pc, DW_FORM_addr);
		}
		if (attr & H_EXTN) {
			set_attribute(DW_AT_DD_indirect_attributes,
				      DW_FORM_block2);
		}
		set_attribute(0, 0);
		c++;
	} while ((en->attr)[c]);
}


static void
struct_abbrev(abbrev_entry *en, int tag_code)
{
	int c = 0;
	do {
		long attr = (en->attr)[c];
		set_abbrev_tag(en, c, tag_code, 1);
		if (attr & H_SP) {
			set_attribute(DW_AT_specification, DW_FORM_ref_addr);
		}
		if (attr & H_DC) {
			set_attribute(DW_AT_declaration, DW_FORM_flag);
		}
		if (attr & H_NM) {
			set_attribute(DW_AT_name, DW_FORM_string);
		}
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_SZ) {
			set_attribute(DW_AT_byte_size, DW_FORM_udata);
		}
		if (attr & H_NW) {
			set_attribute(DW_AT_DD_newtype, DW_FORM_flag);
		}
		if (attr & H_EXTN) {
			set_attribute(DW_AT_DD_indirect_attributes,
				      DW_FORM_block2);
		}
		set_attribute(0, 0);
		c++;
	} while ((en->attr)[c]);
}


void
do_abbreviations(void)
{
	int c;
	enter_section("debug_abbrev");
	out_ext_label(abbrev_name);

	set_abbrev_tag(&dwe_comp_unit, 0, DW_TAG_compile_unit, 1);
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(DW_AT_name, DW_FORM_string);
	set_attribute(DW_AT_language, DW_FORM_udata);
	set_attribute(DW_AT_stmt_list, DW_FORM_ref_addr);
	set_attribute(DW_AT_comp_dir, DW_FORM_string);
	set_attribute(DW_AT_producer, DW_FORM_string);
	set_attribute(DW_AT_identifier_case, DW_FORM_data1);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_cmac_unit, 0, DW_TAG_compile_unit, 1);
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(DW_AT_name, DW_FORM_string);
	set_attribute(DW_AT_language, DW_FORM_udata);
	set_attribute(DW_AT_stmt_list, DW_FORM_ref_addr);
	set_attribute(DW_AT_macro_info, DW_FORM_ref_addr);
	set_attribute(DW_AT_comp_dir, DW_FORM_string);
	set_attribute(DW_AT_producer, DW_FORM_string);
	set_attribute(DW_AT_identifier_case, DW_FORM_data1);
	set_attribute(0, 0);

	module_abbrev(&dwe_module, DW_TAG_module);

	module_abbrev(&dwe_namespace, DW_TAG_DD_namespace);

	set_abbrev_tag(&dwe_subunit, 0, DW_TAG_DD_subunit, 1);
	set_attribute(DW_AT_DD_parent, DW_FORM_ref_addr);
	set_attribute(DW_AT_artificial, DW_FORM_flag);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_childunit, 0, DW_TAG_DD_child_unit, 1);
	set_attribute(DW_AT_DD_parent, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_child_acc, 0, DW_TAG_DD_child_unit, 1);
	set_attribute(DW_AT_DD_parent, DW_FORM_ref_addr);
	set_attribute(DW_AT_accessibility, DW_FORM_data1);
	set_attribute(0, 0);

	c = 0;
	do {
		long attr = (dwe_import.attr)[c];
		set_abbrev_tag(&dwe_import, c, DW_TAG_imported_declaration, 0);
		if (attr & H_NM) {
			set_attribute(DW_AT_name, DW_FORM_string);
		}
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_AC) {
			set_attribute(DW_AT_accessibility, DW_FORM_data1);
		}
		set_attribute(DW_AT_import, DW_FORM_ref_addr);
		set_attribute(DW_AT_DD_import_kind, DW_FORM_udata);
		if (attr & H_SS) {
			set_attribute(DW_AT_start_scope, DW_FORM_data2);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_import.attr)[c]);

	c = 0;
	do {
		long attr = (dwe_import_p.attr)[c];
		set_abbrev_tag(&dwe_import_p, c, DW_TAG_imported_declaration, 1);
		if (attr & H_NM) {
			set_attribute(DW_AT_name, DW_FORM_string);
		}
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_AC) {
			set_attribute(DW_AT_accessibility, DW_FORM_data1);
		}
		set_attribute(DW_AT_import, DW_FORM_ref_addr);
		set_attribute(DW_AT_DD_import_kind, DW_FORM_udata);
		if (attr & H_SS) {
			set_attribute(DW_AT_start_scope, DW_FORM_data2);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_import_p.attr)[c]);

	c = 0;
	do {
		long attr = (dwe_proc.attr)[c];
		set_abbrev_tag(&dwe_proc, c, DW_TAG_subprogram, 1);
		if (attr & H_AO) {
			set_attribute(DW_AT_abstract_origin, DW_FORM_ref_addr);
		}
		if (attr & H_SP) {
			set_attribute(DW_AT_specification, DW_FORM_ref_addr);
		}
		if (attr & H_DC) {
			set_attribute(DW_AT_declaration, DW_FORM_flag);
		}
		if (attr & H_NM) {
			set_attribute(DW_AT_name, DW_FORM_string);
		}
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_EX) {
			set_attribute(DW_AT_external, DW_FORM_flag);
		}
		if (attr & H_AT) {
			set_attribute(DW_AT_artificial, DW_FORM_flag);
		}
		if (attr & H_AC) {
			set_attribute(DW_AT_accessibility, DW_FORM_data1);
		}
		if (attr & H_CC) {
			set_attribute(DW_AT_calling_convention, DW_FORM_data1);
		}
		if (attr & H_TP) {
			set_attribute(DW_AT_type, DW_FORM_ref_addr);
		}
		if (attr & H_PT) {
			set_attribute(DW_AT_prototyped, DW_FORM_flag);
		}
		if (attr & H_IL) {
			set_attribute(DW_AT_inline, DW_FORM_data1);
		}
		if (attr & H_VT) {
			set_attribute(DW_AT_virtuality, DW_FORM_data1);
		}
		if (attr & H_VL) {
			set_attribute(DW_AT_vtable_elem_location,
				      DW_FORM_block1);
		}
		if (attr & H_SS) {
			set_attribute(DW_AT_start_scope, DW_FORM_data2);
		}
		if (attr & H_PC) {
			set_attribute(DW_AT_low_pc, DW_FORM_addr);
			set_attribute(DW_AT_high_pc, DW_FORM_addr);
			set_attribute(DW_AT_return_addr, DW_FORM_block1);
			set_attribute(DW_AT_frame_base, DW_FORM_block1);
		}
		if (attr & H_SL) {
			set_attribute(DW_AT_static_link, DW_FORM_block1);
		}
		if (attr & H_EXTN) {
			set_attribute(DW_AT_DD_indirect_attributes,
				      DW_FORM_block2);
		}
		if (attr & H_EL) {
			set_attribute(DW_AT_DD_elaboration, DW_FORM_ref_addr);
		}
		if (attr & H_GN) {
			set_attribute(DW_AT_DD_generic_name, DW_FORM_string);
		}
		if (attr & H_RP) {
			set_attribute(DW_AT_DD_repn, DW_FORM_indirect);
		}
		if (attr & H_LN) {
			set_attribute(DW_AT_language, DW_FORM_udata);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_proc.attr)[c]);

	set_abbrev_tag(&dwe_entrypt, 0, DW_TAG_entry_point, 0);
	set_attribute(0, 0);

	obj_abbrev(&dwe_param, DW_TAG_formal_parameter);

	set_abbrev_tag(&dwe_formal, 0, DW_TAG_formal_parameter, 0);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_opt_par, 0, DW_TAG_unspecified_parameters, 0);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_thrown_t, 0, DW_TAG_thrown_type, 0);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_inl_call, 0, DW_TAG_inlined_subroutine, 1);
	set_attribute(DW_AT_abstract_origin, DW_FORM_ref_addr);
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_inl_opnd, 0, DW_TAG_inlined_subroutine, 1);
	set_attribute(DW_AT_abstract_origin, DW_FORM_ref_addr);
	set_attribute(0, 0);

	c = 0;
	do {
		long attr = (dwe_scope.attr)[c];
		set_abbrev_tag(&dwe_scope, c, DW_TAG_lexical_block, 1);
		if (attr & H_NM) {
			set_attribute(DW_AT_name, DW_FORM_string);
		}
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_PC) {
			set_attribute(DW_AT_low_pc, DW_FORM_addr);
			set_attribute(DW_AT_high_pc, DW_FORM_addr);
		}
		if (attr & H_BG) {
			set_attribute(DW_AT_DD_begin, DW_FORM_addr);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_scope.attr)[c]);

	set_abbrev_tag(&dwe_fragment, 0, DW_TAG_DD_lexical_fragment, 1);
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_label, 0, DW_TAG_label, 0);
	set_attribute(DW_AT_name, DW_FORM_string);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_with, 0, DW_TAG_with_stmt, 1);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(DW_AT_location, DW_FORM_block1);
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_try, 0, DW_TAG_try_block, 1);
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_catch, 0, DW_TAG_catch_block, 1);
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(0, 0);

	obj_abbrev(&dwe_variable, DW_TAG_variable);
	obj_abbrev(&dwe_constant, DW_TAG_constant);

	set_abbrev_tag(&dwe_tmpl_type, 0, DW_TAG_template_type_param, 0);
	set_attribute(DW_AT_name, DW_FORM_string);
	set_decl_attributes();
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_tmpl_val, 0, DW_TAG_template_value_param, 0);
	set_attribute(DW_AT_name, DW_FORM_string);
	set_decl_attributes();
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(DW_AT_const_value, DW_FORM_indirect);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_tmpl_proc, 0, DW_TAG_DD_template_proc_param, 0);
	set_attribute(DW_AT_name, DW_FORM_string);
	set_decl_attributes();
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_tmpl_mod, 0, DW_TAG_DD_template_module_param, 0);
	set_attribute(DW_AT_name, DW_FORM_string);
	set_decl_attributes();
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	c = 0;
	do {
		long attr = (dwe_typedef.attr)[c];
		set_abbrev_tag(&dwe_typedef, c, DW_TAG_typedef, 0);
		if (attr & H_AO) {
			set_attribute(DW_AT_abstract_origin, DW_FORM_ref_addr);
		}
		if (attr & H_SP) {
			set_attribute(DW_AT_specification, DW_FORM_ref_addr);
		}
		if (attr & H_DC) {
			set_attribute(DW_AT_declaration, DW_FORM_flag);
		}
		if (attr & H_NM) {
			set_attribute(DW_AT_name, DW_FORM_string);
		}
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_AT) {
			set_attribute(DW_AT_artificial, DW_FORM_flag);
		}
		if (attr & H_AC) {
			set_attribute(DW_AT_accessibility, DW_FORM_data1);
		}
		if (attr & H_TP) {
			set_attribute(DW_AT_type, DW_FORM_ref_addr);
		}
		if (attr & H_NW) {
			set_attribute(DW_AT_DD_newtype, DW_FORM_flag);
		}
		if (attr & H_AD) {
			set_attribute(DW_AT_DD_ada_derived, DW_FORM_flag);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_typedef.attr)[c]);

	c = 0;
	do {
		long attr = (dwe_typecon.attr)[c];
		set_abbrev_tag(&dwe_typecon, c, DW_TAG_typedef, 1);
		if (attr & H_SP) {
			set_attribute(DW_AT_specification, DW_FORM_ref_addr);
		}
		if (attr & H_DC) {
			set_attribute(DW_AT_declaration, DW_FORM_flag);
		}
		if (attr & H_NM) {
			set_attribute(DW_AT_name, DW_FORM_string);
		}
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_AT) {
			set_attribute(DW_AT_artificial, DW_FORM_flag);
		}
		if (attr & H_AC) {
			set_attribute(DW_AT_accessibility, DW_FORM_data1);
		}
		if (attr & H_TP) {
			set_attribute(DW_AT_type, DW_FORM_ref_addr);
		}
		if (attr & H_NW) {
			set_attribute(DW_AT_DD_newtype, DW_FORM_flag);
		}
		if (attr & H_AD) {
			set_attribute(DW_AT_DD_ada_derived, DW_FORM_flag);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_typecon.attr)[c]);

	c = 0;
	do {
		long attr = (dwe_cnstraint.attr)[c];
		set_abbrev_tag(&dwe_cnstraint, c, DW_TAG_DD_constraint, 0);
		if (attr & H_RM) {
			set_attribute(DW_AT_DD_constraint_ref,
				      DW_FORM_ref_addr);
		}
		if (attr & H_CV) {
			set_attribute(DW_AT_const_value, DW_FORM_indirect);
		}
		if (attr & H_TP) {
			set_attribute(DW_AT_type, DW_FORM_ref_addr);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_cnstraint.attr)[c]);

	set_abbrev_tag(&dwe_base_type, 0, DW_TAG_base_type, 0);
	set_attribute(DW_AT_name, DW_FORM_string);
	set_attribute(DW_AT_encoding, DW_FORM_data1);
	set_attribute(DW_AT_byte_size, DW_FORM_udata);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_cnst_type, 0, DW_TAG_const_type, 0);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_vol_type, 0, DW_TAG_volatile_type, 0);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_clwd_type, 0, DW_TAG_DD_class_wide_type, 0);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_als_type, 0, DW_TAG_DD_aliased_type, 0);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_lim_type, 0, DW_TAG_DD_limited_type, 0);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_ptr_type, 0, DW_TAG_pointer_type, 0);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_hpptr_t, 0, DW_TAG_pointer_type, 0);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(DW_AT_DD_heap_only_pointer, DW_FORM_flag);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_ref_type, 0, DW_TAG_reference_type, 0);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_pack_type, 0, DW_TAG_packed_type, 0);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_arr_type, 0, DW_TAG_array_type, 1);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(DW_AT_stride_size, DW_FORM_indirect);
	set_attribute(DW_AT_ordering, DW_FORM_data1);
	set_attribute(DW_AT_byte_size, DW_FORM_udata);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_arr_dyn, 0, DW_TAG_array_type, 1);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(DW_AT_stride_size, DW_FORM_indirect);
	set_attribute(DW_AT_ordering, DW_FORM_data1);
	set_attribute(0, 0);

	c = 0;
	do {
		long attr = (dwe_subr_type.attr)[c];
		set_abbrev_tag(&dwe_subr_type, c, DW_TAG_subrange_type, 0);
		if (attr & H_TP) {
			set_attribute(DW_AT_type, DW_FORM_ref_addr);
		}
		if (attr & H_SZ) {
			set_attribute(DW_AT_byte_size, DW_FORM_udata);
		}
		if (attr & H_LB) {
			set_attribute(DW_AT_lower_bound, DW_FORM_indirect);
		}
		if (attr & H_UB) {
			set_attribute(DW_AT_upper_bound, DW_FORM_indirect);
		}
		if (attr & H_CN) {
			set_attribute(DW_AT_count, DW_FORM_indirect);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_subr_type.attr)[c]);

	c = 0;
	do {
		long attr = (dwe_enum_type.attr)[c];
		set_abbrev_tag(&dwe_enum_type, c, DW_TAG_enumeration_type, 1);
		if (attr & H_SP) {
			set_attribute(DW_AT_specification, DW_FORM_ref_addr);
		}
		if (attr & H_DC) {
			set_attribute(DW_AT_declaration, DW_FORM_flag);
		}
		if (attr & H_NM) {
			set_attribute(DW_AT_name, DW_FORM_string);
		}
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_SZ) {
			set_attribute(DW_AT_byte_size, DW_FORM_udata);
		}
		if (attr & H_NW) {
			set_attribute(DW_AT_DD_newtype, DW_FORM_flag);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_enum_type.attr)[c]);

	set_abbrev_tag(&dwe_enum_tor, 0, DW_TAG_enumerator, 0);
	set_attribute(DW_AT_name, DW_FORM_string);
	set_attribute(DW_AT_const_value, DW_FORM_indirect);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_enum_char, 0, DW_TAG_enumerator, 0);
	set_attribute (DW_AT_name, DW_FORM_udata);	/* character constant */
	set_attribute(DW_AT_const_value, DW_FORM_indirect);
	set_attribute(0, 0);

	struct_abbrev(&dwe_struct_t, DW_TAG_structure_type);

	struct_abbrev(&dwe_union_t, DW_TAG_union_type);

	struct_abbrev(&dwe_class_t, DW_TAG_class_type);

	c = 0;
	do {
		long attr = (dwe_member.attr)[c];
		set_abbrev_tag(&dwe_member, c, DW_TAG_member, 0);
		if (attr & H_NM) {
			set_attribute(DW_AT_name, DW_FORM_string);
		}
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_AC) {
			set_attribute(DW_AT_accessibility, DW_FORM_data1);
		}
		if (attr & H_TP) {
			set_attribute(DW_AT_type, DW_FORM_ref_addr);
		}
		if (attr & H_LC) {
			set_attribute(DW_AT_data_member_location,
				      DW_FORM_block1);
		}
		if (attr & H_BF) {
			set_attribute(DW_AT_bit_offset, DW_FORM_data1);
			set_attribute(DW_AT_bit_size, DW_FORM_data1);
		}
		if (attr & H_DS) {
			set_attribute(DW_AT_DD_discriminant, DW_FORM_flag);
		}
#ifdef H_DX
		if (attr & H_DX) {
			set_attribute(DW_AT_DD_computed_default, DW_FORM_flag);
		}
#endif
		if (attr & H_DF) {
			set_attribute(DW_AT_default_value, DW_FORM_indirect);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_member.attr)[c]);

	set_abbrev_tag(&dwe_varpart, 0, DW_TAG_variant_part, 1);
	set_attribute(DW_AT_discr, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_varpart_t, 0, DW_TAG_variant_part, 1);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_variant_0, 0, DW_TAG_variant, 1);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_variant_1, 0, DW_TAG_variant, 1);
	set_attribute(DW_AT_discr_value, DW_FORM_indirect);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_variant_n, 0, DW_TAG_variant, 1);
	set_attribute(DW_AT_discr_list, DW_FORM_block2);
	set_attribute(0, 0);

	c = 0;
	do {
		long attr = (dwe_inheritce.attr)[c];
		set_abbrev_tag(&dwe_inheritce, c, DW_TAG_inheritance, 0);
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_TP) {
			set_attribute(DW_AT_type, DW_FORM_ref_addr);
		}
		if (attr & H_LC) {
			set_attribute(DW_AT_data_member_location,
				      DW_FORM_block1);
		}
		if (attr & H_AC) {
			set_attribute(DW_AT_accessibility, DW_FORM_data1);
		}
		if (attr & H_VT) {
			set_attribute(DW_AT_virtuality, DW_FORM_data1);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_inheritce.attr)[c]);

	set_abbrev_tag(&dwe_friend, 0, DW_TAG_friend, 0);
	set_attribute(DW_AT_friend, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_ptrmem_t, 0, DW_TAG_ptr_to_member_type, 0);
	set_attribute(DW_AT_containing_type, DW_FORM_ref_addr);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(DW_AT_byte_size, DW_FORM_udata);
	set_attribute(0, 0);

	c = 0;
	do {
		long attr = (dwe_ind_mem.attr)[c];
		set_abbrev_tag(&dwe_ind_mem, c, DW_TAG_DD_indirect_member, 0);
		if (attr & H_NM) {
			set_attribute(DW_AT_name, DW_FORM_string);
		}
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_TP) {
			set_attribute(DW_AT_type, DW_FORM_ref_addr);
		}
		if (attr & H_LC) {
			set_attribute(DW_AT_data_member_location,
				      DW_FORM_block1);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_ind_mem.attr)[c]);

	set_abbrev_tag(&dwe_proc_type, 0, DW_TAG_subroutine_type, 1);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_procv_t, 0, DW_TAG_subroutine_type, 1);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_string_t, 0, DW_TAG_string_type, 0);
	set_attribute(DW_AT_string_length, DW_FORM_block1);
	set_attribute(DW_AT_byte_size, DW_FORM_udata);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_stringc_t, 0, DW_TAG_string_type, 0);
	set_attribute(DW_AT_byte_size, DW_FORM_udata);
	set_attribute(0, 0);

	c = 0;
	do {
		long attr = (dwe_file_t.attr)[c];
		set_abbrev_tag(&dwe_file_t, c, DW_TAG_file_type, 0);
		if (attr & H_SP) {
			set_attribute(DW_AT_specification, DW_FORM_ref_addr);
		}
		if (attr & H_DC) {
			set_attribute(DW_AT_declaration, DW_FORM_flag);
		}
		if (attr & H_TP) {
			set_attribute(DW_AT_type, DW_FORM_ref_addr);
		}
		if (attr & H_SZ) {
			set_attribute(DW_AT_byte_size, DW_FORM_udata);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_file_t.attr)[c]);

	c = 0;
	do {
		long attr = (dwe_set_t.attr)[c];
		set_abbrev_tag(&dwe_set_t, c, DW_TAG_set_type, 0);
		if (attr & H_SP) {
			set_attribute(DW_AT_specification, DW_FORM_ref_addr);
		}
		if (attr & H_DC) {
			set_attribute(DW_AT_declaration, DW_FORM_flag);
		}
		if (attr & H_TP) {
			set_attribute(DW_AT_type, DW_FORM_ref_addr);
		}
		if (attr & H_SZ) {
			set_attribute(DW_AT_byte_size, DW_FORM_udata);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_set_t.attr)[c]);

	c = 0;
	do {
		long attr = (dwe_fixpt_t.attr)[c];
		set_abbrev_tag(&dwe_fixpt_t, c, DW_TAG_DD_fixed_point_type, 0);
		set_attribute(DW_AT_type, DW_FORM_ref_addr);
		set_attribute(DW_AT_DD_small_value, DW_FORM_indirect);
		if (attr & H_DF) {
			set_attribute(DW_AT_DD_delta, DW_FORM_indirect);
		}
		if (attr & H_DS) {
			set_attribute(DW_AT_DD_digits, DW_FORM_indirect);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_fixpt_t.attr)[c]);

	set_abbrev_tag(&dwe_fldg_t, 0, DW_TAG_DD_floating_digits_type, 0);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(DW_AT_DD_digits, DW_FORM_indirect);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_modular_t, 0, DW_TAG_DD_modular_type, 0);
	set_attribute(DW_AT_type, DW_FORM_ref_addr);
	set_attribute(DW_AT_count, DW_FORM_indirect);
	set_attribute(0, 0);

	struct_abbrev(&dwe_task_t, DW_TAG_DD_task_type);

	struct_abbrev(&dwe_synch_t, DW_TAG_DD_synchronized_type);

	c = 0;
	do {
		long attr = (dwe_entry.attr)[c];
		set_abbrev_tag(&dwe_entry, c, DW_TAG_DD_entry, 1);
		if (attr & H_NM) {
			set_attribute(DW_AT_name, DW_FORM_string);
		}
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_AC) {
			set_attribute(DW_AT_accessibility, DW_FORM_data1);
		}
		if (attr & H_TP) {
			set_attribute(DW_AT_type, DW_FORM_ref_addr);
		}
		if (attr & H_RP) {
			set_attribute(DW_AT_DD_repn, DW_FORM_indirect);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_entry.attr)[c]);

	set_abbrev_tag(&dwe_for_unit, 0, DW_TAG_DD_foreign_source, 0);
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(DW_AT_import, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_for_lang, 0, DW_TAG_DD_foreign_source, 0);
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(DW_AT_language, DW_FORM_udata);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_call, 0, DW_TAG_DD_subroutine_call, 0);
	set_attribute(DW_AT_name, DW_FORM_string);
	set_decl_attributes();
	set_attribute(DW_AT_DD_call_kind, DW_FORM_udata);
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_location, DW_FORM_block1);
	set_attribute(0, 0);

	c = 0;
	do {
		long attr = (dwe_return.attr)[c];
		set_abbrev_tag(&dwe_return, c, DW_TAG_DD_subroutine_return, 0);
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_PC) {
			set_attribute(DW_AT_low_pc, DW_FORM_addr);
		}
		if (attr & H_LC) {
			set_attribute(DW_AT_location, DW_FORM_block1);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_return.attr)[c]);

	c = 0;
	do {
		long attr = (dwe_destruct.attr)[c];
		set_abbrev_tag(&dwe_destruct, c, DW_TAG_DD_destruct, 1);
		set_decl_attributes();
		set_attribute(DW_AT_low_pc, DW_FORM_addr);
		if (attr & H_TP) {
			set_attribute(DW_AT_type, DW_FORM_ref_addr);
		}
		if (attr & H_LC) {
			set_attribute(DW_AT_location, DW_FORM_block1);
		}
		if (attr & H_CV) {
			set_attribute(DW_AT_const_value, DW_FORM_indirect);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_destruct.attr)[c]);

	set_abbrev_tag(&dwe_branch, 0, DW_TAG_DD_branch, 1);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_branch_0, 0, DW_TAG_DD_branch, 0);
	set_decl_attributes();
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_break, 0, DW_TAG_DD_breakpoint, 0);
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_test, 0, DW_TAG_DD_test, 0);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_DD_cont_pc, DW_FORM_addr);
	set_attribute(DW_AT_DD_jump_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_test_0, 0, DW_TAG_DD_test, 0);
	set_decl_attributes();
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_jump, 0, DW_TAG_DD_jump, 0);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_DD_jump_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_jump_0, 0, DW_TAG_DD_jump, 0);
	set_decl_attributes();
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_lj, 0, DW_TAG_DD_long_jump, 0);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_location, DW_FORM_block1);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_lj_0, 0, DW_TAG_DD_long_jump, 0);
	set_decl_attributes();
	set_attribute(0, 0);

	c = 0;
	do {
		long attr = (dwe_throw.attr)[c];
		set_abbrev_tag(&dwe_throw, c, DW_TAG_DD_throw, 0);
		if (attr & H_XY) {
			set_decl_attributes();
		}
		if (attr & H_TP) {
			set_attribute(DW_AT_type, DW_FORM_ref_addr);
		}
		if (attr & H_LC) {
			set_attribute(DW_AT_location, DW_FORM_block1);
		}
		if (attr & H_CV) {
			set_attribute(DW_AT_const_value, DW_FORM_indirect);
		}
		set_attribute(0, 0);
		c++;
	} while ((dwe_throw.attr)[c]);

	set_abbrev_tag(&dwe_barrier, 0, DW_TAG_DD_entry_barrier, 0);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_select, 0, DW_TAG_DD_select, 1);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_accept, 0, DW_TAG_DD_accept, 0);
	set_decl_attributes();
	set_attribute(DW_AT_DD_alt, DW_FORM_flag);
	set_attribute(DW_AT_DD_entry_spec, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_accept_c, 0, DW_TAG_DD_accept, 1);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(DW_AT_DD_alt, DW_FORM_flag);
	set_attribute(DW_AT_DD_entry_spec, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_rts, 0, DW_TAG_DD_rts_call, 0);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_DD_alt, DW_FORM_flag);
	set_attribute(DW_AT_DD_call_kind, DW_FORM_udata);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_rts_en, 0, DW_TAG_DD_rts_call, 0);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_DD_alt, DW_FORM_flag);
	set_attribute(DW_AT_DD_entry_spec, DW_FORM_ref_addr);
	set_attribute(DW_AT_DD_call_kind, DW_FORM_udata);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_sel_alt, 0, DW_TAG_DD_select_alternative, 1);
	set_decl_attributes();
	set_attribute(DW_AT_DD_alt_kind, DW_FORM_udata);
	set_attribute(DW_AT_DD_alt_no, DW_FORM_indirect);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_sel_alt_c, 0, DW_TAG_DD_select_alternative, 1);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(DW_AT_DD_alt_kind, DW_FORM_udata);
	set_attribute(DW_AT_DD_alt_no, DW_FORM_indirect);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_sel_guard, 0, DW_TAG_DD_select_guard, 1);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_asynchsel, 0, DW_TAG_DD_asynchronous_select, 1);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_trigger, 0, DW_TAG_DD_triggering_alternate, 1);
	set_decl_attributes();
	set_attribute(DW_AT_DD_alt_kind, DW_FORM_udata);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_trigger_c, 0, DW_TAG_DD_triggering_alternate, 1);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(DW_AT_DD_alt_kind, DW_FORM_udata);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_abort_pt, 0, DW_TAG_DD_abortable_part, 0);
	set_decl_attributes();
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_abort_ptc, 0, DW_TAG_DD_abortable_part, 1);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_requeue, 0, DW_TAG_DD_requeue, 1);
	set_decl_attributes();
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(DW_AT_DD_entry_spec, DW_FORM_ref_addr);
	set_attribute(DW_AT_DD_abort, DW_FORM_flag);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_unknown_t, 0, DW_TAG_DD_incomplete_type, 0);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_span, 0, DW_TAG_DD_source_span, 1);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_span_strt, 0, DW_TAG_DD_source_start, 0);
	set_decl_attributes();
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_span_end, 0, DW_TAG_DD_source_end, 0);
	set_decl_attributes();
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_absent, 0, DW_TAG_DD_absent_code, 1);
	set_attribute(DW_AT_DD_optimisation_kind, DW_FORM_udata);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_absent_r, 0, DW_TAG_DD_absent_code, 1);
	set_attribute(DW_AT_DD_optimisation_kind, DW_FORM_udata);
	set_attribute(DW_AT_DD_optim_ref, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_absent_x, 0, DW_TAG_DD_absent_code, 0);
	set_attribute(DW_AT_DD_optimisation_kind, DW_FORM_udata);
	set_decl_attributes();
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_absent_xr, 0, DW_TAG_DD_absent_code, 0);
	set_attribute(DW_AT_DD_optimisation_kind, DW_FORM_udata);
	set_attribute(DW_AT_DD_optim_ref, DW_FORM_ref_addr);
	set_decl_attributes();
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_displaced, 0, DW_TAG_DD_absent_code, 0);
	set_attribute(DW_AT_DD_optim_ref, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_displ_x, 0, DW_TAG_DD_absent_code, 0);
	set_attribute(DW_AT_DD_optim_ref, DW_FORM_ref_addr);
	set_decl_attributes();
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_moved, 0, DW_TAG_DD_moved_code, 1);
	set_attribute(DW_AT_DD_optimisation_kind, DW_FORM_udata);
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_moved_r, 0, DW_TAG_DD_moved_code, 1);
	set_attribute(DW_AT_DD_optimisation_kind, DW_FORM_udata);
	set_attribute(DW_AT_DD_optim_ref, DW_FORM_ref_addr);
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_moved_x, 0, DW_TAG_DD_moved_code, 1);
	set_attribute(DW_AT_DD_optimisation_kind, DW_FORM_udata);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_moved_xr, 0, DW_TAG_DD_moved_code, 1);
	set_attribute(DW_AT_DD_optimisation_kind, DW_FORM_udata);
	set_attribute(DW_AT_DD_optim_ref, DW_FORM_ref_addr);
	set_attribute(0, 0);

	set_abbrev_tag(&dwe_optim, 0, DW_TAG_DD_optimisation_block, 1);
	set_attribute(DW_AT_DD_optimisation_kind, DW_FORM_udata);
	set_attribute(DW_AT_low_pc, DW_FORM_addr);
	set_attribute(DW_AT_high_pc, DW_FORM_addr);
	set_attribute(DW_AT_DD_obj_noassgn, DW_FORM_block2);
	set_attribute(DW_AT_DD_obj_assgn, DW_FORM_block2);
	set_attribute(0, 0);

	out8();
	asm_printf("%d\n", 0);
	exit_section();
}
