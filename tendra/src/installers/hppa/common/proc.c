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
$Log: proc.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.15  1996/12/09  12:52:46  wfs
 *    Prevented the superfluous "loading" to GR0.
 *
 * Revision 1.14  1996/11/14  15:22:24  wfs
 *    Fixed a bug in regexps.c which was common to most of the installers and
 * has only just come to light due to PWE's work on powertrans. (There was
 * previously only a patch.) Cosmetic changes to other files.
 *
 * Revision 1.13  1996/09/05  11:05:11  wfs
 * "dynamic_init" boolean variable removed - must always be considered true.
 *
 * Revision 1.12  1996/08/30  09:02:32  wfs
 * Various fixes of bugs arising from avs and pl_tdf tests.
 *
 * Revision 1.11  1996/03/28  10:53:19  wfs
 * Bug fixes to scan(), peephole optimisations in proc.c, and enum diagnostics.
 *
 * Revision 1.10  1996/03/08  11:52:27  wfs
 * Another typo in "proc.c".
 *
 * Revision 1.9  1996/03/08  11:31:14  wfs
 * typo in "proc.c" dynamic initialization code.
 *
 * Revision 1.8  1996/03/06  17:40:27  wfs
 * Corrected typo in last bug fix.
 *
 * Revision 1.7  1996/03/06  17:26:30  wfs
 * Fixed a bug in the profiling option.
 *
 * Revision 1.6  1996/01/30  15:36:31  wfs
 * Added the dynamic initialization files "dyn_begin.s" and "dyn_end.s" to
 * the hppatrans repository. The bl_install and bl_update scripts were
 * expanded to deal with these new "initcode" files.
 *
 * Revision 1.5  1996/01/19  14:13:20  wfs
 * Added "bool" type to an extern declaration in "frames.h".
 *
 * Revision 1.4  1996/01/11  14:46:33  wfs
 * Fixed bug in "ass_tag" case of scan(). Removed superfluous macro and comment.
 *
 * Revision 1.3  1995/12/19  16:52:51  wfs
 * Reinstated the "__main" call and a ".CODE" directive when producing gdb
 * diagnostic code.
 *
 * Revision 1.2  1995/12/18  13:12:18  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.5  1995/10/20  14:10:06  wfs
 * gcc compilation changes.
 *
 * Revision 5.4  1995/10/11  16:00:23  wfs
 * Moved all of the "apply_tag" stuff to "makecode.c".
 *
 * Revision 5.3  1995/10/09  10:41:02  wfs
 * Only one return from a procedure when producing diagnostics. White space
 * changes.
 *
 * Revision 5.2  1995/09/25  10:50:50  wfs
 * A "ghostscript" bug fix.
 *
 * Revision 5.1  1995/09/15  13:09:18  wfs
 * Finished the implementation of the exception token and stack limit
 * stuff + minor cosmetic changes.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.3  1995/08/25  10:21:17  wfs
 * A fairly major revision. A lot of the code which set up the frame
 * specific variables has been moved to "frames.c". 3.1 and 4.0 stuff
 * such as "return_to_label" and "untidy_return" have been incorporated.
 * Register synonyms changed. A lot of superfluous code was removed
 * after the register allocation stuff was changed.
 *
 * Revision 3.3  1995/08/25  10:21:17  wfs
 * A fairly major revision. A lot of the code which set up the frame
 * specific variables has been moved to "frames.c". 3.1 and 4.0 stuff
 * such as "return_to_label" and "untidy_return" have been incorporated.
 * Register synonyms changed. A lot of superfluous code was removed
 * after the register allocation stuff was changed.
 *
 * Revision 3.1  95/04/10  16:27:45  16:27:45  wfs (William Simmonds)
 * Apr95 tape version.
 *
 * Revision 3.0  95/03/30  11:18:36  11:18:36  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 *
 * Revision 2.0  95/03/15  15:28:27  15:28:27  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 *
 * Revision 1.3  95/02/22  11:28:47  11:28:47  wfs (William Simmonds)
 * Added Has_ll, changed the base register of mem_temp0 to R_FP.
 *
 * Revision 1.2  95/01/17  17:30:24  17:30:24  wfs (William Simmonds)
 * Changed name of an included header file.
 *
 * Revision 1.1  95/01/11  13:14:46  13:14:46  wfs (William Simmonds)
 * Initial revision
 *
*/


#define HPPATRANS_CODE
#include "config.h"
#include "myassert.h"
#include "addrtypes.h"
#include "tags.h"
#include "expmacs.h"
#include "installtypes.h"
#include "exp.h"
#include "exptypes.h"
#include "frames.h"
#include "maxminmacs.h"
#include "shapemacs.h"
#include "basicread.h"
#include "proctypes.h"
#include "eval.h"
#include "move.h"
#include "comment.h"
#include "getregs.h"
#include "guard.h"
#include "locate.h"
#include "codehere.h"
#include "inst_fmt.h"
#include "hppains.h"
#include "bitsmacs.h"
#include "labels.h"
#include "regexps.h"
#include "regmacs.h"
#include "regable.h"
#include "flags.h"
#include "special.h"
#include "translat.h"
#include "makecode.h"
#include "out.h"
#include "proc.h"
#include "misc.h"
#include "hppadiags.h"
#include "loc_signal.h"

#define RES    1
#define TO_LAB 2
#define UNTIDY 3

#define	RN(r)  reg_name(r)  /* short hand */
#define NA    -1


extern outofline *odd_bits;
extern int repeat_level;
extern regpeep regexps[64];
extern char *proc_name;
extern int line;
extern char export[128];
extern int firstlab,labno;
int leaf;
extern baseoff find_tg PROTO_S ((char* s));
extern exp find_named_tg PROTO_S ((char *,shape));
extern shape f_pointer PROTO_S ((alignment));
extern alignment f_alignment PROTO_S ((shape));
extern shape f_proc;
extern void do_exception PROTO_S ((int));

int res_label;
static int untidy_return_label,return_to_label_label;
static bool simpleans;
static ans procans;
int RSCOPE_LEVEL,RSCOPE_LABEL;

/*
*   Temporary space on stack which can be referenced by short instruction
*   sequences, the space is initialised by each procedure prelude.
 */
baseoff mem_temp
    PROTO_N ( (byte_offset) )
    PROTO_T ( int byte_offset )
{
   baseoff b;
   b = MEM_TEMP_BOFF;

   /* Only 2 words of temporary memory allocated */
   assert(byte_offset >= 0 && byte_offset < 8);

   b.offset+=byte_offset;
   return b;
}



/* Save callee-saves ("s") registers on the stack. */
void save_sregs
    PROTO_Z ()
{
   if (fixdump==0)
      return;
   else
   {
      int o=0,r;
      for(r=16;r<32;r++)
      {
	 if (fixdump&(1<<r))
	 {
	    st_ir_ins(i_stw,cmplt_,r,fs_,empty_ltrl,o,SP);
	    o+=4;
	 }
      }
   }
}


/* Restore the callee-saves ("s") registers saved on the stack. */
void restore_sregs
    PROTO_Z ()
{
   if (fixdump==0)
      return;
   else
   {
      int o=0,r;
      for(r=16;r<32;r++)
      {
	 if (fixdump&(1<<r))
	 {
	    ld_ir_ins(i_ldw,cmplt_,fs_,empty_ltrl,o,SP,r);
	    o+=4;
	 }
      }
   }
}


/*
*   Some (more or less) common code for res_tag, return_to_label and
*   untidy_return.
 */
static void code_for_ret
    PROTO_N ( (which_ret) )
    PROTO_T ( int which_ret )
{
   if (which_ret==UNTIDY)
      rr_ins(i_copy,SP,T2);
   if (Has_fp)
      rr_ins(i_copy,FP,SP);
   else
   {
      baseoff b;
      b.base=(Has_vsp ? EP : SP); b.offset=-(frame_sz>>3);
      ld_ins(i_lo,0,b,SP);
   }
   restore_sregs();
   if (which_ret!=TO_LAB)
      ld_ir_ins(i_ldw,cmplt_,fs_,empty_ltrl,-20,SP,RP);
   extj_reg_ins(i_bv,RP);
   if (which_ret==UNTIDY)
      rr_ins(i_copy,T2,SP);
   else
      z_ins(i_nop);
}


static void add_odd_bits
    PROTO_N ( (r) )
    PROTO_T ( outofline *r )
{
   space sp;
   if (r!=(outofline*)nilexp)
   {
      add_odd_bits(r->next);
      if (r->next==(outofline*)nilexp)
	 last_odd_bit=1;
   }
   else
      return;
   outlab("L$$",r->labno);
   sp=r->sp;
   clear_all();
   make_code(r->body,sp,r->dest, name(sh(r->body))!=bothd ? ptno(r->jr) : res_label);
   if (name(sh(r->body))!=bothd)
      ub_ins(cmplt_,ptno(r->jr));
}


/*
 * The following functions generate code for various procedure related
 * constructs.  They put the result in dest using t-regs given by sp.
 * If non-zero, exitlab is the label of where the code is to continue.
 * These functions are called by make_code(), the code selection switch.
 */


/*
*    Procedure definition
 */
makeans make_proc_tag_code
    PROTO_N ( (e,sp,dest,exitlab) )
    PROTO_T ( exp e X space sp X where dest X int exitlab )
{
   static int p_lab = 0;
   procrec *pr=&procrecs[no(e)];
   needs *ndpr=&pr->needsproc;
   long pprops=(long) (ndpr->propsneeds);
   makeans mka;
   bool is_main=STRCMP(proc_name,"main");
   bool save_sp;

   set_up_frame(e);

   /*
   *   Grab the frame size, offsets, etc. of this procedure's frame
    */
   leaf = pr->leaf;
   locals_space = pr->locals_space;
   max_args = pr->max_args;
   frame_sz = pr->frame_sz;
   callees_offset = pr->callees_offset;
   params_offset = pr->params_offset;
   locals_offset = pr->locals_offset;
   callee_sz = pr->callee_sz;
   simpleans = (pprops & long_result_bit) == 0;

   save_sp = ( ((Has_fp && (No_S || (Uses_crt_env && Has_vcallees)))) ||
	       (Uses_crt_env && (!leaf || proc_has_checkstack(e)
				       || Has_checkalloc)));

   if (OPTIM)
   {
      lines=BLOCK;
      pCode = (pIn*) malloc(BLOCK*sizeof(pIn));
      nLabels=4096;
      labIntro = (int*) malloc(nLabels*sizeof(int));
      for(line=0;line<4096;line++)
	 labIntro[line]=-1;
      line=0;
   }
   odd_bits = (outofline*)0;
   repeat_level=0;

   mka.lab = exitlab;
   mka.regmove = NOREG;

   assert(name(e) == proc_tag);	/* procedure definition */

   export[0]=0;
   outnl();
   if (is_main)
   {
      if (gcc_assembler)
      {
	 outs("\t.IMPORT\t__CTOR_LIST__,DATA\n");
	 outs("\t.IMPORT\t__main,CODE\n");
      }
      else
	 outs("\t.IMPORT\t__TDF_CTOR_LIST__,DATA\n");
   }
   if (do_profile)
   {
      outs("\t.BSS\n");
      outs("\t.ALIGN\t4\n");
      outs("G$");
      outn(p_lab);
      outs("\t.BLOCKZ\t4\n");
   }
   outs("\t.CODE\n");
   outs(proc_name);
   outnl();
   outs("\t.PROC\n");
   /*
   *   Output `CALLINFO' directive (c.f. pp 3-10 - 3-13 of assembly language
   *   reference manual)
    */
   outs("\t.CALLINFO FRAME=");
		  /* FRAME=frame size - frame marker bytes (if allocated) */
   if (gcc_assembler)
   {
      outn(frame_sz>>3);
   }
   else
   {
      outn((frame_sz>>3) - (leaf ? 0 : 8<<2));
   }
   if (save_sp)
      outs(",SAVE_SP");
   outs(",SAVE_RP,ENTRY_GR=3");
   if (leaf)
   {
      outc('\n');
   }
   else
   {
      outs(",CALLS\n");
   }
   outs("\t.ENTRY\n");

   /* store return pointer */
   st_ir_ins(i_stw,cmplt_,RP,fs_,empty_ltrl,-20,SP);

   if (fixdump != 0)
   {
      save_sregs();  /* Save the s-regs on stack. */
   }

   if (do_profile)
   {
      char g[128];
      baseoff b;
      b.base=SP;
      b.offset=-36;
      st_ins(i_sw,ARG0,b);
      b.offset-=4;
      st_ins(i_sw,ARG1,b);
      b.offset-=4;
      st_ins(i_sw,ARG2,b);
      b.offset-=4;
      st_ins(i_sw,ARG3,b);
      b.base=0; b.offset=0;
      sprintf(g,"G$%d",p_lab);
      set_ins(g,b,ARG2);
      rr_ins(i_blr,GR0,ARG1);
      rr_ins(i_copy,RP,ARG0);
      call_ins(cmplt_,"_mcount",RP,"ARGW0=GR,ARGW1=GR,ARGW2=GR");
      p_lab++;
      b.base=SP;
      b.offset=-36;
      ld_ins(i_lw,0,b,ARG0);
      b.offset-=4;
      ld_ins(i_lw,0,b,ARG1);
      b.offset-=4;
      ld_ins(i_lw,0,b,ARG2);
      b.offset-=4;
      ld_ins(i_lw,0,b,ARG3);
   }

   {
      /*
      *   Increment the Stack Pointer
       */
      int R = SP;
      if (proc_has_checkstack(e))
      {
	 R = T1;
      }
      else if (Has_fp)
      {
	 rr_ins(i_copy,SP,FP);
      }
      else
      if (save_sp)
      {
	 rr_ins(i_copy,SP,T1);
      }
      if (Has_vcallees)
      {
	 /* Add on callee_sz passed on stack by caller... */
	 ld_ir_ins(i_ldw,cmplt_,fs_,empty_ltrl,(16<<2),SP,GR1);
	 rrr_ins(i_add,c_,SP,GR1,R);
	 /* ...and ensure the stack pointer stays 16 word (64 byte) aligned */
	 if (SIMM14((frame_sz>>3)+63))
	 {
	    ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,(frame_sz>>3)+63,R,R);
	 }
	 else
	 {
	    ir_ins(i_addil,fs_L,empty_ltrl,(frame_sz>>3)+63,R);
	    ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,(frame_sz>>3)+63,GR1,R);
	 }
	 riir_ins(i_dep,c_,0,31,6,R);
      }
      else
      {
	 if (SIMM14(frame_sz>>3))
	 {
	    ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,frame_sz>>3,SP,R);
	 }
	 else
	 {
	    ir_ins(i_addil,fs_L,empty_ltrl,frame_sz>>3,SP);
	    ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,frame_sz>>3,GR1,R);
	 }
      }
   }

   if (save_sp && !Has_fp)
   {
      if (proc_has_checkstack(e))
	 st_ir_ins(i_stw,cmplt_,SP,fs_,empty_ltrl,FP_BOFF.offset,T1);
      else
	 st_ir_ins(i_stw,cmplt_,T1,fs_,empty_ltrl,FP_BOFF.offset,SP);
   }

   if (proc_has_checkstack(e))
   {
      baseoff b;
      exp stl = find_named_tg("__TDFstacklim",
			      f_pointer(f_alignment(f_proc)));
      setvar(stl);
      b = boff(stl);
      stackerr_lab = new_label();
      ld_ins(i_lw,1,b,GR1);
      cj_ins(c_g,T1,GR1,stackerr_lab);
      if (Has_fp)
	 rr_ins(i_copy,SP,FP);
      rr_ins(i_copy,T1,SP);
   }

   if (PIC_code)
   {
      st_ir_ins(i_stw,cmplt_,GR19,fs_,empty_ltrl,-32,SP);
      if (!leaf && !is_main)
      {
	 rr_ins(i_copy,GR19,GR5);
      }
   }

   if (is_main)
   {
      int n = new_label();
      int end = new_label();
      baseoff b;
      b.base = 0; b.offset = (gcc_assembler ? 0 : 4 );
      set_ins((gcc_assembler ? "__CTOR_LIST__" : "__TDF_CTOR_LIST__"),b,GR4);
      b.base = GR4;
      b.offset = 4;
      if (gcc_assembler)
      {
	 ld_ins(i_lwm,1,b,GR5);
	 cj_ins(c_eq,GR0,GR5,end);
	 rrr_ins(i_sh2add,c_,GR5,GR4,GR5);
	 outlab("L$$",n);
	 ld_ins(i_lwm,1,b,GR22);
	 call_millicode( MILLI_DYNCALL, RP, "",0 );
	 cj_ins(c_l,GR4,GR5,n);
	 outlab("L$$",end);
	 if (is_PIC_and_calls)
	    ld_ir_ins(i_ldw,cmplt_,fs_,empty_ltrl,-32,SP,GR5);
	 call_ins(cmplt_,"__main",RP,"");
      }
      else
      {
	 ld_ins(i_lwm,1,b,GR22);
	 cj_ins(c_eq,GR0,GR22,end);
	 outlab("L$$",n);
	 call_millicode( MILLI_DYNCALL, RP, "",0 );
	 ld_ins(i_lwm,1,b,GR22);
	 cj_ins(c_neq,GR0,GR22,n);
	 outlab("L$$",end);
      }
   }

   if (Has_vsp)
      rr_ins(i_copy,SP,EP);
   if (Has_tos)
      st_ins(i_sw,SP,SP_BOFF);
   if ( (Has_fp && (No_S || (Uses_crt_env && Has_vcallees))) )
      st_ins(i_sw,FP,FP_BOFF);

   if (!simpleans)
   {
      /* structure or union result */
      instore is;
      /* where to find address of result */
      is.adval = 0;
      is.b = LONG_RESULT_BOFF;
      setinsalt(procans,is);
      st_ins(i_sw,RET0,is.b);
   }
   else if ((pprops & realresult_bit) != 0)
   {
      /* real result */
      freg frg;
      frg.fr = R_FR4;
      frg.dble = (pprops & longrealresult_bit) ? 1 : 0;
      setfregalt(procans,frg);
   }
   else if ((pprops & has_result_bit) != 0)
   {
      /* fixed register result */
      setregalt(procans,RET0);
   }
   else
   {
      /* no result */
      setregalt(procans,GR0);
   }

  clear_all();
  RSCOPE_LEVEL = 0;
  res_label = 0;
  untidy_return_label = 0;
  return_to_label_label = 0;
  last_odd_bit = 0;
  doing_odd_bits = 0;

  code_here(son(e),sp,nowhere);	/* Code body of procedure. */

  if (stackerr_lab!=0)
  {
     outlab("L$$",stackerr_lab);
     do_exception(SIGUSR1);
  }
  if (aritherr_lab!=0)
  {
     outlab("L$$",aritherr_lab);
     do_exception(SIGFPE);
  }

  doing_odd_bits = 1;
  while (odd_bits != (outofline*)0)
  {
     outofline *ol = odd_bits;
     odd_bits = (outofline*)0;
     last_odd_bit=0;
     add_odd_bits(ol);
  }

  if (xdb)
  {
     outlab("L$$",res_label);
     code_for_ret(RES);
  }


  if (OPTIM)
  {
     /*
     *   Jump and "peephole" optimisations
      */
     int i,j;
     char *hit;
     FILE_POSN Pos;
     GET_FILE_POSN(outf,Pos);
     hit = (char*) malloc( (nLabels+8)*sizeof(char) );
     for(i=0;i<line;i++)
     {
	char s[65];
	int lab,to=0,jump;
	lab=pCode[i]->lab;
	if (lab==res_label && lab>0)
	   to=labIntro[lab-firstlab];
	else
	if (lab>NA && lab != res_label && pCode[i]->ins != i_lab)
	{
	   for (j=0;j<nLabels+8;j++)
	       hit[j]=0;
	   to=labIntro[lab-firstlab];
	   while(to+1<line && lab!=res_label && pCode[to+1]->lab>NA
			   && pCode[to+1]->ins==i_ub && hit[lab-firstlab]==0)
	   {
	      hit[lab-firstlab]=1;
	      lab=pCode[to+1]->lab;
	      to=labIntro[lab-firstlab];
	   }
	}
	if (pCode[i]->ins==i_bb)
	{
	   jump = i-to ;
	   if (SIMM11(jump*4))
	   {
	      ins_p cc;
	      int a,b;
	      cc=pCode[i]->cc;
	      SET_FILE_POSN(outf,(pCode[i]->fpos));
	      a=pCode[i]->op[0];
	      b=pCode[i]->op[1];
	      IGNORE sprintf(s,"\tbb%s,N\t%s,%d,L$$%d\n\tnop",cc,RN(a),b,lab);
	      j=(int)strlen(s);
	      for(;j<63;j++)
		 s[j]=' ';
	      s[63]=0;
	      fprintf(outf,"%s\n",s);
	   }
	   else
	   {
	      ins_p cc;
	      int a,b;
	      if (pCode[i]->cc==bit_is_0)
		 cc=c_OD;
	      else
		 cc=c_EV;
	      SET_FILE_POSN(outf,(pCode[i]->fpos));
	      a=pCode[i]->op[0];
	      b=pCode[i]->op[1];
	      IGNORE sprintf(s,"\textru%s\t%s,%d,1,0\n\tb\tL$$%d\n\tnop",cc,RN(a),b,lab);
	      j=(int)strlen(s);
	      for(;j<63;j++)
		 s[j]=' ';
	      s[63]=0;
	      fprintf(outf,"%s\n",s);
	   }
	}
	else
	if (pCode[i]->ins==i_ub)
	{
	   jump = i-to ;
	   SET_FILE_POSN(outf,(pCode[i]->fpos));
#if 0
	   if (SIMM19(jump*4))
	   {
#endif
	      IGNORE sprintf(s,"\tb\tL$$%d\n\tnop",lab);
	      j=(int)strlen(s);
	      for(;j<63;j++)
		 s[j]=' ';
	      s[63]='\n';
	      s[64]=0;
	      fprintf(outf,"%s",s);
#if 0
	   }
	   else
	   {
	   }
#endif
	}
	else
	if (pCode[i]->ins==i_cj || pCode[i]->ins==i_cij)
	{
	   jump = i-to ;
	   if (SIMM11(jump*4))
	   {
	      ins_p cc;
	      int a,b;
	      cc=pCode[i]->cc;
	      SET_FILE_POSN(outf,(pCode[i]->fpos));
	      a=pCode[i]->op[0];
	      b=pCode[i]->op[1];
	      if (jump<0 && line>i)
	      {
	      if (pCode[i]->ins==i_cj)
		 IGNORE sprintf(s,"\tcomb%s,N\t%s,%s,L$$%d\n",cc,RN(a),RN(b),lab);
	      else
		 IGNORE sprintf(s,"\tcomib%s,N\t%d,%s,L$$%d\n",cc,a,RN(b),lab);
	      }
	      else
	      {
	      if (pCode[i]->ins==i_cj)
		 IGNORE sprintf(s,"\tcomb%s,N\t%s,%s,L$$%d\n\tnop",cc,RN(a),RN(b),lab);
	      else
		 IGNORE sprintf(s,"\tcomib%s,N\t%d,%s,L$$%d\n\tnop",cc,a,RN(b),lab);
	      }
	      j=(int)strlen(s);
	      for(;j<63;j++)
		 s[j]=' ';
	      s[63]=0;
	      fprintf(outf,"%s\n",s);
	   }
	   else
#if 0
	   if (SIMM19(jump*4))
#endif
	   {
	      ins_p cc;
	      int a,b;
	      cc=opp(pCode[i]->cc);
	      SET_FILE_POSN(outf,(pCode[i]->fpos));
	      a=pCode[i]->op[0];
	      b=pCode[i]->op[1];
	      if (pCode[i]->ins==i_cj)
		 IGNORE sprintf(s,"\tcomclr%s\t%s,%s,0\n\tb\tL$$%d\n\tnop",cc,RN(a),RN(b),lab);
	      else
		 IGNORE sprintf(s,"\tcomiclr%s\t%d,%s,0\n\tb\tL$$%d\n\tnop",cc,a,RN(b),lab);
	      j=(int)strlen(s);
	      for(;j<63;j++)
		 s[j]=' ';
	      s[63]=0;
	      fprintf(outf,"%s\n",s);
	   }
#if 0
	   else
	   {
	      ins_p cc;
	      int a,b;
	      cc=pCode[i]->cc;
	      SET_FILE_POSN(outf,(pCode[i]->fpos));
	      a=pCode[i]->op[0];
	      b=pCode[i]->op[1];
	      if (pCode[i]->ins==i_cj)
		 IGNORE sprintf(s,"\tcomb%s,N\t%s,%s,.+16\n\tnop\n\tLB\tL$$%d\n",cc,RN(a),RN(b),lab);
	      else
		 IGNORE sprintf(s,"\tcomib%s,N\t%d,%s,.+16\n\tnop\n\tLB\tL$$%d\n",cc,a,RN(b),lab);
	      j=(int)strlen(s);
	      for(;j<63;j++)
		 s[j]=' ';
	      s[63]=0;
	      fprintf(outf,"%s\n",s);
	   }
#endif
	}
     }
     SET_FILE_POSN(outf,Pos);
     free(hit);
  }



{
   int i;
   for(i=0;i<line;i++)
   {
      pIn j=pCode[line];
      free(j);
   }
   free(pCode);
   free(labIntro);
}


   outs("\t.EXIT\n");
   clear_all();  /* for next proc */
   return mka;
}


/*
*   res_tag, return_to_label or untidy_return
 */

makeans make_res_tag_code
    PROTO_N ( (e,sp,dest,exitlab) )
    PROTO_T ( exp e X space sp X where dest X int exitlab )
{
   makeans mka;
   int nm,*ret_label;
   mka.lab = exitlab;
   mka.regmove = NOREG;
   if (name(e)==res_tag)
   {
      nm=RES;
      ret_label=&res_label;
   }
   else
   if (name(e)==return_to_label_tag)
   {
      nm=TO_LAB;
      ret_label=&return_to_label_label;
   }
   else
   {
      nm=UNTIDY;
      ret_label=&untidy_return_label;
   }
   if (nm!=TO_LAB)  /* don't evaluate result if returning to label */
   {
      where w;
      bool cmpd;
      w.answhere = procans;
      w.ashwhere = ashof(sh(son(e)));
      cmpd = (w.ashwhere.ashsize<65 && !simpleans);
      if (cmpd)
      {
	 /*
	 *   The HP_PA RISC convention states that compound results of 64
	*    bits are to be returned in the registers RET0 and RET1. We put
	*    the result into the stack space LONG_RESULT_BOFF and then load
	 *   into the registers.
	  */
	w.answhere.val.instoreans.adval=1;
      }
      code_here(son(e),sp,w); /*  Get the result  */
      if (cmpd)
      {
	 instore is;
	 baseoff b;
	 is=procans.val.instoreans;
	 b = is.b;
	 ld_ins(i_lw,SIGNED,b,RET0);
	 b.offset+=4;
	 ld_ins(i_lw,SIGNED,b,RET1);
      }
   }
   if (RSCOPE_LEVEL==0)
   {
      if (nm==TO_LAB)
	 reg_operand_here(son(e),sp,RP);
      if (*ret_label==0)
      {
	 /*
	 *    Must be the first res_tag, the first return_to_label, or the
	 *    first untidy_return encountered in this procedure - label
	  *   and output relevant code sequence
	   */
	 *ret_label = new_label();
	 if (xdb)
	 {
	    ub_ins(cmplt_,*ret_label);
	 }
	 else
	 {
	    outlab("L$$",*ret_label);
	    code_for_ret(nm);
	 }
      }
      else
      if (xdb || fixdump)
	 ub_ins(cmplt_,*ret_label);
      else
	 code_for_ret(nm);  /*
			    *   A very short return sequence - output code
			    *   each time thus avoiding a jump to *ret_label
			     */
   }
   else
   {
      /* inlined result */
      if (RSCOPE_LABEL == 0)
	 RSCOPE_LABEL = new_label();
      if (RSCOPE_LABEL != exitlab)
	 ub_ins(cmplt_,RSCOPE_LABEL);
   }

   clear_all();	  /* regs invalid after return. (Not needed for inlining?) */

   return mka;
}



