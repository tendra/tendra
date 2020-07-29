/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef dg_aux_key
#define dg_aux_key

extern dg_name new_dg_name(dg_name_key k);
extern dg_type new_dg_type(dg_type_key k);
extern dg_info new_dg_info(dg_info_key k);
extern void extend_dg_name(dg_name name);
extern void extend_dg_type(dg_type name);
extern void init_dgtag(dg_tag tag);
extern dg_type get_qual_dg_type(dg_qual_type_key qual, dg_type type);
extern dg_type get_dg_bitfield_type(dg_type type, shape sha,
				    bitfield_variety bv);
extern char *idname_chars(dg_idname name);
extern dg_filename get_filename(long dat, char *host, char *path, char *name);
extern short_sourcepos shorten_sourcepos(dg_sourcepos pos);
extern short_sourcepos end_sourcepos(dg_sourcepos pos);
extern dg_type find_proc_type(dg_type t);

extern exp diaginfo_exp(exp e);

extern exp relative_exp(shape s, token t);

#endif
