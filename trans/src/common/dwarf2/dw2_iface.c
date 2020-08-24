/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stdio.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <local/dw2_config.h>

#include <tdf/tag.h>

#include <reader/basicread.h>

#include <main/driver.h>
#include <main/print.h>

#include <dwarf2/dw2_iface.h>
#include <dwarf2/dw2_types.h>
#include <dwarf2/dw2_entries.h>
#include <dwarf2/dw2_codes.h>
#include <dwarf2/dw2_basic.h>
#include <dwarf2/dw2_lines.h>
#include <dwarf2/dw2_info.h>
#include <dwarf2/dw2_locdata.h>

#ifdef TDF_DIAG3
#include <diag3/diagglob.h>
#endif
#ifdef TDF_DIAG4
#include <diag4/diagglob.h>
#endif


long dw_info_start;
long dw_text_start;

static long statprog_start;	/* compilation unit level label */
static long statprog_end;
static long text_end;


void
dw_out_path(dg_filename f, int w)
{
	char *com;
	if (!w && f->file_path[0] && f->file_path[0]!= '/') {
		dw_at_string(f->file_path);
	} else {
		size_t n = strlen(f->file_path) + strlen(f->file_host) + 2;
		if (w) {
			n += (strlen(f->file_name) + 1);
		}
		com = xmalloc(n);
		IGNORE strcat(strcat(strcpy(com, f->file_host), ":"),
			      f->file_path);
		if (w) {
			if (f->file_path[0]!= '/') {
				IGNORE strcpy(com, f->file_path);
			}
			IGNORE strcat(strcat(com, "/"), f->file_name);
		}
		dw_at_string(com);
		xfree(com);
	}
}


/* Prepare to read diag unit information */
void
init_dwarf2(void)
{
	init_dw_entries();
}


/* called from text segment */
void
dwarf2_prelude(void)
{
	static int dw_started = 0;
	if (dw_started) {
		error(ERR_INTERNAL, "DWARF output not compatible with separate units");
	}
	dw_started = 1;

	dw_info_start = next_dwarf_label();
	do_compunit_header();
	statprog_start = next_dwarf_label();
	statprog_end = next_dwarf_label();
	do_statprog_prologue(statprog_start, statprog_end);

	/* we may need to separate these */
	dw_text_start = set_dw_text_label();

	/* for multiple compilation units */
	text_end = next_dwarf_label();

	init_dw_locdata();
}


static int
item_present(dg_name item)
{
	UNUSED(item);
	return 1;
#if 0
	exp x;
	if (item->key == DGN_OBJECT)
		x = item->data.n_obj.obtain_val;
	else
		if (item->key == DGN_PROC)
			x = item->data.n_proc.obtain_val;
		else
			return 1;
	while (x && (x->tag == hold_tag || x->tag == name_tag ||
		     x->tag == cont_tag || x->tag == reff_tag))
		x = child(x);
	if (x && x->tag == ident_tag)
		x = child(x);
	if (x) return 1;
	return 0;
#endif
}


static void
out_macros(dg_macro_list macs)
{
	int i;
	for (i = 0; i < macs.len; i++) {
		dg_macro m;
		m = macs.array[0];
		switch (m.key) {
		case DGM_FN: {
			int j;
			out8();
			asm_printf("%d, ", DW_MACINFO_define);
			uleb128((unsigned long)m.pos.line);
			asm_printf("\n");
			start_string(m.u.d.name);
			asm_printf("(");
			for (j = 0; j < m.u.d.pms.len; j++) {
				if (j) {
					asm_printf("'");
				}
				asm_printf("%s", m.u.d.pms.array[j]);
			}
			asm_printf(") %s", m.u.d.defn);
			end_string();
			break;
		}
		case DGM_OBJ:
			out8();
			asm_printf("%d, ", DW_MACINFO_define);
			uleb128((unsigned long)m.pos.line);
			asm_printf("\n");
			start_string(m.u.d.name);
			asm_printf(" %s", m.u.d.defn);
			end_string();
			break;
		case DGM_UNDEF:
			out8();
			asm_printf("%d, ", DW_MACINFO_undef);
			uleb128((unsigned long)m.pos.line);
			asm_printf("\n");
			out_string(m.u.d.name);
			break;
		case DGM_INC:
			out8();
			asm_printf("%d, ", DW_MACINFO_start_file);
			uleb128((unsigned long)m.pos.line);
			asm_printf(", ");
			uleb128((unsigned long)(m.u.i.file->index));
			asm_printf("\n");
			out_macros(m.u.i.macs);
			dw_at_data(1, (long)DW_MACINFO_end_file);
			break;
		}
	}
}


/* called from text segment */
void
dwarf2_postlude(void)
{
	int inside = 0;
	long maclab = 0;
	dg_compilation this_comp;
	complete_dw_locdata();
	this_comp = all_comp_units;
	while (this_comp) {
		dg_name item = this_comp->dn_list;
		abbrev_entry comp_dwe = dwe_comp_unit;
		while (item && !item_present(item)) {
			item = item->next;
		}
		if (item) {
			if (inside) {
				/* => in debug_info section */
				dw_sibling_end();
				exit_section();
			}
			inside = 1;
			if (this_comp->macros.len) {
				/* comp unit has macros */
				comp_dwe = dwe_cmac_unit;
				maclab = next_dwarf_label();
				enter_section("debug_macinfo");
				out_dwf_label(maclab, 1);
				out_macros(this_comp->macros);
				dw_at_data(1, 0);
				exit_section();
			}
			enter_section("debug_info");
			IGNORE dw_entry(comp_dwe, 0);
			dw_at_address(dw_text_start);
			dw_at_address(text_end);
			if (this_comp->prim_file->file_path[0] &&
			    !streq(this_comp->prim_file->file_path,
				   this_comp->comp_dir->file_path)) {
				dw_out_path(this_comp->prim_file, 1);
			} else {
				dw_at_string(this_comp->prim_file->file_name);
			}
			dw_at_udata((unsigned long)(this_comp->language));
			dw_at_address(statprog_start);
			if (this_comp->macros.len) {
				dw_at_address(maclab);
			}
			dw_out_path(this_comp->comp_dir, 0);
			out_producer(this_comp->producer);
			dw_at_data(1, (long)(this_comp->id_case));
			while (item) {
				if (item_present(item)) {
					dw2_out_name(item, GLOBAL_NAME);
				}
				item = item->next;
			}
		}
		this_comp = this_comp->another;
	}
	if (inside) {
		/* back to text section */
		exit_section();
	}
}


/* Output type entries and close info */
void
end_dwarf2(void)
{
	enter_section("debug_info");
	dw2_out_all_types();
	complete_defaults();
	dw_sibling_end();
	exit_section();
	out_dwf_label(text_end, 1);
	close_statprog(statprog_end);
	enter_section("debug_aranges");
	out32();
	out_dwf_label(dw_text_start, 0);
	asm_printf("\n");
	out32();
	out_dwf_labdiff(dw_text_start, text_end);
	asm_printf("\n");
	exit_section();
	dw2_data_aranges();
	close_compunit_info();
}
