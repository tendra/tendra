/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <tdf/tag.h>
#include <tdf/name.h>

char *
getname(int n)
{
	switch (n) {
	case 0:                       return "zero";
	case ident_tag:               return "ident";
	case seq_tag:                 return "seq";
	case cond_tag:                return "cond";
	case labst_tag:               return "labst";
	case rep_tag:                 return "rep";
	case goto_tag:                return "goto";
	case test_tag:                return "test";
	case ass_tag:                 return "ass";
	case apply_tag:               return "apply";
	case res_tag:                 return "res";
	case goto_lv_tag:             return "goto_lv";
	case solve_tag:               return "solve";
	case assvol_tag:              return "assvol";
	case compound_tag:            return "compound";
	case nof_tag:                 return "nof";
	case local_free_all_tag:      return "local_free_all";
	case local_free_tag:          return "local_free";
	case last_local_tag:          return "last_local";
	case long_jump_tag:           return "long_jump";
	case concatnof_tag:           return "concatnof";
	case ncopies_tag:             return "ncopies";
	case case_tag:                return "case";
	case movecont_tag:            return "movecont";
	case testbit_tag:             return "testbit";
	case alloca_tag:              return "alloca";
	case diagnose_tag:            return "diagnose";
	case prof_tag:                return "prof";
	case ignorable_tag:           return "ignorable";
	case bfass_tag:               return "bfass";
	case bfassvol_tag:            return "bfassvol";
	case condassign_tag:          return "condassign";
	case apply_general_tag:       return "apply_general";
	case tail_call_tag:           return "tail_call";
	case untidy_return_tag:       return "untidy_return";
	case same_callees_tag:        return "same_callees";
	case plus_tag:                return "plus";
	case neg_tag:                 return "neg";
	case shl_tag:                 return "shl";
	case mod_tag:                 return "mod";
	case rem2_tag:                return "rem2";
	case abs_tag:                 return "abs";
	case round_tag:               return "round";
	case offset_pad_tag:          return "offset_pad";
	case offset_div_tag:          return "offset_div";
	case offset_max_tag:          return "offset_max";
	case minptr_tag:              return "minptr";
	case fpower_tag:              return "fpower";
	case fplus_tag:               return "fplus";
	case fminus_tag:              return "fminus";
	case fmult_tag:               return "fmult";
	case fdiv_tag:                return "fdiv";
	case fabs_tag:                return "fabs";
	case fneg_tag:                return "fneg";
	case float_tag:               return "float";
	case chfl_tag:                return "chfl";
	case and_tag:                 return "and";
	case or_tag:                  return "or";
	case xor_tag:                 return "xor";
	case not_tag:                 return "not";
	case component_tag:           return "component";
	case max_tag:                 return "max";
	case min_tag:                 return "min";
	case bitf_to_int_tag:         return "bitf_to_int";
	case bfcont_tag:              return "bfcont";
	case fmax_tag:                return "fmax";
	case shr_tag:                 return "shr";
	case fmin_tag:                return "fmin";
	case div0_tag:                return "div0";
	case bfcontvol_tag:           return "bfcontvol";
	case absbool_tag:             return "absbool";
	case addptr_tag:              return "addptr";
	case chvar_tag:               return "chvar";
	case minus_tag:               return "minus";
	case mult_tag:                return "mult";
	case subptr_tag:              return "subptr";
	case realpart_tag:            return "realpart";
	case div1_tag:                return "div1";
	case div2_tag:                return "div2";
	case offset_add_tag:          return "offset_add";
	case offset_div_by_int_tag:   return "offset_div_by_int";
	case offset_mult_tag:         return "offset_mult";
	case offset_negate_tag:       return "offset_negate";
	case offset_subtract_tag:     return "offset_subtract";
	case rem0_tag:                return "rem0";
	case rotl_tag:                return "rotl";
	case rotr_tag:                return "rotr";
	case power_tag:               return "power";
	case imag_tag:                return "imag";
	case make_complex_tag:        return "make_complex";
	case int_to_bitf_tag:         return "int_to_bitf";
	case hold_tag:                return "hold";
	case hold2_tag:               return "hold2";
	case cont_tag:                return "cont";
	case field_tag:               return "field";
	case val_tag:                 return "val";
	case reff_tag:                return "reff";
	case name_tag:                return "name";
	case proc_tag:                return "proc";
	case top_tag:                 return "top";
	case contvol_tag:             return "contvol";
	case current_env_tag:         return "current_env";
	case env_offset_tag:          return "env_offset";
	case make_lv_tag:             return "make_lv";
	case clear_tag:               return "clear";
	case null_tag:                return "null";
	case real_tag:                return "real";
	case string_tag:              return "string";
	case general_proc_tag:        return "general_proc";
	case env_size_tag:            return "env_size";
	case give_stack_limit_tag:    return "give_stack_limit";
	case general_env_offset_tag:  return "general_env_offset";
	case caller_tag:              return "caller";
	case caller_name_tag:         return "caller_name";
	case make_dynamic_callee_tag: return "make_dynamic_callee";
	case make_callee_list_tag:    return "make_callee_list";
	case set_stack_limit_tag:     return "set_stack_limit";
	case formal_callee_tag:       return "formal_callee";
	case trap_tag:                return "trap_tag";

	/* Powertrans specific */
#if 0
	case locptr_tag:              return "locptr_tag";
#endif

	default:                      return "undefined"; 
	}
}

char *
find_test_name(int n)
{
	switch (n) {
	case 1:  return "greater_than";
	case 2:  return "greater_than_or_equal";
	case 3:  return "less_than";
	case 4:  return "less_than_or_equal";
	case 5:  return "equal";
	case 6:  return "not_equal";
	case 7:  return "not_less_than_or_equal";
	case 8:  return "not_less_than";
	case 9:  return "not_greater_than_or_equal";
	case 10: return "not_greater_than";
	case 11: return "less_than_or_greater_than";
	case 12: return "not_less_than_and_not_greater_than";
	case 13: return "comparable";
	case 14: return "not_comparable";
	default: return "unknown";
	}
}

char *
shape_name(int n)
{
	switch (n) {
	case 1:  return "bothd";
	case 2:  return "tophd";
	case 3:  return "scharhd";
	case 4:  return "ucharhd";
	case 5:  return "swordhd";
	case 6:  return "uwordhd";
	case 7:  return "slonghd";
	case 8:  return "ulonghd";
	case 9:  return "s64hd";
	case 10: return "u64hd";
	case 17: return "shcomplexhd";
	case 18: return "complexhd";
	case 19: return "complexdoublehd";
	case 20: return "shrealhd";
	case 21: return "realhd";
	case 22: return "doublehd";
	case 23: return "bitfhd";
	case 24: return "prokhd";
	case 25: return "ptrhd";
	case 26: return "offsethd";
	case 27: return "sizehd";
	case 28: return "cpdhd";
	case 29: return "nofhd";
	case 30: return "tokhd";
	default: return "unknown";
	}
}

