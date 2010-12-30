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


#include <sys/types.h>
#include <sys/stat.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "filename.h"
#include "list.h"
#include "archive.h"
#include "environ.h"
#include "flags.h"
#include "main.h"
#include "options.h"
#include "startup.h"
#include "suffix.h"
#include "utility.h"
#include "path_subs.h"
#include "table.h"


/*
 * TYPE REPRESENTING AN OPTION ACTION
 *
 * The output commands of an optmap are stored as an args_out, which is a
 * simple array of strings.
 */

#define max_var 100

typedef struct {
	int argc;
	char *argv[max_var];
} args_out;


/*
 * THE LIST OF ALL INPUT FILES
 *
 * All input files found by process_options are added to this list.
 */
filename *input_files = NULL;


/*
 * THE MAIN OPTION MAP
 *
 * This table gives all the command-line options. The first entry is the 'match
 * in' and roughly corresponds to command line input. The second entry is the
 * 'match out' and provides instructions to the command line interpreter. The
 * third entry is a description. The the final entry is a relative ranking,
 * with lower numbers being higher priority. Thus, no matter what order the
 * command line options are given, the lower ranked option will always be
 * evaluated first. (Option rankings can be disabled with the -no_shuffle
 * option.)
 */
optmap main_optmap[] = {
	/* Common options */
	{ "^-$",         "I?$0",              "specifies an input file",                     1000 },
	{ "-o+$",        "SFN$1",             "specifies output file name",                   100 },
	{ "-D+$=$",      "D#define$s$1$s$2$n"
	                 "|AOC$0",            "defines a macro",                              101 },
	{ "-D+$",        "D#define$s$1$s1$n"
	                 "|AOC$0",            "defines a macro to be 1",                      102 },
	{ "-F?",         "H$1",               "halts the compilation at the given stage",     103 },
	{ "-I+$",        "AUI$0|AOC$0|AUP$0", "specifies an include file directory",          104 },
	{ "-L+$",        "1ON|Io$0|AUL$0",    "specifies a system library directory",         105 },
	{ "-N+$:+$",     "AUI$0|AOC-I$2",     "specifies an include file directory "
	                                       "(with mode)",                                 106 },
	{ "-O$",         "1OP|AOC$0",         "switches optimisation level",                  107 },
	{ "-P?*",        "K$1",               "causes intermediate files to be preserved",    108 },
	{ "-S",          "Hs",                "halts compilation after creating .s files",    109 },
	{ "-T+$",        "CAT:$1|AOC-D$1",    "specifies a command-line token",               110 },
	{ "-U+$",        "D#undef$s$1$n"
	                 "|AOC$0",            "undefines a macro",                            111 },
	{ "-W?,+$,+*",   "AQ$1$2",            "passed an option to a compilation tool",       112 },
	{ "-W?:+$",      "AQ$1$2",            "passed an option to a compilation tool",       113 },
	{ "-X:+$,+*",    "CAP:$1",            "specifies a compilation option",               114 },
	{ "-X$",         "EX$1",              "specifies a compilation mode",                 115 },
	{ "-Y+$",        "E$1",               "reads an environment",                          12 },
	{ "-c",          "Ho",                "halts compilation after creating .o files",    118 },
	{ "-d",          "Hd",                "halts compilation after creating .d files",    119 },
	{ "-dry",        "1VB|1DR",           "causes a dry run",                             120 },
	{ "-e+$",        "AUe$0",             "specifies a producer end-up file",             121 },
	{ "-f+$",        "AUf$0",             "specifies a producer start-up file",           122 },
	{ "-g",          "1DG",               "produces debugging information "
	                                       "(default format)",                            123 },
	{ "-g1",         "1DG",               "produces debugging information "
	                                       "(old format)",                                124 },
	{ "-g2",         "2DG",               "produces debugging information "
	                                       "(new format)",                                125 },
	{ "-g3",         "3DG",               "produces debugging information "
	                                       "(new format)",                                126 },
	{ "-k",          "Hk|HK",             "halts compilation after creating "
	                                       ".k and .K files",                             128 },
	{ "-l+$",        "1ON|Io$0|AUl$0",    "specifies a system library",                   129 },
	{ "-not_ansi",   "ASs-fnot_ansi",     "allows some non-ANSI C features",              130 },
	{ "-nepc",       "1NE|ASs-fnepc",     "switches off extra portability checks",        131 },
	{ "-sym",        "1CS|SDO-d=",        "enables symbol table dump linking",            132 },
	{ "-sym:$",      "1CS|SDO-d$1=",      "enables symbol table dump linking with flags", 133 },
	{ "-v",          "1VB",               "specifies verbose mode",                        50 },
	{ "-vb",         "1TC",               "specifies fairly verbose mode",                 51 },
	{ "-vd",         "1TD",               "dump the env information tcc got hold of",      51 },
	{ "-ve",         "1TE",               "verbose information about "
	                                       "tool chain environment",                       51 },
	{ "-vt",         "1TT",               "verbose information about "
	                                       "tool chain invocation",                        51 },
	{ "-no_shuffle", "1ES",               "turns off shuffle ranking of cmd line args",    -1 },
	{ "-y+$=$",      "E?$1?$2",           "sets an env directory variable",                 1 },

	/* Options not allowed in checker */
	{ "-J+$",           "AUJ-L$1",          "specifies a TDF library directory",           20 },
	{ "-M",             "1MC",              "causes all .j files to be merged",           133 },
	{ "-MA",            "1MC|1MP",          "as -M, but with hiding",                     134 },
	{ "-ch",            "1CH",              "invokes checker mode",                       135 },
	{ "-disp",          "1PP",              "causes all .j files to be pretty printed",   136 },
	{ "-disp_t",        "2PP",              "causes all .t files to be pretty printed",   137 },
	{ "-i",             "Hj",               "halts compilation after creating .j files",  139 },
	{ "-im",            "1CS",              "enables intermodular checks",                139 },
	{ "-j+$",           "AUj-l$1",          "specifies a TDF library",                     30 },
	{ "-prod",          "1AR",              "causes a TDF archive to be produced",        141 },

	/* Less common options */
	{ "-A+-",           "AOC$0",            "unasserts all built-in predicates",          142 },
	{ "-A+$",           "D#pragma$saccept$sdirective$sassert$n"
	                    "|D#assert$s$1$n|AOC$0", "asserts a predicate",                   143 },
	{ "-B+$",           "1ON|Io$0",         "passed to the system linker",                144 },
	{ "-C",             "AOC$0",            "preserves comments when preprocessing",       30 },
	{ "-E",             "1PR",              "causes C source files to be preprocessed",   145 },
	{ "-E?:+$",         "LE$1$2",           "specifies an executable to be used",         146 },
	{ "-H",             "1PI",              "causes included files to be printed",        147 },
	{ "-S?,+$,+*",      "I$1$2",            "specifies input files",                       15 },
	{ "-S?:+$",         "I$1$2",            "specifies input files",                       15 },
	{ "-V",             "EVersions|1CR",    "causes all tools to print their "
	                                         "version numbers",                            21 },
	{ "-cc",            "1CC",              "forces the system compiler to be used",       23 },
	{ "-cc_only",       "2CC",              "forces only the system compiler to be used",  22 },
	{ "-do?+$",         "SN$1$2",           "sets a default output file name",            148 },
	{ "-dump",          "CDS",              "dumps the current status",                   200 },
	{ "-ignore_case",   "1LC",              "ignores case in file names",                  12 },
	{ "-im0",           "2CS",              "disables intermodular checks",               148 },
	{ "-info",          "1SA",              "causes API information to be printed",       201 },
	{ "-keep_errors",   "1KE",              "causes files to be preserved on errors",      13 },
	{ "-make_up_names", "1MN",              "makes up names for intermediate files",      149 },
	{ "-message+$",     "@X$1",             "causes %s to print a message",                24 },
	{ "-p",             "1PF",              "causes profiling information to be produced", 31 },
	{ "-q",             "0VB",              "specifies quiet mode",                         1 },
	{ "-quiet",         "0VB",              "equivalent to -q",                             1 },
	{ "-query",         "Q",                "causes a list of options to be printed",       2 },
	{ "-s?:+$",         "SS$1$2|1SO",       "specifies a suffix override",                 25 },
	{ "-show_errors",   "1SE",              "causes error producing commands to be shown",  3 },
	{ "-show_env",      "CSE",              "causes the environment path to be printed",  202 },
	{ "-special+$",     "SXX$1|CSP",        "allows various internal options",              4 },
	{ "-startup+$",     "@D$1$n",           "specifies a start-up option",                  5 },
	{ "-target+$",      "AOC-target|AOC$1", "provided for cc compatibility",              150 },
	{ "-temp+$",        "STD$1",            "specifies the temporary directory",            1 },
	{ "-tidy",          "1TU",              "causes %s to tidy up as it goes along",      152 },
	{ "-time",          "1TI|1VB",          "causes all commands to be timed",            153 },
	{ "-verbose",       "1VB",              "equivalent to -v",                             1 },
	{ "-version",       "CPV",              "causes %s to print its version number",        1 },
	{ "-w",             "0WA",              "suppresses %s warnings",                       1 },
	{ "-work+$",        "SWD$1",            "specifies the work directory",                 1 },

	/* Options not allowed in checker */
	{ "-G",             "EGoption",         "provided for cc compatibility",      154 },
	{ "-K+$,+*",        "EK-$1",            "provided for cc compatibility",      155 },
	{ "-Z$",            "EZ-$1",            "provided for cc compatibility",      156 },
	{ "-b",             "LSc",              "suppresses -lc in system linking",   157 },
	{ "-dn",            "AOl$0",            "passed to the system linker",        158 },
	{ "-dy",            "AOl$0",            "passed to the system linker",        159 },
	{ "-h+$",           "AOl$0",            "passed to the system linker",        160 },
	{ "-no_startup_options", "0ST",         "suppresses start-up options",        161 },
	{ "-s",             "1SR",              "passed to the system linker",        162 },
	{ "-u+$",           "AOl$0",            "passed to the system linker",        163 },
	{ "-wsl",           "Ewsl",             "causes string literals to "
	                                         "be made writable",                  164 },
	{ "-z+$",           "AOl$0",            "passed to the system linker",        165 },
	{ "-#",             "1VB",              "equivalent to -v",                     1 },
	{ "-##",            "1VB",              "equivalent to -v",                     1 },
	{ "-###",           "1VB|1DR",          "equivalent to -dry",                   1 },

	/* Default options */
	{ "--+$,+*", "$1", "communicates directly with the option interpreter", 0 },
	{ "$",       "XUnknown option,$s$0|AXO$0", "unknown option",            0 },

	/* End marker */
	{ NULL, NULL, NULL, 9999 }
};


/*
 * THE ENVIRONMENT OPTION MAP
 *
 * This table gives all the environment options. It needs to be kept in line
 * with Table 4.
 */
optmap environ_optmap[] = {
	/* Options */
	{ "\\+FLAG $",               "=$1",   NULL, 0 },
	{ "\\+FLAG_TDFC $",          "AOc$1", NULL, 0 },
	{ "\\+FLAG_TDFCPP $",        "AOp$1", NULL, 0 },
	{ "\\+FLAG_TCPPLUS $",       "AOx$1", NULL, 0 },
	{ "\\+FLAG_TCPPLUSPP $",     "AOg$1", NULL, 0 },
	{ "\\+FLAG_TOT_CAT $",       "",      NULL, 0 },
	{ "\\+FLAG_TLD $",           "AOL$1", NULL, 0 },
	{ "\\+FLAG_TRANS $",         "AOt$1", NULL, 0 },
	{ "\\+FLAG_AS $",            "AOa$1", NULL, 0 },
	{ "\\+FLAG_DYN_LINK $",      "AOD$1", NULL, 0 },
	{ "\\+FLAG_LD $",            "AOl$1", NULL, 0 },
	{ "\\+FLAG_DISP $",          "AOd$1", NULL, 0 },
	{ "\\+FLAG_TNC $",           "AOn$1", NULL, 0 },
	{ "\\+FLAG_PL_TDF $",        "AOP$1", NULL, 0 },
	{ "\\+FLAG_AS1 $",           "AOA$1", NULL, 0 },
	{ "\\+FLAG_TDFOPT $",        "",      NULL, 0 },
	{ "\\+FLAG_SPEC_LINK $",     "AOs$1", NULL, 0 },
	{ "\\+FLAG_CPP_SPEC_LINK $", "AOS$1", NULL, 0 },
	{ "\\+FLAG_DUMP_ANAL $",     "AOe$1", NULL, 0 },
	{ "\\+FLAG_DUMP_LINK $",     "AOu$1", NULL, 0 },
	{ "\\+FLAG_CC $",            "AOC$1", NULL, 0 },
	{ "\\+FLAG_INSTALL $",       "AOI$1", NULL, 0 },

	/* Additional filename suffixes */
	{ "\\+SUFFIX_CPP $",    "SSC$1|1SO", NULL, 0 },

	/* Executables */
	{ "?AS $",                 "$1Ea$2", NULL, 0 },
	{ "?AS1 $",                "$1EA$2", NULL, 0 },
	{ "?BUILD_ARCH $",         "$1BB$2", NULL, 0 },
	{ "?CAT $",                "$1BC$2", NULL, 0 },
	{ "?CC $",                 "$1EC$2", NULL, 0 },
	{ "?CPP_SPEC_LINK $",      "$1ES$2", NULL, 0 },
	{ "?DISP $",               "$1Ed$2", NULL, 0 },
	{ "?DUMP_ANAL $",          "$1Ee$2", NULL, 0 },
	{ "?DUMP_LINK $",          "$1Eu$2", NULL, 0 },
	{ "?DYN_LINK $",           "$1ED$2", NULL, 0 },
	{ "?LD $",                 "$1El$2", NULL, 0 },
	{ "?MKDIR $",              "$1BD$2", NULL, 0 },
	{ "?MOVE $",               "$1BM$2", NULL, 0 },
	{ "?PL_TDF $",             "$1EP$2", NULL, 0 },
	{ "?REMOVE $",             "$1BR$2", NULL, 0 },
	{ "?SPEC_LINK $",          "$1Es$2", NULL, 0 },
	{ "?SPLIT_ARCH $",         "$1BS$2", NULL, 0 },
	{ "?TCPPLUS $",            "$1Ex$2", NULL, 0 },
	{ "?TCPPLUSPP $",          "$1Eg$2", NULL, 0 },
	{ "?TDFC $",               "$1Ec$2", NULL, 0 },
	{ "?TDFCPP $",             "$1Ep$2", NULL, 0 },
	{ "?TDFOPT $",             "",       NULL, 0 },
	{ "?TLD $",                "$1EL$2", NULL, 0 },
	{ "?TNC $",                "$1En$2", NULL, 0 },
	{ "?TOUCH $",              "$1BT$2", NULL, 0 },
	{ "?TRANS $",              "$1Et$2", NULL, 0 },

	/*
	 * Set special env file variables.
	 * These must be kept in sync with Table 5 in path_subs.h
	 */
	{ "$PREFIX $",         "SSV0$2",  NULL, 0 },
	{ "$PREFIX_BIN $",     "SSV1$2",  NULL, 0 },
	{ "$PREFIX_LIB $",     "SSV2$2",  NULL, 0 },
	{ "$PREFIX_LIBEXEC $", "SSV3$2",  NULL, 0 },
	{ "$PREFIX_SHARE $",   "SSV4$2",  NULL, 0 },
	{ "$PREFIX_INCLUDE $", "SSV5$2",  NULL, 0 },
	{ "$PREFIX_MAN $",     "SSV6$2",  NULL, 0 },
	{ "$PREFIX_TSPEC $",   "SSV7$2",  NULL, 0 },
	{ "$PREFIX_STARTUP $", "SSV8$2",  NULL, 0 },
	{ "$PREFIX_ENV $",     "SSV9$2",  NULL, 0 },
	{ "$PREFIX_API $",     "SSV10$2", NULL, 0 },
	{ "$PREFIX_LPI $",     "SSV11$2", NULL, 0 },
	{ "$PREFIX_TMP $",     "SSV12$2", NULL, 0 },

	{ "$MD_EXECFORMAT $",  "SSV13$2", NULL, 0 },
	{ "$MD_BLDARCH $",     "SSV14$2", NULL, 0 },
	{ "$MD_BLDARCHBITS $", "SSV15$2", NULL, 0 },
	{ "$MD_OSFAM $",       "SSV16$2", NULL, 0 },
	{ "$MD_OSVER $",       "SSV17$2", NULL, 0 },

	/* Flags */
	{ "?API $",                "",       NULL, 0 },
	{ "?API_NAME $",           "",       NULL, 0 },
	{ "?INCL $",               "$1SI$2", NULL, 0 },
	{ "?INCL_CPP $",           "$1Si$2", NULL, 0 },
	{ "?STARTUP_DIR $",        "$1Sd$2", NULL, 0 },
	{ "?STARTUP $",            "$1Ss$2", NULL, 0 },
	{ "?STARTUP_CPP_DIR $",    "$1SD$2", NULL, 0 },
	{ "?STARTUP_CPP $",        "$1SS$2", NULL, 0 },
	{ "?PORTABILITY $",        "$1SP$2", NULL, 0 },
	{ "?LINK $",               "$1SJ$2", NULL, 0 },
	{ "?LIB $",                "$1Sj$2", NULL, 0 },
	{ "?CRT0 $",               "$1S0$2", NULL, 0 },
	{ "?CRT1 $",               "$1S1$2", NULL, 0 },
	{ "?CRTN $",               "$1S2$2", NULL, 0 },
	{ "?CRTP_N $",             "$1S3$2", NULL, 0 },
	{ "?SYS_LINK $",           "$1SL$2", NULL, 0 },
	{ "?SYS_LIB $",            "$1Sl$2", NULL, 0 },
	{ "?SYS_LIBC $",           "$1Sc$2", NULL, 0 },
	{ "?LINK_ENTRY $",         "$1Se$2", NULL, 0 },

	/* Startup and endup lines */
	{ "\\+COMP_OPTION $",      "@CAP:$1", NULL, 0 },
	{ "\\+LINE_START $",       "@D$1$n",  NULL, 0 },
	{ "\\+LINE_END $",         "@F$1$n",  NULL, 0 },

	/* Miscellaneous */
	{ "\\+INFO $",    "@SAI$1",           NULL, 0 },
	{ ">INFO $",      "@SAI$SAI@plus@$1", NULL, 0 },
	{ "<INFO $",      "@SAI$1@plus@$SAI", NULL, 0 },
	{ "\\+ENVDIR $",  "SED$1|CFE",        NULL, 0 },
	{ "\\?ENVDIR $",  "?:ED$1",           NULL, 0 },
	{ "\\+MACHINE $", "SMN$1|CSM",        NULL, 0 },
	{ "\\?MACHINE $", "?:MN$1",           NULL, 0 },
	{ "\\+SUFFIX $",  "STD$1",            NULL, 0 }, /* XXX: this MUST be wrong !!! */
	{ "\\+TEMP $",    "STD$1",            NULL, 0 },
	{ "\\?TEMP $",    "?:TD$1",           NULL, 0 },
	{ "\\+VERSION $", "SVF$1",            NULL, 0 },
	{ "\\?VERSION $", "?:VF$1",           NULL, 0 },

	/* Errors */
	{ "\\+E$ $", "X+E$soptions$sno$slonger$ssupported",    NULL, 0 },
	{ "$ $",     "XUnknown$senvironmental$svariable,$s$1", NULL, 0 },
	{ "$",       "XIllegal$senvironmental$soption,$s$0",   NULL, 0 },

	/* End marker */
	{ NULL, NULL, NULL, 9999 }
};


/*
 * OPTION INTERPRETER DEBUGGING FLAG
 *
 * This flag indicates whether option interpreter debugging information should
 * be printed.
 */
static boolean debug_options = 0;


/*
 * LOCAL FLAGS
 *
 * These values may be used for temporary storage by the option interpreter.
 */
static boolean xx_bool = 0;
static list *xx_list = NULL;
static const char *xx_string = NULL;


/*
 * ROUTINE IMPLEMENTING THE -SPECIAL OPTION
 *
 * This routine enables certain internal options depending on the value of the
 * string held in xx_string.
 */
static void
special_option(void)
{
	size_t i;
	boolean b = 1;
	const char *s = xx_string;

	assert(xx_string != NULL);

	struct {
		boolean notchecker;
		boolean dump;
		const char *s;
		boolean *b;
	} t[] = {
		{ 0, 0, "cpp",      &allow_cpp      },
		{ 1, 0, "tnc",      &allow_notation },
		{ 1, 0, "pl_tdf",   &allow_pl_tdf   },
		{ 0, 0, "c_spec",   &allow_specs    },
		{ 0, 0, "cpp_spec", &allow_specs    },
		{ 0, 1, "dump",     &allow_specs    },
		{ 0, 1, "cpp_dump", &allow_specs    }
	};

	if (strneq(s, "no_", 3)) {
		b = 0;
		s += 3;
	}

	for (i = 0; i < sizeof t / sizeof *t; i++) {
		if (0 != strcmp(t[i].s, s)) {
			continue;
		}

		if (t[i].notchecker && checker) {
			continue;
		}

		*t[i].b = b;

		if (t[i].dump && dump_opts == NULL) {
			dump_opts = "-d=";
		}

		return;
	};

	error(WARNING, "Unknown special option, '%s'", s);
}


/*
 * CONVERT A TWO LETTER CODE INTO A BOOLEAN
 *
 * This routine takes a two letter code, s, and returns a pointer to the
 * corresponding boolean variable.
 */
static boolean *
lookup_bool(const char *s)
{
	size_t i;

	/* TODO: with all of these as arrays, see if we can merge into one table */
	struct {
		char *s;
		boolean *b;
	} t[] = {
		{ "AA", &use_alpha_assembler },
		{ "AC", &api_checks          },
		{ "AR", &make_archive        },
		{ "AS", &use_assembler       },
		{ "CC", &use_system_cc       },
		{ "CH", &checker             },
		{ "CS", &allow_specs         },
		{ "DB", &debug_options       },
		{ "DG", &flag_diag           },
		{ "DL", &use_dynlink         },
		{ "DR", &dry_run             },
		{ "ES", &no_shuffle          },
		{ "HL", &use_hp_linker       },
		{ "KE", &flag_keep_err       },
		{ "LC", &case_insensitive    },
		{ "LS", &link_specs          },
		{ "MA", &use_mips_assembler  },
		{ "MC", &make_complex        },
		{ "MN", &make_up_names       },
		{ "MP", &flag_merge_all      },
		{ "NE", &flag_nepc           },
		{ "ON", &option_next         },
		{ "OP", &flag_optim          },
		{ "PF", &flag_prof           },
		{ "PI", &flag_incl           },
		{ "PL", &allow_pl_tdf        },
		{ "PP", &make_pretty         },
		{ "PR", &make_preproc        },
		{ "SA", &show_api            },
		{ "SC", &use_sparc_cc        },
		{ "SE", &show_errors         },
		{ "SO", &suffix_overrides    },
		{ "SR", &flag_strip          },
		{ "ST", &flag_startup        },
		{ "TC", &taciturn            },
		{ "TD", &env_dump            },
		{ "TE", &tool_chain_environ  },
		{ "TI", &time_commands       },
		{ "TN", &allow_notation      },
		{ "TS", &make_tspec          },
		{ "TT", &tool_chain          },
		{ "TU", &tidy_up             },
		{ "VB", &verbose             },
		{ "WA", &warnings            },
		{ "XX", &xx_bool             }
	};

	assert(s != NULL);

	for (i = 0; i < sizeof t / sizeof *t; i++) {
		if (0 == strncmp(t[i].s, s, 2)) {
			return t[i].b;
		}
	}

	error(OPTION, "Unknown boolean identifier, '%.2s'", s);
	return NULL;
}


/*
 * CONVERT A TWO LETTER CODE INTO A LIST
 *
 * This routine takes a two letter code, s, and returns a pointer to the
 * corresponding list variable. This routine needs to be kept in step with
 * Table 4.
 */
static list **
lookup_list(const char *s)
{
	size_t i;

	struct {
		boolean checkeronly;
		char s[3];
		list **l;
	} t[] = {
		{ 0,   "BB",                    &exec_build_arch        },
		{ 0,   "BC",                    &exec_cat               },
		{ 0,   "BD",                    &exec_mkdir             },
		{ 0,   "BM",                    &exec_move              },
		{ 0,   "BR",                    &exec_remove            },
		{ 0,   "BS",                    &exec_split_arch        },
		{ 0,   "BT",                    &exec_touch             },

		{ 0, { 'E', PRODUCE_ID       }, &exec_produce           },
		{ 0, { 'E', PREPROC_ID       }, &exec_preproc           },
		{ 0, { 'E', CPP_PRODUCE_ID   }, &exec_cpp_produce       },
		{ 0, { 'E', CPP_PREPROC_ID   }, &exec_cpp_preproc       },
		{ 0, { 'E', TDF_LINK_ID      }, &exec_tdf_link          },
		{ 0, { 'E', TRANSLATE_ID     }, &exec_translate         },
		{ 0, { 'E', ASSEMBLE_ID      }, &exec_assemble          },
		{ 0, { 'E', LINK_ID          }, &exec_link              },
		{ 0, { 'E', PRETTY_ID        }, &exec_pretty            },
		{ 0, { 'E', NOTATION_ID      }, &exec_notation          },
		{ 0, { 'E', PL_TDF_ID        }, &exec_pl_tdf            },
		{ 0, { 'E', ASSEMBLE_MIPS_ID }, &exec_assemble_mips     },
		{ 0, { 'E', SPEC_LINK_ID     }, &exec_spec_link         },
		{ 0, { 'E', CPP_SPEC_LINK_ID }, &exec_cpp_spec_link     },
		{ 0, { 'E', CC_ID            }, &exec_cc                },
		{ 0, { 'E', DYNLINK_ID       }, &exec_dynlink           },
		{ 0, { 'E', DUMP_ANAL_ID     }, &exec_dump_anal         },
		{ 0, { 'E', DUMP_LINK_ID     }, &exec_dump_link         },

		{ 1, { 'Q', PRODUCE_ID       }, &opt_produce            },
		{ 1, { 'Q', CPP_PRODUCE_ID   }, &opt_cpp_produce        },
		{ 1, { 'Q', SPEC_LINK_ID     }, &opt_spec_link          },
		{ 1, { 'Q', CPP_SPEC_LINK_ID }, &opt_cpp_spec_link      },
		{ 1, { 'Q', ARCHIVER_ID      }, &opt_joiner             },
		{ 1, { 'Q', CC_ID            }, &opt_cc                 },
		{ 0, { 'Q', PRODUCE_ID       }, &opt_produce            },
		{ 0, { 'Q', PREPROC_ID       }, &opt_preproc            },
		{ 0, { 'Q', CPP_PRODUCE_ID   }, &opt_cpp_produce        },
		{ 0, { 'Q', CPP_PREPROC_ID   }, &opt_cpp_preproc        },
		{ 0, { 'Q', TDF_LINK_ID      }, &opt_tdf_link           },
		{ 0, { 'Q', TRANSLATE_ID     }, &opt_translate          },
		{ 0, { 'Q', ASSEMBLE_ID      }, &opt_assemble           },
		{ 0, { 'Q', DYNLINK_ID       }, &opt_dynlink            },
		{ 0, { 'Q', LINK_ID          }, &opt_link               },
		{ 0, { 'Q', PRETTY_ID        }, &opt_pretty             },
		{ 0, { 'Q', NOTATION_ID      }, &opt_notation           },
		{ 0, { 'Q', PL_TDF_ID        }, &opt_pl_tdf             },
		{ 0, { 'Q', ASSEMBLE_MIPS_ID }, &opt_assemble_mips      },
		{ 0, { 'Q', SPEC_LINK_ID     }, &opt_spec_link          },
		{ 0, { 'Q', CPP_SPEC_LINK_ID }, &opt_cpp_spec_link      },
		{ 0, { 'Q', INSTALL_ID       }, &opt_archive            },
		{ 0, { 'Q', ARCHIVER_ID      }, &opt_joiner             },
		{ 0, { 'Q', CC_ID            }, &opt_cc                 },
		{ 0, { 'Q', DUMP_ANAL_ID     }, &opt_dump_anal          },
		{ 0, { 'Q', DUMP_LINK_ID     }, &opt_dump_link          },

		{ 0, { 'O', PRODUCE_ID       }, &opt_produce            },
		{ 0, { 'O', PREPROC_ID       }, &opt_preproc            },
		{ 0, { 'O', CPP_PRODUCE_ID   }, &opt_cpp_produce        },
		{ 0, { 'O', CPP_PREPROC_ID   }, &opt_cpp_preproc        },
		{ 0, { 'O', TDF_LINK_ID      }, &opt_tdf_link           },
		{ 0, { 'O', TRANSLATE_ID     }, &opt_translate          },
		{ 0, { 'O', ASSEMBLE_ID      }, &opt_assemble           },
		{ 0, { 'O', DYNLINK_ID       }, &opt_dynlink            },
		{ 0, { 'O', LINK_ID          }, &opt_link               },
		{ 0, { 'O', PRETTY_ID        }, &opt_pretty             },
		{ 0, { 'O', NOTATION_ID      }, &opt_notation           },
		{ 0, { 'O', PL_TDF_ID        }, &opt_pl_tdf             },
		{ 0, { 'O', ASSEMBLE_MIPS_ID }, &opt_assemble_mips      },
		{ 0, { 'O', SPEC_LINK_ID     }, &opt_spec_link          },
		{ 0, { 'O', CPP_SPEC_LINK_ID }, &opt_cpp_spec_link      },
		{ 0, { 'O', INSTALL_ID       }, &opt_archive            },
		{ 0, { 'O', ARCHIVER_ID      }, &opt_joiner             },
		{ 0, { 'O', CC_ID            }, &opt_cc                 },
		{ 0, { 'O', DUMP_ANAL_ID     }, &opt_dump_anal          },
		{ 0, { 'O', DUMP_LINK_ID     }, &opt_dump_link          },

		{ 0,   "SI",                    &std_prod_incldirs      },
		{ 0,   "SP",                    &std_prod_portfile      },
		{ 0,   "Sd",                    &std_prod_startdirs     },
		{ 0,   "Ss",                    &std_prod_startup       },
		{ 0,   "Si",                    &std_cpp_prod_incldirs  },
		{ 0,   "SD",                    &std_cpp_prod_startdirs },
		{ 0,   "SS",                    &std_cpp_prod_startup   },
		{ 0,   "SJ",                    &std_tdf_link_libdirs   },
		{ 0,   "Sj",                    &std_tdf_link_libs      },
		{ 0,   "S0",                    &std_link_crt0          },
		{ 0,   "S1",                    &std_link_crt1          },
		{ 0,   "S2",                    &std_link_crtn          },
		{ 0,   "S3",                    &std_link_crtp_n        },
		{ 0,   "SL",                    &std_link_libdirs       },
		{ 0,   "Sl",                    &std_link_libs          },
		{ 0,   "Sc",                    &std_link_c_libs        },
		{ 0,   "Se",                    &std_link_entry         },

		{ 0,   "UI",                    &usr_prod_incldirs      },
		{ 0,   "Us",                    &usr_prod_startup       },
		{ 0,   "Ue",                    &usr_prod_eoptions      },
		{ 0,   "Uf",                    &usr_prod_foptions      },
		{ 0,   "UP",                    &usr_pl_tdf_incldirs    },
		{ 0,   "UJ",                    &usr_tdf_link_libdirs   },
		{ 0,   "Uj",                    &usr_tdf_link_libs      },
		{ 0,   "UL",                    &usr_link_libdirs       },
		{ 0,   "Ul",                    &usr_link_libs          },

		{ 0,   "XO",                    &opt_unknown            },
		{ 0,   "XX",                    &xx_list                }
	};

	assert(s != NULL);

	for (i = 0; i < sizeof t / sizeof *t; i++) {
		if (s[0] == 'Q' && checker && !t[i].checkeronly) {
			continue;
		}

		if (0 == strncmp(t[i].s, s, 2)) {
			return t[i].l;
		}
	}

	switch (s[0]) {
	case 'E':
	case 'Q':
	case 'O':
		error(OPTION, "Unknown%s compilation stage, '%c'",
			checker ? "/non-checker" : "", s[1]);
		return NULL;

	default:
		break;
	}

	error(OPTION, "Unknown list identifier, '%.2s'", s);
	return NULL;
}


/*
 * CONVERT A TWO LETTER CODE INTO A STRING
 *
 * This routine takes a two letter code, s, and returns a pointer to the
 * corresponding string variable.
 */
static const char **
lookup_string(const char *s)
{
	size_t i;

	struct {
		const char *s;
		const char **p;
	} t[] = {
		{ "AI", &api_info      },
		{ "AO", &api_output    },
		{ "DO", &dump_opts     },
		{ "ED", &environ_dir   },
		{ "FN", &final_name    },
		{ "MN", &machine_name  },
		{ "PN", &progname      },
		{ "TD", &temporary_dir },
		{ "VF", &version_flag  },
		{ "WD", &workdir       },
		{ "XX", &xx_string     }
	};

	assert(s != NULL);

	if (s[0] == 'N') {
		switch (table_findbykey(s[1])) {
		case INDEP_TDF:    return &name_j_file;
		case C_SPEC:       return &name_k_file;
		case CPP_SPEC:     return &name_K_file;
		case STARTUP_FILE: return &name_h_file;
		case PRETTY_TDF:   return &name_p_file;

		default:
			error(OPTION, "Unknown output file specifier, '%c'", s[1]);
			return (NULL);
		}
	}

	if (0 == strncmp(s, "SV", 2)) {
		const char *p1;
		int i;

		i = s[2] - '0';
		p1 = (s + 3);

		/* change the path, if it was not set at cmd line */
		if (env_paths[i] == NULL) {
			env_paths[i] = p1;
		}

		/* XXX: hack */
		return &dev_null;
	}

	if (s[0] == 'S') {
		enum filetype t;

		t = find_type_stage(s[1]);
		return &filetype_table[t].suffix;
	}

	for (i = 0; i < sizeof t / sizeof *t; i++) {
		if (0 == strncmp(t[i].s, s, 2)) {
			return t[i].p;
		}
	}

	error(OPTION, "Unknown string identifier, '%.2s'", s);
	return NULL;
}


/*
 * DUMMY ARGUMENT FOR PROCEDURE
 *
 * This variable is used to hold any argument passed to one of the procedures
 * in lookup_proc.
 */
static const char *lookup_proc_arg = NULL;


/*
 * DUMMY WRAPPER PROCEDURES
 *
 * These routine(s) are used to call procedures with an argument using
 * lookup_proc.
 */
static void
add_pragma_aux(void)
{
	add_pragma(lookup_proc_arg);
}

static void
add_token_aux(void)
{
	add_token(lookup_proc_arg);
}


/*
 * CONVERT A TWO LETTER CODE INTO A PROCEDURE
 *
 * This routine takes a two letter code, s, and returns a pointer to the
 * corresponding procedure.
 */
typedef void (*proc)(void);

static proc
lookup_proc(const char *s)
{
	size_t i;

	struct {
		const char *s;
		proc f;
	} t[] = {
		{ "AP", add_pragma_aux },
		{ "AT", add_token_aux  },
		{ "FE", find_envpath   },
		{ "PV", print_version  },
		{ "SE", show_envpath   },
		{ "SM", set_machine    },
		{ "SP", special_option }
	};

	assert(s != NULL);

	/* TODO: ensure all these functions are passed strings, if possible, and use strcmp */
	for (i = 0; i < sizeof t / sizeof *t; i++) {
		if (0 == strncmp(t[i].s, s, 2)) {
			return t[i].f;
		}
	}

	error(OPTION, "Unknown procedure identifier, '%.2s'", s);
	return NULL;
}


/*
 * RETURN VALUES FOR MATCH_OPTION
 *
 * These values are returned by match_option. MATCH_OK means that the option
 * matches, MATCH_MORE means that it may match with an additional option,
 * MATCH_FAILED means it does not match, and the other values indicate errors
 * of some kind.
 */
enum match_option {
	MATCH_OK,
	MATCH_MORE,
	MATCH_FAILED,
	MATCH_IN_ERR,
	MATCH_OUT_ERR,
	MATCH_OPT_ERR
};


/*
 * MATCH AN OPTION
 */
static enum match_option
match_option(char *in, char *out, const char *opt, args_out *res)
{
	char *p;
	const char *q = opt;

	int i, a, v = 1;
	int go = 1, loop = 1, loopv = -1;
	struct {
		const char *txt;
		int len;
	} var[max_var];

	assert(in != NULL);
	assert(out != NULL);
	assert(opt != NULL);
	assert(res != NULL);

	/* Process input */
	for (p = in; *p && go; p++) {
		switch (*p) {
		case '$': {
			char c = p[1];
			int wraps;

			if (!c) {
				/* Simple string : $ */
				int l = strlen(q);
				var[v].txt = q;
				var[v].len = l;
				if (++v >= max_var) return MATCH_OPT_ERR;
				go = 0;
				continue;
			}

			wraps = 0;
			if (p[2] == '+' && p[3] == '*') {
				/* List of strings with breaks : $c+* */
				wraps = 1;
				p++;
			}
			if (p[2] == '*') {
				/* List of strings : $c* */
				loop = 0;
				loopv = v;
				if (p[3]) return MATCH_IN_ERR;
				while (*q) {
					int l = 0;
					var[v].txt = q;
					while (*q && *q != c) {
						l++;
						q++;
					}
					var[v].len = l;
					if (*q) {
						/* Found c */
						q++;
						if (*q == 0 && wraps) return MATCH_MORE;
					}
					if (++v >= max_var) return MATCH_OPT_ERR;
					loop++;
				}
				go = 0;
			} else {
				/* Terminated string : $c */
				int l = 0;
				var[v].txt = q;
				while (*q != c) {
					if (*q == 0) return MATCH_FAILED;
					l++;
					q++;
				}
				var[v].len = l;
				if (++v >= max_var) return MATCH_OPT_ERR;
			}
			continue;
		}

		case '?':
			if (p[1] == '*') {
				/* List of characters : ?* */
				if (p[2]) return MATCH_IN_ERR;
				loop = 0;
				loopv = v;
				while (*q) {
					var[v].txt = q;
					var[v].len = 1;
					if (++v >= max_var) return MATCH_OPT_ERR;
					q++;
					loop++;
				}
				go = 0;
			} else {
				/* Simple character : ? */
				if (*q == 0) return MATCH_FAILED;
				var[v].txt = q;
				var[v].len = 1;
				if (++v >= max_var) return MATCH_OPT_ERR;
				q++;
			}
			continue;

		/* Potential break : + */
		case '+':
			if (*q == 0) return MATCH_MORE;
			continue;

		/* Negated letter */
		case '^':
			p++;
			if (*p == 0) return MATCH_IN_ERR;
			if (*p == *q) return MATCH_FAILED;
			q++;
			continue;

		/* Escaped letter : \c */
		case '\\':
			p++;
			if (*p == 0) return MATCH_IN_ERR;
			if (*p != *q) return MATCH_FAILED;
			q++;
			continue;

		/* Letter : c */
		default:
			if (*p != *q) return MATCH_FAILED;
			q++;
			continue;
		}
	}

	/* Check end of option */
	if (go && *q) return MATCH_FAILED;

	/* The first variable is the whole option */
	var[0].txt = opt;
	var[0].len = strlen(opt);

	/* Print output */
	a = 0;
	for (i = 0; i < loop; i++) {
		int count = 0;
		char buff[MAX_LINE];
		char *q = buff;		/* TODO rename */

		for (p = out; *p && count < MAX_LINE; p++, count++) {
			int n;
			char c;

			switch (*p) {
			case '|':	/* Multiple output */
				*q = 0;
				res->argv[a] = string_copy(buff);
				if (++a >= max_var) return MATCH_OPT_ERR;
				q = buff;
				continue;

			case '\\':	/* Escaped output character */
				if (*(++p) == 0) return MATCH_OUT_ERR;
				*(q++) = *p;
				continue;

			default:	/* Simple output character */
				if (*p != '$') {
					*(q++) = *p;
					continue;
				}
				break;
			}

			/* Variable */
			c = *(++p);
			switch (c) {
			case 's':	/* $s expands to a space */
				*(q++) = ' ';
				break;

			case 'n':	/* $n expands to a newline */
				*(q++) = '\n';
				break;

			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				n = (c - '0');
				if (n == loopv) n += i;
				if (n < v) {
					size_t l = var[n].len;
					IGNORE strncpy(q, var[n].txt, l);
					q += l;
				}
				break;

			case 'B': {
				const boolean *b = lookup_bool(p + 1);
				if (b == NULL) return MATCH_OUT_ERR;
				IGNORE sprintf(q, "%d", (int) *b);
				while (*q) q++;
				p += 2;
				break;
			}

			case 'L': {
				list *pt;
				list **sp;

				sp = lookup_list(p + 1);
				if (sp == NULL) return MATCH_OUT_ERR;

				for (pt = *sp; pt; pt = pt->next) {
					int l = (int)strlen(pt->item.s);
					IGNORE strncpy(q, pt->item.s,(size_t)l);
					q += l;
					*(q++) = ' ';
				}
				p += 2;
				break;
			}

			case 'S': {
				int l;
				const char **sp;

				sp = lookup_string(p + 1);
				if (sp == NULL) return MATCH_OUT_ERR;

				if (*sp) {
					l = (int)strlen(*sp);
					IGNORE strncpy(q, *sp,(size_t)l);
					q += l;
				}
				p += 2;
				break;
			}

			default:
				return MATCH_OUT_ERR;
			}
		}

		*q = 0;
		res->argv[a] = string_copy(buff);
		if (++a >= max_var) {
			return MATCH_OPT_ERR;
		}
	}

	res->argc = a;
	return MATCH_OK;
}


/*
 * INTERPRET AN OPTION COMMAND
 */
static void
interpret_cmd(const char *cmd)
{
	char c = *cmd;

	assert(cmd != NULL);

	/* Debugging */
	if (debug_options) {
		error(OPTION, "Interpreting '%s'", cmd);
	}

	/* Deal with at-hack */
	if (c == '@') {
		char *p = string_copy(cmd + 1), *q;
		for (q = p; *q; q++) {
			if (*q == '@') {
				*q = ' ';
			}
		}
		cmd = p;
		c = *p;
	}

	/* Deal with empty strings */
	if (c == '\0') {
		return;
	}

	/* Digits set values */
	if (c >= '0' && c <= '9') {
		boolean *b = lookup_bool(cmd + 1);
		if (b == NULL) {
			return;
		}
		*b = (boolean)(c - '0');
		return;
	}

	/* Translations */
	if (c == '>') c = 'A';
	if (c == '<') c = 'B';
	if (c == '+') c = 'L';

	/* Deal with list query */
	if (c == '?') {
		if (cmd[1] == ':') {
			const char **sp = lookup_string(cmd + 2);
			if (sp == NULL) {
				return;
			}
			comment(1, "%s=\"%s\"\n", cmd + 4, *sp);
		} else if (cmd[1] == '!') {
			const boolean *bp = lookup_bool(cmd + 2);
			if (bp == NULL) {
				return;
			}
			comment(1, "%s=\"%d\"\n", cmd + 4, *bp);
		} else {
			list *p;
			list **sp = lookup_list(cmd + 1);
			if (sp == NULL) return;
			comment(1, "%s=\"", cmd + 3);
			for (p = *sp; p != NULL; p = p->next) {
				comment(1, "%s", p->item.s);
				if (p->next) {
					comment(1, " ");
				}
			}
			comment(1, "\"\n");
		}
		return;
	}

	/* Deal with equivalences */
	if (c == '=') {
		list *p = make_list(cmd + 1);
		process_options(p, main_optmap, 1);
		free_list(p);
		return;
	}

	/* Deal with primitives */
	/* TODO: consider having this as a lookup table of cmd_*() function pointers */
	switch (c) {

	/* Change list */
	case 'A': {
		list **sp = lookup_list(cmd + 1);
		if (sp == NULL) {
			return;
		}
		*sp = add_list(*sp, make_list(cmd + 3));
		return;
	}

	/* Change list */
	case 'B': {
		list **sp = lookup_list(cmd + 1);
		if (sp == NULL) {
			return;
		}
		*sp = add_list(make_list(cmd + 3), *sp);
		return;
	}

	/* Change list */
	case 'L': {
		list **sp = lookup_list(cmd + 1);
		if (sp == NULL) {
			return;
		}
		free_list(*sp);
		*sp = make_list(cmd + 3);
		return;
	}

	/* Call */
	case 'C': {
		proc p = lookup_proc(cmd + 1);
		if (p == NULL) {
			return;
		}
		if (cmd[3] == ':') {
			lookup_proc_arg = cmd + 4;
		} else {
			lookup_proc_arg = NULL;
		}
		(*p)();
		return;
	}

	/* Startup options */
	case 'D':
		add_to_startup(cmd + 1);
		return;

	/* Environment */
	case 'E': {
		char var[MAX_LINE];
		char val[MAX_LINE];
		int  count;
		char *q, *r;
		const char *p;
		char c1;
		char **subs;
		int i;

		if (*(cmd + 1) != '?') {
			read_env(cmd + 1);
			return;
		}

		q = var;
		r = val;
		p = cmd + 2;
		count = 0;
		while ((c1 = *p++) != '?') {
			*q++ = c1;
		}
		*q++='\0';

		while ((c1 = *p++) != '\0') {
			*r++ = c1;
			/*
			 * Only the value is user supplied and needs bounds checking.
			 */
			if (++count >= MAX_LINE) {
				error(FATAL, "Exceeded maximum buffer length in -y argument\n");
			}
		}
		*r++ ='\0';

		/*
		 * Additional error checking for those platforms supporting stat() for
		 * variables which represent paths on the filesystem.
		 * TODO: this probably also ought to check
		 */
		if (0 == strncmp(var, "PREFIX_", 7) && strlen(val) > 0) {
			struct stat sb;
	
			if (stat(val, &sb) == -1) {
				error(SERIOUS, "interpret_cmd: %s %s", val, strerror(errno));
			}

			/* TODO: check sb S_IFDIR */
		}

		i = 0;
		subs = PATH_SUBS;
		while (*subs) {
			if (0 == strcmp(*subs, var)) {
				env_paths[i] = string_copy(val);
				break;
			}
			i++;
			subs++;
		}

		if (!*subs) {
			error(WARNING, "Ignoring non-standard env assignment: %s=%s", var, val);
		}
		return;
	}

	/* Endup options */
	case 'F':
		add_to_endup(cmd + 1);
		return;

	/* Halt */
	case 'H': {
		char stage = cmd[1];
		set_stage(find_type_stage(stage), STOP_STAGE);
		return;
	}

	/* Input file */
	case 'I': {
		enum filetype t;
		filename *f;
		char stage = cmd[1];
		const char *name = cmd + 2;

		t = (stage == '?') ? UNKNOWN_TYPE
		                   : find_type_stage(stage);

		f = find_filename(name, t);
		input_files = add_filename(input_files, f);
		return;
	}

	/* Keep */
	case 'K': {
		static int k = KEEP_STAGE;
		char stage = cmd[1];

		if (stage == '-') {
			k = DONT_KEEP_STAGE;
		} else {
			set_stage(find_type_stage(stage), k);
			k = KEEP_STAGE;
		}
		return;
	}

	/* Query */
	case 'Q': {
		char *s;
		optmap *t;

		error(INFO, "List of recognised options");

		for (t = main_optmap; s = t->in, s != NULL; t++) {
			char d;

			if (*s != '-') {
				continue;
			}

			comment(0, " ");
			while (d = *(s++), d != 0) {
				switch (d) {
				case '$':  IGNORE fputs("<string>", stderr); break;
				case '?':  IGNORE fputs("<letter>", stderr); break;
				case '*':  IGNORE fputs("...",      stderr); break;
				case '+':  IGNORE fputc(' ',        stderr); break;
				case '\\': IGNORE fputc(*(s++),     stderr); break;
				default:   IGNORE fputc(d,          stderr); break;
				}
			}

			s = t->explain;
			if (s == NULL) {
				s = "not documented";
			}

			comment(0, " : ");
			comment(0, s, progname);
			comment(0, ".\n");
		}
		return;
	}

	/* String */
	case 'S': {
		const char **s = lookup_string(cmd + 1);
		if (s == NULL) {
			return;
		}

		*s = cmd + 3;
		return;
	}

	case 'V':
		switch (cmd[1]) {
		case 'B': {
			boolean *b = lookup_bool(cmd + 2);
			if (b == NULL) {
				return;
			}
			comment(1, "%c%c = %d\n", cmd[2], cmd[3], *b);
			return;
		}

		case 'L': {
			list **sp = lookup_list(cmd + 2), *pt;
			if (sp == NULL) {
				return;
			}
			comment(1, "%c%c =", cmd[2], cmd[3]);
			for (pt = *sp; pt != NULL; pt = pt->next) {
				if (pt->item.s) {
					comment(1, " %s", pt->item.s);
				} else {
					comment(1, " (NULL)");
				}
			}
			comment(1, "\n");
			return;
		}

		case 'S': {
			const char **s = lookup_string(cmd + 2);
			if (s == NULL) {
				return;
			}
			if (*s) {
				comment(1, "%c%c = %s\n", cmd[2], cmd[3], *s);
			} else {
				comment(1, "%c%c = (NULL)\n", cmd[2], cmd[3]);
			}
			return;
		}
		}
		break;

	/* Error */
	case 'X':
		error(WARNING, "%s", cmd + 1);
		return;
	}

	error(OPTION, "Syntax error, '%s'", cmd);
}


/*
 * PROCESS A LIST OF OPTIONS
 *
 * This routine processes a list of options, opt, using the options from table
 * tab.
 */
void
process_options(list *opt, optmap *tab, int fast)
{
	optmap *t;
	list *p;
	list *accum = NULL;
	const char *arg = NULL;
	enum match_option status = MATCH_OK;
	int a;

	assert(tab != NULL);

	/* Scan through the options */
	for (p = opt; p != NULL; p = p->next) {
		if (status == MATCH_MORE) {
			arg = string_concat(arg, p->item.s);
		} else {
			arg = p->item.s;
		}

		status = MATCH_FAILED;
		for (t = tab; t->in != NULL; t++) {
			args_out res;
			status = match_option(t->in, t->out, arg, &res);

			switch (status) {
			case MATCH_OK:
				/* Complete option - interpret result */
				for (a = 0; a < res.argc; a++) {
					if (no_shuffle != 0 || fast == 1) {
						interpret_cmd(res.argv[a]);
					} else {
						ordered_node *dn = xalloc(sizeof(ordered_node));
						dn->rank = t->rank;
						dn->cmd  = res.argv[a];
						accum = insert_inorder(dn, accum);
					}
				}
				goto end_search;

			case MATCH_MORE:
				/* Incomplete option - move on to next option */
				goto end_search;

			case MATCH_FAILED:
				/* Try again */
				break;

			case MATCH_IN_ERR:
				/* Error in optmap input */
				error(OPTION, "Illegal input '%s'", t->in);
				status = MATCH_FAILED;
				break;

			case MATCH_OUT_ERR:
				/* Error in optmap output */
				error(OPTION, "Illegal option '%s'", t->out);
				status = MATCH_FAILED;
				break;

			case MATCH_OPT_ERR:
				/* Ran out of space for result */
				error(OPTION, "Too many components, '%s'", arg);
				status = MATCH_FAILED;
				break;
			}
		}

		error(OPTION, "Can't interpret '%s'", arg);
end_search:
		;
	}

	/* Check for incomplete options */
	if (status == MATCH_MORE) {
		error(WARNING, "Option '%s' is incomplete", arg);
	}

	/* if the no_shuffle flag is unset, we have order cmds to run */
	if (no_shuffle == 0 && fast == 0) {
		while (accum) {
			ordered_node* dn;
			dn = accum->item.on;
			interpret_cmd(dn->cmd);
			accum = accum->next;
		}
	}
}

