/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include "obj_c/errors.h"
#include "obj_c/entry_ops.h"
#include "obj_c/map_ops.h"
#include "obj_c/msg_ops.h"
#include "obj_c/name_ops.h"
#include "obj_c/param_ops.h"

#include "lex.h"
#include "process.h"


/*
    These variables are used to store the standard header information.
*/

char *db_name = "ERRORS";
char *db_name_alt = "ERRORS";
char *rig_name = "ERR_";
char *rig_comp_output = "ERR_";
char *rig_from_comp = "ERR_USE_";
char *rig_from_db = "ERR_NO_";


/*
    These variables are used to store the various lists of information
    built up by the parser.
*/

LIST(ENTRY)all_entries = NULL_list(ENTRY);
LIST(KEY)all_keys = NULL_list(KEY);
LIST(PROPERTY)all_props = NULL_list(PROPERTY);
LIST(TYPE)all_types = NULL_list(TYPE);
LIST(USAGE)all_usages = NULL_list(USAGE);
LIST(KEY)all_keys_aux = NULL_list(KEY);
LIST(PROPERTY)all_props_aux = NULL_list(PROPERTY);
LIST(TYPE)all_types_aux = NULL_list(TYPE);
LIST(USAGE)all_usages_aux = NULL_list(USAGE);
LIST(KEY)all_keys_alt = NULL_list(KEY);
LIST(PROPERTY)all_props_alt = NULL_list(PROPERTY);
LIST(TYPE)all_types_alt = NULL_list(TYPE);
LIST(USAGE)all_usages_alt = NULL_list(USAGE);


/*
    This routine finds a code letter corresponding to the number n.  It
    assumes the ASCII character set.
*/

static int
code_letter(int n)
{
	if (n < 10) {
		return '0' + n;
	}
	if (n < 36) {
		return 'A' + (n - 10);
	}
	if (n < 72) {
		return 'a' + (n - 36);
	}
	return n + 128;
}


/*
    This routine looks up the value of the property named s in the list
    of property mappings p.
*/

static MAP
find_map(LIST(MAP)p, string s)
{
	while (!IS_NULL_list(p)) {
		MAP m = DEREF_map(HEAD_list(p));
		NAME n = DEREF_name(map_key(m));
		if (!IS_NULL_name(n)) {
			string t = DEREF_string(name_id(n));
			if (streq(s, t)) {
				return m;
			}
		}
		p = TAIL_list(p);
	}
	return NULL_map;
}


/*
    This routine prints the message list p to the file f.
*/

static void
output_msg(FILE *f, LIST(MESSAGE) p)
{
	int sp = 0;
	IGNORE fputc('"', f);
	while (!IS_NULL_list(p)) {
		MESSAGE m = DEREF_msg(HEAD_list(p));
		if (!IS_NULL_msg(m)) {
			if (IS_msg_param(m)) {
				PARAM a = DEREF_param(msg_param_arg(m));
				int an = DEREF_int(param_number(a));
				an = code_letter(an);
				if (sp) {
					IGNORE fputc(' ', f);
					sp = 0;
				}
				IGNORE fprintf(f, "%%%c", an);
			} else {
				char c;
				string s = DEREF_string(msg_text_arg(m));
				while (c = *(s++), c != 0) {
					if (c == ' ' || c == '\t' ||
					    c == '\n') {
						sp = 1;
					} else {
						if (sp) {
							IGNORE fputc(' ', f);
							sp = 0;
						}
						IGNORE fputc(c, f);
					}
				}
			}
		}
		p = TAIL_list(p);
	}
	IGNORE fputc('"', f);
	return;
}


/*
    This routine outputs all the error definitions to the file f.
*/

static void
output_defn(FILE *f)
{
	/* Print error catalog */
	LIST(NAME) p;
	char *d1 = db_name;
	char *d2 = db_name_alt;
	char *pre = rig_comp_output;
	char *pre_comp = rig_from_comp;
	LIST(ENTRY) q = all_entries;

	/* Print each catalogue entry */
	IGNORE fprintf(f, "/* Error catalogue */\n\n");
	if (streq(d1, d2)) {
		IGNORE fprintf(f, "const char *%sNAME = \"%s\" ;\n", pre, d1);
	} else {
		IGNORE fprintf(f, "#ifndef %sALTERNATE\n", pre);
		IGNORE fprintf(f, "const char *%sNAME = \"%s\" ;\n", pre, d1);
		IGNORE fprintf(f, "#else\n");
		IGNORE fprintf(f, "const char *%sNAME = \"%s\" ;\n", pre, d2);
		IGNORE fprintf(f, "#endif\n");
	}
	IGNORE fprintf(f, "\n%sDATA %sCATALOG [] = {\n", pre, pre);
	while (!IS_NULL_list(q)) {
		unsigned u = 0;
		char *suff = ",\n";
		ENTRY e = DEREF_entry(HEAD_list(q));
		string en = DEREF_string(entry_name(e));
		USAGE eu = DEREF_name(entry_use(e));
		USAGE ev = DEREF_name(entry_alt_use(e));
		LIST(MAP) em = DEREF_list(entry_maps(e));
		LIST(PROPERTY) eq = DEREF_list(entry_props(e));
		LIST(PARAM) ep = DEREF_list(entry_signature(e));

		/* Print error name */
		IGNORE fprintf(f, "    {\n\t\"%s\",\n", en);

		/* Print error signature */
		if (IS_NULL_list(ep)) {
			IGNORE fprintf(f, "\tNULL,\n");
		} else {
			IGNORE fprintf(f, "\t\"");
			while (!IS_NULL_list(ep)) {
				PARAM a = DEREF_param(HEAD_list(ep));
				TYPE at = DEREF_name(param_type(a));
				int an = DEREF_int(name_number(at));
				an = code_letter(an);
				IGNORE fputc(an, f);
				ep = TAIL_list(ep);
			}
			IGNORE fprintf(f, "\",\n");
		}

		/* Print error usage */
		if (!EQ_name(eu, ev)) {
			IGNORE fprintf(f, "#ifndef %sALTERNATE\n", pre);
		}
		if (IS_NULL_name(eu)) {
			IGNORE fprintf(f, "\t0,\n");
		} else {
			string un = DEREF_string(name_id(eu));
			IGNORE fprintf(f, "\t%s%s,\n", pre_comp, un);
		}
		if (!EQ_name(eu, ev)) {
			IGNORE fprintf(f, "#else\n");
			if (IS_NULL_name(ev)) {
				IGNORE fprintf(f, "\t0,\n");
			} else {
				string vn = DEREF_string(name_id(ev));
				IGNORE fprintf(f, "\t%s%s,\n", pre_comp, vn);
			}
			IGNORE fprintf(f, "#endif\n");
		}

		/* Print error properties */
		p = all_keys;
		if (IS_NULL_list(p)) {
			suff = "\n";
		}
		while (!IS_NULL_list(eq)) {
			PROPERTY nq = DEREF_name(HEAD_list(eq));
			unsigned n = (unsigned)DEREF_int(name_number(nq));
			u |= (((unsigned)1) << n);
			eq = TAIL_list(eq);
		}
		IGNORE fprintf(f, "\t%u%s", u, suff);

		/* Print error keys */
		while (!IS_NULL_list(p)) {
			NAME n = DEREF_name(HEAD_list(p));
			string pn = DEREF_string(name_id(n));
			MAP pm = find_map(em, pn);
			p = TAIL_list(p);
			if (IS_NULL_list(p)) {
				suff = "\n";
			}
			if (IS_NULL_map(pm)) {
				IGNORE fprintf(f, "\tNULL%s", suff);
			} else {
				LIST(MESSAGE)m1 = DEREF_list(map_msg(pm));
				LIST(MESSAGE)m2 = DEREF_list(map_alt_msg(pm));
				if (!EQ_list(m1, m2)) {
					IGNORE fprintf(f, "#ifndef %sALTERNATE\n",
						  pre);
				}
				IGNORE fprintf(f, "\t");
				output_msg(f, m1);
				IGNORE fprintf(f, "%s", suff);
				if (!EQ_list(m1, m2)) {
					IGNORE fprintf(f, "#else\n\t");
					output_msg(f, m2);
					IGNORE fprintf(f, "%s#endif\n", suff);
				}
			}
		}
		IGNORE fprintf(f, "    },\n");
		q = TAIL_list(q);
	}

	/* Print dummy end marker */
	IGNORE fprintf(f, "    {\n");
	IGNORE fprintf(f, "\tNULL,\n");
	IGNORE fprintf(f, "\tNULL,\n");
	IGNORE fprintf(f, "\t0,\n");
	IGNORE fprintf(f, "\t0");
	p = all_keys;
	while (!IS_NULL_list(p)) {
		IGNORE fprintf(f, ",\n\tNULL");
		p = TAIL_list(p);
	}
	IGNORE fprintf(f, "\n    }\n");
	IGNORE fprintf(f, "} ;\n");
	return;
}


/*
    This routine outputs all the error declarations to the file f.
*/

static void
output_decl(FILE *f)
{
	int qn = 0;
	LIST(ENTRY) q = all_entries;

	/* Print main type definition */
	char *pre = rig_comp_output;
	char *pre_comp = rig_from_comp;
	LIST(NAME) p = all_keys;
	IGNORE fprintf(f, "#ifndef %sINCLUDED\n", pre);
	IGNORE fprintf(f, "#define %sINCLUDED\n\n\n", pre);
	if (LENGTH_list(all_props) < 16) {
		IGNORE fprintf(f, "typedef unsigned %sPROPS ;\n\n", pre);
	} else {
		IGNORE fprintf(f, "typedef unsigned long %sPROPS ;\n\n", pre);
	}
	IGNORE fprintf(f, "typedef struct {\n");
	IGNORE fprintf(f, "    const char *name ;\n");
	IGNORE fprintf(f, "    const char *signature ;\n");
	IGNORE fprintf(f, "    int usage ;\n");
	IGNORE fprintf(f, "    %sPROPS props ;\n", pre);
	while (!IS_NULL_list(p)) {
		NAME t = DEREF_name(HEAD_list(p));
		string tn = DEREF_string(name_id(t));
		IGNORE fprintf(f, "    const char *key_%s ;\n", tn);
		p = TAIL_list(p);
	}
	IGNORE fprintf(f, "} %sDATA ;\n\n", pre);
	IGNORE fprintf(f, "extern %sDATA %sCATALOG [] ;\n", pre, pre);
	IGNORE fprintf(f, "extern const char *%sNAME ;\n\n\n", pre);

	/* Print type keys */
	p = all_types;
	IGNORE fprintf(f, "/* Error type keys */\n\n");
	while (!IS_NULL_list(p)) {
		NAME t = DEREF_name(HEAD_list(p));
		string tn = DEREF_string(name_id(t));
		int n = DEREF_int(name_number(t));
		n = code_letter(n);
		IGNORE fprintf(f, "#define %sKEY_%s '%c'\n", pre, tn, n);
		p = TAIL_list(p);
	}
	IGNORE fprintf(f, "\n\n");

	/* Print usage keys */
	p = all_usages;
	IGNORE fprintf(f, "/* Error usage keys */\n\n");
	IGNORE fprintf(f, "#ifndef %sUSE\n", pre);
	while (!IS_NULL_list(p)) {
		NAME t = DEREF_name(HEAD_list(p));
		string tn = DEREF_string(name_id(t));
		int n = DEREF_int(name_number(t));
		IGNORE fprintf(f, "#define %s%s %d\n", pre_comp, tn, n);
		p = TAIL_list(p);
	}
	IGNORE fprintf(f, "#endif\n\n\n");

	/* Print property keys */
	p = all_props;
	IGNORE fprintf(f, "/* Error property keys */\n\n");
	IGNORE fprintf(f, "#ifndef %sPROP\n", pre);
	while (!IS_NULL_list(p)) {
		NAME t = DEREF_name(HEAD_list(p));
		string tn = DEREF_string(name_id(t));
		unsigned n = (unsigned)DEREF_int(name_number(t));
		unsigned u = (((unsigned)1) << n);
		IGNORE fprintf(f, "#define %sPROP_%s ( ( %sPROPS ) 0x%x )\n",
			  pre, tn, pre, u);
		p = TAIL_list(p);
	}
	IGNORE fprintf(f, "#endif\n\n\n");

	/* Print type checking macros */
	p = all_types;
	IGNORE fprintf(f, "/* Error type checking */\n\n");
	IGNORE fprintf(f, "#if defined ( %sCHECK ) && defined ( __STDC__ )\n", pre);
	while (!IS_NULL_list(p)) {
		NAME t = DEREF_name(HEAD_list(p));
		string tn = DEREF_string(name_id(t));
		int n = DEREF_int(name_number(t));
		n = code_letter(n);
		IGNORE fprintf(f, "extern %s chk_%c ( %s ) ;\n", tn, n, tn);
		p = TAIL_list(p);
	}
	IGNORE fprintf(f, "#else\n");
	p = all_types;
	while (!IS_NULL_list(p)) {
		NAME t = DEREF_name(HEAD_list(p));
		int n = DEREF_int(name_number(t));
		n = code_letter(n);
		IGNORE fprintf(f, "#define chk_%c( A ) ( A )\n", n);
		p = TAIL_list(p);
	}
	IGNORE fprintf(f, "#endif\n\n\n");

	/* Print error macros */
	IGNORE fprintf ( f, "/* Error message macros */\n\n" ) ;
	IGNORE fprintf(f, "#ifdef %sGEN\n\n", pre);
	while (!IS_NULL_list(q)) {
		ENTRY e = DEREF_entry(HEAD_list(q));
		string en = DEREF_string(entry_name(e));
		LIST(PARAM) ep = DEREF_list(entry_signature(e));
		size_t np = LENGTH_list(ep);
		IGNORE fprintf(f, "#define %s%s(", pre, en);
		if (!IS_NULL_list(ep)) {
			/* Print parameter list */
			int arg = 0;
			LIST(PARAM)eq = ep;
			while (!IS_NULL_list(eq)) {
				if (arg) {
					IGNORE fputc(',', f);
				}
				IGNORE fprintf(f, " %c", 'A' + arg);
				eq = TAIL_list(eq);
				arg++;
			}
			IGNORE fputc(' ', f);
		}
		IGNORE fprintf(f, ")\\\n");
		IGNORE fprintf(f, "\t%sGEN ( %d", pre, qn);
		if (np) {
			/* Print error definition */
			int arg = 0;
			LIST(PARAM) eq = ep;
			while (!IS_NULL_list(eq)) {
				PARAM a = DEREF_param(HEAD_list(eq));
				TYPE at = DEREF_name(param_type(a));
				int an = DEREF_int(name_number(at));
				an = code_letter(an);
				IGNORE fprintf(f, ", chk_%c ( %c )", an, 'A' + arg);
				eq = TAIL_list(eq);
				arg++;
			}
		}
		IGNORE fprintf(f, " )\n\n");
		q = TAIL_list(q);
		qn++;
	}
	IGNORE fprintf(f, "\n#endif\n#endif\n");
	return;
}


/*
    This routine outputs all the error numbers to the file f.
*/

static void
output_number(FILE *f)
{
	int qn = 0;
	LIST(ENTRY) q = all_entries;
	char *pre = rig_comp_output;
	char *pre_db = rig_from_db;
	IGNORE fprintf(f, "#ifndef %sNO_INCLUDED\n", pre);
	IGNORE fprintf(f, "#define %sNO_INCLUDED\n\n\n", pre);
	IGNORE fprintf(f, "/* Error message macros */\n\n");
	while (!IS_NULL_list(q)) {
		ENTRY e = DEREF_entry(HEAD_list(q));
		string en = DEREF_string(entry_name(e));
		IGNORE fprintf(f, "#define %s%s %d\n", pre_db, en, qn);
		q = TAIL_list(q);
		qn++;
	}
	IGNORE fprintf(f, "\n#endif\n");
	return;
}


/*
    This routine output all the usages to the file f.
*/

static void
output_usage(FILE *f)
{
	char *pre = rig_comp_output;
	char *pre_comp = rig_from_comp;
	LIST(USAGE) p = all_usages;
	LIST(USAGE) q = all_usages_aux;
	LIST(USAGE) r = all_usages_alt;
	while (!IS_NULL_list(p)) {
		USAGE u = DEREF_name(HEAD_list(p));
		USAGE v = DEREF_name(HEAD_list(q));
		USAGE w = DEREF_name(HEAD_list(r));
		string s = DEREF_string(name_id(u));
		string t = DEREF_string(name_id(v));
		if (!EQ_name(v, w)) {
			IGNORE fprintf(f, "#ifndef %sALTERNATE\n", pre);
		}
		IGNORE fprintf(f, "{ \"%s\", %sVALUE_%s },\n", s, pre_comp, t);
		if (!EQ_name(v, w)) {
			t = DEREF_string(name_id(w));
			IGNORE fprintf(f, "#else\n");
			IGNORE fprintf(f, "{ \"%s\", %sVALUE_%s },\n", s, pre_comp,
				  t);
			IGNORE fprintf(f, "#endif\n");
		}
		r = TAIL_list(r);
		q = TAIL_list(q);
		p = TAIL_list(p);
	}
	return;
}


/*
    This routine outputs all the information gained into the file nm using
    the action indicated by act.  If nm is the null string then the standard
    output is used.
*/

void
output_all(char *nm, int act)
{
	/* Open output file */
	FILE *f;
	if (nm == NULL || streq(nm, "-")) {
		f = stdout;
		nm = NULL;
	} else {
		f = fopen(nm, "w");
		if (f == NULL) {
			error(ERR_SERIOUS, "Can't open output file, '%s'",
			      nm);
			return;
		}
	}

	/* Print header comment */
	if (first_comment) {
		IGNORE fprintf(f, "%s\n\n", first_comment);
	}
	IGNORE fprintf ( f, "/* AUTOMATICALLY GENERATED BY %s FROM %s */\n\n\n",
		    progname, db_name);

	/* Print appropriate information */
	switch (act) {
	case 0:
		output_decl(f);
		break;
	case 1:
		output_defn(f);
		break;
	case 2:
		output_number(f);
		break;
	case 3:
		output_usage(f);
		break;
	}

	/* Close output file */
	if (nm != NULL) {
		(void) fclose(f);
	}
	return;
}
