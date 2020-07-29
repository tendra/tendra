/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <filehdr.h>
#include <syms.h>

#include <shared/check.h>
#include <shared/string.h>

#define IS_BAD_MAGIC_NUMBER(x)	((x != 0x1df) ? 1 : 0)
void output_assembler_file(void);
void scan_object_file(void);
void found_one(char *);
void fail(char *);
int main(int, char **);
FILE *open_file(char *, char *);

char **names;
long names_size = 0;
long names_found = 0;
char *output_file;
char *input_file;

int
main(int argc, char ** argv)
{
  int report_version = 0;
  if (streq(argv[1], "-V") || streq(argv[1], "-v"))
  {
    printf("dyninit for powertrans version 1.1\n");
    report_version = 1;
  }

  if ((argc - report_version) != 3)
  {
    if (report_version) exit(0);
    fail("Wrong number of arguments: <object_file> <assembler_file>");
  }
  input_file = argv[1 + report_version];
  output_file = argv[2 + report_version];
  scan_object_file();
  return 0;
}

FILE *
open_file(char * filename, char *option)
{
  FILE * ret_fp;
  if (ret_fp = fopen(filename, option)) {
    return ret_fp;
  }
  else{
    fprintf(stderr, "Cannot open file <%s>\n", filename);
    exit(1);
  }
}

void fail(char * message)
{
  fprintf(stderr, "*fail* : %s\n" ,message);
  exit(1);
}


void found_one(char *str)
{
  if (names_size == names_found)
  {
    if (names_size == 0)
    {
      names = malloc(20 * sizeof(char *));
      names_size = 20;
    }
    else
    {
      names_size += 20;
      names = realloc(names, names_size * sizeof(char *));
    }
  }
  names[names_found] = malloc(strlen(str) +1);
  strcpy(names[names_found] ,str);
  names_found++;
  return;
}

void scan_object_file(void)
{
  int i;
  struct filehdr header;
  struct syment symbol;
  FILE *fp = open_file(input_file, "r");

  fread(&header, sizeof(struct filehdr), 1, fp);

  if (IS_BAD_MAGIC_NUMBER(header.f_magic))
  {
    fail("Bad magic number");
  }
  if (header.f_nsyms == 0)
  {
    fail("No symbol table info");
  }

  fseek(fp, header.f_symptr, 0);
  for (i = 0; i < header.f_nsyms; i++)
  {
    long keeppos;

    fread(&symbol, SYMESZ, 1, fp);
    if (symbol.n_sclass == C_EXT && symbol._n._n_n._n_zeroes == 0)
    {
      char str[256];
      long offset = symbol._n._n_n._n_offset + header.f_symptr + (SYMESZ*header.f_nsyms);
      long keeppos = ftell(fp);

      fseek(fp, offset, 0);
      fgets(str, 256, fp);
      if (strncmp(str, "__I.TDF", 7) == 0)
      {
        found_one(str);
      }
      fseek(fp, keeppos, 0);
    }
  }
  fclose(fp);

  output_assembler_file();
}

void output_assembler_file(void)
{
  int i;
  FILE *of = fopen(output_file, "w");

  for (i = 0; i < names_found; i++)
  {
    fprintf(of, "\t.extern %s\n", names[i]);
    fprintf(of, "\t.extern .%s\n", names[i]);
  }
  fprintf(of, "\t.globl\t__main\n");
  fprintf(of, "\t.globl\t.__main\n");
  fprintf(of, "\t.extern\t__main\n");
  fprintf(of, "\t.extern\t.__main\n\n");
  fprintf(of, "\t.toc\n");

  for (i = 0; i < names_found; i++)
  {
    fprintf(of, "\tT.%s:\t.tc\t%s[TC], %s\n", names[i], names[i], names[i]);
  }

  fprintf(of, "\t.csect\t[DS]\n");
  fprintf(of, "__main:\n");
  fprintf(of, "\t.long\t.__main, TOC[tc0], 0\n");
  fprintf(of, "\t.csect\t[PR]\n");

  fprintf(of, ".__main:\n");
  fprintf(of, "\tmflr\t0\n");
  fprintf(of, "\tst\t0, 8(1)\n");
  fprintf(of, "\tai\t1, 1, -56\n");

  for (i = 0; i < names_found; i++)
  {
    fprintf(of, "\tbl\t.%s\n", names[i]);
    fprintf(of, "\tcror\t15, 15, 15\n");
  }

  fprintf(of, "\tai\t1, 1, 56\n");
  fprintf(of, "\tl\t0, 8(1)\n");
  fprintf(of, "\tmtlr\t0\n");
  fprintf(of, "\tbr\n");

  fclose(of);

}
