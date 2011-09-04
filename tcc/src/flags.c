/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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

#include <shared/error.h>

#include "config.h"
#include "filename.h"
#include "list.h"
#include "archive.h"
#include "environ.h"
#include "flags.h"
#include "startup.h"
#include "suffix.h"
#include "utility.h"
#include "table.h"


/*
 * STRING VARIABLES
 *
 * These variables given various compilation values, including the location of
 * the main temporary directory.
 */

const char *api_info = "unknown";
const char *api_output = API_ANAL_NAME;
const char *dump_opts = NULL;
const char *environ_dir = ".";
const char *final_name = NULL;
const char *machine_name = "unknown";
const char *name_E_file = ENDUP_NAME;
const char *name_h_file = STARTUP_NAME;
const char *name_j_file = TDF_COMPLEX_NAME;
const char *name_k_file = C_SPEC_COMPLEX_NAME;
const char *name_K_file = CPP_SPEC_COMPLEX_NAME;
const char *name_p_file = TOKDEF_NAME;
const char *temporary_dir = "/tmp";	/* TODO: use PREFIX_TMP instead */
const char *tokdef_output = NULL;
const char *version_flag = "";
const char *dev_null = NULL;


/*
 * INTERNAL OPTIONS
 *
 * These variables control the overall behaviour of tcc. For example, should
 * we be running in verbose mode?
 */

boolean api_checks = 0;
boolean checker = 0;
boolean dry_run = 0;
boolean env_dump = 0;
boolean link_specs = 1;
boolean make_up_names = 0;
boolean show_api = 0;
boolean show_errors = 0;
boolean suffix_overrides = 0;
boolean taciturn = 0;
boolean tidy_up = 0;
boolean time_commands = 0;
boolean tool_chain = 0;
boolean tool_chain_environ = 0;
boolean verbose = 0;
boolean warnings = 1;
/* Should the cmd line args be rank sorted, or taken as is? */
boolean no_shuffle = 0;


/*
 * COMPILATION CONTROL OPTIONS
 *
 * These variables control the main compilation path taken. For example, should
 * we form a TDF archive?
 */


boolean make_archive = 0;
boolean make_complex = 0;
boolean make_preproc = 0;
boolean make_pretty = 0;
boolean make_tspec = 0;
boolean use_assembler = 1;
boolean use_mips_assembler = 0;
boolean use_alpha_assembler = 0;
boolean use_hp_linker = 0;
boolean use_dynlink = 0;
boolean use_sparc_cc = 0;
boolean use_system_cc = 0;
boolean allow_cpp = 0;
boolean allow_notation = 0;
boolean allow_pl_tdf = 0;
boolean allow_specs = 0;


static enum filetype_keep keep_all = FTK_FC;

/*
 * The special variable, keep_ofiles, indicates whether all
 * binary object files should be kept when more than one input file is given
 * (this is for cc compatibility).
 */
static boolean keep_ofiles = 1;


/*
 * INDIVIDUAL OPTIONS
 *
 * These flags control those individual executable options which are not easily
 * integrated into the main scheme of things.
 */

boolean flag_diag = 0;
boolean flag_keep_err = 0;
boolean flag_incl = 0;
boolean flag_merge_all = 0;
boolean flag_nepc = 0;
boolean flag_no_files = 0;
boolean flag_optim = 0;
boolean flag_prof = 0;
boolean flag_startup = 1;
boolean flag_strip = 0;


/*
 * EXECUTABLES
 *
 * These variables give the values of the various executables comprising the
 * system. For example, exec_produce gives the location of the C to TDF
 * producer.
 */

list *exec_produce = NULL;
list *exec_preproc = NULL;
list *exec_cpp_produce = NULL;
list *exec_cpp_preproc = NULL;
list *exec_tdf_link = NULL;
list *exec_translate = NULL;
list *exec_assemble = NULL;
list *exec_assemble_mips = NULL;
list *exec_link = NULL;
list *exec_notation = NULL;
list *exec_pl_tdf = NULL;
list *exec_pretty = NULL;
list *exec_spec_link = NULL;
list *exec_cpp_spec_link = NULL;
list *exec_split_arch = NULL;
list *exec_build_arch = NULL;
list *exec_cat = NULL;
list *exec_cc = NULL;
list *exec_mkdir = NULL;
list *exec_move = NULL;
list *exec_remove = NULL;
list *exec_touch = NULL;
list *exec_dynlink = NULL;
list *exec_dump_anal = NULL;
list *exec_dump_link = NULL;


/*
 * BUILT-IN OPTIONS
 *
 * These lists of options are built into the system, although they may be
 * altered by environments and command-line options.
 */

list *std_prod_incldirs = NULL;
list *std_prod_portfile = NULL;
list *std_prod_startdirs = NULL;
list *std_prod_startup = NULL;
list *std_cpp_prod_incldirs = NULL;
list *std_cpp_prod_startdirs = NULL;
list *std_cpp_prod_startup = NULL;
list *std_tdf_link_libdirs = NULL;
list *std_tdf_link_libs = NULL;
list *std_link_crt0 = NULL;
list *std_link_crt1 = NULL;
list *std_link_crtp_n = NULL;
list *std_link_crtn = NULL;
list *std_link_libdirs = NULL;
list *std_link_libs = NULL;
list *std_link_c_libs = NULL;
list *std_link_entry = NULL;



/*
 * COMMAND-LINE OPTIONS
 *
 * These lists of options are those specified on the command-line.
 */

list *usr_prod_incldirs = NULL;
list *usr_prod_foptions = NULL;
list *usr_prod_eoptions = NULL;
list *usr_prod_startup = NULL;
list *usr_cpp_prod_startup = NULL;
list *usr_pl_tdf_incldirs = NULL;
list *usr_tdf_link_libdirs = NULL;
list *usr_tdf_link_libs = NULL;
list *usr_link_libdirs = NULL;
list *usr_link_libs = NULL;


/*
 * EXECUTABLE OPTIONS
 *
 * These lists record the command-line options which are passed directly to the
 * various executables.
 */

list *opt_produce = NULL;
list *opt_preproc = NULL;
list *opt_cpp_produce = NULL;
list *opt_cpp_preproc = NULL;
list *opt_tdf_link = NULL;
list *opt_translate = NULL;
list *opt_assemble = NULL;
list *opt_assemble_mips = NULL;
list *opt_dynlink = NULL;
list *opt_link = NULL;
list *opt_notation = NULL;
list *opt_pl_tdf = NULL;
list *opt_pretty = NULL;
list *opt_spec_link = NULL;
list *opt_cpp_spec_link = NULL;
list *opt_dump_anal = NULL;
list *opt_dump_link = NULL;
list *opt_archive = NULL;
list *opt_joiner = NULL;
list *opt_cc = NULL;
list *opt_startup = NULL;
list *opt_unknown = NULL;


/*
 * SET A KEEP OR STOP OPTION
 *
 * This routine sets a value in the keeps or stops arrays. The variable t gives
 * the file type (including ALL_TYPES) and k gives the storage command (see
 * flags.h).
 */

void
set_stage(enum filetype t, int k)
{
	if (t == ALL_TYPES) {
		boolean ks = table_keep(STARTUP_FILE);
		if (k == STOP_STAGE || k == STOP_ONLY_STAGE) {
			error(ERROR_WARNING, "Illegal stop option");
		} else if (k == KEEP_STAGE) {
			enum filetype i;
			/* TODO rework this */
			for (i = 0; i < array_size(filetype_table); i++) {
				if (table_keep(i) == FTK_FC) {
					filetype_table[i].keep = FTK_TC;
				}
			}
			keep_all = FTK_TC;
		} else if (k == DONT_KEEP_STAGE) {
			enum filetype i;
			for (i = 0; i < array_size(filetype_table); i++) {
				if (table_keep(i) == FTK_TC) {
					filetype_table[i].keep = FTK_FC;
				}
			}
			keep_all = FTK_FC;
			keep_ofiles = 0;
		}
		filetype_table[STARTUP_FILE].keep = ks;
	} else {
		if (k == STOP_STAGE || k == STOP_ONLY_STAGE) {
			static enum filetype last_stop = UNKNOWN_TYPE;
			if (table_stop(t) == 0) {
				filetype_table[t].stop = 1;
			}
			if (k == STOP_STAGE && table_keep(t) == FTK_FC) {
				filetype_table[t].keep = FTK_TC;
			}
			switch (last_stop) {
			case UNKNOWN_TYPE:
				break;
			case INDEP_TDF:
			case C_SPEC:
			case CPP_SPEC:
				if (t == C_SPEC || t == CPP_SPEC) {
					break;
				}
				if (t == INDEP_TDF) {
					break;
				}
				goto default_lab;
			case PREPROC_C:
			case PREPROC_CPP:
				if (t == PREPROC_CPP) {
					break;
				}
				goto default_lab;
			default:
default_lab:
				if (t != last_stop) {
					error(ERROR_WARNING, "More than one stop option given");
				}
				break;
			}
			last_stop = t;
		} else if (k == KEEP_STAGE) {
			if (table_keep(t) == FTK_FC) {
				filetype_table[t].keep = FTK_TC;
			}
			filetype_table[t].keep_aux = FTK_TC;
			if (t == BINARY_OBJ) {
				keep_ofiles = 1;
			}
		} else if (k == DONT_KEEP_STAGE) {
			if (table_keep(t) == FTK_TC) {
				filetype_table[t].keep = FTK_TC;
			}
			filetype_table[t].keep_aux = FTK_TC;
			if (t == BINARY_OBJ) {
				keep_ofiles = 0;
			}
		}
	}
}


/*
 * SET THE MACHINE NAME
 *
 * This routine sets any special flags required by the machine indicated by
 * machine_name.
 */

void
set_machine(void)
{
#if 0
	char *mach = machine_name;
	use_assembler = 1;
	use_mips_assembler = 0;
	use_alpha_assembler = 0;
	use_hp_linker = 0;
	if (streq(mach, "hp") || streq(mach, "hppa")) {
		use_hp_linker = 1;
	} else if (streq(mach, "mips")) {
		use_mips_assembler = 1;
	} else if (streq(mach, "alpha")) {
		use_alpha_assembler = 1;
	} else if (streq(mach, "sparc") || streq(mach, "svr4_sparc")) {
		use_sparc_cc = 1;
	} else if (streq(mach, "svr4_i386")) {
		use_sparc_cc = 2;
	} else if (streq(mach, "transputer")) {
		use_assembler = 0;
	}
#endif
}


/*
 * INITIALISE ALL OPTIONS
 *
 * This routine initialises any necessary values before the command-line
 * options are read.
 */

void
initialise_options(void)
{
	exec_produce = make_list("builtin/undef C_producer");
	exec_preproc = make_list("builtin/undef C_preprocessor");
	exec_cpp_produce = make_list("builtin/undef C++_producer");
	exec_cpp_preproc = make_list("builtin/undef C++_preprocessor");
	exec_tdf_link = make_list("builtin/undef TDF_linker");
	exec_translate = make_list("builtin/undef TDF_translator");
	exec_assemble = make_list("builtin/undef system_assembler");
	exec_assemble_mips = make_list("builtin/undef mips_assembler");
	exec_link = make_list("builtin/undef system_linker");
	exec_notation = make_list("builtin/undef TDF_notation_compiler");
	exec_pl_tdf = make_list("builtin/undef PL_TDF_compiler");
	exec_pretty = make_list("builtin/undef TDF_pretty_printer");
	exec_spec_link = make_list("builtin/undef C_spec_linker");
	exec_cpp_spec_link = make_list("builtin/undef C++_spec_linker");
	exec_split_arch = make_list("builtin/split_archive");
	exec_build_arch = make_list("builtin/build_archive");
	exec_cat = make_list("builtin/cat");
	exec_cc = make_list("builtin/undef system_compiler");
	exec_mkdir = make_list("builtin/mkdir");
	exec_move = make_list("builtin/move");
	exec_remove = make_list("builtin/remove");
	exec_touch = make_list("builtin/touch");
	exec_dynlink = make_list("builtin/undef dynamic_initialiser");

	/* Initialise other options */
	find_envpath();
	if (checker) {
		allow_specs = 1;
	}
}


/*
 * UPDATE ALL OPTIONS
 *
 * This routine updates the values of the variables above after all the
 * command-line options have been read. The stops options need to be kept in
 * step with the general compilation scheme given in compile.c. Deciding which
 * versions of certain file types to preserve (INDEP_TDF and C_SPEC in
 * particular) gets pretty messy.
 */

void
update_options(void)
{
	char *mode = NULL;
	static boolean done_diag = 0;
	static boolean done_preproc = 0;
	static boolean done_prof = 0;
	static boolean done_time = 0;

	/* Process archive options */
	process_archive_opt();

	/* Deal with cc mode */
	if (checker) {
		mode = "checker";
	}
	if (use_system_cc) {
		if (!checker) {
			error(ERROR_WARNING, "Using the system C compiler");
		}
		mode = "system compiler";
	}
	/* TODO there must be a nicer way to express this */
	if (mode) {
		if (make_archive) {
			error(ERROR_WARNING, "Can't build TDF archive in %s mode",
			      mode);
			filetype_table[INDEP_TDF].stop = FTK_TC;
			make_archive = 0;
		}
		if (make_complex) {
			error(ERROR_WARNING, "Can't build TDF complex in %s mode",
			      mode);
			make_complex = 0;
		}
		if (make_pretty) {
			error(ERROR_WARNING, "Can't pretty print TDF in %s mode",
			      mode);
			filetype_table[INDEP_TDF].stop = FTK_TC;
			make_pretty = 0;
		}
		allow_notation = 0;
		allow_pl_tdf = 0;
	}

	/* Register extra stops */
	if (make_archive) {
		set_stage(TDF_ARCHIVE, STOP_STAGE);
	}
	if (make_preproc) {
		set_stage(PREPROC_C, STOP_ONLY_STAGE);
		set_stage(PREPROC_CPP, STOP_ONLY_STAGE);
	}
	if (make_pretty) {
		set_stage(PRETTY_TDF, STOP_STAGE);
	}

	/* Read special environments etc. */
	if (make_preproc && table_keep(PREPROC_C) && !done_preproc) {
		read_env(PREPROC_ENV);
		done_preproc = 1;
	}
	if (flag_diag && !done_diag) {
		read_env(DIAG_ENV);
		done_diag = 1;
	}
	if (flag_prof && !done_prof) {
		read_env(PROF_ENV);
		done_prof = 1;
	}
	if (time_commands && !done_time) {
		read_env(TIME_ENV);
		done_time = 1;
	}

	/* Print API information */
	if (show_api) {
		printf("API is %s", api_info);
		show_api = 0;
	}

#if 0
	/* The option -Fk means stop after producer */
	if (table_stop(C_SPEC) || table_stop(CPP_SPEC) ||
	    table_stop(PREPROC_C) || table_stop(PREPROC_CPP)) {
		filetype_table[INDEP_TDF].stop = FTK_TC;
	}
#endif

	/* Propagate stop options down */
	/* TODO perhaps if our table contains a notion of "previous" types, we can automate this */
	if (table_stop(INDEP_TDF)) {
		filetype_table[INDEP_TDF_COMPLEX].stop = FTK_TC;
		filetype_table[DEP_TDF].stop = FTK_TC;
		filetype_table[AS_SOURCE].stop = FTK_TC;
		filetype_table[BINARY_OBJ].stop = FTK_TC;
	} else if (table_stop(DEP_TDF)) {
		filetype_table[AS_SOURCE].stop = FTK_TC;
		filetype_table[BINARY_OBJ].stop = FTK_TC;
	} else if (table_stop(AS_SOURCE)) {
		filetype_table[BINARY_OBJ].stop = FTK_TC;
	} else if (table_stop(MIPS_G_FILE)) {
		filetype_table[BINARY_OBJ].stop = FTK_TC;
	} else if (table_stop(MIPS_T_FILE)) {
		filetype_table[BINARY_OBJ].stop = FTK_TC;
	}

	/* Check keep options */
	if (make_complex) {
		if (table_keep(INDEP_TDF)) {
			filetype_table[INDEP_TDF].keep = keep_all;
			filetype_table[INDEP_TDF_COMPLEX].keep = FTK_TC;
		}
		if (table_stop(INDEP_TDF)) {
			filetype_table[C_SPEC_1].keep = FTK_TC;
			filetype_table[CPP_SPEC_1].keep = FTK_TC;
		}
	}
	if (table_keep(C_SPEC)) {
		if (make_complex) {
			filetype_table[C_SPEC].keep = keep_all;
			filetype_table[C_SPEC_1].keep = FTK_TC;
		}
	} else {
		if (filetype_table[C_SPEC].keep_aux == FTK_TN) {
			filetype_table[C_SPEC_1].keep = FTK_FC;
			filetype_table[C_SPEC_2].keep = FTK_FC;
		}
	}
	if (table_keep(CPP_SPEC)) {
		if (make_complex) {
			filetype_table[CPP_SPEC].keep = keep_all;
			filetype_table[CPP_SPEC_1].keep = FTK_TC;
		}
	} else if (filetype_table[CPP_SPEC].keep_aux == FTK_TN) {
		filetype_table[CPP_SPEC_1].keep = FTK_FC;
		filetype_table[CPP_SPEC_2].keep = FTK_FC;
	}
	if (keep_ofiles && no_input_files > 1 && !make_complex) {
		filetype_table[BINARY_OBJ].keep = FTK_TC;
	}
	if (filetype_table[BINARY_OBJ].keep_aux == FTK_TC) {
		filetype_table[BINARY_OBJ_AUX].keep = FTK_TC;
	}
	if (link_specs) {
		enum filetype_keep b;
		if (checker && !use_system_cc) {
			if (filetype_table[BINARY_OBJ].keep_aux) {
				b = FTK_TC;
			} else if (table_stop(BINARY_OBJ) && !table_stop(AS_SOURCE)) {
				b = filetype_table[BINARY_OBJ].keep;
			} else {
				b = FTK_TN;
			}
		} else {
			b = table_keep(BINARY_OBJ);
		}
		if (b) {
			if (make_complex) {
				filetype_table[C_SPEC_1].keep = FTK_TC;
				filetype_table[CPP_SPEC_1].keep = FTK_TC;
			} else {
				filetype_table[C_SPEC].keep = FTK_TC;
				filetype_table[CPP_SPEC].keep = FTK_TC;
			}
			filetype_table[BINARY_OBJ_AUX].keep = FTK_TC;
		}
	}

	/* Set checker options */
	if (checker) {
		if (allow_specs == 0) {
			allow_specs = 1;
		}
		if (!use_system_cc) {
			filetype_table[C_SPEC_2].stop = FTK_TC;
			filetype_table[CPP_SPEC_2].stop = FTK_TC;
		}
	}

	/* A couple of housekeeping routines */
	close_startup();
	find_envpath();
}

