/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include <string.h>

#include <shared/error.h>
#include <shared/string.h>

#include "config.h"
#include "filename.h"
#include "list.h"
#include "archive.h"
#include "execute.h"
#include "flags.h"
#include "options.h"
#include "stages.h"
#include "startup.h"
#include "suffix.h"
#include "utility.h"
#include "table.h"
#include "environ.h"


/*
 * BINARY OBJECT FILE TYPE
 *
 * The type of binary object file to be produced, for example, by the assembler
 * varies according to whether it will later be included in a spec archive.
 * This value determines this file type.
 */

enum filetype binary_obj_type = BINARY_OBJ;


/*
 * COPY A FILE
 *
 * This routine moves the file from to the file to. If to is null then from is
 * copied to the standard output. All the routines in this module return their
 * set of output files. This may be null if an error has occurred.
 */

static filename *
do_move(filename *from, filename *to)
{
	if (from == NULL) {
		return from;
	}
	if (to) {
		if (strcmp(from->name, to->name) == 0) {
			return to;
		}
		cmd_env("MOVE");
		cmd_filename(from);
		cmd_filename(to);
	} else {
		cmd_env("CAT");
		cmd_filename(from);
	}
	return execute(from, to);
}


/*
 * PRESERVE A FILE
 *
 * This routine preserves the file p by moving it, if necessary, to the work
 * directory. It returns the new location of p.
 */

filename *
do_keep(filename *p)
{
	if (p->storage == TEMP_FILE) {
		filename *q = make_filename(p, p->type, PRESERVED_FILE);
		cmd_env("MOVE");
		cmd_filename(p);
		cmd_filename(q);
		IGNORE execute(no_filename, no_filename);
		return q;
	}
	return p;
}


/*
 * TEMPORARY FILE NAME
 *
 * This is set by uniq_filename to be either its output file or a temporary
 * file if the output corresponds to an input file.
 */

static filename *uniq_tempfile = NULL;


/*
 * MAKE A UNIQUE FILE NAME
 *
 * This routine creates a filename with name nm, type t and storage s. If this
 * coincides with one of the files in input then a temporary file is stored in
 * uniq_tempfile, otherwise it holds the output file.
 */

static filename *
uniq_filename(const char *nm, enum filetype t, int s, filename *input)
{
	filename *p = find_filename(nm, t);
	filename *q = make_filename(p, t, s);
	uniq_tempfile = q;
	for (p = input; p != NULL; p = p->next) {
		if (strcmp(p->name, q->name) == 0) {
			if (p->storage == TEMP_FILE) {
				uniq_tempfile = make_filename(no_filename, t,
							      TEMP_FILE);
			} else {
				char *m = NULL;
				static char plus[] = { EXTRA_KEY, 0 };
				q->name = xstrcat(q->name, plus);
				switch (t)EXHAUSTIVE {
				case INDEP_TDF:
					m = "merged TDF capsule";
					break;
				case TDF_ARCHIVE:
					m = "archive file";
					break;
				case C_SPEC:
					m = "linked C spec file";
					break;
				case CPP_SPEC:
					m = "linked C++ spec file";
					break;
				case EXECUTABLE:
					m = "executable";
					break;

				default:
					break;
				}
				error(ERROR_WARNING,
				      "Renaming %s '%s' to '%s' to avoid clash with input",
				      m, p->name, q->name);
			}
			return q;
		}
	}
	return q;
}


/*
 * PRINT PRODUCER/PREPROCESSOR OPTIONS
 *
 * The C/C++ to TDF producers and the TDF C/C++ preprocessor accept the same
 * command-line options; the parameter 'pp' is used to determine which startup
 * files are appropriate.
 */

static void
producer_options(int pp)
{
	int is_c = (pp == PRODUCE_ID || pp == PREPROC_ID);

	if (!flag_nepc && envvar_get(envvars, "PORTABILITY") != NULL) {
		cmd_string("-n");
		cmd_env("PORTABILITY");
	}
	if (flag_diag) {
		if (flag_diag == 1) {
			cmd_string("-g1");
		} else {
			cmd_string("-g2");
		}
	}
	if (flag_incl) {
		cmd_string("-H");
	}
	if (flag_startup) {
		if (is_c) {
			cmd_env("STARTUP");
			cmd_env("USR_STARTUP");
		} else {
			cmd_env("STARTUP_CPP");
			cmd_env("USR_STARTUP_CPP");
		}
		if (startup_name != NULL) {
			cmd_string("-f");
			cmd_string(startup_name);
		}
		cmd_env("USR_PROD_FOPTIONS");
		cmd_env("USR_PROD_EOPTIONS");
		if (endup_name != NULL) {
			cmd_string("-e");
			cmd_string(endup_name);
		}
	}
	cmd_env("USR_INCL");
	if (!is_c) {
		cmd_env("INCL_CPP");
	}
	cmd_env("INCL");
	if (flag_startup) {
		if (is_c) {
			cmd_env("STARTUP_DIR");
		} else {
			cmd_env("STARTUP_CPP_DIR");
		}
	}
	if (checker) {
		cmd_string("-c");
	}
	if (make_pretty) {
		cmd_string("-t");
	}
}


/*
 * APPLY THE C PRODUCER
 *
 * This routine applies the C to TDF producer to input and returns the result.
 */

filename *
do_produce(filename *input)
{
	int spec_produced;
	filename *output;
	filename *spec = NULL;

	if (input == NULL) {
		return input;
	}
	output = make_filename(input, INDEP_TDF, where(INDEP_TDF));
	cmd_env("TDFC");
	if (allow_specs == 1) {
		spec = make_filename(input, C_SPEC, where(C_SPEC));
		if (dump_opts) {
			cmd_string(xstrcat(dump_opts, spec->name));
		} else {
			cmd_string("-s");
			cmd_string(spec->name);
		}
	}
	cmd_env("FLAG_TDFC");
	producer_options(PRODUCE_ID);
	cmd_filename(input);
	cmd_filename(output);

	/* Execute the command */
	enable_delayed_signal();
	output = execute(input, output);
	spec_produced = (allow_specs == 1) && (last_return != 2) &&
	    (checker || output != NULL);
	disable_delayed_signal();
	process_delayed_signal();
	if (spec_produced) {
		SET(spec);
		output = add_filename(output, spec);
	}
	if (allow_specs == 2) {
		spec = make_filename(input, C_SPEC, where(C_SPEC));
		cmd_env("TOUCH");
		cmd_filename(spec);
		cmd_string("-k");
		spec = execute(no_filename, spec);
		output = add_filename(output, spec);
	}
	return output;
}


/*
 * APPLY THE C PREPROCESSOR
 *
 * This routine applies the TDF C preprocessor to input and returns the result.
 * If files of type PREPROC_C are not being preserved then the output is sent
 * to the standard output.
 */

filename *
do_preproc(filename *input)
{
	filename *output;
	if (input == NULL) {
		return input;
	}
	if (checker && !use_system_cc) {
		return input;
	}
	if (table_keep(PREPROC_C)) {
		output = make_filename(input, PREPROC_C, where(PREPROC_C));
	} else {
		output = NULL;
	}
	cmd_env("TDFCPP");
	cmd_env("FLAG_TDFCPP");
	producer_options(PREPROC_ID);
	cmd_filename(input);
	if (output) {
		cmd_filename(output);
	}
	output = execute(input, output);
	return output;
}


/*
 * APPLY THE C++ PRODUCER
 *
 * This routine applies the C++ to TDF producer to input and returns the
 * result.
 */

filename *
do_cpp_produce(filename *input)
{
	filename *spec = NULL;
	filename *output, *producer_output;
	if (input == NULL) {
		return input;
	}
	output = make_filename(input, INDEP_TDF, where(INDEP_TDF));
	cmd_env("TCPPLUS");
	if (allow_specs == 1) {
		spec = make_filename(input, CPP_SPEC, where(CPP_SPEC));
		if (dump_opts) {
			cmd_string(xstrcat(dump_opts, spec->name));
		} else {
			cmd_string("-s");
			cmd_string(spec->name);
		}
	}
	cmd_env("FLAG_TCPPLUS");
	producer_options(CPP_PRODUCE_ID);
	cmd_filename(input);
	cmd_filename(output);
	producer_output = execute(input, output);

	/*
	 * If we are in checker mode and intermodular checks are enabled we
	 * must ignore any errors from the producer and continue to run the
	 * dump_linker.
	 */
	if (checker) {
		reset_exec_error();
	} else {
		output = producer_output;
	}
	if (allow_specs == 1) {
		SET(spec);
		output = add_filename(output, spec);
	}
	if (allow_specs == 2 && output) {
		spec = make_filename(input, CPP_SPEC, where(CPP_SPEC));
		cmd_env("TOUCH");
		cmd_filename(spec);
		cmd_string("-k");
		spec = execute(no_filename, spec);
		output = add_filename(output, spec);
	}
	return output;
}


/*
 * APPLY THE C++ PREPROCESSOR
 *
 * This routine applies the TDF C++ preprocessor to input and returns the
 * result. If files of type PREPROC_C are not being preserved then the output
 * is copied to the standard output.
 */

filename *
do_cpp_preproc(filename *input)
{
	filename *output;
	if (input == NULL) {
		return input;
	}
	if (checker && !use_system_cc) {
		return input;
	}
	if (table_keep(PREPROC_CPP)) {
		output = make_filename(input, PREPROC_CPP, where(PREPROC_CPP));
	} else {
		output = NULL;
	}
	cmd_env("TCPPLUSPP");
	cmd_env("FLAG_TCPPLUSPP");
	producer_options(CPP_PREPROC_ID);
	cmd_filename(input);
	if (output != NULL) {
		cmd_filename(output);
	}
	output = execute(input, output);
	return output;
}


/*
 * APPLY THE TDF LINKER
 *
 * This routine applies the TDF linker to input and returns the result. This
 * is the normal action of the TDF linker - linking target independent TDF with
 * the TDF libraries to form target dependent TDF (also see do_tdf_build).
 */

filename *
do_tdf_link(filename *input)
{
	filename *output;
	if (input == NULL || table_stop(INDEP_TDF)) {
		return input;
	}
	output = make_filename(input, DEP_TDF, where(DEP_TDF));
	cmd_env("TLD");
	cmd_env("FLAG_TLD");
	cmd_env("USR_LINK");
	cmd_env("LINK");
	cmd_env("USR_LIB");
	cmd_env("LIB");
	cmd_string("-o");
	cmd_filename(output);
	cmd_filename(input);
	if (tokdef_output) {
		cmd_string(tokdef_output);
	}
	return execute(input, output);
}


/*
 * APPLY THE TDF LINKER TO BUILD A COMPLEX
 *
 * This routine applies the TDF linker to combine a set of target independent
 * TDF capsules, input, into a single independent TDF capsule, which is then
 * returned. To avoid possible clashes with the input files, the output is
 * firstly directed to a temporary file, which is then moved to the output
 * file.
 */

filename *
do_tdf_build(filename *input)
{
	int keep;
	filename *output;
	if (input == NULL) {
		return input;
	}
	if (exec_error) {
		return NULL;
	}
	keep = where(INDEP_TDF_COMPLEX);
	output = uniq_filename(name_j_file, INDEP_TDF, keep, input);
	cmd_env("TLD");
	cmd_env("FLAG_TLD");
	if (flag_merge_all) {
		cmd_string("-a");
		cmd_string("-k");
		cmd_string("tag");
		cmd_string("main");
	}
	cmd_string("-o");
	cmd_filename(uniq_tempfile);
	cmd_filename(input);
	return do_move(execute(input, uniq_tempfile), output);
}


/*
 * APPLY THE TRANSLATOR
 *
 * This routine applies the TDF translator to the input files, input, and
 * returns the result. This routine is complicated by the fact that most TDF
 * translators produce assembler source, but some bypass the assembler to
 * directly produce binary object files. The mips translator produces two
 * output files, a .G file and a .T file, so this is also a special case.
 */

filename *
do_translate(filename *input)
{
	enum filetype t;
	filename *output;
	if (input == NULL || table_stop(DEP_TDF)) {
		return input;
	}
	if (use_assembler) {
		t = AS_SOURCE;
		output = make_filename(input, t, where(t));
	} else {
		t = binary_obj_type;
		output = make_filename(input, t, where(t));
		output->type = BINARY_OBJ;
	}
	cmd_env("TRANS");
	if (flag_diag) {
		if (flag_diag == 2) {
			cmd_string("-J");
		} else {
			if (flag_optim) {
				cmd_string("-HO");
			} else {
				cmd_string("-HN");
			}
		}
	}
	if (flag_nepc) {
		cmd_string("-E");
	}
	cmd_env("FLAG_TRANS");

	if (use_binasm) {
		/* Deal with binasm */
		if (table_keep(AS_SOURCE)) {
			error(ERROR_WARNING,
			      "Disregading binasm to keep source");
			use_binasm = 0;
		}
		t = BINASM_G_FILE;
		output->aux = make_filename(input, t, where(t));
		t = BINASM_T_FILE;
		output->aux->aux = make_filename(input, t, where(t));
		cmd_string("-s");
		cmd_filename(input);
		cmd_filename(output->aux);
		cmd_filename(output->aux->aux);
	} else if (use_assembler) {
		/* Deal with normal assemblers */
		cmd_filename(input);
		cmd_filename(output);
	} else {
		/* Deal with non-assemblers */
		if (table_keep(AS_SOURCE)) {
			t = AS_SOURCE;
			output->aux = make_filename(input, t, where(t));
			cmd_string("-S");
			cmd_filename(input);
			cmd_filename(output);
			cmd_filename(output->aux);
		} else {
			cmd_filename(input);
			cmd_filename(output);
		}
	}
	return execute(input, output);
}


/*
 * APPLY THE ASSEMBLER
 *
 * This routine applies the assembler to the input files, input, and returns
 * the result. The routine is complicated because of the need to handle the .G
 * and .T files output by the mips translator.
 */

filename *
do_assemble(filename *input)
{
	filename *output;
	enum filetype t = binary_obj_type;
	if (input == NULL || table_stop(AS_SOURCE)) {
		return input;
	}
	output = make_filename(input, t, where(t));
	output->type = BINARY_OBJ;
	if (input->aux && input->aux->type == BINASM_G_FILE &&
	    input->aux->aux && input->aux->aux->type == BINASM_T_FILE) {
		/* Deal with binasm */
		cmd_env("AS1");
		cmd_env("FLAG_AS1");
		cmd_string("-o");
		cmd_filename(output);
		cmd_filename(input->aux);
		cmd_string("-t");
		cmd_filename(input->aux->aux);
	} else {
		/* Deal with normal assemblers */
		cmd_env("AS");
		cmd_env("FLAG_AS");
		cmd_string("-o");
		cmd_filename(output);
		cmd_filename(input);
	}
	return execute(input, output);
}


/*
 * DYNLINK SWITCH
 *
 * This remains 0 if normal linking is being done, and is set to 1 before the
 * first-stage dynamic-initialisation linking. After the first call to
 * 'linker_options', the value is increase so that it becomes two for the
 * second-stage link.
 */

static int dl_state = 0;


/*
 * PRINT LINK/DYNLINK OPTIONS
 *
 * The link and dynlink stages use the same command-line options with the
 * exception of crt0, crt1 and crtn files since the dynamic-initialisation
 * linking doesn't produce an executable. The variable 'use_dynlink' is either
 * 1, 2 or 3 depending on whether the CRT startup files are linked on the
 * first, second or both of the two dynlink stages.
 */

static void
linker_options(filename *input, filename *output)
{
	if (use_system_cc) {
		cmd_env("CC");
		if (flag_diag) {
			cmd_string("-g");
		}
		if (flag_strip) {
			cmd_string("-s");
		}
		cmd_env("FLAG_CC");
		cmd_string("-o");
		cmd_filename(output);
	} else {
		cmd_env("LD");
		if (dl_state == 1) {
			cmd_string("-r");
		} else {
			cmd_env("LINK_ENTRY");
		}
		if (flag_strip && (dl_state != 1)) {
			cmd_string("-s");
		}
		cmd_env("FLAG_LINK");
		cmd_string("-o");
		cmd_filename(output);
		if ((dl_state == 0) || (dl_state & use_dynlink)!= 0) {
			cmd_env("CRT0");
			cmd_env("CRT1");
		}
	}
	if (use_hp_linker) {
		filename *p;
		for (p = input; p != NULL; p = p->next) {
			const char *arg = p->name;
			if (strneq(arg, "-B", 2)) {
				cmd_string("-B");
				cmd_string(arg + 2);
			} else if (strneq(arg, "-L", 2)) {
				cmd_string("-L");
				cmd_string(arg + 2);
			} else if (strneq(arg, "-l", 2)) {
				/*
				 * Save up -l options for inclusion after any
				 * -L options.
				 */
				envvar_set(&envvars, "DL_LIBS", arg, HASH_APPEND, HASH_SYSENV);
			} else {
				cmd_string(arg);
			}
		}
	} else {
		filename *p;
		for (p = input; p != NULL; p = p->next) {
			const char *arg = p->name;
			if (strneq(arg, "-l", 2)) {
				/*
				 * Save up -l options for inclusion after any
				 * -L options.
				 */
				envvar_set(&envvars, "DL_LIBS", arg, HASH_APPEND, HASH_SYSENV);
			} else if (dl_state && (p->storage == INPUT_OPTION)) {
				/*
				 * Add input options to user link options for
				 * subsequent use.
				 */
				envvar_set(&envvars, "FLAG_LINK", arg, HASH_APPEND, HASH_SYSENV);
				cmd_string(arg);
			} else {
				cmd_string(arg);
			}
		}
	}
	if (!use_system_cc) {
		/* usr_link_libdirs forms part of input */
		cmd_env("SYS_LINK");
	}
	/* now include the -l options */
	/*
	 * This is set by linker_options to be the list of libraries passed to the
	 * linker. Needs to be passed twice in the case of DYNLINK with shared
	 * libaries.
	 */
	if (envvar_get(envvars, "DL_LIBS") != NULL) {
		cmd_env("DL_LIBS");
	}
	if (!use_system_cc) {
		/* usr_link_libs forms part of input */
		cmd_env("SYS_LIB");
		cmd_env("SYS_LIBC");
		if ((dl_state == 0) || (dl_state & use_dynlink)!= 0) {
			cmd_env("CRTP_N");
			cmd_env("CRTN");
		}
	}
	dl_state++;
}


/*
 * APPLY THE RS6000/SPARC DYNAMIC INITIALISATION PROGRAM
 *
 * This routine calls the program to create a .s file with the necessary
 * dynamic initialisation calls for AIX and SunOS, and adds the corresponding
 * .o to the file list.
 */

filename *
do_dynlink(filename *input)
{
	filename *linked_ofiles, *extra_sfile, *output = NULL;
	if (input == NULL || table_stop(BINARY_OBJ)) {
		return input;
	}
	if (checker && !use_system_cc) {
		return input;
	}
	if (!exec_error) {
		linked_ofiles = make_filename(no_filename, binary_obj_type,
					      TEMP_FILE);
		dl_state = 1;
		linker_options(input, linked_ofiles);
		IGNORE execute(input, output);
	}
	if (!exec_error) {
		output = make_filename(no_filename, AS_SOURCE, TEMP_FILE);
		cmd_env("DYN_LINK");
		cmd_env("FLAG_DYN_LINK");
		SET(linked_ofiles);
		cmd_filename(linked_ofiles);
		cmd_filename(output);
		extra_sfile = execute(linked_ofiles, output);
	}
	if (exec_error) {
		last_return = 1;
		return NULL;
	}
	SET(linked_ofiles);
	SET(extra_sfile);
	output = do_assemble(extra_sfile);
	if (use_dynlink == 3) {
		return add_filename(output, input);
	}
	return add_filename(output, linked_ofiles);
}


/*
 * APPLY THE SYSTEM LINKER
 *
 * This routine applies the system linker to the input files, input, and
 * returns the result. The output executable name is, by default,
 * EXECUTABLE_NAME. Things are slightly complicated by the fact that the HP
 * linkers insist on certain options being in two parts.
 */

filename *
do_link(filename *input)
{
	int keep;
	filename *output;
	if (input == NULL || table_stop(BINARY_OBJ)) {
		return input;
	}
	if (checker && !use_system_cc) {
		return input;
	}
	if (exec_error) {
		last_return = 1;
		return NULL;
	}
	keep = where(EXECUTABLE);
	output = uniq_filename(EXECUTABLE_NAME, EXECUTABLE, keep, no_filename);
	linker_options(input, output);
	return execute(input, output);
}


/*
 * APPLY THE TDF NOTATION COMPILER
 *
 * This routine applies the TDF notation compiler to the input files, input,
 * and returns the result.
 */

filename *
do_notation(filename *input)
{
	int keep;
	filename *output;
	if (input == NULL) {
		return input;
	}
	keep = where(INDEP_TDF);
	if (tokdef_name != NULL && strcmp(input->name, tokdef_name) == 0) {
		keep = TEMP_FILE;
	}
	output = make_filename(input, INDEP_TDF, keep);
	cmd_env("TNC");
	cmd_env("FLAG_TNC");
	cmd_env("USR_INCL");
	cmd_filename(input);
	cmd_filename(output);
	return execute(input, output);
}


/*
 * APPLY THE PL_TDF COMPILER
 *
 * This routine applies the PL_TDF compiler to the input files, input, and
 * returns the result.
 */

filename *
do_pl_tdf(filename *input)
{
	filename *output;
	if (input == NULL) {
		return input;
	}
	output = make_filename(input, INDEP_TDF, where(INDEP_TDF));
	cmd_env("PL_TDF");
	cmd_env("FLAG_PL_TDF");
	cmd_env("USR_PL_TDF_INCLDIRS");
	if (flag_diag) {
		cmd_string("-g");
	}
	cmd_filename(input);
	cmd_filename(output);
	return execute(input, output);
}


/*
 * APPLY THE TDF PRETTY PRINTER
 *
 * This routine applies the TDF pretty printer to the input files, input, and
 * returns the result.
 */

filename *
do_pretty(filename *input)
{
	filename *output;
	if (input == NULL || table_stop(DEP_TDF)) {
		return input;
	}
	output = make_filename(input, PRETTY_TDF, where(PRETTY_TDF));
	cmd_env("DISP");
	if (flag_diag) {
		cmd_string("-g");
	}
	cmd_env("FLAG_DISP");
	cmd_filename(input);
	cmd_filename(output);
	return execute(input, output);
}


/*
 * SPLIT A TDF ARCHIVE
 *
 * This routine splits the TDF archive, input, and returns the result.
 */

filename *
do_split_arch(filename *input)
{
	if (input == NULL) {
		return input;
	}
	cmd_env("SPLIT_ARCH");
	cmd_filename(input);
	return execute(input, no_filename);
}


/*
 * BUILD A TDF ARCHIVE
 *
 * This routine creates a TDF archive from the input files, input, and the
 * archive options, opt_archive, and returns the result. The output archive
 * name is, by default, TDF_ARCHIVE_NAME. The aux field of the output contains
 * the archive contents.
 */

filename *
do_build_arch(filename *input)
{
	int keep;
	filename *output;
	if (input == NULL || table_stop(INDEP_TDF)) {
		return input;
	}
	if (exec_error) {
		return NULL;
	}
	archive_type = TDF_ARCHIVE;
	keep = where(TDF_ARCHIVE);
	output = uniq_filename(TDF_ARCHIVE_NAME, TDF_ARCHIVE, keep,
			       no_filename);
	cmd_env("BUILD_ARCH");
	cmd_filename(output);
	cmd_filename(input);
	if (envvar_get(envvars, "FLAG_ARCHIVE")) {
		cmd_string(ARCHIVE_OPTION_START);
		cmd_env("FLAG_ARCHIVE");
	}
	output = execute(input, output);
	if (output) {
		output->aux = input;
	}
	return output;
}


/*
 * BUILD AN ARCHIVE FILE
 *
 * This routine creates an archive file of type t from the input files and
 * returns the result. The aux field of the output contains the archive
 * contents.
 */

filename *
do_build_file(filename *input, enum filetype t)
{
	enum filetype s;
	filename *output;
	if (input == NULL) {
		return input;
	}
	if (!(table_keep(t) || filetype_table[t].keep_aux == FTK_TC)) {	/* TODO not also FTK_TN? */
		return input;
	}
	archive_type = t;
	s = input->type;
	input->type = UNKNOWN_TYPE;
	output = make_filename(input, t, where(t));
	input->type = s;
	cmd_env("BUILD_ARCH");
	cmd_filename(output);
	cmd_filename(input);
	if (allow_specs == 2) {
		cmd_string(ARCHIVE_OPTION_START);
		cmd_string("--2CS");
	}
	output = execute(input, output);
	if (output) {
		output->aux = input;
	}
	return output;
}


/*
 * LINK A NUMBER OF C AND C++ SPECS
 *
 * This routine links a number of C++ specs, input, into one, which is then
 * returned. To avoid possible clashes with the input files, the output is
 * firstly directed to a temporary file, which is then moved to the output
 * file. The variable t is the dummy file type, C_SPEC_1, C_SPEC_2, CPP_SPEC_1
 * or CPP_SPEC_2.
 */

filename *
do_link_specs(filename *input, enum filetype t)
{
	int keep;
	filename *output, *spec_file;
	if (input == NULL) {
		return input;
	}
	if (t == C_SPEC_2 || t == CPP_SPEC_2) {
		/* Don't link in these cases */
		if (table_stop(BINARY_OBJ)) {
			return input;
		}
	}
	if (exec_error && !checker) {
		last_return = 1;
		return NULL;
	}
	keep = where(t);
	if (allow_specs == 1 && dump_opts == NULL) {
		output = make_filename(no_filename, INDEP_TDF, TEMP_FILE);
		if (t == C_SPEC_1 || t == C_SPEC_2) {
			spec_file = uniq_filename(name_k_file, C_SPEC, keep,
						  input);
			cmd_env("SPEC_LINK");
			cmd_env("FLAG_SPEC_LINK");
		} else {
			spec_file = uniq_filename(name_K_file, CPP_SPEC, keep,
						  input);
			cmd_env("CPP_SPEC_LINK");
			cmd_env("FLAG_CPP_SPEC_LINK");
		}
		if (checker) {
			cmd_string("-c");
		}
		if (make_pretty) {
			cmd_string("-t");
		}
		cmd_string("-s");
		cmd_string(uniq_tempfile->name);
		cmd_filename(input);
		cmd_filename(output);
		output = execute(input, output);
		if (checker) {
			output = NULL;
		}
		output = add_filename(output, do_move(uniq_tempfile,
						      spec_file));
	} else {
		if (t == C_SPEC_1 || t == C_SPEC_2) {
			output = uniq_filename(name_k_file, C_SPEC, keep,
					       input);
		} else {
			output = uniq_filename(name_K_file, CPP_SPEC, keep,
					       input);
		}
		if (allow_specs == 1) {
			cmd_env("DUMP_LINK");
			cmd_env("FLAG_DUMP_LINK");
			cmd_filename(input);
			cmd_filename(output);
			output = execute(input, output);
		} else {
			cmd_env("TOUCH");
			cmd_filename(uniq_tempfile);
			cmd_string("-k");
			output = execute(no_filename, output);
		}
	}
	return output;
}


/*
 * USE THE SYSTEM COMPILER
 *
 * tcc may optionally be used do invoke the system compiler, cc. This routine
 * applies cc to the input files, input, compiling as far as files of type t,
 * and returning the output files.
 */

filename *
do_cc(filename *input, enum filetype t)
{
	char *flag;
	filename *output;
	if (input == NULL) {
		return input;
	}
	output = make_filename(input, t, where(t));
	if (t == PREPROC_C) {
		if (table_keep(t)) {
			flag = "-P";
		} else {
			flag = "-E";
			output = NULL;
		}
	} else if (t == AS_SOURCE) {
		flag = "-S";
	} else {
		flag = "-c";
		output->type = BINARY_OBJ;
	}
	cmd_env("CC");
	cmd_string(flag);
	if (flag_diag) {
		cmd_string("-g");
	}
	cmd_env("FLAG_CC");
	if (use_sparc_cc == 2 && output) {
		filename *real_output;
		real_output = make_filename(input, output->type,
					    PRESERVED_FILE);
		real_output->name = find_basename(real_output->name);
		cmd_filename(input);
		real_output = execute(input, real_output);
		return do_move(real_output, output);
	} else {
		if (output) {
			cmd_string("-o");
			cmd_filename(output);
		}
		cmd_filename(input);
		return execute(input, output);
	}
}
