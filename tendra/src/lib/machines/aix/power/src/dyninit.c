/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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

#include <stdio.h>
#include <stdlib.h>
#include <filehdr.h>
#include <syms.h>
#include "ossg.h"

#define IS_BAD_MAGIC_NUMBER(x) ((x!=0x1df)?1:0)
void output_assembler_file PROTO_S ((void));
void scan_object_file PROTO_S ((void));
void found_one PROTO_S ((char *));
void fail PROTO_S ((char *));
int main PROTO_S ((int,char **));
FILE *open_file PROTO_S ((char *,char *));

char **names;
long names_size = 0;
long names_found = 0;
char *output_file;
char *input_file;

int main PROTO_N ((argc,argv)) PROTO_T (int argc X char ** argv)
{
  int report_version = 0;
  if (!strcmp(argv[1],"-V") || !strcmp(argv[1],"-v"))
  {
    printf("dyninit for powertrans version 1.1\n");
    report_version = 1; 
  }
  
  if ((argc - report_version)!=3)
  {
    if(report_version) exit(0);
    fail("Wrong number of arguments: <object_file> <assembler_file>");
  }
  input_file = argv[1+report_version];
  output_file = argv[2+report_version];
  scan_object_file();
  return 0;
}

FILE *open_file PROTO_N ((filename,option)) PROTO_T (char * filename X char *option)
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

void fail PROTO_N ((message)) PROTO_T (char * message)
{
  fprintf(stderr,"*fail* : %s\n",message);
  exit(1);
}


void found_one PROTO_N ((str)) PROTO_T (char *str)
{
  if (names_size == names_found)
  {
    if (names_size==0)
    {
      names = (char **)malloc(20*sizeof(char *));
      names_size = 20;
    }
    else
    {
      names_size +=20;
      names = (char **)realloc(names,names_size*sizeof(char *));
    }
  }
  names[names_found] = (char *)malloc(strlen(str)+1);
  strcpy(names[names_found],str);
  names_found++;
  return;
}

void scan_object_file PROTO_Z ()
{
  int i;
  struct filehdr header;
  struct syment symbol;
  FILE *fp = open_file(input_file,"r");
  
  fread(&header,sizeof(struct filehdr),1,fp);
  
  if (IS_BAD_MAGIC_NUMBER(header.f_magic))
  {
    fail("Bad magic number");
  }
  if (header.f_nsyms==0)
  {
    fail("No symbol table info");
  }
  
  fseek(fp,header.f_symptr,0);
  for (i=0; i<header.f_nsyms;i++)
  {
    long keeppos;
    
    fread(&symbol,SYMESZ,1,fp);
    if (symbol.n_sclass==C_EXT && symbol._n._n_n._n_zeroes==0)
    {
      char str[256];
      long offset = symbol._n._n_n._n_offset + header.f_symptr + (SYMESZ*header.f_nsyms);
      long keeppos = ftell(fp);

      fseek(fp,offset,0);
      fgets(str,256,fp);
      if (strncmp(str,"__I.TDF",7)==0)
      {
        found_one(str);
      }
      fseek(fp,keeppos,0);
    }
  }
  fclose(fp);
  
  output_assembler_file();
}

void output_assembler_file PROTO_Z ()
{
  int i;
  FILE *of = fopen(output_file,"w");
  
  for (i=0;i<names_found;i++)
  {
    fprintf (of,"\t.extern %s\n",names[i]);
    fprintf (of,"\t.extern .%s\n",names[i]);
  }
  fprintf(of,"\t.globl\t__main\n");
  fprintf(of,"\t.globl\t.__main\n");
  fprintf(of,"\t.extern\t__main\n");
  fprintf(of,"\t.extern\t.__main\n\n");
  fprintf(of,"\t.toc\n");
  
  for (i=0;i<names_found;i++)
  {
    fprintf (of,"\tT.%s:\t.tc\t%s[TC],%s\n",names[i],names[i],names[i]);
  }

  fprintf(of,"\t.csect\t[DS]\n");
  fprintf(of,"__main:\n");
  fprintf(of,"\t.long\t.__main,TOC[tc0],0\n");
  fprintf(of,"\t.csect\t[PR]\n");
  
  fprintf(of,".__main:\n");
  fprintf(of,"\tmflr\t0\n");
  fprintf(of,"\tst\t0,8(1)\n");
  fprintf(of,"\tai\t1,1,-56\n");
  
  for (i=0;i<names_found;i++)
  {
    fprintf (of,"\tbl\t.%s\n",names[i]);
    fprintf(of,"\tcror\t15,15,15\n");
  }

  fprintf(of,"\tai\t1,1,56\n");
  fprintf(of,"\tl\t0,8(1)\n");
  fprintf(of,"\tmtlr\t0\n");
  fprintf(of,"\tbr\n");
  
  fclose(of);
  
}
