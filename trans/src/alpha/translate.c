/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <shared/error.h>
#include <shared/xalloc.h>

#include <local/ash.h>

#include <reader/code.h>

#include <construct/installglob.h>
#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shape.h>

#include <refactor/optimise.h>

#include <symtab/symconst.h>
#include <symtab/syms.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include "tempdecs.h"
#include "weights.h"
#include "procrectypes.h"
#include "regalloc.h"
#include "procrecs.h"
#include "make_code.h"
#include "code_here.h"
#include "eval.h"
#include "bitsmacs.h"
#include "scan.h"
#include "main.h"
#include "frames.h"
#include "reg_defs.h"
#include "stabs_diag3.h"
#include "out_ba.h"
#include "ibinasm.h"
#include "directives.h"
#include "pseudo.h"
#include "outofline.h"
#include "alpha_ins.h"
#include "labels.h"
#include "inst_fmt.h"
#include "regexps.h"
#include "getregs.h"
#include "extern_adds.h"
#include "locate.h"
#include "translate.h"
#include "localexpmacs.h"

bool do_extern_adds;

procrec * procrecs;
dec ** main_globals;
int main_globals_index;

extern filename * fds;

/*
  return the appropriate storage class based on the size parameter.
  The size is given in bytes.
*/
char *
storage_class(int size)
{
  switch(size){
    case 1: return s_byte;
    case 2: return s_word;
    case 4: return s_long;
    case 8: return s_quad;
    default:
    error(ERR_FATAL, "illegal size for global");
  }
}

/*
  used to prevent illegal use of the 
  various identifiers reserved by the alpha
  assembler
*/
static bool
not_reserved(char *id)
{

  if (!strcmp(id, "edata"))  return 0;
  if (!strcmp(id, "etext"))  return 0;
  if (!strcmp(id, "end"))    return 0;
  if (!strcmp(id, "_ftext")) return 0;
  if (!strcmp(id, "_fdata")) return 0;
  if (!strcmp(id, "_fbss"))  return 0;
  if (!strcmp(id, "_gp"))    return 0;

  if (!strcmp(id, "_procedure_table"))        return 0;
  if (!strcmp(id, "_procedure_string_table")) return 0;

  return 1;
}


/* return true if sha has an exposed nof component, false otherwise */
bool
varsize(shape sha)
{
  return name(sha)==nofhd;
}

static int current_symno;

static void
add_odd_bits(outofline *r)
{
  space sp;
  if (r != (outofline*)NULL) {
    if (r -> next == (outofline*)NULL){
    }
    add_odd_bits(r -> next);
  }
  else {
    return;
  }	
  set_label(r->labno);
  sp = r->sp;
  clear_all();
  make_code(r->body,sp,r->dest,ptno(r->jr));
  if (name(sh(r->body)) != bothd)  {
    integer_branch(i_br,31,ptno(r->jr));
  }
}

void
code_it(dec *my_def)
{
  exp tg = my_def -> dec_u.dec_val.dec_exp;
  char *id = my_def -> dec_u.dec_val.dec_id;
  int symdef = my_def ->dec_u.dec_val.sym_number;
  bool extnamed =  my_def -> dec_u.dec_val.extnamed;
  static  space tempspace = {
    0, 0
    };
  if (symnos[symdef] >=0){
    if (son (tg) != NULL && (!extnamed || !is_comm(son(tg)))) {
      if (name (son (tg)) == proc_tag || name(son(tg)) == general_proc_tag) {
	diag_descriptor * dd =  my_def -> dec_u.dec_val.diag_info;
	/* compile code for proc */
	set_text_section();
	if(dyn_init && !strncmp("__I.TDF",id,7)) {
	  /* we have an initialisation procedure, just change its name 
	     and the linker will do the rest */
	  char *new_id = (char*)xcalloc(strlen(id)+strlen("__init_")+1,
					sizeof(char));
	  strcpy(new_id,"__init_");
	  strcat(new_id,id);
	  xfree(id);
	  id = new_id;
	  my_def -> dec_u.dec_val.dec_id = id;
	}
	if (diag != DIAG_NONE && dd != (diag_descriptor*)NULL) {
	  sourcemark *sm = &dd -> data.id.whence;
	  set_file(sm->file->file.ints.chars,2);
	  stabd(fscopefile = find_file(sm->file->file.ints.chars),
		sm->line_no.nat_val.small_nat);
	}
	else if (diag != DIAG_NONE){
	  out_value(0,ifile,make_INT64(0,1),0);
	  out_data("NOFILE.c",strlen("NOFILE.c"));
	  out_loc(0,0);
	  
#if 0
	  init_table_space(1,0);
	  if (nofds == 0) {
	    nofds = 1;
	    symnosforfiles();
	    nofds = 0;
	  }
	  stabd(0,1);
#endif
	}
	
	if (as_file){
	  asm_printop(".ent %s\n%s:", id, id);
	}	
	out_ent(current_symno = symnos[symdef],ient,2);
	out_common(symnos[symdef],ilabel);
	out_option(1,(diag != DIAG_NONE)?1:2);
	symnoforstart (symdef, currentfile);
	settempregs (son(tg));
	code_here (son (tg), tempspace, nowhere);
	if(diag != DIAG_NONE && dd != (diag_descriptor*)NULL){
	  stabd(fscopefile,currentlno+1);
	}
	if (as_file){
	  asm_printop(".end %s", id);
	}
	out_common(symnoforend(my_def,currentfile),iend);
      }
      else {			/* global values */
	exp c = son (tg);
	(void)evaluated (c,(isvar (tg))?(-symdef - 1):symdef+1);
      }
    }
    else {	/* global declarations but no definitions or is_comm */
      long  size;
      shape s = my_def -> dec_u.dec_val.dec_shape;
      bool vs = son(tg)!=NULL /* ie is_comm */;
      size = (shape_size(s) + 7) >> 3;
      if ((isvar(tg) || name(s) != prokhd) && not_reserved (id)) {
	if (vs /*&& size != 0*/) {
	  if (as_file){
	    asm_printop(".comm %s %ld", id, size==0?4:size);
	  }
	  out_value(symnos[symdef],icomm,(size==0)?4:size, 0);
	}	
	else {
	  if (as_file){
	    asm_printop(".extern %s %ld", id, size);
	  }
	  out_value(symnos[symdef],iextern,size,1);
	}
      }
      else if (son (tg) == NULL && !extnamed) {
	if (as_file){
	  asm_printf( "\n\t.lcomm\t%s %ld\n", id, size);
	}
	out_value(symnos[symdef],ilcomm,size,1);
      }			
    }
  
  /*  NO! the pt fields are wrong!
      kill_exp(son(tg), son(tg));
      */
  }
/*end:*/
  /*son(tg) = NULL;*/
  my_def -> dec_u.dec_val.processed = 1;
}

static void
mark_unaliased(exp e)
{
  exp p = pt (e);
  bool ca = 1;
  while (p != NULL && ca) {
    if (bro(p)==NULL || (!(last (p) && name (bro (p)) == cont_tag) &&
	 !(!last (p) && last (bro (p)) && name (bro (bro (p))) == ass_tag)))
      ca = 0;
    p = pt (p);
  }
  if (ca)
    setcaonly (e);
}

/*
  Return the tag with name 'name'
*/
baseoff
find_tag(char *name)
{
  int i;
  for(i=0; i<main_globals_index; i++){
    exp tag = main_globals[i]->dec_u.dec_val.dec_exp;
    char * id = main_globals[i]->dec_u.dec_val.dec_id;
    if(!strcmp(id,name)) return boff(tag);
  }
  printf("%s\n: ",name);
  error(ERR_FATAL, "tag not declared");
}


void
translate_capsule(void)
{
  dec * my_def;
  int noprocs;
  int i;
  extern exp* usages;
  setregalt (nowhere.answhere, NO_REG);
  nowhere.ashwhere.ashsize = 0;
  nowhere.ashwhere.ashsize = 0;
  opt_all_exps ();
    /* mark static unaliased */
  for (my_def = top_def; my_def != NULL; my_def = my_def -> def_next) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son (crt_exp) != NULL && !my_def -> dec_u.dec_val.extnamed &&
	isvar (crt_exp)) {
      mark_unaliased (crt_exp);
    }
  }

  if(diag != DIAG_NONE){
    /* remove static functions with no uses if compiling with diagnostics */
    dec **ptr_def = &top_def;
    while(*ptr_def) {
      exp crt_exp = (*ptr_def)->dec_u.dec_val.dec_exp;
      if(son(crt_exp) != NULL) {
	if(((name(son(crt_exp)) == general_proc_tag) || 
	   (name(son(crt_exp)) == proc_tag)) &&
	   ((no(crt_exp) == 0) && (diag != DIAG_NONE) && !(*ptr_def)->dec_u.dec_val.extnamed)) {
	  dec *old_ptr = *ptr_def;
	  *ptr_def = (*ptr_def)->def_next;
	  free(old_ptr);
	}
	else {
	  ptr_def = &((*ptr_def)->def_next);
	}
      }
      else {
	ptr_def = &((*ptr_def)->def_next);
      }
    }
  }

  noprocs = 0;
  for (my_def = top_def; my_def != NULL; my_def = my_def -> def_next) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son (crt_exp) != NULL && (name (son (crt_exp)) == proc_tag ||
	name(son(crt_exp))==general_proc_tag)) {
      noprocs++;
    }
  }
  /* count procs */

  procrecs = (procrec *) xcalloc (noprocs, sizeof (procrec));
  noprocs = 0;

  for (my_def = top_def; my_def != NULL; my_def = my_def -> def_next) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son (crt_exp) != NULL && (name (son (crt_exp)) == proc_tag
				    || name(son(crt_exp))==general_proc_tag)) {
      no (son (crt_exp)) = noprocs++;
      /* put index into procrecs in no(proc) */
    }
  }
  if(do_extern_adds) {
    usages = (exp*)xcalloc(noprocs, sizeof(exp));
    for (my_def = top_def; my_def != NULL; my_def = my_def -> def_next) {
      exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
      if (son(crt_exp) == NULL && isvar(crt_exp) ) {
	global_usages(crt_exp, noprocs);
	/* try to identify globals ptrs in procs */
      }
    }
  }
  

  if(diag != DIAG_NONE){
    int l,i;
    char * ftmp;
    init_table_space(nofds,noprocs);
    add_dense_no(0,0);
    add_dense_no(0,0);
#if 1
    for(i=0; i<nofds; ++i) {
      l = (int)strlen (fds[i]->file.ints.chars);
      ftmp = xcalloc(l+1,sizeof(char));
      ftmp[0] = 'X';
      strcpy(ftmp+1,fds[i]->file.ints.chars);
      fds[i]->file.ints.chars = (char*)xrealloc((void*)fds[i]->file.ints.chars,
						(l+1)*sizeof(char));
      strcpy(fds[i]->file.ints.chars,ftmp);	
      xfree(ftmp);
    }
#endif
    symnosforfiles();
    stab_types();
  }
  else{
    init_table_space(1,noprocs);
    add_dense_no(0,0);
    add_dense_no(0,0);
    (void)new_lsym_d ("NOFILE.c",0,stFile,scText,0,0);
  }
  for (my_def = top_def; my_def != NULL; my_def = my_def -> def_next) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son (crt_exp) != NULL && (name (son (crt_exp)) == proc_tag
				    || name(son(crt_exp))==general_proc_tag)) {
      procrec * pr = &procrecs[no (son (crt_exp))];
      exp * st = &son(crt_exp);
      bool has_varargs = vascan(st);
      (*st)->dfile = "";
      if(has_varargs){
	set_has_c_vararg(*st);
      }
      else {
	clear_has_c_vararg(*st);
      }
      
      pr -> needsproc = scan (st, &st);
      pr->callee_size = (callee_size + 63)&~63;
    }
  }


  /* calculate the break points for register allocation and do it */
  for (my_def = top_def; my_def != NULL; my_def = my_def -> def_next) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son (crt_exp) != NULL && (name (son (crt_exp)) == proc_tag
				    || name(son(crt_exp))==general_proc_tag)){
      procrec * pr = &procrecs[no (son (crt_exp))];
      needs * ndpr = & pr->needsproc;
      long pprops = (ndpr->propsneeds);
      bool leaf = (pprops & anyproccall) == 0;
      spacereq forrest;
      int   freefixed = 6;
      int   freefloat = 8;	
      setframe_flags(son(crt_exp), leaf);
      /*      if(Has_vcallees || proc_has_gen_call(son(crt_exp))) freefixed--;*/
      if(Has_vcallees) freefixed--;
      freefixed += (Has_fp==0);
      if (!No_S) (void)weightsv (1.0, bro (son (son (crt_exp))));
      /* estimate usage of tags in body of proc */
      forrest = regalloc (bro (son (son (crt_exp))), freefixed, freefloat, 0);
      /* reg and stack allocation for tags */
      pr -> spacereqproc = forrest;
      setframe_info(son(crt_exp));
    }
  }
  /* put defs in main globals and set up symnos*/
  main_globals_index = 0;
  for (my_def = top_def; my_def != NULL; my_def = my_def -> def_next) {
    main_globals_index++;
  }
  
  data_lab = (main_globals_index > 33)?main_globals_index:33;
  main_globals = (dec**)xcalloc(main_globals_index, sizeof(dec*));
  symnos = (int *) xcalloc (main_globals_index, sizeof (int));
  
  my_def = top_def;
  for (i=0; i < main_globals_index; i++) {
    main_globals[i] = my_def;
    my_def = my_def -> def_next;
  }
  	
  /* ... and set in the position and "addresses" of the externals */
  for (i = 0; i < main_globals_index; i++) {
    exp tg = main_globals[i] -> dec_u.dec_val.dec_exp;
    char *id = main_globals[i] -> dec_u.dec_val.dec_id;
    bool extnamed = main_globals[i] -> dec_u.dec_val.extnamed;
    main_globals[i] ->dec_u.dec_val.sym_number = i;	    
    /* if not NULL */
    if ( no (tg) != 0 || (extnamed && son(tg) != NULL) 
	 || !strcmp(id,"__alpha_errhandler") || !strcmp(id,"__alpha_stack_limit")) {
      if(no(tg)==1 && son(tg)==NULL && 
	 (bro(pt(tg)) == NULL || 
	  name(bro(pt(tg)))==101 || name(bro(pt(tg)))==102 ) 
          /* diagnostics only! */ ) {
	symnos[i]= -1;
      }
      else {	 
	no (tg) = (i + 1) * 64 + 32;
	symnos[i] = symnoforext (main_globals[i], mainfile);
      }
    }
    else{
      /* only applies to alphatrans */
      symnos[i] = -1;
/*      symnos[i] = symnoforext (main_globals[i],mainfile);*/
    }
  }

  if(as_file){
    asm_comment("produced by TDF->Alpha/OSF1 installer");
    asm_printop(".ugen");
  }
  out_common(0,iugen);
  
  if (assembler & ASM_OSF1) {
    if(as_file){
      asm_printop(".verstamp %d %d",majorno,minorno);
    }
  }

  out_verstamp(majorno,minorno);

  out_option(1,diag != DIAG_NONE?1:2);

  if (diag != DIAG_NONE && nofds!=0) {
    stab_file (0);
  }
  else{
    currentfile = 0;
  }

  /* 
     compile procedures, evaluate constants, put in the 
     .comm entries for undefined objects 
  */

  for (my_def = top_def; my_def != NULL; my_def = my_def -> def_next) {
    exp tg = my_def -> dec_u.dec_val.dec_exp;
    char *id = my_def -> dec_u.dec_val.dec_id;
    bool extnamed = my_def -> dec_u.dec_val.extnamed;
    if (son (tg) != NULL && (extnamed || no (tg) != 0 || 
			       !strcmp (id, "main"))) {
      if (extnamed) {
	/* globalise all global names  */
	if(dyn_init && !strncmp("__I.TDF",id,7)) {
	  char *new_id = (char*)xcalloc(strlen(id)+strlen("__init_")+1,
					sizeof(char));
	  strcpy(new_id,"__init_");
	  strcat(new_id,id);
	  xfree(id);
	  id = new_id;
	  my_def->dec_u.dec_val.dec_id = new_id;
	}
	
	if (as_file){
	  asm_printop(".globl %s", id);
	}
	out_common(symnos[my_def->dec_u.dec_val.sym_number] ,iglobal);
      }
    }
  }
     
  for (my_def = top_def; my_def != NULL; my_def = my_def -> def_next) {
    if (!my_def -> dec_u.dec_val.processed){
      code_it (my_def);
    }
  }
}

