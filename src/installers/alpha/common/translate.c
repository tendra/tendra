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


/* 	$Id: translate.c,v 1.2 1998/02/04 10:43:34 release Exp $	 */

#ifndef lint
static char vcid[] = "$Id: translate.c,v 1.2 1998/02/04 10:43:34 release Exp $";
#endif /* lint */

/*
$Log: translate.c,v $
 * Revision 1.2  1998/02/04  10:43:34  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:56:01  release
 * First version to be checked into rolling release.
 *
 * Revision 1.24  1996/03/25  14:35:45  john
 * introduced do_extern_adds
 *
 * Revision 1.23  1996/02/15  09:58:29  john
 * Fixed handling of initialisation procedures
 *
 * Revision 1.22  1996/01/23  16:59:10  john
 * Fix to diagnostics
 *
 * Revision 1.21  1996/01/18  09:33:31  john
 * Fix diagnostics
 *
 * Revision 1.20  1996/01/17  10:05:07  john
 * Fix to diagnostics
 *
 * Revision 1.19  1996/01/17  09:31:53  john
 * Fix to diagnostics
 *
 * Revision 1.18  1995/12/04  09:14:16  john
 * Fix to diagnostics
 *
 * Revision 1.17  1995/11/14  15:40:12  john
 * Implemented dynamic initialisations
 *
 * Revision 1.16  1995/11/13  12:44:45  john
 * Minor change
 *
 * Revision 1.15  1995/09/22  16:02:27  john
 * Changed special id's
 *
 * Revision 1.14  1995/09/04  16:27:08  john
 * Fix to general procs
 *
 * Revision 1.13  1995/08/21  08:46:45  john
 * Changed include files
 *
 * Revision 1.12  1995/08/04  15:51:29  john
 * Minor change
 *
 * Revision 1.11  1995/06/28  10:27:52  john
 * Hack to fix source file names for diagnostics.
 *
 * Revision 1.10  1995/06/21  14:25:47  john
 * Reformatting
 *
 * Revision 1.9  1995/06/15  08:33:56  john
 * Fixed syntax error
 *
 * Revision 1.8  1995/06/13  14:02:22  john
 * Fixed s-register allocation with frame pointer & added support for
 * trap error treatment
 *
 * Revision 1.7  1995/05/25  15:33:39  john
 * Cosmetic change
 *
 * Revision 1.6  1995/05/23  15:38:28  john
 * Changed Version information
 *
 * Revision 1.5  1995/05/16  10:56:33  john
 * Changes for spec 3.1
 *
 * Revision 1.4  1995/04/10  14:14:16  john
 * Minor change
 *
 * Revision 1.3  1995/04/07  11:07:13  john
 * Changed assembler output (mainly scheduling changes).
 *
 * Revision 1.2  1995/03/29  14:06:31  john
 * Changes to keep tcheck happy
 *
 * Revision 1.1.1.1  1995/03/23  10:39:25  john
 * Entered into CVS
 *
 * Revision 1.13  1995/03/23  10:16:41  john
 * Added support for scheduler
 *
 * Revision 1.12  1995/01/26  13:52:12  john
 * Removed unused variable and added include files
 *
 * Revision 1.11  1995/01/10  09:43:56  john
 * Added code for out-of-line optimisation
 *
*/

#include "config.h"
#include "common_types.h"
#include "installglob.h"
#include "tags.h"
#include "exp.h"
#include "expmacs.h"
#include "optimise.h"
#include "flags.h"
#include "shapemacs.h"
#include "tempdecs.h"
#include "weights.h"
#include "procrectypes.h"
#include "regalloc.h"
#include "procrecs.h"
#include "coder.h"
#include "code_here.h"
#include "eval.h"
#include "bitsmacs.h"
#include "scan.h"
#include "xalloc.h"
#include "main.h"
#include "frames.h"
#include "reg_defs.h"
#include "symbol.h"
#include "alphadiags.h"
#include "out_ba.h"
#include "syms.h"
#include "ibinasm.h"
#include "machine.h"
#include "fail.h"
#include "directives.h"
#include "pseudo.h"
#include "outofline.h"
#include "alpha_ins.h"
#include "labels.h"
#include "inst_fmt.h"
#include "regexps.h"
#include "getregs.h"
#include "extern_adds.h"
#include "version.h"
#include "locate.h"
#include "translate.h"
#include "cross_config.h"

#if DO_SCHEDULE
#include "scheduler.h"
#endif

#ifndef CROSS_INCLUDE
#include <symconst.h>
#else
#include CROSS_INCLUDE/symconst.h>
#endif

procrec * procrecs;
dec ** main_globals;
int main_globals_index;

extern filename * fds;

/*
  return the appropriate storage class based on the size parameter.
  The size is given in bytes.
*/
char *storage_class
    PROTO_N ( ( size ) )
    PROTO_T ( int size )
{
  switch(size){
    case 1:{
      return s_byte;
    }
    case 2:{
      return s_word;
    }
    case 4:{
      return s_long;
    }
    case 8:{
      return s_quad;
    }
    default:
    failer("illegal size for global");
  }
  return s_byte;
}


ash ashof
    PROTO_N ( ( s ) )
    PROTO_T ( shape s )
{
  ash a;
  a.ashsize = shape_size(s);
  a.ashalign = shape_align(s);
  return a;
}

/*
  used to prevent illegal use of the 
  various identifiers reserved by the alpha
  assembler
*/
static bool not_reserved
    PROTO_N ( ( id ) )
    PROTO_T ( char *id )
{

  if (!strcmp (id, "edata"))
    return (0);
  if (!strcmp (id, "etext"))
    return (0);
  if (!strcmp (id, "end"))
    return (0);
  if (!strcmp (id, "_ftext"))
    return (0);
  if (!strcmp (id, "_fdata"))
    return (0);
  if (!strcmp (id, "_fbss"))
    return (0);
  if (!strcmp (id, "_gp"))
    return (0);
  if (!strcmp (id, "_procedure_table"))
    return (0);
  if (!strcmp (id, "_procedure_string_table"))
    return (0);
  return (1);
}


/* return true if sha has an exposed nof component, false otherwise */
bool varsize
    PROTO_N ( ( sha ) )
    PROTO_T ( shape sha )
{
  return (name(sha)==nofhd);
}

static int current_symno;

static void add_odd_bits
    PROTO_N ( ( r ) )
    PROTO_T ( outofline *r )
{
  space sp;
  if (r != (outofline*)nilexp) {
    if (r -> next == (outofline*)nilexp){
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
  return;
}

void code_it
    PROTO_N ( ( my_def ) )
    PROTO_T ( dec *my_def )
{
  exp tg = my_def -> dec_u.dec_val.dec_exp;
  char *id = my_def -> dec_u.dec_val.dec_id;
  char * outline;
  int symdef = my_def ->dec_u.dec_val.sym_number;
  bool extnamed =  my_def -> dec_u.dec_val.extnamed;
  static  space tempspace = {
    0, 0
    };
  if (symnos[symdef] >=0){
    if (son (tg) != nilexp && (!extnamed || !is_comm(son(tg)))) {
      if (name (son (tg)) == proc_tag || name(son(tg)) == general_proc_tag) {
	diag_descriptor * dd =  my_def -> dec_u.dec_val.diag_info;
	/* compile code for proc */
	set_text_section();
	if(!strncmp("__I.TDF",id,7)) {
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
	if (diagnose && dd != (diag_descriptor*)NULL) {
	  sourcemark *sm = &dd -> data.id.whence;
	  set_file(sm->file->file.ints.chars,2);
	  stabd(fscopefile = find_file(sm->file),
		sm->line_no.nat_val.small_nat);
	}
	else if (diagnose){
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
#if DO_SCHEDULE
	  outline = (char*)xcalloc(80,sizeof(char));
	  sprintf(outline,"\t.ent\t%s\n%s:\n", id, id);
#else	
	  fprintf(as_file, "\t.ent\t%s\n%s:\n", id, id);
#endif
	}	
	output_instruction(class_null,outline,
			   out_ent(current_symno = symnos[symdef],ient,2));
	output_instruction(class_null,(char*)NULL,
			   out_common(symnos[symdef],ilabel));
	output_instruction(class_null,(char*)NULL,
			   out_option(1,(diagnose)?1:2));
	symnoforstart (symdef, currentfile);
	settempregs (son(tg));
#if DO_SCHEDULE
	start_new_capsule(true);
#endif
	code_here (son (tg), tempspace, nowhere);
#if DO_SCHEDULE
	close_capsule();
#endif
	if(diagnose && dd != (diag_descriptor*)NULL){
	  stabd(fscopefile,currentlno+1);
	}
	if (as_file){
#if DO_SCHEDULE
	  outline = (char*)xcalloc(strlen(id)+10,sizeof(char));
	  sprintf(outline,"\t.end\t%s\n",id);
#else
	  fprintf (as_file, "\t.end\t%s\n", id);
#endif
	}
	output_data(outline,out_common(symnoforend(my_def,currentfile),iend));
      }
      else {			/* global values */
	exp c = son (tg);
#if DO_SCHEDULE
	start_new_capsule(false);
#endif
	(void)evaluated (c,(isvar (tg))?(-symdef - 1):symdef+1);
#if DO_SCHEDULE
	close_capsule();
#endif
      }
    }
    else {	/* global declarations but no definitions or is_comm */
      long  size;
      shape s = my_def -> dec_u.dec_val.dec_shape;
      bool vs = son(tg)!=nilexp /* ie is_comm */;
      size = (shape_size(s) + 7) >> 3;
      if ((isvar(tg) || name(s) != prokhd) && not_reserved (id)) {
	if (vs /*&& size != 0*/) {
	  if (as_file){
#if DO_SCHEDULE
	    outline = (char*)xcalloc(80,sizeof(char));
	    sprintf(outline,"\t.comm\t%s %ld\n",id,(size==0)?4:size);
#else	
	    fprintf (as_file, "\t.comm\t%s %ld\n", id, size==0?4:size);
#endif
	  }
	  output_instruction(class_null,outline,
			     out_value(symnos[symdef],icomm,(size==0)?4:size,
				       0));
	}	
	else {
	  if (as_file){
#if !DO_SCHEDULE
	    fprintf (as_file, "\t.extern\t%s %ld\n", id,
		     size);
#else	
	    outline = (char*)xcalloc(80,sizeof(char));
	    sprintf(outline,"\t.extern\t%s %ld\n",id,size);
#endif
	  }
	  output_instruction(class_null,outline,
			     out_value(symnos[symdef],iextern,size,1));
	}
      }
      else if (son (tg) == nilexp && !extnamed) {
	if (as_file){
#if !DO_SCHEDULE
	  fprintf (as_file, "\n\t.lcomm\t%s %ld\n", id, size);
#else
	  outline = (char*)xcalloc(80,sizeof(char));
	  sprintf(outline,"\n\t.lcomm\t%s %ld\n", id, size);
#endif
	}
	output_instruction(class_null,outline,
			   out_value(symnos[symdef],ilcomm,size,1));
      }			
    }
  
  /*  NO! the pt fields are wrong!
      kill_exp(son(tg), son(tg));
      */
  }
/*end:*/
  /*son(tg) = nilexp;*/
  my_def -> dec_u.dec_val.processed = 1;
  return;
}

static void mark_unaliased
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
  exp p = pt (e);
  bool ca = 1;
  while (p != nilexp && ca) {
    if (bro(p)==nilexp || (!(last (p) && name (bro (p)) == cont_tag) &&
	 !(!last (p) && last (bro (p)) && name (bro (bro (p))) == ass_tag)))
      ca = 0;
    p = pt (p);
  }
  if (ca)
    setcaonly (e);
  return;
}

/*
  Return the tag with name 'name'
*/
baseoff find_tag
    PROTO_N ( ( name ) )
    PROTO_T ( char *name )
{
  int i;
  for(i=0; i<main_globals_index; i++){
    exp tag = main_globals[i]->dec_u.dec_val.dec_exp;
    char * id = main_globals[i]->dec_u.dec_val.dec_id;
    if(!strcmp(id,name)) return boff(tag);
  }
  printf("%s\n: ",name);
  failer("tag not declared");
  exit(EXIT_FAILURE);
}


void translate_capsule
    PROTO_Z ()
{
  dec * my_def;
  int noprocs;
  int i;
  char * outline = (char*)xcalloc(80,sizeof(char));
  extern exp* usages;
  setregalt (nowhere.answhere, NO_REG);
  nowhere.ashwhere.ashsize = 0;
  nowhere.ashwhere.ashsize = 0;
  opt_all_exps ();
    /* mark static unaliased */
  my_def = top_def;
  while (my_def != (dec *) 0) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son (crt_exp) != nilexp && !my_def -> dec_u.dec_val.extnamed &&
	isvar (crt_exp)) {
      mark_unaliased (crt_exp);
    }
    my_def = my_def -> def_next;
  }

  if(diagnose){
    /* remove static functions with no uses if compiling with diagnostics */
    dec **ptr_def = &top_def;
    while(*ptr_def) {
      exp crt_exp = (*ptr_def)->dec_u.dec_val.dec_exp;
      if(son(crt_exp) != nilexp) {
	if(((name(son(crt_exp)) == general_proc_tag) || 
	   (name(son(crt_exp)) == proc_tag)) &&
	   ((no(crt_exp) == 0) && (diagnose) && !(*ptr_def)->dec_u.dec_val.extnamed)) {
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
  my_def = top_def;
  while (my_def != (dec *) 0) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son (crt_exp) != nilexp && (name (son (crt_exp)) == proc_tag ||
	name(son(crt_exp))==general_proc_tag)) {
      noprocs++;
    }
    my_def = my_def -> def_next;
  }
  /* count procs */

  procrecs = (procrec *) xcalloc (noprocs, sizeof (procrec));
  noprocs = 0;

  my_def = top_def;
  while (my_def != (dec *) 0) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son (crt_exp) != nilexp && (name (son (crt_exp)) == proc_tag
				    || name(son(crt_exp))==general_proc_tag)) {
      no (son (crt_exp)) = noprocs++;
      /* put index into procrecs in no(proc) */
    }
    my_def = my_def -> def_next;
  }
  if(do_extern_adds) {
    usages = (exp*)xcalloc(noprocs, sizeof(exp));
    my_def = top_def;
    while (my_def != (dec *) 0) {
      exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
      if (son(crt_exp) == nilexp && isvar(crt_exp) ) {
	global_usages(crt_exp, noprocs);
	/* try to identify globals ptrs in procs */
      }
      my_def = my_def -> def_next;
    }
  }
  

  if(diagnose){
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
  my_def = top_def;
  while (my_def != (dec *) 0) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son (crt_exp) != nilexp && (name (son (crt_exp)) == proc_tag
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
    my_def = my_def -> def_next;
  }


  /* calculate the break points for register allocation and do it */
  my_def = top_def;
  while (my_def != (dec *) 0) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son (crt_exp) != nilexp && (name (son (crt_exp)) == proc_tag
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
    my_def = my_def -> def_next;
  }
  /* put defs in main globals and set up symnos*/
  my_def = top_def;
  main_globals_index = 0;
  while (my_def != (dec*) 0) {
    main_globals_index++;
    my_def = my_def -> def_next;
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
    /* if not nilexp */
    if ( no (tg) != 0 || (extnamed && son(tg) != nilexp) 
	 || !strcmp(id,"__alpha_errhandler") || !strcmp(id,"__alpha_stack_limit")) {
      if(no(tg)==1 && son(tg)==nilexp && 
	 (bro(pt(tg)) == nilexp || 
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
    fprintf(as_file," # produced by TDF->Alpha/OSF1 installer\n");
    fprintf(as_file," # installer version %d.%d.%d\n",target_version,
	    target_revision,target_patchlevel);
    /*comment(" # produced by TDF->Alpha/OSF1 installer\n");*/
#if !DO_SCHEDULE
    fprintf(as_file,"\t.ugen\n");
#else
    sprintf(outline,"\t.ugen\n");
#endif
  }
#if DO_SCHEDULE
  output_data(outline,out_common(0,iugen));
#else
  out_common(0,iugen);
#endif
  
  if(as_file){
#if !DO_SCHEDULE
    fprintf(as_file,"\t.verstamp %d %d\n",majorno,minorno);
#else
    outline = (char*)xcalloc(30,sizeof(char));
    sprintf(outline,"\t.verstamp %d %d\n",majorno,minorno);
#endif
  }

#if DO_SCHEDULE
  output_data(outline,out_verstamp(majorno,minorno));
#else
  out_verstamp(majorno,minorno);
#endif  

#if DO_SCHEDULE
  output_data((char*)NULL,out_option(1,diagnose?1:2));
#else
  out_option(1,diagnose?1:2);
#endif  

  if (diagnose && nofds!=0) {
    stab_file (0);
  }
  else{
    currentfile = 0;
  }

  /* 
     compile procedures, evaluate constants, put in the 
     .comm entries for undefined objects 
  */
  my_def = top_def;

#if DO_SCHEDULE
    start_new_capsule(false);
#endif
  while (my_def != (dec *) 0) {
    exp tg = my_def -> dec_u.dec_val.dec_exp;
    char *id = my_def -> dec_u.dec_val.dec_id;
    bool extnamed = my_def -> dec_u.dec_val.extnamed;
    if (son (tg) != nilexp && (extnamed || no (tg) != 0 || 
			       !strcmp (id, "main"))) {
      if (extnamed) {
	/* globalise all global names  */
	if(!strncmp("__I.TDF",id,7)) {
	  char *new_id = (char*)xcalloc(strlen(id)+strlen("__init_")+1,
					sizeof(char));
	  strcpy(new_id,"__init_");
	  strcat(new_id,id);
	  xfree(id);
	  id = new_id;
	  my_def->dec_u.dec_val.dec_id = new_id;
	}
	
	if (as_file){
#if DO_SCHEDULE
	  outline = (char*)xcalloc(strlen(id)+10,sizeof(char));
	  sprintf (outline,"\t.globl\t%s\n ",id);
#else
	  fprintf (as_file, "\t.globl\t%s\n", id);
#endif	
	}
	output_data(outline,out_common(symnos[my_def->dec_u.dec_val.sym_number]
				       ,iglobal));
      }
    }
    my_def = my_def -> def_next;
  }
#if DO_SCHEDULE
    close_capsule();
#endif
     
  my_def = top_def;
#if DO_SCHEDULE
  setnoreorder();
#endif
  while (my_def != (dec *) 0) {
    if (!my_def -> dec_u.dec_val.processed){
      code_it (my_def);
      my_def = my_def -> def_next;
    }
  }
#if DO_SCHEDULE
  schedule_block();
#endif
  return;
}

void translate_unit
    PROTO_Z ()
{
  if (separate_units){
    dec * my_def;
    translate_capsule();
    my_def = top_def;
    while (my_def != (dec *) 0) {
      exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
      no(crt_exp) = 0;
      pt(crt_exp) = nilexp;
      my_def = my_def -> def_next;
    }
    crt_repeat = nilexp;
    repeat_list = nilexp;
  }
  return;
}

void translate_tagdef
    PROTO_Z ()
{
  return;
}















