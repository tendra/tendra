/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>


/*
  dyninit

  This program extracts all the initialisation procedures from a SunOS
  object file.  It then writes out a .s file containing a function
  (___TDF_main) which contains calls to each of these procedures.
  Initialisation procedures are identified by the ___I.TDF prefix.
  Note: the actual prefix starts with two '_'s but SunOS inserts
  an extra one.

  the command line syntax is

  dyninit <name of object file> <name of destination (.s) file>

*/

#include <stdio.h>
#include <sparc/a.out.h>

#define MAJOR_VERSION		1
#define MINOR_VERSION		1

void fail(char *);
FILE *open_file(char *,char *);
#define open_file_read(x)	open_file(x,"r")
#define open_file_write(x)	open_file(x,"w")


FILE *
open_file(char *filename, char *option)
{
  FILE *ret_fp;
  if (ret_fp = fopen(filename,option)) {
    return ret_fp;
  }
  else{
    fprintf(stderr,"Cannot open file <%s>\n", filename);
    exit(1);
  }
}


typedef struct exec EXEC_STRUCT;

typedef struct nlist SYMBOL_STRUCT;

#define INIT_FUNC_NAME "___TDF_main"

EXEC_STRUCT header;
SYMBOL_STRUCT symbol;


void
fail(char *message)
{
  fprintf(stderr, "*fail* : %s\n", message);
  exit(1);
}


/*#define symbol_is_function(x) (x.n_type & N_TEXT)*/
#define is_intitialisation_function(x)	(!strncmp(x + 1, "__I.TDF", 7))
#define is_function(x)1


void
print_ass_preamble(FILE *of)
{
  fprintf(of, ".global ");
  fprintf(of, INIT_FUNC_NAME);
  fprintf(of, "\n");
  fprintf(of, "\t.seg\t\"text\"\n");
  fprintf(of, "\t.align\t4\n");
  fprintf(of, INIT_FUNC_NAME);
  fprintf(of, ":\n");
  fprintf(of, "\tsave\t%%sp, -64, %%sp\n");
  return;
}

void
print_ass_postlude(FILE *of)
{
  fprintf(of, "\tret\n\trestore\n");
}

void
construct_init_proc(FILE *fp, long symtab_pos, long stringtab_pos,
		    EXEC_STRUCT header, char *outname)
{
  int i;
  char str[256];
  long keeppos;
  FILE *outfile;
  if (!(outfile = open_file_write(outname))) {
    fail("Cannot Open output file");
  }
  fseek(fp, symtab_pos, 0);
  print_ass_preamble(outfile);
  for (i = 0; i < header.a_syms / sizeof(SYMBOL_STRUCT); ++i) {
    fread(&symbol, sizeof(SYMBOL_STRUCT), 1, fp);
    if (is_function(symbol)) {
      keeppos = ftell(fp);
      fseek(fp, stringtab_pos + symbol.n_un.n_strx, 0);
      fgets(str, 256, fp);
      if (is_intitialisation_function(str)) {
	fprintf(outfile, "\tcall\t%s, 0\n\tnop\n", str);
      }
      fseek(fp, keeppos, 0);
    }
  }
  print_ass_postlude(outfile);
  return;
}

void
process_flag(char *option)
{
  switch (option[1]) {
    case 'V':
    case 'v': {
     IGNORE fprintf(stderr, "Dynamic initialisation linker V%d.%d\n",
		    MAJOR_VERSION, MINOR_VERSION);
      break;
    }
    default: {
     IGNORE fprintf(stderr, "Error: unknown option %s\n", option);
    }
  }
  return;
}


int
main(int argc, char **argv)
{
  FILE *fp;
  long symtab_pos, stringtab_pos;
  int i;
  int symsize;
  char str[80];
  long keeppos;
  int num_flags = 0;

  for (i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      num_flags++;
      process_flag(argv[i]);
    }
  }
  if (argc - num_flags < 3) {
    fprintf(stderr, "*fail*: syntax is %s [-options] <input filename> <output filename>\n", argv[0]);
    exit(1);
  }
  fp = open_file_read(argv[1 + num_flags]);

  fread(&header, sizeof(EXEC_STRUCT), 1, fp);
  if (N_BADMAG(header)) {
    fail("Bad magic number\n");
  }
  symtab_pos = N_SYMOFF(header);

  stringtab_pos = N_STROFF(header);
  construct_init_proc(fp, symtab_pos, stringtab_pos, header,
		      argv[2 + num_flags]);
  return 0;
}
