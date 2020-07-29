/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CODE_INCLUDED
#define CODE_INCLUDED


extern int extra_asserts;
extern int extra_headers;
extern int map_proto;
extern void main_action_c(char *);
extern void print_deref(TYPE_P, char *, char *);
extern void print_proto(void);
extern void print_include(void);
extern void print_struct_defn(void);
extern void print_map_args(char *);
extern void print_enum_consts(void);
extern void print_union_map_c(char *, char *);
extern void print_union_hdr_c(char *, char *);
extern int field_not_empty(void);


#endif
