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
$Date: 1998/03/15 16:00:34 $
$Revision: 1.4 $
$Log: dw2_iface.c,v $
 * Revision 1.4  1998/03/15  16:00:34  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.3  1998/03/11  11:03:43  pwe
 * DWARF optimisation info
 *
 * Revision 1.2  1998/01/21  10:30:05  pwe
 * labdiff change
 *
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.10  1998/01/09  09:31:28  pwe
 * prep restructure
 *
 * Revision 1.9  1997/12/08  16:37:04  pwe
 * abbrev key & directory names
 *
 * Revision 1.8  1997/12/04  19:41:26  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.7  1997/11/06  09:22:07  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.6  1997/10/23  09:27:36  pwe
 * ANDF-DE v1.7, extra diags
 *
 * Revision 1.5  1997/10/10  18:18:32  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.4  1997/08/23  13:36:39  pwe
 * initial ANDF-DE
 *
 * Revision 1.3  1997/04/17  11:50:22  pwe
 * Sparc and 80x86 support
 *
 * Revision 1.2  1997/03/24  11:10:26  pwe
 * struct bitfields
 *
 * Revision 1.1  1997/03/20  16:09:12  pwe
 * first version
 *
**********************************************************************/

#include "config.h"
#include "common_types.h"
#include "basicread.h"
#include "dg_globs.h"
#include "tags.h"
#include "expmacs.h"
#include "dw2_config.h"
#include "dw2_iface.h"
#include "dw2_types.h"
#include "dw2_entries.h"
#include "dw2_codes.h"
#include "dw2_basic.h"
#include "dw2_lines.h"
#include "dw2_info.h"
#include "dw2_locdata.h"
#include "xalloc.h"
#include "diagglob.h"


int dwarf2 = 0;

long dw_info_start;
long dw_text_start;

static long statprog_start;	/* compilation unit level label */
static long statprog_end;
static long text_end;


void dw_out_path
    PROTO_N ( (f, w) )
    PROTO_T ( dg_filename f X int w )
{
  char * com;
  if (!w && f->file_path[0] && f->file_path[0] != '/')
    dw_at_string (f->file_path);
  else {
    size_t n = strlen (f->file_path) + strlen (f->file_host) + 2;
    if (w)
      n += (strlen (f->file_name) + 1);
    com = (char *)xmalloc (n);
    IGNORE strcat (strcat (strcpy (com, f->file_host), ":"), f->file_path);
    if (w) {
      if (f->file_path[0] != '/')
	IGNORE strcpy (com, f->file_path);
      IGNORE strcat (strcat (com, "/"), f->file_name);
    }
    dw_at_string (com);
    xfree ((void *)com);
  }
  return;
}


void init_dwarf2
    PROTO_Z ()
	/* Prepare to read diag unit information */
{
  init_dw_entries ();
  return;
}


void dwarf2_prelude
    PROTO_Z ()
	/* called from text segment */
{
  static int dw_started = 0;
  if (dw_started) {
    failer ("DWARF output not compatible with separate units");
  }
  dw_started = 1;

  dw_info_start = next_dwarf_label ();
  do_compunit_header ();
  statprog_start = next_dwarf_label ();
  statprog_end = next_dwarf_label ();
  do_statprog_prologue (statprog_start, statprog_end);

  dw_text_start = set_dw_text_label ();	/* we may need to separate these */
  text_end = next_dwarf_label ();	/* for multiple compilation units */

  init_dw_locdata ();
  return;
}


static int item_present
    PROTO_N ( (item) )
    PROTO_T ( dg_name item )
{
  UNUSED (item);
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
  while (x && (name(x) == hold_tag || name(x) == name_tag ||
	name(x) == cont_tag || name(x) == reff_tag))
    x = son(x);
  if (x && name(x) == ident_tag)
    x = son(x);
  if (x) return 1;
  return 0;
#endif
}


static char * sep = ", ";

static void out_macros
    PROTO_N ( (macs) )
    PROTO_T ( dg_macro_list macs )
{
  int i;
  for (i = 0; i < macs.len; i++) {
    dg_macro m;
    m = macs.array[0];
    switch (m.key) {
      case DGM_FN: {
	int j;
	out8(); outn ((long)DW_MACINFO_define); outs (sep);
	uleb128 ((unsigned long)m.pos.line); d_outnl ();
	start_string (m.u.d.nam);
	outs ("(");
	for (j = 0; j < m.u.d.pms.len; j++) {
	  if (j) outs ("'");
	  outs (m.u.d.pms.array[j]);
	}
	outs (") "); outs (m.u.d.defn);
	end_string ();
	break;
      }
      case DGM_OBJ: {
	out8(); outn ((long)DW_MACINFO_define); outs (sep);
	uleb128 ((unsigned long)m.pos.line); d_outnl ();
	start_string (m.u.d.nam);
	outs (" "); outs (m.u.d.defn);
	end_string ();
	break;
      }
      case DGM_UNDEF: {
	out8(); outn ((long)DW_MACINFO_undef); outs (sep);
	uleb128 ((unsigned long)m.pos.line); d_outnl ();
	out_string (m.u.d.nam);
	break;
      }
      case DGM_INC: {
	out8(); outn ((long)DW_MACINFO_start_file); outs (sep);
	uleb128 ((unsigned long)m.pos.line); outs (sep);
	uleb128 ((unsigned long)(m.u.i.file->index)); d_outnl ();
	out_macros (m.u.i.macs);
	dw_at_data (1, (long)DW_MACINFO_end_file);
	break;
      }
    }
  }
  return;
}


void dwarf2_postlude
    PROTO_Z ()
	/* called from text segment */
{
  int inside = 0;
  long maclab = 0;
  dg_compilation this_comp;
  complete_dw_locdata ();
  this_comp = all_comp_units;
  while (this_comp) {
    dg_name item = this_comp->dn_list;
    abbrev_entry comp_dwe = dwe_comp_unit;
    while (item && !item_present(item))
      item = item -> next;
    if (item) {
      if (inside) {		/* => in debug_info section */
	dw_sibling_end ();
	exit_section ();
      }
      inside = 1;
      if (this_comp->macros.len) {	/* comp unit has macros */
	comp_dwe = dwe_cmac_unit;
	maclab = next_dwarf_label ();
	enter_section ("debug_macinfo");
	out_dwf_label (maclab, 1);
	out_macros (this_comp->macros);
	dw_at_data (1, (long)0);
	exit_section ();
      }
      enter_section ("debug_info");
      IGNORE dw_entry (comp_dwe, (long)0);
      dw_at_address (dw_text_start);
      dw_at_address (text_end);
      if (this_comp->prim_file->file_path[0] &&
		strcmp (this_comp->prim_file->file_path,
			this_comp->comp_dir->file_path) )
	dw_out_path (this_comp->prim_file, 1);
      else
        dw_at_string (this_comp->prim_file->file_name);
      dw_at_udata ((unsigned long)(this_comp->language));
      dw_at_address (statprog_start);
      if (this_comp->macros.len)
	dw_at_address (maclab);
      dw_out_path (this_comp->comp_dir, 0);
      out_producer (this_comp->producer);
      dw_at_data (1, (long)(this_comp->id_case));
      while (item) {
	if (item_present(item))
	  dw2_out_name (item, GLOBAL_NAME);
	item = item -> next;
      }
    }
    this_comp = this_comp->another;
  }
  if (inside)
    exit_section ();	/* back to text section */
  return;
}


void end_dwarf2
    PROTO_Z ()
	/* Output type entries and close info */
{
  enter_section ("debug_info");
  dw2_out_all_types ();
  complete_defaults ();
  dw_sibling_end ();
  exit_section ();
  out_dwf_label (text_end, 1);
  close_statprog (statprog_end);
  enter_section ("debug_aranges");
  out32 (); out_dwf_label (dw_text_start, 0); d_outnl ();
  out32 (); out_dwf_labdiff (dw_text_start, text_end); d_outnl ();
  exit_section ();
  dw2_data_aranges ();
  close_compunit_info ();
  return;
}
