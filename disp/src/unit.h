/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef UNIT_INCLUDED
#define UNIT_INCLUDED


/*
 * TOKEN/TAG DECLARATIONS/DEFINITIONS
 *
 * This file contains the routines for decoding token declarations, token
 * definitions, tag declarations, tag definitions and the standard unit
 * types associated with them.
 */

extern void token_sort(object *, sortname, char *, long);
extern void read_no_labs(void);
extern void de_tagdec_props(void);
extern void de_tagdef_props(void);
extern void de_tokdec_props(void);
extern void de_tokdef_props(void);
extern void de_al_tagdef_props(void);
extern void de_dg_comp_props(void);
extern void de_diag_type_unit(void);
extern void de_diag_unit(void);
extern void de_linkinfo_props(void);
extern void de_version_props(void);
extern void de_tld2_unit(void);
extern void de_tld_unit(void);
extern void de_make_version(char *);
extern void de_magic(char *);
extern long max_lab_no;
extern int show_usage;
extern int diagnostics;
extern int versions;


/*
 * UNIT USAGE INFORMATION
 *
 * These macros describe the units decoded by the routines above and
 * give the flags which control their use.
 */

#define MSG_tagdec_props		"TAG DECLARATIONS"
#define MSG_tagdef_props		"TAG DEFINITIONS"
#define MSG_tokdec_props		"TOKEN DECLARATIONS"
#define MSG_tokdef_props		"TOKEN DEFINITIONS"
#define MSG_al_tagdef_props		"ALIGNMENT TAG DEFINITIONS"
#define MSG_dg_comp_props		"DIAGNOSTIC INFORMATION"
#define MSG_diag_type_unit		"DIAGNOSTIC TYPE INFORMATION"
#define MSG_diag_unit			"DIAGNOSTIC INFORMATION"
#define MSG_linkinfo_props		"LINKING INFORMATION"
#define MSG_version_props		"TDF VERSION NUMBER"
#define MSG_tld2_unit			"LINKER INFORMATION"
#define MSG_tld_unit			"LINKER INFORMATION"

#define OPT_tagdec_props		1
#define OPT_tagdef_props		1
#define OPT_tokdec_props		1
#define OPT_tokdef_props		1
#define OPT_al_tagdef_props		1
#define OPT_dg_comp_props		diagnostics
#define OPT_diag_type_unit		diagnostics
#define OPT_diag_unit			diagnostics
#define OPT_linkinfo_props		show_usage
#define OPT_version_props		versions
#define OPT_tld2_unit			show_usage
#define OPT_tld_unit			show_usage


#endif
