/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

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
#include "table.h"
#include "hash.h"


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
 * third entry is a description.
 */
struct optmap main_optmap[] = {
	/* Common options */
	{ "^-$",         "I?$0",              "specifies an input file"                       },
	{ "-o+$",        "SFN$1",             "specifies output file name"                    },
	{ "-D+$=$",      "D#define$s$1$s$2$n"
	                 "|AOC$0",            "defines a macro"                               },
	{ "-D+$",        "D#define$s$1$s1$n"
	                 "|AOC$0",            "defines a macro to be 1"                       },
	{ "-F?",         "H$1",               "halts the compilation at the given stage"      },
	{ "-I+$",        "AUI$0|AOC$0|AUP$0", "specifies an include file directory"           },
	{ "-L+$",        "1ON|Io$0|AUL$0",    "specifies a system library directory"          },
	{ "-N+$:+$",     "AUI$0|AOC-I$2",     "specifies an include file directory "
	                                       "(with mode)"                                  },
	{ "-O$",         "1OP|AOC$0",         "switches optimisation level"                   },
	{ "-P?*",        "K$1",               "causes intermediate files to be preserved"     },
	{ "-S",          "Hs",                "halts compilation after creating .s files"     },
	{ "-T+$",        "CAT:$1|AOC-D$1",    "specifies a command-line token"                },
	{ "-U+$",        "D#undef$s$1$n"
	                 "|AOC$0",            "undefines a macro"                             },
	{ "-W?,+$,+*",   "AQ$1$2",            "passed an option to a compilation tool"        },
	{ "-W?:+$",      "AQ$1$2",            "passed an option to a compilation tool"        },
	{ "-X:+$,+*",    "CAP:$1",            "specifies a compilation option"                },
	{ "-X$",         "EX$1",              "specifies a compilation mode"                  },
	{ "-Y+$",        "E$1",               "reads an environment"                          },
	{ "-c",          "Ho",                "halts compilation after creating .o files"     },
	{ "-d",          "Hd",                "halts compilation after creating .d files"     },
	{ "-dry",        "1VB|1DR",           "causes a dry run"                              },
	{ "-e+$",        "AUe$0",             "specifies a producer end-up file"              },
	{ "-f+$",        "AUf$0",             "specifies a producer start-up file"            },
	{ "-g",          "1DG",               "produces debugging information "
	                                       "(default format)"                             },
	{ "-g1",         "1DG",               "produces debugging information (old format)"   },
	{ "-g2",         "2DG",               "produces debugging information (new format)"   },
	{ "-g3",         "3DG",               "produces debugging information (new format)"   },
	{ "-k",          "Hk|HK",             "halts compilation after creating "
	                                       ".k and .K files"                              },
	{ "-l+$",        "1ON|Io$0|AUl$0",    "specifies a system library"                    },
	{ "-not_ansi",   "ASs-fnot_ansi",     "allows some non-ANSI C features"               },
	{ "-nepc",       "1NE|ASs-fnepc",     "switches off extra portability checks"         },
	{ "-sym",        "1CS|SDO-d=",        "enables symbol table dump linking"             },
	{ "-sym:$",      "1CS|SDO-d$1=",      "enables symbol table dump linking with flags"  },
	{ "-v",          "1VB",               "specifies verbose mode"                        },
	{ "-vb",         "1TC",               "specifies fairly verbose mode"                 },
	{ "-vd",         "1TD",               "dump the env information tcc got hold of"      },
	{ "-ve",         "1TE",               "verbose information about "
	                                       "tool chain environment"                       },
	{ "-vt",         "1TT",               "verbose information about "
	                                       "tool chain invocation"                        },
	{ "-y+$=$",      "E?$1?$2",           "sets an env directory variable"                },

	/* Options not allowed in checker */
	{ "-J+$",           "AUJ-L$1",          "specifies a TDF library directory"           },
	{ "-M",             "1MC",              "causes all .j files to be merged"            },
	{ "-MA",            "1MC|1MP",          "as -M, but with hiding"                      },
	{ "-ch",            "1CH",              "invokes checker mode"                        },
	{ "-disp",          "1PP",              "causes all .j files to be pretty printed"    },
	{ "-disp_t",        "2PP",              "causes all .t files to be pretty printed"    },
	{ "-i",             "Hj",               "halts compilation after creating .j files"   },
	{ "-im",            "1CS",              "enables intermodular checks"                 },
	{ "-j+$",           "AUj-l$1",          "specifies a TDF library"                     },
	{ "-prod",          "1AR",              "causes a TDF archive to be produced"         },

	/* Less common options */
	{ "-A+-",           "AOC$0",            "unasserts all built-in predicates"           },
	{ "-A+$",           "D#pragma$sTenDRA$sdirective$sassert$sallow$n"
	                    "|D#assert$s$1$n|AOC$0", "asserts a predicate"                    },
	{ "-B+$",           "1ON|Io$0",         "passed to the system linker"                 },
	{ "-C",             "AOC$0",            "preserves comments when preprocessing"       },
	{ "-E",             "1PR",              "causes C source files to be preprocessed"    },
	{ "-E?:+$",         "LE$1$2",           "specifies an executable to be used"          },
	{ "-H",             "1PI",              "causes included files to be printed"         },
	{ "-S?,+$,+*",      "I$1$2",            "specifies input files"                       },
	{ "-S?:+$",         "I$1$2",            "specifies input files"                       },
	{ "-V",             "EVersions",        "causes all tools to print their "
	                                         "version numbers"                            },
	{ "-cc",            "1CC",              "forces the system compiler to be used"       },
	{ "-cc_only",       "2CC",              "forces only the system compiler to be used"  },
	{ "-do?+$",         "SN$1$2",           "sets a default output file name"             },
	{ "-dump",          "CDS",              "dumps the current status"                    },
	{ "-ignore_case",   "1LC",              "ignores case in file names"                  },
	{ "-im0",           "2CS",              "disables intermodular checks"                },
	{ "-info",          "1SA",              "causes API information to be printed"        },
	{ "-keep_errors",   "1KE",              "causes files to be preserved on errors"      },
	{ "-make_up_names", "1MN",              "makes up names for intermediate files"       },
	{ "-message+$",     "@X$1",             "causes %s to print a message"                },
	{ "-p",             "1PF",              "causes profiling information to be produced" },
	{ "-q",             "0VB",              "specifies quiet mode"                        },
	{ "-quiet",         "0VB",              "equivalent to -q"                            },
	{ "-query",         "Q",                "causes a list of options to be printed"      },
	{ "-s?:+$",         "SS$1$2|1SO",       "specifies a suffix override"                 },
	{ "-show_errors",   "1SE",              "causes error producing commands to be shown" },
	{ "-special+$",     "SXX$1|CSP",        "allows various internal options"             },
	{ "-startup+$",     "@D$1$n",           "specifies a start-up option"                 },
	{ "-temp+PREFIX_TMP=$", "E?$1?$2",      "specifies the temporary directory"           },
	{ "-tidy",          "1TU",              "causes %s to tidy up as it goes along"       },
	{ "-verbose",       "1VB",              "equivalent to -v"                            },
	{ "-version",       "CPV",              "causes %s to print its version number"       },
	{ "-w",             "0WA",              "suppresses %s warnings"                      },
	{ "-work+$",        "SWD$1",            "specifies the work directory"                },

	/* Options not allowed in checker */
	{ "-K+$,+*",        "EK-$1",            "provided for cc compatibility"    },
	{ "-b",             "LSc",              "suppresses -lc in system linking" },
	{ "-dn",            "AOl$0",            "passed to the system linker"      },
	{ "-dy",            "AOl$0",            "passed to the system linker"      },
	{ "-h+$",           "AOl$0",            "passed to the system linker"      },
	{ "-no_startup_options", "0ST",         "suppresses start-up options"      },
	{ "-s",             "1SR",              "passed to the system linker"      },
	{ "-u+$",           "AOl$0",            "passed to the system linker"      },
	{ "-wsl",           "Ewsl",             "causes string literals to "
	                                         "be made writable"                },
	{ "-z+$",           "AOl$0",            "passed to the system linker"      },
	{ "-#",             "1VB",              "equivalent to -v"                 },
	{ "-##",            "1VB",              "equivalent to -v"                 },
	{ "-###",           "1VB|1DR",          "equivalent to -dry"               },

	/* Default options */
	{ "--+$,+*", "$1", "communicates directly with the option interpreter" },
	{ "$",       "XUnknown option,$s$0|AXO$0", "unknown option"            },

	/* End marker */
	{ NULL, NULL, NULL }
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

	assert(xx_string != NULL);

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

	error(ERROR_USAGE, "Unknown special option, '%s'", s);
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

	struct {
		char *s;
		boolean *b;
	} t[] = {
		{ "AC", &api_checks          },
		{ "AR", &make_archive        },
		{ "AS", &use_assembler       },
		{ "BA", &use_binasm          },
		{ "CC", &use_system_cc       },
		{ "CH", &checker             },
		{ "CS", &allow_specs         },
		{ "DB", &debug_options       },
		{ "DG", &flag_diag           },
		{ "DL", &use_dynlink         },
		{ "DR", &dry_run             },
		{ "HL", &use_hp_linker       },
		{ "KE", &flag_keep_err       },
		{ "LC", &case_insensitive    },
		{ "LS", &link_specs          },
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

	error(ERROR_USAGE, "Unknown boolean identifier, '%.2s'", s);
	return NULL;
}


/*
 * CONVERT A TWO LETTER CODE INTO AN ENVIRONMENT VARIABLE
 *
 * This routine takes a two letter code, s, and returns a pointer to the
 * corresponding variable name. This routine needs to be kept in step with
 * Table 4.
 */
static const char *
lookup_env(const char *s)
{
	size_t i;

	struct {
		boolean checkeronly;
		char s[3];
		const char *envvar;
	} t[] = {
		{ 0,   "BB",                    "BUILD_ARCH"         },
		{ 0,   "BS",                    "SPLIT_ARCH"         },

		/*
		 * EXECUTABLES
		 *
		 * These variables give the values of the various executables comprising the
		 * system. For example, exec_produce gives the location of the C to TDF
		 * producer.
		 */
		{ 0, { 'E', ASSEMBLE_ID        }, "AS"                 },
		{ 0, { 'E', ASSEMBLE_BINASM_ID }, "AS1"                },
		{ 0, { 'E', CAT_ID             }, "CAT"                },
		{ 0, { 'E', CC_ID              }, "CC"                 },
		{ 0, { 'E', CPP_PREPROC_ID     }, "TCPPLUSPP"          },
		{ 0, { 'E', CPP_PRODUCE_ID     }, "TCPPLUSPP"          },
		{ 0, { 'E', CPP_SPEC_LINK_ID   }, "CPP_SPEC_LINK"      },
		{ 0, { 'E', DUMP_ANAL_ID       }, "DUMP_ANAL"          },
		{ 0, { 'E', DUMP_LINK_ID       }, "DUMP_LINK"          },
		{ 0, { 'E', DYNLINK_ID         }, "DYN_LINK"           },
		{ 0, { 'E', LINK_ID            }, "LD"                 },
		{ 0, { 'E', MKDIR_ID           }, "MKDIR"              },
		{ 0, { 'E', MOVE_ID            }, "MOVE"               },
		{ 0, { 'E', NOTATION_ID        }, "TNC"                },
		{ 0, { 'E', PL_TDF_ID          }, "TPL"                },
		{ 0, { 'E', PREPROC_ID         }, "TDFCPP"             },
		{ 0, { 'E', PRETTY_ID          }, "DISP"               },
		{ 0, { 'E', PRODUCE_ID         }, "TDFC"               },
		{ 0, { 'E', RMDIR_ID           }, "RMDIR"              },
		{ 0, { 'E', RMFILE_ID          }, "RMFILE"             },
		{ 0, { 'E', SPEC_LINK_ID       }, "SPEC_LINK"          },
		{ 0, { 'E', TDF_LINK_ID        }, "TLD"                },
		{ 0, { 'E', TOUCH_ID           }, "TOUCH"              },
		{ 0, { 'E', TRANSLATE_ID       }, "TRANS"              },

		/*
		 * EXECUTABLE OPTIONS
		 *
		 * These lists record the command-line options which are passed directly to the
		 * various executables.
		 */
		{ 1, { 'Q', PRODUCE_ID         }, "FLAG_TDFC"          },
		{ 1, { 'Q', CPP_PRODUCE_ID     }, "FLAG_TCPPLUSPP"     },
		{ 1, { 'Q', SPEC_LINK_ID       }, "FLAG_SPEC_LINK"     },
		{ 1, { 'Q', CPP_SPEC_LINK_ID   }, "FLAG_CPP_SPEC_LINK" },
		{ 1, { 'Q', ARCHIVER_ID        }, "FLAG_AR"            },
		{ 1, { 'Q', CC_ID              }, "FLAG_CC"            },
		{ 0, { 'Q', PRODUCE_ID         }, "FLAG_TDFC"          },
		{ 0, { 'Q', PREPROC_ID         }, "FLAG_TDFCPP"        },
		{ 0, { 'Q', CPP_PRODUCE_ID     }, "FLAG_TCPPLUSPP"     },
		{ 0, { 'Q', CPP_PREPROC_ID     }, "FLAG_TCPPLUSPP"     },
		{ 0, { 'Q', TDF_LINK_ID        }, "FLAG_TLD"           },
		{ 0, { 'Q', TRANSLATE_ID       }, "FLAG_TRANS"         },
		{ 0, { 'Q', ASSEMBLE_ID        }, "FLAG_AS"            },
		{ 0, { 'Q', DYNLINK_ID         }, "FLAG_DYN_LINK"      },
		{ 0, { 'Q', LINK_ID            }, "FLAG_LINK"          },
		{ 0, { 'Q', PRETTY_ID          }, "FLAG_DISP"          },
		{ 0, { 'Q', NOTATION_ID        }, "FLAG_TNC"           },
		{ 0, { 'Q', PL_TDF_ID          }, "FLAG_PL_TDF"        },
		{ 0, { 'Q', ASSEMBLE_BINASM_ID }, "FLAG_AS1"           },
		{ 0, { 'Q', SPEC_LINK_ID       }, "FLAG_SPEC_LINK"     },
		{ 0, { 'Q', CPP_SPEC_LINK_ID   }, "FLAG_CPP_SPEC_LINK" },
		{ 0, { 'Q', INSTALL_ID         }, "FLAG_INSTALL"       },
		{ 0, { 'Q', ARCHIVER_ID        }, "FLAG_ARCHIVER"      },
		{ 0, { 'Q', CC_ID              }, "FLAG_CC"            },
		{ 0, { 'Q', DUMP_ANAL_ID       }, "FLAG_DUMP_ANAL"     },
		{ 0, { 'Q', DUMP_LINK_ID       }, "FLAG_DUMP_LINK"     },

		{ 0, { 'O', PRODUCE_ID         }, "FLAG_TDFC"          },
		{ 0, { 'O', PREPROC_ID         }, "FLAG_TDFCPP"        },
		{ 0, { 'O', CPP_PRODUCE_ID     }, "FLAG_TCPPLUSPP"     },
		{ 0, { 'O', CPP_PREPROC_ID     }, "FLAG_TCPPLUSPP"     },
		{ 0, { 'O', TDF_LINK_ID        }, "FLAG_TLD"           },
		{ 0, { 'O', TRANSLATE_ID       }, "FLAG_TRANS"         },
		{ 0, { 'O', ASSEMBLE_ID        }, "FLAG_AS"            },
		{ 0, { 'O', DYNLINK_ID         }, "FLAG_DYN_LINK"      },
		{ 0, { 'O', LINK_ID            }, "FLAG_LINK"          },
		{ 0, { 'O', PRETTY_ID          }, "FLAG_DISP"          },
		{ 0, { 'O', NOTATION_ID        }, "FLAG_TNC"           },
		{ 0, { 'O', PL_TDF_ID          }, "FLAG_PL_TDF"        },
		{ 0, { 'O', ASSEMBLE_BINASM_ID }, "FLAG_AS1"           },
		{ 0, { 'O', SPEC_LINK_ID       }, "FLAG_SPEC_LINK"     },
		{ 0, { 'O', CPP_SPEC_LINK_ID   }, "FLAG_CPP_SPEC_LINK" },
		{ 0, { 'O', INSTALL_ID         }, "FLAG_INSTALL"       },
		{ 0, { 'O', ARCHIVER_ID        }, "FLAG_ARCHIVER"      },
		{ 0, { 'O', CC_ID              }, "FLAG_CC"            },
		{ 0, { 'O', DUMP_ANAL_ID       }, "FLAG_DUMP_ANAL"     },
		{ 0, { 'O', DUMP_LINK_ID       }, "FLAG_DUMP_LINK"     },

		/*
		 * BUILT-IN OPTIONS
		 *
		 * These lists of options are built into the system, although they may be
		 * altered by environments and command-line options.
		 */
		{ 0,   "SI", "INCL"                },
		{ 0,   "SP", "PORTABILITY"         },
		{ 0,   "Sd", "STARTUP_DIR"         },
		{ 0,   "Ss", "STARTUP"             },
		{ 0,   "Si", "INCL_CPP"            },
		{ 0,   "SD", "STARTUP_CPP_DIR"     },
		{ 0,   "SS", "STARTUP_CPP"         },
		{ 0,   "SJ", "LINK"                },
		{ 0,   "Sj", "LIB"                 },
		{ 0,   "S0", "CRT0"                },
		{ 0,   "S1", "CRT1"                },
		{ 0,   "S2", "CRTN"                },
		{ 0,   "S3", "CRTP_N"              },
		{ 0,   "SL", "SYS_LINK"            },
		{ 0,   "Sl", "SYS_LIB"             },
		{ 0,   "Sc", "SYS_LIBC"            },
		{ 0,   "Se", "LINK_ENTRY"          },

		/*
		 * COMMAND-LINE OPTIONS
		 *
		 * These lists of options are those specified on the command-line.
		 */
		/* TODO: maybe these can just use the std_ equivalents instead */
		{ 0,   "UI", "USR_INCL"            },
		{ 0,   "Us", "USR_STARTUP"         },
		{ 0,   "Ue", "USR_PROD_EOPTIONS"   },
		{ 0,   "Uf", "USR_PROD_FOPTIONS"   },
		{ 0,   "UP", "USR_PL_TDF_INCLDIRS" },
		{ 0,   "UJ", "USR_LINK"            },
		{ 0,   "Uj", "USR_LIB"             },
		{ 0,   "UL", "USR_SYS_LINK"        },
		{ 0,   "Ul", "USR_SYS_LIB"         },

		{ 0,   "XO", "OPT_UNKNOWN"         },
		{ 0,   "XX", "XX_LIST"             }
	};

	assert(s != NULL);

	for (i = 0; i < sizeof t / sizeof *t; i++) {
		if (s[0] == 'Q' && checker && !t[i].checkeronly) {
			continue;
		}

		if (0 == strncmp(t[i].s, s, 2)) {
			return t[i].envvar;
		}
	}

	switch (s[0]) {
	case 'E':
	case 'Q':
	case 'O':
		error(ERROR_USAGE, "Unknown%s compilation stage, '%c'",
			checker ? "/non-checker" : "", s[1]);
		return NULL;

	default:
		break;
	}

	error(ERROR_USAGE, "Unknown list identifier, '%.2s'", s);
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
		{ "PN", &progname      },
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
			error(ERROR_USAGE, "Unknown output file specifier, '%c'", s[1]);
			return NULL;
		}
	}

	if (0 == strncmp(s, "SV", 2)) {
		const char *q;

		q = s + 3 + strcspn(s + 3, " ");

		envvar_set(&envvars, s + 3, q + 1, *(s + 2), HASH_DEFAULT);

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

	error(ERROR_USAGE, "Unknown string identifier, '%.2s'", s);
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
		{ "PV", print_version  },
		{ "SP", special_option }
	};

	assert(s != NULL);

	for (i = 0; i < sizeof t / sizeof *t; i++) {
		if (0 == strncmp(t[i].s, s, 2)) {
			return t[i].f;
		}
	}

	error(ERROR_USAGE, "Unknown procedure identifier, '%.2s'", s);
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
				res->argv[a] = xstrdup(buff);
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
				const char *sp;

				sp = lookup_env(p + 1);
				if (sp != NULL) {
					size_t l;

					l = strlen(sp);
					IGNORE strncpy(q, sp, l);
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
		res->argv[a] = xstrdup(buff);
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
interpret_cmd(const char *cmd, enum hash_precedence precedence)
{
	char c = *cmd;

	assert(cmd != NULL);

	/* Debugging */
	if (debug_options) {
		error(ERROR_WARNING, "Interpreting '%s'", cmd);
	}

	/* Deal with at-hack */
	if (c == '@') {
		char *p = xstrdup(cmd + 1), *q;
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
			const char *sp = lookup_env(cmd + 1);
			if (sp == NULL) return;
			comment(1, "%s=\"%s\"\n", cmd + 3, sp);
		}
		return;
	}

	/* Deal with equivalences */
	if (c == '=') {
		list *p = make_list(cmd + 1);
		process_options(p, main_optmap, precedence);
		free_list(p);
		return;
	}

	/* Deal with primitives */
	/* TODO: consider having this as a lookup table of cmd_*() function pointers */
	switch (c) {

	/* Change list */
	case 'A': {
		const char *var;

		var = lookup_env(cmd + 1);
		if (var == NULL) {
			return;
		}

		envvar_set(&envvars, var, cmd + 3, HASH_APPEND, HASH_CLI);
		return;
	}

	/* Change list */
	case 'B': {
		const char *var;

		var = lookup_env(cmd + 1);
		if (var == NULL) {
			return;
		}

		envvar_set(&envvars, var, cmd + 3, HASH_PREPEND, HASH_CLI);
		return;
	}

	/* Change list */
	case 'L': {
		const char *var;

		var = lookup_env(cmd + 1);
		if (var == NULL) {
			return;
		}

		envvar_set(&envvars, var, cmd + 3, HASH_ASSIGN, HASH_CLI);
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
				error(ERROR_FATAL, "Exceeded maximum buffer length in -y argument\n");
			}
		}
		*r++ ='\0';

		envvar_set(&envvars, var, val, HASH_ASSIGN, precedence);
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
		struct optmap *t;

		fprintf(stderr, "List of recognised options");

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
			const char *sp = lookup_env(cmd + 2);
			if (sp == NULL) {
				return;
			}
			comment(1, "%c%c = \"%s\"\n", cmd[2], cmd[3], sp);
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
		error(ERROR_USAGE, "%s", cmd + 1);
		return;
	}

	error(ERROR_USAGE, "Syntax error, '%s'", cmd);
}


/*
 * PROCESS A LIST OF OPTIONS
 *
 * This routine processes a list of options, opt, using the options from table
 * tab.
 */
void
process_options(list *opt, struct optmap *tab, enum hash_precedence precedence)
{
	struct optmap *t;
	list *p;
	const char *arg = NULL;
	enum match_option status = MATCH_OK;
	int a;

	assert(tab != NULL);

	/* Scan through the options */
	for (p = opt; p != NULL; p = p->next) {
		if (status == MATCH_MORE) {
			arg = xstrcat(arg, p->s);
		} else {
			arg = p->s;
		}

		status = MATCH_FAILED;
		for (t = tab; t->in != NULL; t++) {
			args_out res;
			status = match_option(t->in, t->out, arg, &res);

			switch (status) {
			case MATCH_OK:
				/* Complete option - interpret result */
				for (a = 0; a < res.argc; a++) {
					interpret_cmd(res.argv[a], precedence);
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
				error(ERROR_USAGE, "Illegal input '%s'", t->in);
				status = MATCH_FAILED;
				break;

			case MATCH_OUT_ERR:
				/* Error in optmap output */
				error(ERROR_USAGE, "Illegal option '%s'", t->out);
				status = MATCH_FAILED;
				break;

			case MATCH_OPT_ERR:
				/* Ran out of space for result */
				error(ERROR_USAGE, "Too many components, '%s'", arg);
				status = MATCH_FAILED;
				break;
			}
		}

		error(ERROR_USAGE, "Can't interpret '%s'", arg);
end_search:
		;
	}

	/* Check for incomplete options */
	if (status == MATCH_MORE) {
		error(ERROR_USAGE, "Option '%s' is incomplete", arg);
	}
}

