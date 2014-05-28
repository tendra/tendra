/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>

#include <shared/check.h>
#include <shared/getopt.h>
#include <shared/error.h>

#include <local/exptypes.h>
#include <local/out.h>

#include <reader/main_reads.h>		/* for d_capsule */
#include <reader/basicread.h>	/* for good_trans */
#include <reader/externs.h>

#include <construct/flags.h>		/* for option flags */
#include <construct/flpt.h>
#include <construct/exp.h>		/* for current_alloc_size */
#include <construct/installglob.h>	/* for top_def */
#include <construct/installtypes.h>

#include <main/driver.h>

#include "comment.h"		/* for do_comment */
#include "addrtypes.h"		/* for where */
#include "makecode.h"		/* for nowhere */
#include "diag_out.h"
#include "frames.h"

#define VERSION_STR "7.8"

extern int good_trans;

char *local_prefix, *name_prefix;

/*
 * XXX: Some of the conditional optimisations local to this installer are
 * miscategorised as OPTIM_PEEPHOLE (which I'm using here for general purpose
 * optimisations, rather than introduce a new category specifically for
 * hppatrans). In particular the jump table optimisations ought to be split
 * out to OPTIM_JUMPS instead.
 */

static void
init(void)
{
	endian    = ENDIAN_BIG;
	assembler = ASM_HP;
	format    = FORMAT_SOM;
	diag      = DIAG_NONE;
	cconv     = CCONV_HPPA;
	abi       = ABI_HPUX;

	/* initialise output file */
	outf = stdout;

	/* errors messages are output on stdout, ensure they get out */
	setbuf(stdout, NULL);

	redo_structfns     = 0; /* procs delivering structs recast to extra param */
	redo_structparams  = 1; /* struct and union value parameters indirected   */
	do_profile         = 0; /* -P option for profiling info */
	do_alloca          = 0; /* inline alloca */
	PIC_code           = 0;
	keep_PIC_vars      = 1;
	diagnose_registers = 0;
	use_long_double    = 1;
	do_comment         = 0; /* implement -c option */

#if use_long_double
	target_dbl_maxexp = 16384;
#else
	target_dbl_maxexp = 308;
#endif
}

static int
option(char c, const char *optarg)
{
	switch (c) {
	case 'c': do_comment       = 1; break;
	case 'd': plusZ            = 1; break; /* -d emulates cc's +Z flag */
	case 'i': do_indexed_loads = 0; break;

	default:
		return -1;
	}

	return 0;
}

/*
 * Open input and output files.
 */
static int
init_trans(char *infname, char *outfname)
{
  if (!initreader(infname)) {
    fprintf(stderr, "hppatrans: cannot open input file %s\n", infname);
    return 3;
  }

  if (strcmp(outfname, "-") == 0) {
    /* "-" by convention means stdout */
    outf = stdout;
  } else {
    outf = fopen(outfname, "w+");
    if (outf == (FILE *)0) {
      fprintf(stderr, "hppatrans: cannot open output file %s\n", outfname);
      return 3;
    }
  }

  return 0;
}

static void
main(int argc, char ** argv)
{
	char *arg;
	bool errflg     = 0;
	bool versionflg = 0; /* XXX: get rid of this */

	char *infname   = NULL;
	char *outfname  = NULL;

	if (writable_strings) {
		/* TODO: either always on, or always off. error out accordingly */
	}

	if (report_versions) {
		versionflg = 1;
	}

   /* we expect two further filename arguments */
   if (argc == 2) {
     infname = argv[0];
     outfname = argv[1];
   } else if (argc == 1) {
     infname = argv[0];
     outfname = "-";
   } else {
     errflg = 1;
   };

   if (errflg) {
     exit(EXIT_FAILURE);
   }

   if (do_profile && PIC_code) {
      fprintf(stderr,"hppatrans warning: \"-P\" and \"-D\" are mutually exclusive. \"-P\" ignored.\n");
      do_profile = 0;
   }

   /* Things trans.hppa does not "has" */
   has &= ~HAS_BYTEOPS;
   has &= ~HAS_BYTEREGS;
   has &= ~HAS_NEGSHIFT;
   has &= ~HAS_ROTATE;
   has &= ~HAS_MAXMIN;
   has &= ~HAS_DIV0;
   has &= ~HAS_SETCC;
   has &= ~HAS_COMPLEX;
   has &= ~HAS_64_BIT;

   /* not implemented */
   optim &= ~OPTIM_TAIL;
   optim &= ~OPTIM_ZEROOFFSETS;
   optim &= ~OPTIM_SUBSTPARAMS;

   /* Careful with procedure results */
   optim &= ~OPTIM_UNPAD_APPLY;

   if (diag != DIAG_NONE) {
      optim = 0;
      /* TODO: do gdb diagnostics depend on gcc assembly? */
   }

   /* init nowhere */
  setregalt(nowhere.answhere, 0);
  nowhere.ashwhere.ashsize = 0;
  nowhere.ashwhere.ashsize = 0;

  local_prefix = "$";		/* Label prefix */
  crt_labno = 101;		/* First label; avoid conflict with reg nos */
				/* (and backward compatibility) */

   name_prefix = "";

  init_flpt();			/* initialise the floating point array */
#include <reader/inits.h>		/* initialise common parts of translator */
  top_def = (dec *)0;

  if (diag != DIAG_NONE) {
     init_stab();
  }

  if (init_trans(infname,outfname) || d_capsule() || good_trans)
     exit(EXIT_FAILURE);

  exit_translator();

  /* check for output errors and close the .s file */
  if (ferror(outf) != 0 || fclose(outf) != 0) {
    fprintf(stderr, "hppatrans: error writing to output file %s\n", outfname);
    exit(EXIT_FAILURE);
  }
}

void
out_rename(char * oldid, char * newid)
{
    comment2("renamed %s as %s", oldid, newid);
    return;
}

struct driver driver = {
	VERSION_STR,

	init,
	main,

	"cdi",
	option,
	NULL,

	ABI_HPUX,
	CCONV_HPPA,
	ENDIAN_BIG | ENDIAN_LITTLE,
	FORMAT_SOM,
#ifdef _SYMTAB_INCLUDED
	DIAG_NONE | DIAG_STABS,
#else
	DIAG_NONE | DIAG_STABS | DIAG_XDB | DIAG_GDB,
#endif
	ASM_HP | ASM_GAS
};

