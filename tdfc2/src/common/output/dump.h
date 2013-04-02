/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef DUMP_INCLUDED
#define DUMP_INCLUDED


/*
    DUMP FILE VERSION NUMBER

    These macros give the major and minor version numbers for the dump
    files.  The minor number is increased for upwardly compatible changes
    and the major number for incompatible changes.
*/

#define DUMP_major	((unsigned long)(DUMP_VERSION / 100))
#define DUMP_minor	((unsigned long)(DUMP_VERSION % 100))


/*
    DUMP FILE DECLARATIONS

    The routines in this module are concerned with the output of the
    status dump file.
*/

extern void dump_declare(IDENTIFIER, LOCATION *, int);
extern void dump_undefine(IDENTIFIER, LOCATION *, int);
extern void dump_destr(IDENTIFIER, LOCATION *);
extern void dump_token(IDENTIFIER, IDENTIFIER);
extern void dump_instance(IDENTIFIER, TYPE, TYPE);
extern void dump_use(IDENTIFIER, LOCATION *, int);
extern void dump_call(IDENTIFIER, LOCATION *, int);
extern void dump_override(IDENTIFIER, IDENTIFIER);
extern void dump_alias(IDENTIFIER, IDENTIFIER, LOCATION *);
extern void dump_using(NAMESPACE, NAMESPACE, LOCATION *);
extern void dump_builtin(IDENTIFIER);
extern void dump_token_param(IDENTIFIER);
extern void dump_promote(INT_TYPE, INT_TYPE);
extern void dump_base(CLASS_TYPE);
extern void dump_begin_scope(IDENTIFIER, NAMESPACE, NAMESPACE, LOCATION *);
extern void dump_end_scope(IDENTIFIER, NAMESPACE, LOCATION *);
extern void dump_string_lit(string, string, unsigned);
extern void dump_include(LOCATION *, string, int, int);
extern int dump_error(ERROR, LOCATION *, int, int);
extern void init_dump(string, string);
extern void term_dump(void);

#ifdef FILE_INCLUDED
extern void dump_start(LOCATION *, INCL_DIR *);
extern void dump_end(LOCATION *);
#endif

extern ulong dump_id_next;
extern int dump_anon_class;
extern int dump_template;
extern int dump_implicit;

extern int do_dump;
extern int do_error;
extern int do_header;
extern int do_keyword;
extern int do_local;
extern int do_macro;
extern int do_scope;
extern int do_string;
extern int do_usage;


#endif
