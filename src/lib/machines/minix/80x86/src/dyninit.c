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


/*
  dyninit

  This program extracts all the initialisation procedures from an ACK
  object file.  It then writes out a .s file containing a function 
  (___TDF_main) which contains calls to each of these procedures.
  Initialisation procedures are identified by the ___I_TDF prefix.
  Note: the actual prefix starts with two '_'s but TenDRA C compiler
  inserts an extra one.

  the command line syntax is

  dyninit <name of object file> <name of destination (.s) file>

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "out.h"
#include "ossg.h"

#define MAJOR_VERSION		1
#define MINOR_VERSION		1

void fail PROTO_S((char *));
FILE *open_file PROTO_S((char *,char *));
#define open_file_read(x)	open_file(x,"r")
#define open_file_write(x)	open_file(x,"w")


FILE *open_file
    PROTO_N((filename,option))
    PROTO_T(char *filename X char *option)
{
  FILE * ret_fp;
  if(ret_fp = fopen(filename,option)){
    return ret_fp;
  }
  else{
    fprintf(stderr,"Cannot open file <%s>\n",filename);
    exit(1);
  }
}


typedef struct outhead EXEC_STRUCT;

typedef struct outname SYMBOL_STRUCT;

#define INIT_FUNC_NAME "___TDF_main"

EXEC_STRUCT header;
SYMBOL_STRUCT symbol;


void fail
    PROTO_N((message))
    PROTO_T(char *message)
{
  fprintf(stderr,"*fail* : %s\n",message);
  exit(1);
}


/*#define symbol_is_function(x) (x.n_type & N_TEXT)*/
#define is_initialisation_function(x) (!strncmp(x+1,"__I_TDF",7))
#define is_function(x) 1


void print_ass_preamble
    PROTO_N((of))
    PROTO_T(FILE *of)
{
  fprintf(of,".sect .text; .sect .rom; .sect .data; .sect .bss\n");
  fprintf(of,".sect .text\n");
  fprintf(of,".define %s\n",INIT_FUNC_NAME);
  fprintf(of,".align 16\n");
  fprintf(of,"%s:\n",INIT_FUNC_NAME);
  return;
}

void print_ass_postlude
    PROTO_N((of))
    PROTO_T(FILE *of)
{
  fprintf(of,"\tret\n");
}

void construct_init_proc
    PROTO_N((fp,symtab_pos,stringtab_pos,header,outfilename))
    PROTO_T(FILE *fp X long symtab_pos X long stringtab_pos X
	    EXEC_STRUCT header X char *outfilename)
{
  int i;
  char str[256];
  long keeppos;
  FILE *outfile;
  if(!(outfile = open_file_write(outfilename))){
    fail("Cannot open output file");
  }
  fseek(fp,symtab_pos,0);
  print_ass_preamble(outfile);
  for(i=0;i<header.oh_nname;++i){
    fread(&symbol,sizeof(SYMBOL_STRUCT),1,fp);
    if(is_function(symbol)){
      keeppos = ftell(fp);
      /* note: in ACK, on_u.on_off is the offset from the start of file,
         not from start of symbol table, so we don't add stringtab_pos here */
      fseek(fp,symbol.on_u.on_off,0);
      fgets(str,256,fp);
      if(is_initialisation_function(str)){
	fprintf(outfile,"\tcall\t%s\n",str);
      }
      fseek(fp,keeppos,0);
    }
  }
  print_ass_postlude(outfile);
  return;
}

void process_flag
    PROTO_N((option))
    PROTO_T(char *option)
{
  switch(option[1]) {
    case 'V':
    case 'v': {
      (void)fprintf(stderr,"Dynamic initialisation linker V%d.%d\n",
		    MAJOR_VERSION,MINOR_VERSION);
      break;
    }
    default: {
      (void)fprintf(stderr,"Error: unknown option %s\n",option);
    }
  }
  return;
}


int main
    PROTO_N((argc,argv))
    PROTO_T(int argc X char **argv)
{
  FILE *fp;
  long symtab_pos,stringtab_pos;
  int i;
  int symsize;
  char str[80];
  long keeppos;
  int num_flags = 0;
  
  for(i=1;i<argc;++i) {
    if(argv[i][0] == '-') {
      num_flags++;
      process_flag(argv[i]);
    }
  }
  if(argc - num_flags < 3) {
    fprintf(stderr,"*fail*: syntax is %s [-options] <input filename> <output filename>\n",argv[0]);
    exit(1);
  }
  fp = open_file_read(argv[1+num_flags]);

  fread(&header,sizeof(EXEC_STRUCT),1,fp);
  if(BADMAGIC(header)){
    fail("Bad magic number\n");
  }
  symtab_pos = OFF_NAME(header);
  
  stringtab_pos = OFF_CHAR(header);
  construct_init_proc(fp,symtab_pos,stringtab_pos,header,argv[2+num_flags]);
  return 0;
}
