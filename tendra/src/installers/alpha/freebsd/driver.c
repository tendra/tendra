/*
 * Copyright (c) 2003, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/* 	$Id$	 */

#ifndef lint
static char vcid[] = "$Id$";
#endif /* lint */

/*
  driver.c
  Provides the driver function for the TDF->DEC Alpha translator.
  JM  17/9/93
*/

/**/


#include "config.h"
#include "release.h"
#include "common_types.h"
#include "basicread.h"
#include "flags.h"
#include "main_reads.h"
#include "flpt.h"
#include "externs.h"
#include "installglob.h"
#include "machine.h"
#include "exp.h"
#include "dump_distr.h"
#include "file.h"
#include "fail.h"
#include "version.h"
#include "reader_v.h"
#include "construct_v.h"
#include "symbol.h"
#include "bool.h"
FILE *as_file;		/* assembly file */
FILE *ba_file;

#define SUCCESS 0
#define FAILURE 1
#ifndef compile_date
#ifdef __DATE__
#define compile_date __DATE__
#else
#error "compile_date is not set"
#define compile_date	"04/07/71"
#endif
#endif
int use_umulh_for_div;
bool do_scheduling = TRUE;
bool fail_with_denormal_constant = TRUE;
bool treat_denorm_specially = FALSE;
bool trap_all_fops = FALSE;
bool do_extern_adds = FALSE;

static int infoopt = FALSE;	/* set if the -V option has been invoked */
static bool produce_symbolic_assembler = FALSE;

void printinfo
    PROTO_Z ()
{
  (void)fprintf(stderr,"DRA TDF DEC Alpha/OSF1 translator %d.%d.%d:(TDF version %d.%d)\n",
		target_version,target_revision,target_patchlevel,
		MAJOR_VERSION,MINOR_VERSION);
  (void)fprintf(stderr,"reader %d.%d: ",reader_version,reader_revision);
  (void)fprintf(stderr,"construct %d.%d: \n",construct_version,
		construct_revision);
  (void)fprintf(stderr,"installer compilation %s\n",compile_date);
  (void)fprintf(stderr,"release: %s\n",RELEASE);
  return;
}

void out_rename
    PROTO_N ( ( oldid,newid ) )
    PROTO_T ( char *oldid X char *newid )
{
  UNUSED(oldid);
  UNUSED(newid);
  return;
}

int get_switch
    PROTO_N ( ( option,range_max ) )
    PROTO_T ( char option X int range_max )
{
  int val = option - '0';
  if (val>=0 && val <= range_max){
    return val;
  }	
  else {
    (void)fprintf(stderr,"alphatrans: error : illegal option value : 0 .. %d expected\n",range_max);
    exit(EXIT_FAILURE);
  }
  return 0;
}



/*
  Reads and processes a command line option.
*/
void process_flag
    PROTO_N ( ( option ) )
    PROTO_T ( char *option )
{
  switch(option[1]){
   case 'A':
    /* alloca switching */
    do_alloca = get_switch(option[2],1);
    break;
   case 'B':
    /* big floating point constants -> infinity */
    break;
   case 'C':
    do_loopconsts = get_switch(option[2],1);
    break;
   case 'D':
    failer("no PIC code available");
    exit(EXIT_FAILURE);
   case 'E':
    extra_checks = 0;
    break;
   case 'F':
    do_foralls = get_switch(option[2],1);
    break;
   case 'H':
    diagnose = 1;
    do_inlining = 0;
    do_loopconsts = 0;
    do_foralls = 0;
    do_dump_opt = 0;
    do_alloca = 0;
    break;
   case 'I':
    do_inlining=get_switch(option[2],1);
    break;
   case 'K':
    fprintf(stderr,"alphatrans: [-K..] -> only one kind of processor is supported\n");
    break;
   case 'M':
    strict_fl_div = get_switch(option[2],1);
    break;
   case 'P':
    do_profile = 1;
    break;
   case 'Q':
    exit(EXIT_SUCCESS);
    break;
   case 'R':
    round_after_flop = get_switch(option[2],1);
    break;
   case 'S':
    produce_symbolic_assembler = TRUE;
    break;
   case 'U':
    do_unroll = get_switch(option[2],1);
    break;
   case 'X':
    do_inlining=0;
    do_loopconsts=0;
#ifdef USE_OLD_UNROLLER
    dostrengths=0;
#endif
    do_special_fns=0;
    do_foralls=0;
    do_dump_opt=0;
    break;
   case 'V':
   case 'v':
   case 'i':
    printinfo();
    infoopt = TRUE;
    break;
   case 'W':
    writable_strings = get_switch(option[2],1);
    break;
   case 'Z':
    report_versions = 1;
    break;
   case 'u':
    use_umulh_for_div = get_switch(option[2],1);
    break;
   case 's':
    do_scheduling = get_switch(option[2],1);
    break;
   case 'd':	
    /* handle IEEE denormals */
     treat_denorm_specially = TRUE;
     switch(get_switch(option[2],2)){
     case 0: /* replace denormal const with 0.0 (don't do this) */
       alphawarn("Unsupported denormal switch");
       fail_with_denormal_constant = FALSE;
       break;
     case 1: /* error if denormal const is encountered */
       fail_with_denormal_constant = TRUE;
       break;
     case 2: 
     /* handle denormals properly (and slowly), by 
       stopping the interleaving of floating point 
       operations and using the OS exception handler */
       treat_denorm_specially = FALSE;
       trap_all_fops = TRUE;
       break;
     }
     break;
  default:
    alphafail(ILLEGAL_FLAG,option);
    break;
  }
}

bool BIGEND = (little_end == 0);
bool do_tlrecursion = 1;
int currentfile = -1;
int mainfile=0;
int majorno = 3;
int minorno = 11;

#define MIN_COMMAND_LINE_ARGS 4

int main
    PROTO_N ( ( argc,argv ) )
    PROTO_T ( int argc X char *argv[] )
{
  int i;
  int num_flags=0;
  char *aname;	/* name of file for assembly output */
  char *dname;	/* name of file to hold symbol table */
  char *baname;
  char *tname;
  do_inlining=0;
  redo_structfns=1;
  do_foralls=0;
  do_alloca=1;
#if DO_NEW_DIVISION 
  use_umulh_for_div = 1;
#else
  use_umulh_for_div = 0;
#endif
  /* read command line options */
  for(i=1;i<argc;++i){
    if(argv[i][0] == '-'){
      num_flags++;
      process_flag(argv[i]);
    }
  }
  if((argc-num_flags)<MIN_COMMAND_LINE_ARGS){
    if(infoopt){
      exit(EXIT_SUCCESS);
    }
    else{
      alphafail(TOO_FEW_PARAMETERS);
    }
  }

  /* the files are passed in the order .t .G .T .s */

  if(produce_symbolic_assembler){
      aname = argv[argc-1];
      as_file = open_file(aname,WRITE);
      argc--;
  }
  baname = argv[argc-2];
  dname = argv[argc-1];
  tname = argv[argc-3];

  ba_file = open_file(baname,WRITE);
  if(!initreader (tname)) alphafail(OPENING_T_FILE,tname);
  init_flpt();
#include "inits.h"
  top_def = (dec*)0;
  local_prefix="$$";
  name_prefix="";
#if DO_SCHEDULE
  if(do_scheduling){
    initialise_scheduler();
  }
#endif

  (void)d_capsule();
  output_symtab(dname);
#if DO_SCHEDULE
  if(do_scheduling){
/*    schduler_finished();*/
  }
#endif
  if (as_file != NULL)
    close_file(as_file);
  close_file(ba_file);
  return (SUCCESS);
}







