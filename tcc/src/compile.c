/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include <stdio.h>

#include <shared/bool.h>
#include <shared/error.h>

#include "filename.h"
#include "list.h"
#include "archive.h"
#include "environ.h"
#include "flags.h"
#include "compile.h"
#include "execute.h"
#include "options.h"
#include "stages.h"
#include "startup.h"
#include "suffix.h"
#include "utility.h"
#include "table.h"

static filename *apply_unjoin(filename *, enum filetype);


/*
 * CHECK IF ONE FILE IS THE C SPEC OF THE OTHER
 *
 * This macro checks if q is the C or C++ spec file corresponding to p.  q must
 * be of type C_SPEC and have the same uniq value as p.
 */

#define spec_of(p, q)	((q) &&\
			 ((q)->type == C_SPEC || (q)->type == CPP_SPEC) &&\
			 (q)->uniq == (p)->uniq)


/*
 * APPLY THE SYSTEM COMPILER
 *
 * This routine applies the system C compiler to the files, input, returning
 * the result.
 */

static filename *
apply_cc(filename *input)
{
	filename *p = input;
	filename *output = NULL;
	while (p != NULL) {
		filename *ps = NULL;
		filename *pn = p->next;
		p->next = NULL;
		switch (p->type) {
		case C_SOURCE:
			/* C source */
			if (make_preproc || table_keep(PREPROC_C)) {
				p = do_cc(p, PREPROC_C);
				if (table_stop(PREPROC_C)) {
					break;
				}
			}
			goto preproc_c_lab;
		case PREPROC_C:
preproc_c_lab:
			/* Preprocessed C source */
			if (use_system_cc == 1) {
				ps = do_produce(p);
				if (ps == NULL) {
					p = NULL;
					break;
				} else {
					ps = ps->next;
				}
			}
			if (table_stop(DEP_TDF)) {
				if (ps != NULL) {
					p = NULL;
				}
				break;
			} else if (table_stop(AS_SOURCE)) {
				p = do_cc(p, AS_SOURCE);
				break;
			} else if (table_keep(AS_SOURCE)) {
				p = do_cc(p, AS_SOURCE);
			} else {
				p = do_cc(p, binary_obj_type);
				break;
			}
			goto as_source_lab;
		case CPP_SOURCE:
			/* C++ source */
			if (make_preproc || table_keep(PREPROC_CPP)) {
				p = do_cc(p, PREPROC_CPP);
				if (table_stop(PREPROC_CPP)) {
					break;
				}
			}
			goto preproc_cpp_lab;
		case PREPROC_CPP:
preproc_cpp_lab:
			/* Preprocessed C++ source */
			if (use_system_cc == 1) {
				ps = do_cpp_produce(p);
				if (ps == NULL) {
					p = NULL;
					break;
				} else {
					ps = ps->next;
				}
			}
			if (table_stop(DEP_TDF)) {
				if (ps != NULL) {
					p = NULL;
				}
				break;
			} else if (table_stop(AS_SOURCE)) {
				p = do_cc(p, AS_SOURCE);
				break;
			} else if (table_keep(AS_SOURCE)) {
				p = do_cc(p, AS_SOURCE);
			} else {
				p = do_cc(p, binary_obj_type);
				break;
			}
			goto as_source_lab;
		case AS_SOURCE:
as_source_lab:
			/* Assembly source file */
			if (!table_stop(AS_SOURCE)) {
				p = do_cc(p, BINARY_OBJ);
			}
			break;
		case BINARY_OBJ:
			/* Binary object file */
			break;
		case C_SPEC:
			/* C spec file */
			if (!allow_specs) {
				error(ERR_WARN, "'%s' is a C spec file",
				      p->name);
				p->type = DEFAULT_TYPE;
			} else {
				if (p->storage == INPUT_FILE &&
				    filetype_table[BINARY_OBJ].keep_aux == FTK_TC &&
				    !table_stop(AS_SOURCE)) {
					p = do_build_file(p, BINARY_OBJ);
				}
			}
			break;
		case CPP_SPEC:
			/* C++ spec file */
			if (!allow_specs || !allow_cpp) {
				error(ERR_WARN, "'%s' is a C++ spec file",
				      p->name);
				p->type = DEFAULT_TYPE;
			} else {
				if (p->storage == INPUT_FILE &&
				    filetype_table[BINARY_OBJ].keep_aux == FTK_TC &&
				    !table_stop(AS_SOURCE)) {
					p = do_build_file(p, BINARY_OBJ);
				}
			}
			break;
		default:
			/* Other file types give an error */
			error(ERR_WARN,
			      "TDF file '%s' not recognised in cc mode",
			      p->name);
			p->type = DEFAULT_TYPE;
			break;
		}
		if (p && p->storage != INPUT_FILE && p->aux == NULL) {
			bool have_spec = 0;
			filename *p_archive = p;
			enum filetype t = p->type;
			if (t == BINARY_OBJ && table_keep(t) &&
			    binary_obj_type != t) {
				if (spec_of(p_archive, ps)) {
					p_archive->next = ps;
					p_archive = p_archive->next;
					ps = ps->next;
					p_archive->next = NULL;
					have_spec = 1;
				}
				if (have_spec) {
					p = do_build_file(p, BINARY_OBJ);
				}
			}
		}
		output = add_filename(output, p);
		if (ps) {
			output = add_filename(output, ps);
		}
		p = pn;
	}
	return output;
}


/*
 * APPLY THE TDF LINKER
 *
 * This routine applies the TDF linker to p, returning the result.
 */

static filename *
apply_tdf_link(filename *p)
{
	static bool tried = 0;
	if (p == NULL || table_stop(INDEP_TDF)) {
		return p;
	}
	if (tokdef_name && tokdef_output == NULL && !tried) {
		filename *q;
		if (!allow_notation) {
			read_env(TNC_ENV);
		}
		q = find_filename(tokdef_name, PRETTY_TDF);
		q = do_notation(q);
		if (q) {
			tokdef_output = q->name;
		}
		tried = 1;
	}
	return do_tdf_link(p);
}


/*
 * APPLY THE MAIN COMPILATION STAGES
 *
 * This routine applies the main compilation phases to the input files input,
 * and returns the corresponding output files. If produce is true then the
 * compilation stops at the target independent TDF stage. This, and all the
 * routines in this module, needs to be kept in step with Table 1.
 */

static filename *
apply_compile(filename *input, int produce)
{
	filename *p = input;
	filename *output = NULL;
	if (use_system_cc) {
		return apply_cc(input);
	}
	while (p != NULL) {
		filename *pc = p;
		filename *pn = p->next;
		p->next = NULL;
		/* TODO consider callbacks instead of switching here; then this is centralised to table.c */
		switch (p->type) {
		case C_SOURCE:
			/* C source */
			if (table_keep(PREPROC_C)) {
				p = do_preproc(p);
			} else {
				p = do_produce(p);
			}
			if (allow_specs && table_stop(C_SPEC)) {
				p = NULL;
			}
			if (p != pc) {
				p = apply_compile(p, produce);
			}
			break;
		case PREPROC_C:
			/* Preprocessed C source */
			if (table_stop(PREPROC_C)) {
				break;
			}
			p = do_produce(p);
			if (allow_specs && table_stop(C_SPEC)) {
				p = NULL;
			}
			if (p != pc) {
				p = apply_compile(p, produce);
			}
			break;
		case CPP_SOURCE:
			/* C++ source */
			if (allow_cpp) {
				if (table_keep(PREPROC_CPP)) {
					p = do_cpp_preproc(p);
				} else {
					p = do_cpp_produce(p);
				}
				if (allow_specs && table_stop(CPP_SPEC)) {
					p = NULL;
				}
				if (p != pc) {
					p = apply_compile(p, produce);
				}
			} else {
				error(ERR_WARN, "'%s' is a C++ source file",
				      p->name);
				p->type = DEFAULT_TYPE;
			}
			break;
		case PREPROC_CPP:
			/* Preprocessed C++ source */
			if (table_stop(PREPROC_CPP)) {
				break;
			}
			if (allow_cpp) {
				p = do_cpp_produce(p);
				if (allow_specs && table_stop(CPP_SPEC)) {
					p = NULL;
				}
				if (p != pc) {
					p = apply_compile(p, produce);
				}
			} else {
				error(ERR_WARN,
				      "'%s' is a preprocessed C++ source file",
				      p->name);
				p->type = DEFAULT_TYPE;
			}
			break;
		case INDEP_TDF:
			/* Target independent TDF */
			if (!produce) {
				p = apply_tdf_link(p);
				if (p != pc) {
					p = apply_compile(p, produce);
				}
			}
			break;
		case DEP_TDF:
			/* Target dependent TDF */
			if (!produce) {
				p = do_translate(p);
				if (p != pc) {
					p = apply_compile(p, produce);
				}
			}
			break;
		case AS_SOURCE:
			/* Assembly source */
			if (!produce) {
				p = do_assemble(p);
				if (p != pc) {
					p = apply_compile(p, produce);
				}
			}
			break;
		case PRETTY_TDF:
			/* TDF notation source */
			if (allow_notation) {
				p = do_notation(p);
				if (p != pc) {
					p = apply_compile(p, produce);
				}
			} else {
				error(ERR_WARN,
				      "'%s' is a TDF notation source file",
				      p->name);
				p->type = DEFAULT_TYPE;
			}
			break;
		case PL_TDF:
			/* PL_TDF source */
			if (allow_pl_tdf) {
				p = do_pl_tdf(p);
				if (p != pc) {
					p = apply_compile(p, produce);
				}
			} else {
				error(ERR_WARN,
				      "'%s' is a PL_TDF source file", p->name);
				p->type = DEFAULT_TYPE;
			}
			break;
		case C_SPEC:
			/* C spec file */
			if (!allow_specs) {
				error(ERR_WARN, "'%s' is a C spec file",
				      p->name);
				p->type = DEFAULT_TYPE;
			} else {
				if (p->storage == INPUT_FILE &&
				    filetype_table[BINARY_OBJ].keep_aux == FTK_TC &&
				    !table_stop(AS_SOURCE)) {
					p = do_build_file(p, BINARY_OBJ);
				}
			}
			break;
		case CPP_SPEC:
			/* C++ spec file */
			if (!allow_specs || !allow_cpp) {
				error(ERR_WARN, "'%s' is a C++ spec file",
				      p->name);
				p->type = DEFAULT_TYPE;
			} else {
				if (p->storage == INPUT_FILE &&
				    filetype_table[BINARY_OBJ].keep_aux == FTK_TC &&
				    !table_stop(AS_SOURCE)) {
					p = do_build_file(p, BINARY_OBJ);
				}
			}
			break;
		default:
			/* TODO: document; here I think we fall through to handle the rest below. */
			break;
		}
		if (p && p->storage != INPUT_FILE && p->aux == NULL) {
			bool have_spec = 0;
			filename *p_archive = p;
			if (spec_of(p_archive, p_archive->next)) {
				p_archive = p_archive->next;
				have_spec = 1;
			} else if (spec_of(p_archive, pn)) {
				p_archive->next = pn;
				p_archive = p_archive->next;
				pn = pn->next;
				p_archive->next = NULL;
				have_spec = 1;
			}
			if (have_spec) {
				enum filetype t = p->type;
				if (t == INDEP_TDF && checker && !table_stop(t)) {
					if (table_stop(BINARY_OBJ) ||
					    filetype_table[BINARY_OBJ].keep_aux == FTK_TC) {
						p = do_build_file(p->next,
								  BINARY_OBJ);
					}
				}
				if (t == BINARY_OBJ && table_keep(t)) {
					p = do_build_file(p, BINARY_OBJ);
				}
			}
		}
		output = add_filename(output, p);
		p = pn;
	}
	return output;
}


/*
 * FILTER OUT LIST OF BINARY OBJECT FILES
 *
 * This routine picks out the TDF capsules from the input files, input,
 * compiles them to binary object files, and returns them.
 */

static filename *
filter_ofiles(filename *input)
{
	filename *p = input;
	filename *links = NULL;
	while (p != NULL) {
		filename *pn = p->next;
		p->next = NULL;
		p->aux = pn;
		if (p->type == INDEP_TDF) {
			filename *q = apply_compile(p, 0);
			if (q && q->type == BINARY_OBJ) {
				links = add_filename(links, q);
			}
		}
		p = pn;
	}
	return links;
}


/*
 * APPLY THE SYSTEM LINKER
 *
 * This routine applies the system linker to the input files, input, and
 * returns the corresponding output files.
 */

static filename *
apply_link(filename *input)
{
	filename *p = input;
	enum filetype spec_out = C_SPEC_2;
	filename *links = NULL, *links_out = NULL;
	filename *specs = NULL, *specs_out;
	filename *others = NULL;
	while (p != NULL) {
		filename *pn = p->next;
		p->next = NULL;
		p->aux = pn;
		if (p->type == BINARY_OBJ) {
			links = add_filename(links, p);
		} else if (p->type == C_SPEC) {
			specs = add_filename(specs, p);
		} else if (p->type == CPP_SPEC) {
			specs = add_filename(specs, p);
			spec_out = CPP_SPEC_2;
		} else {
			others = add_filename(others, p);
		}
		p = pn;
	}
	last_return = 0;
	filetype_table[binary_obj_type].keep = FTK_FC;
	specs_out = do_link_specs(specs, spec_out);
	links = add_filename(links, filter_ofiles(specs_out));
	if (use_dynlink != 0 && use_system_cc == 0) {
		links = do_dynlink(links);
	}
	if (links) {
		links_out = do_link(links);
	}
	if (specs_out && links_out) {
		specs_out->uniq = links_out->uniq;
	}
	p = add_filename(links_out, specs_out);
	p = add_filename(p, others);
	if (last_return) {
		/* If the linking failed, keep the .o files */
		filename *q = input;
		bool b = table_keep(BINARY_OBJ);
		filetype_table[BINARY_OBJ].keep = FTK_TC;
		p = NULL;
		while (q != NULL) {
			filename *qa = q->aux;
			q->next = NULL;
			if (q->type == C_SPEC || q->type == CPP_SPEC) {
				q = NULL;
			} else if (q->type == BINARY_OBJ) {
				if (q->storage == INPUT_FILE || b) {
					q = NULL;
				} else if (allow_specs) {
					if (link_specs) {
						q = do_keep(q);
					}
					if (spec_of(q, qa)) {
						q->next = qa;
						qa->next = NULL;
						qa = qa->aux;
						if (link_specs) {
							q->next =
							    do_keep(q->next);
						}
					}
					q = do_build_file(q, BINARY_OBJ);
				} else {
					q = do_keep(q);
				}
			}
			p = add_filename(p, q);
			q = qa;
		}
	}
	return p;
}


/*
 * SPLIT ALL TDF ARCHIVES
 *
 * This routine splits any TDF archives in the input files, input, and returns
 * the corresponding output files.
 */

static filename *
apply_split_arch(filename *input)
{
	filename *p = input;
	filename *output = NULL;
	archive_type = TDF_ARCHIVE;
	while (p != NULL) {
		filename *pn = p->next;
		p->next = NULL;
		if (p->type == TDF_ARCHIVE) {
			if (use_system_cc) {
				error(ERR_WARN, "'%s' is a TDF archive",
				      p->name);
				p->type = DEFAULT_TYPE;
			} else {
				p = do_split_arch(p);
			}
		}
		output = add_filename(output, p);
		p = pn;
	}
	return output;
}


/*
 * BUILD A TDF ARCHIVE
 *
 * This routine creates a TDF archive from the input files, input, and returns
 * the corresponding output files.
 */

static filename *
apply_build_arch(filename *input)
{
	filename *p = input;
	filename *links = NULL;
	filename *specs = NULL;
	filename *others = NULL;
	enum filetype spec_out = C_SPEC_1;
	while (p != NULL) {
		filename *pn = p->next;
		p->next = NULL;
		if (p->type == INDEP_TDF) {
			links = add_filename(links, p);
		} else if (p->type == C_SPEC) {
			specs = add_filename(specs, p);
		} else if (p->type == CPP_SPEC) {
			specs = add_filename(specs, p);
			spec_out = CPP_SPEC_1;
		} else {
			others = add_filename(others, p);
		}
		p = pn;
	}
	specs = do_link_specs(specs, spec_out);
	links = do_build_arch(links);
	if (specs && links) {
		specs->uniq = links->uniq;
	}
	p = add_filename(links, specs);
	p = add_filename(p, others);
	return p;
}


/*
 * BUILD A TDF COMPLEX
 *
 * This routine creates a complex TDF capsule from the input files, input, and
 * returns the corresponding output files.
 */

static filename *
apply_build(filename *input)
{
	filename *p = input;
	filename *links = NULL;
	filename *specs = NULL;
	filename *others = NULL;
	enum filetype spec_out = C_SPEC_1;
	while (p != NULL) {
		filename *pn = p->next;
		p->next = NULL;
		if (p->type == INDEP_TDF) {
			links = add_filename(links, p);
		} else if (p->type == C_SPEC) {
			specs = add_filename(specs, p);
		} else if (p->type == CPP_SPEC) {
			specs = add_filename(specs, p);
			spec_out = CPP_SPEC_1;
		} else {
			others = add_filename(others, p);
		}
		p = pn;
	}
	specs = do_link_specs(specs, spec_out);
	links = do_tdf_build(links);
	if (specs && links) {
		specs->uniq = links->uniq;
	}
	p = add_filename(links, specs);
	p = add_filename(p, others);
	return p;
}


/*
 * APPLY THE PREPROCESSOR
 *
 * This routine applies the preprocessor to the input files, input, and returns
 * the corresponding output files.
 */

static filename *
apply_preproc(filename *input)
{
	filename *p = input;
	filename *output = NULL;
	if (use_system_cc) {
		return apply_cc(input);
	}
	while (p != NULL) {
		filename *pn = p->next;
		p->next = NULL;
		if (p->type == C_SOURCE) {
			p = do_preproc(p);
		} else if (p->type == CPP_SOURCE) {
			p = do_cpp_preproc(p);
		}
		output = add_filename(output, p);
		p = pn;
	}
	return output;
}


/*
 * APPLY THE TDF PRETTY PRINTER
 *
 * This routine applies the TDF pretty printer to the input files, input, and
 * returns the corresponding output files.
 */

static filename *
apply_pretty(filename *input)
{
	filename *p = input;
	filename *output = NULL;
	while (p != NULL) {
		filename *pn = p->next;
		p->next = NULL;
		if (make_tspec) {
			if (p->type == C_SPEC) {
				p = do_pretty(p);
			}
		} else if (p->type == INDEP_TDF) {
			if (make_pretty == 2) {
				p = apply_tdf_link(p);
			}
			p = do_pretty(p);
		} else if (p->type == DEP_TDF) {
			p = do_pretty(p);
		}
		output = add_filename(output, p);
		p = pn;
	}
	return output;
}


/*
 * APPLY THE ARCHIVER TO UNJOIN C SPEC FILES
 *
 * This routine scans input for input archives of type t. It splits these into
 * their component files. For internal archives the contents are in the aux
 * field.
 */

static filename *
apply_unjoin(filename *input, enum filetype t)
{
	filename *p = input;
	filename *output = NULL;
	archive_type = t;
	while (p != NULL) {
		filename *pn = p->next;
		p->next = NULL;
		if (p->type == t) {
			if (p->storage == INPUT_FILE) {
				if (is_archive(p->name)) {
					p = do_split_arch(p);
				}
			} else if (p->aux != NULL) {
				p = p->aux;
			}
		}
		output = add_filename(output, p);
		p = pn;
	}
	return output;
}


/*
 * APPLY ALL THE COMPILATION STAGES
 *
 * This routine applies all the compilation stages to the input files, input,
 * and returns the corresponding output files.
 */

filename *
apply_all(filename *input)
{
	filename *p = input;

	/* Set up file types */
	if (allow_specs) {
		binary_obj_type = BINARY_OBJ_AUX;
	}

	/* Preprocessing is a special case */
	if (make_preproc) {
		return apply_preproc(p);
	}

	/* Any TDF archives are split immediately */
	p = apply_split_arch(input);

	/* Deal with building TDF archive case */
	if (make_archive) {
		p = apply_compile(p, 1);
		if (make_complex) {
			p = apply_build(p);
		}
		return apply_build_arch(p);
	}

	/* Deal with pretty printing case */
	if (make_pretty) {
		p = apply_compile(p, 1);
		if (make_complex) {
			p = apply_build(p);
		}
		return apply_pretty(p);
	}

	/* Deal with building TDF complex */
	if (make_complex) {
		p = apply_compile(p, 1);
		p = apply_build(p);
	}

	/* Main compilation phases */
	p = apply_compile(p, (int)checker);
	if (allow_specs && !table_stop(BINARY_OBJ)) {
		p = apply_unjoin(p, BINARY_OBJ);
	}
	p = apply_link(p);
	return p;
}
