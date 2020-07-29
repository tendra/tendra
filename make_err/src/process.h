/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef PROCESS_INCLUDED
#define PROCESS_INCLUDED


extern char *db_name;
extern char *db_name_alt;
extern char *rig_name;
extern char *rig_comp_output;
extern char *rig_from_comp;
extern char *rig_from_db;
extern LIST(ENTRY) all_entries;
extern LIST(KEY) all_keys;
extern LIST(PROPERTY) all_props;
extern LIST(TYPE) all_types;
extern LIST(USAGE) all_usages;
extern LIST(KEY) all_keys_aux;
extern LIST(PROPERTY) all_props_aux;
extern LIST(TYPE) all_types_aux;
extern LIST(USAGE) all_usages_aux;
extern LIST(KEY) all_keys_alt;
extern LIST(PROPERTY) all_props_alt;
extern LIST(TYPE) all_types_alt;
extern LIST(USAGE) all_usages_alt;
extern void output_all(char *, int);


#endif
