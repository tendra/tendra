/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <local/expmacs.h>

#include <symtab/symconst.h>
#include <symtab/syms.h>

#include <reader/codetypes.h>
#include <reader/basicread.h>

#include <construct/installglob.h>
#include <construct/machine.h>
#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shapemacs.h>
#include <construct/me_fns.h>

#include <main/flags.h>

#include <refactor/optimise.h>

#include "tempdecs.h"
#include "weights.h"
#include "procrectypes.h"
#include "regalloc.h"
#include "new_code.h"
#include "code_here.h"
#include "eval.h"
#include "bitsmacs.h"
#include "needs_scan.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "diag_out.h"
#include "extern_adds.h"
#include "mips_ins.h"
#include "main.h"
#include "frames.h"
#include "getregs.h"
#include "locate.h"

extern long aritherr_lab;
extern long stackerr_lab;


extern exp find_named_tg(char*, shape);
extern shape f_top;
extern shape f_proc;

procrec * procrecs;
dec ** main_globals;
int main_globals_index;

extern long fscopefile;
extern bool do_extern_adds;

ash ashof
(shape s)
{
	ash a;
	a.ashsize = shape_size(s);
	a.ashalign = shape_align(s);
	return a;
}


bool not_reserved
(char *id)
{
  /* various identifier reserved by MIPS */
  if (!strcmp(id, "edata"))
    return 0;
  if (!strcmp(id, "etext"))
    return 0;
  if (!strcmp(id, "end"))
    return 0;
  if (!strcmp(id, "_ftext"))
    return 0;
  if (!strcmp(id, "_fdata"))
    return 0;
  if (!strcmp(id, "_fbss"))
    return 0;
  if (!strcmp(id, "_gp"))
    return 0;
  if (!strcmp(id, "_procedure_table"))
    return 0;
  if (!strcmp(id, "_procedure_string_table"))
    return 0;
  return 1;
}





char varsize
(shape sha)
{
  return name(sha) ==nofhd;
}

int current_symno;

void globalise_name
(dec * my_def)
{
	char *id = my_def -> dec_u.dec_val.dec_id;
        if (!my_def -> dec_u.dec_val.extnamed) return;
	if (as_file)
	  fprintf(as_file, "\t.globl\t%s\n", id);
	out_common(symnos[my_def->dec_u.dec_val.sym_number], iglobal);

}

void code_it
(dec * my_def)
{
  exp tg = my_def -> dec_u.dec_val.dec_exp;
  char *id = my_def -> dec_u.dec_val.dec_id;
  long symdef = my_def ->dec_u.dec_val.sym_number;
  bool extnamed =  my_def -> dec_u.dec_val.extnamed;

  static  space tempspace = {
      0, 0
    };
  if (symnos[symdef] <0) goto end; /* ? unused symbols */

  if (son(tg)!= nilexp && (!extnamed || !is_comm(son(tg)))) {
    if (name(son(tg)) == proc_tag
		|| name(son(tg)) == general_proc_tag) {
        diag_descriptor * dd =  my_def -> dec_u.dec_val.diag_info;
	/* compile code for proc */
	if (as_file) {
	  fprintf(as_file,"\t.text\n\t.align 3\n");
	}


	out_common(0, itext);
	out_value(0, ialign, 3, 0);
	if (diag != DIAG_NONE) {
	 if (dd != (diag_descriptor*)0) {
	    sourcemark *sm = &dd -> data.id.whence;
	    stabd(fscopefile = find_file(sm->file->file.ints.chars),
	               sm->line_no.nat_val.small_nat);
	 }
	 else { stabd(0,1); /*no diagnostics for this proc */ }
	}

	globalise_name(my_def);

	if (as_file)fprintf(as_file, "\t.ent\t%s\n%s:\n", id, id);

	out_ent (current_symno = symnos[symdef], ient, 2);/* why 2? */
	out_common(symnos[symdef], ilabel);
	if (as_file) {
		fprintf(as_file,
			(diag != DIAG_NONE)? "\t.option O1\n" : "\t.option O2\n");
	}

	out_option(1,(diag != DIAG_NONE)? 1 : 2);

	symnoforstart(symdef, currentfile);
	settempregs(son(tg));
	code_here(son(tg), tempspace, nowhere);
	if (diag != DIAG_NONE && dd != (diag_descriptor*)0) {
		stabd(fscopefile, currentlno+1);
	}
	if (as_file)
	  fprintf(as_file, "\t.end\t%s\n", id);
	out_common(symnoforend(my_def, currentfile), iend);
    }
    else {			/* global values */

	exp c = son(tg);
	IGNORE evaluated(c,(isvar(tg))?(-symdef - 1): symdef + 1, my_def);


    };
  }
  else {	/* global declarations but no definitions or is_comm */
      long  size;
      shape s = (son(tg) ==nilexp)?my_def -> dec_u.dec_val.dec_shape :
				sh(son(tg));
      size = (shape_size(s) + 7) >> 3;

      if ((isvar(tg) || name(s)!= prokhd) && not_reserved(id)) {
	if ((son(tg)!= nilexp && is_comm(son(tg)))
		|| (son(tg) ==nilexp && varsize(sh(tg)))) {
	  if (size !=0) { /* ? ? ! ? */
	     globalise_name(my_def);
	     if (as_file)
	        fprintf(as_file, "\t.comm\t%s %ld\n", id, size);
	      out_value(symnos[symdef], icomm, size, 1);
	  }
	}
	else {
	  if (as_file)
	    fprintf(as_file, "\t.extern\t%s %ld\n", id,
		size);
	  out_value(symnos[symdef], iextern, size, 1);
	}
      }
      else
	if (son(tg) == nilexp && !extnamed) {
	  if (size !=0) { /* ? ? ! ? */
	      if (as_file)
	        fprintf(as_file, "\t.lcomm\t%s %ld\n", id, size);
	      out_value(symnos[symdef], ilcomm, size, 1);
	  }
	}

  }


end:
  my_def -> dec_u.dec_val.processed = 1;
  return;
}

void mark_unaliased
(exp e)
{
  exp p = pt(e);
  bool ca = 1;
  while (p != nilexp && ca) {
    if (bro(p) ==nilexp ||
      (!(last(p) && name(bro(p)) == cont_tag) &&
	!(!last(p) && last(bro(p)) && name(bro(bro(p))) == ass_tag)))
      ca = 0;
    p = pt(p);
  };
  if (ca)
    setcaonly(e);
  return;
}

void remove_unused
(void)
{ dec ** sdef = &top_def;
  while (*sdef != (dec *)0) {
    exp crt_exp = (*sdef) -> dec_u.dec_val.dec_exp;
    bool extnamed = (*sdef) -> dec_u.dec_val.extnamed;
    if (no(crt_exp) == 0 && !extnamed) {
	*sdef = (*sdef) ->def_next;
    }
    else sdef = & ((*sdef) ->def_next);
  }
}



void translate_capsule
(void)
{
  dec * my_def;
  int noprocs;
  int i;

  opt_all_exps();
  remove_unused();

  if (dyn_init) {
    my_def = top_def;
    while (my_def != (dec *)0) {
        exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
	char * id = my_def -> dec_u.dec_val.dec_id;
	if (strcmp(id, "main") ==0 && son(crt_exp)!= nilexp &&
		name(son(crt_exp)) == proc_tag) {
	   exp fn = me_obtain(find_named_tg("__DO_I_TDF", f_proc));
	   exp cll = getexp(f_top, nilexp, 0, fn, nilexp, 0, 0, apply_tag);
	   exp * dm = &son(son(crt_exp));
	   exp hld, seq;
	   bro(fn) = cll; setlast(fn);
	   while (name(*dm) ==ident_tag && isparam(*dm))dm = &bro(son(*dm));
	   /* dm is body of main after params */
	   hld = getexp(f_top, *dm, 0, cll, nilexp, 0, 1, 0);
	   seq = getexp(sh(*dm), bro(*dm), last(*dm), hld, nilexp, 0, 0, seq_tag);
	   bro(*dm) = seq; setlast(*dm);
	   bro(cll) = hld; setlast(cll);
	   *dm = seq;
	   break;
	}
        my_def = my_def -> def_next;
     }
  }

    /* mark static unaliased */
  my_def = top_def;
  while (my_def != (dec *)0) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son(crt_exp)!= nilexp &&
	!my_def -> dec_u.dec_val.extnamed &&
	isvar(crt_exp))
      mark_unaliased(crt_exp);
    my_def = my_def -> def_next;
  };

  noprocs = 0;
  my_def = top_def;
  while (my_def != (dec *)0) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son(crt_exp)!= nilexp
        && (name(son(crt_exp)) == proc_tag ||
		name(son(crt_exp)) == general_proc_tag)) {
      noprocs++;
    }
    my_def = my_def -> def_next;
  }
  /* count procs */

  if (noprocs == 0) {
    procrecs = NULL;
  } else {
    procrecs = (procrec *)xcalloc(noprocs, sizeof(procrec));
    noprocs = 0;
  }

  my_def = top_def;
  while (my_def != (dec *)0) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son(crt_exp)!= nilexp &&
	(name(son(crt_exp)) == proc_tag || name(son(crt_exp)) == general_proc_tag)) {
      no(son(crt_exp)) = noprocs++;
      /* put index into procrecs in no(proc) */
    }
    my_def = my_def -> def_next;
  }

  if (do_extern_adds) {
	usages = (exp*)xcalloc(noprocs, sizeof(exp));
	my_def = top_def;
  	while (my_def != (dec *)0) {
		exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
		if (son(crt_exp) == nilexp && isvar(crt_exp)) {
			global_usages(crt_exp, noprocs);
			/* try to identify globals ptrs in procs */
		}
		my_def = my_def -> def_next;
	}
  }

  if (diag != DIAG_NONE && nofds !=0) {
      init_table_space(nofds, noprocs);
      add_dense_no(0, 0);
      add_dense_no (0, 0);	/* dont know why!! */
      symnosforfiles();
      stab_types();
  }
  else {
    init_table_space(1,noprocs);
    add_dense_no(0, 0);
    add_dense_no (0, 0);	/* dont know why!! */
    IGNORE new_lsym_d("NOFILE.c", 0, stFile, scText, 0, 0);
  };

  /* scan to put everything in MIPS form */

  my_def = top_def;
  while (my_def != (dec *)0) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son(crt_exp)!= nilexp
	&& (name(son(crt_exp)) == proc_tag ||
		name(son(crt_exp)) == general_proc_tag)) {
      procrec * pr = &procrecs[no(son(crt_exp))];
      exp * st = &son(crt_exp);
      pr -> needsproc = scan(st, &st);
      pr->callee_size = (callee_size+63) &~63;
    }
    my_def = my_def -> def_next;
  }


  /* calculate the break points for register allocation and do it */
  my_def = top_def;
  while (my_def != (dec *)0) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (son(crt_exp)!= nilexp
        && (name(son(crt_exp)) == proc_tag ||
		name(son(crt_exp)) == general_proc_tag)) {
      procrec * pr = &procrecs[no(son(crt_exp))];
      needs * ndpr = & pr->needsproc;
      long pprops = (ndpr->propsneeds);
      bool leaf = (pprops & anyproccall) == 0;
      spacereq forrest;
      int   freefixed = 8;	/* NO OF S_REGISTERS */
      int   freefloat = 6;	/* NO OF S $f REGISTERS */

      setframe_flags(son(crt_exp), leaf);
      if (!Has_fp) freefixed++; /* can use $30 as normal caller save */

      if (Has_vcallees) { freefixed--; }

      if (!No_S)IGNORE weightsv(1.0, bro(son(son(crt_exp))));
      /* estimate usage of tags in body of proc */

      forrest = regalloc(bro(son(son(crt_exp))), freefixed, freefloat,
				(PIC_code && !leaf)?32:0);
      /* reg and stack allocation for tags */

      pr -> spacereqproc = forrest;

      setframe_info(son(crt_exp));
    }
    my_def = my_def -> def_next;
  }

  /* put defs in main globals and set up symnos*/
  my_def = top_def;
  main_globals_index = 0;
  while (my_def != (dec*)0) {
  	main_globals_index++;
  	my_def = my_def -> def_next;
  }

  data_lab = (main_globals_index > 33)?main_globals_index:33;
  main_globals = (dec**)xcalloc(main_globals_index, sizeof(dec*));
  symnos = (int *)xcalloc(main_globals_index, sizeof(int));

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
    diag_descriptor * dinf = main_globals[i] -> dec_u.dec_val.diag_info;
    main_globals[i] ->dec_u.dec_val.sym_number = i;
    if (no(tg)!= 0 || (extnamed && son(tg)!= nilexp)
		|| strcmp(id,"__TDFhandler") == 0
		|| strcmp(id,"__TDFstacklim") ==0
	) {
     	if (no(tg) ==1 && son(tg) ==nilexp && dinf != (diag_descriptor *)0
 		 /* diagnostics only! */ ) {
    		symnos[i] = -1;
    	}
    	else {
          no(tg) = (i + 1)* 64 + 32;
          symnos[i] = symnoforext(main_globals[i], mainfile);
        }
    }
    else
      symnos[i] = -1;
  };



  setregalt(nowhere.answhere, 0);
  nowhere.ashwhere.ashsize = 0;
  nowhere.ashwhere.ashsize = 0;

  if (as_file) {
    fprintf(as_file, "\t.verstamp %d %d\n", majorno, minorno);

    if (PIC_code) {
	fprintf(as_file, "\t.option pic2\n");
    }
    else {
        fprintf(as_file,(diag != DIAG_NONE)? "\t.option O1\n" : "\t.option O2\n");
    }
  }

  /* this is the only? use of these nos, to satisfy as1 */
  out_verstamp(majorno, minorno);

  if (PIC_code) {
	out_option(2, 2);
  }
  else
  { out_option(1,(diag != DIAG_NONE)? 1 : 2); }

  if (diag != DIAG_NONE && nofds!=0) {
    stab_file(0);
  }
  else
  {
    currentfile = 0;
  }


  /* compile procedures, evaluate constants, put in the .comm entries for
     undefined objects */

  my_def = top_def;

/*
  while (my_def != (dec *) 0) {
    exp tg = my_def -> dec_u.dec_val.dec_exp;
    char *id = my_def -> dec_u.dec_val.dec_id;
    bool extnamed = my_def -> dec_u.dec_val.extnamed;
    if (son (tg) != nilexp && (extnamed || no (tg) != 0 || !strcmp (id, "main"))) {
      if (extnamed) {
	if (as_file)
	  fprintf (as_file, "\t.globl\t%s\n", id);
	out_common (symnos[my_def->dec_u.dec_val.sym_number], iglobal);
      }
    }
    my_def = my_def -> def_next;
  }
*/
  my_def = top_def;

  while (my_def != (dec *)0) {
    if (!my_def -> dec_u.dec_val.processed)
       code_it(my_def);
    my_def = my_def -> def_next;
  };


  return;		/* return 1 for error, 0 for good */


}
void translate_unit
(void)
{
  if (separate_units)
   {
     dec * my_def;
     translate_capsule();
     my_def = top_def;
     while (my_def != (dec *)0) {
       exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
       no(crt_exp) = 0;
       pt(crt_exp) = nilexp;
       my_def = my_def -> def_next;
     };
     crt_repeat = nilexp;
     repeat_list = nilexp;
   };
  return;
}


void translate_tagdef
(void)
{
  return;
}
