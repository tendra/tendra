/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Procs for outputting various HPPA RISC instruction formats to the
 * external file - outf. Each procedure produces assembler code for a family
 * of HPPA RISC operations, the actual member is passed as the string
 * understood by the assembler.
 */

#include <assert.h>
#include <string.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <local/out.h>
#include <local/expmacs.h>

#include <construct/tags.h>
#include <construct/flags.h>

#include <refactor/optimise.h>

#include "addrtypes.h"
#include "regexps.h"
#include "regmacs.h"
#include "hppains.h"
#include "maxminmacs.h"
#include "comment.h"
#include "translat.h"
#include "inst_fmt.h"
#include "misc.h"
#include "frames.h"
#include "new_tags.h"
#include "eval.h"

#define name( x ) ( ( x )->namef )
#define sh( x ) ( ( x )->shf )
#define son( x ) ( ( x )->sonf.e )

#define GAP "                                                                "
#define prokhd 24

#define plabel( X ) ( (X)<0 ?\
    ( son(main_globals[((-X))-1]->dec_u.dec_val.dec_exp)==nilexp ?\
    name(sh(main_globals[((-X))-1]->dec_u.dec_val.dec_exp))==prokhd :\
    ( IS_A_PROC(son(main_globals[((-X))-1]->dec_u.dec_val.dec_exp)) ) ) : 0 )

#define globaldata(X) ( (X)<0 ?\
    ( (name(sh(main_globals[((-X))-1]->dec_u.dec_val.dec_exp))==proc_tag ||\
    name(sh(main_globals[((-X))-1]->dec_u.dec_val.dec_exp))==general_proc_tag)\
    ? 0 : 1 ) : 0 )


extern int firstlab, labno;
extern int nexps;
char last_ins[96];

int zops[]={0,0,0,0};
int last_line;
char last_symb[128];
int last_o;

static const char reg_name_tab[32][6] =
{ "%r0"  ,
  "%r1"  ,
  "%r2"  ,
  "%r19" ,
  "%r20" ,
  "%r21" ,
  "%r22" ,
  "%r26" ,
  "%r25" ,
  "%r24" ,
  "%r23" ,
  "%dp"  , /* %dp=%r27 */
  "%r28" ,
  "%r29" ,
  "%sp"  , /* %sp=%r30 */
  "%r31" ,
  "%r3"  ,
  "%r4"  ,
  "%r5"  ,
  "%r6"  ,
  "%r7"  ,
  "%r8"  ,
  "%r9"  ,
  "%r10" ,
  "%r11" ,
  "%r12" ,
  "%r13" ,
  "%r14" ,
  "%r15" ,
  "%r16" ,
  "%r17" ,
  "%r18"    };

static const char float_reg_name_tab[32][3][7] =
{
  { "%fr0L", "%fr0", "%fr0R" },
  { "%fr1L", "%fr1", "%fr1R" },
  { "%fr2L", "%fr2", "%fr2R" },
  { "%fr3L", "%fr3", "%fr3R" },
  { "%fr4L", "%fr4", "%fr4R" },
  { "%fr5L", "%fr5", "%fr5R" },
  { "%fr6L", "%fr6", "%fr6R" },
  { "%fr7L", "%fr7", "%fr7R" },
  { "%fr8L", "%fr8", "%fr8R" },
  { "%fr9L", "%fr9", "%fr9R" },
  { "%fr10L", "%fr10", "%fr10R" },
  { "%fr11L", "%fr11", "%fr11R" },
  { "%fr12L", "%fr12", "%fr12R" },
  { "%fr13L", "%fr13", "%fr13R" },
  { "%fr14L", "%fr14", "%fr14R" },
  { "%fr15L", "%fr15", "%fr15R" },
  { "%fr16L", "%fr16", "%fr16R" },
  { "%fr17L", "%fr17", "%fr17R" },
  { "%fr18L", "%fr18", "%fr18R" },
  { "%fr19L", "%fr19", "%fr19R" },
  { "%fr20L", "%fr20", "%fr20R" },
  { "%fr21L", "%fr21", "%fr21R" },
  { "%fr22L", "%fr22", "%fr22R" },
  { "%fr23L", "%fr23", "%fr23R" },
  { "%fr24L", "%fr24", "%fr24R" },
  { "%fr25L", "%fr25", "%fr25R" },
  { "%fr26L", "%fr26", "%fr26R" },
  { "%fr27L", "%fr27", "%fr27R" },
  { "%fr28L", "%fr28", "%fr28R" },
  { "%fr29L", "%fr29", "%fr29R" },
  { "%fr30L", "%fr30", "%fr30R" },
  { "%fr31L", "%fr31", "%fr31R" }
};

static const char space_reg_name_tab[8][5] =
{ "%sr0" ,
  "%sr1" ,
  "%sr2" ,
  "%sr3" ,
  "%sr4" ,
  "%sr5" ,
  "%sr6" ,
  "%sr7"    };


#define	RN(reg)	reg_name( reg )
#define	FN(reg)	float_reg_name(reg)
#define	SN(reg)	space_reg_name_tab[ reg ]

#define NA -1

ins_p NOCOND=0;


const char *
reg_name(int r)
{
  assert(IS_FIXREG(r));
  return reg_name_tab[r];
}

static const char *
float_reg_name(int reg)
{
   return float_reg_name_tab[0][0]+(7*reg);
}


int
outp(ins_p ins, ins_p cc, int *ops, int lab)
{
   if (~optim & OPTIM_PEEPHOLE)
   {
      return 1;
   }
   if ( line>(lines-16) )
   {
      /* Increment number of assembler instructions allowed for by INCR */
      int i;
      pIn *temp=pCode;
      pCode = (pIn*) xmalloc( (lines+INCR)*sizeof(pIn) );
      for(i=0;i<lines;i++)
	 pCode[i]=temp[i];
      free(temp);
      lines+=INCR;
   }
   if (ins==i_add && line>0)
   {
      pIn lst=pCode[line-1];
      ins_p lI=lst->ins;
      if (lst->op[1]==0 && (lI==i_sh1add || lI==i_sh2add || lI==i_sh3add))
      {
	 int r=lst->op[2];
	 int r0=ops[0];
	 int r1=ops[1];
	 if ( r==ops[2] && (r==r0 || r==r1) )
	 {
	    if (r==r1)
	       r1=r0;
	    r0=lst->op[0];
	    SET_FILE_POSN(outf,(lst->fpos));
	    fprintf(outf,"\t%s\t%s,%s,%s\n",lI,RN(r0),RN(r1),RN(r));
	    lst->op[1]=r1;
	    line--;
	    return 0;
	 }
      }
   }
   else if (ins==i_ub && line>0)
   {
      if (pCode[line-1]->ins==i_ub)
      {
	 if (line==1)
	    return 0;
	 else if (pCode[line-2]->ins!=i_ftest && pCode[line-2]->cc==c_)
	    return 0;
      }
   }
   else if (ins==i_lab && line>0)
   {
      int l=line-1;
      pIn j=pCode[l];
      while ( (j->ins==i_ub || j->ins==i_cj || j->ins==i_cij || j->ins==i_bb)                 && j->lab==lab && l>=0 )
      {
	 SET_FILE_POSN(outf,(j->fpos));
	 free(j);
	 l--;
	 if (l>=0)
	 {
	    j=pCode[l];
	    if (j->ins==i_ftest)
	    {
	      free(j);
	      j=pCode[l-1];
	      SET_FILE_POSN(outf,(j->fpos));
	      free(j);
	      l-=2;
	      if (l>=0)
		 j=pCode[l];
	    }
	 }
      }
      line=l+1;
      if ( line>1 && j->ins==i_lab )
      {
	 ins_p jIns;
	 j=pCode[line-2];
	 jIns=j->ins;
	 if ( (jIns==i_cj || jIns==i_cij || jIns==i_ub) && j->lab==lab )
	 {
	    SET_FILE_POSN(outf,(j->fpos));
	    fprintf(outf,"L$$%d\n",pCode[l]->lab);
	    labIntro[pCode[l]->lab-firstlab]=line-2;
	    pCode[l-1]=pCode[l];
	    free(j);
	    line--;
	 }
      }
      else
      if ( line>1 && j->ins!=i_ub && j->ins!=i_cj && j->ins!=i_cij
	   && j->ins!=i_bb && j->ins!=i_lab )
      {
	 ins_p jIns;
	 j=pCode[line-2];
	 jIns=j->ins;
	 if ( (jIns==i_cj || jIns==i_cij) && j->lab==lab )
	 {
	     FILE_POSN pos;
	     char s[64];
	     int a,b,i;
	     a=j->op[0];
	     b=j->op[1];
	     GET_FILE_POSN(outf,pos);
	     SET_FILE_POSN(outf,(j->fpos));
	     if (jIns==i_cj)
	     {
		IGNORE sprintf(s,"\tcomclr%s\t%s,%s,0",j->cc,RN(a),RN(b));
		i=(int)strlen(s);
		j->ins=i_comclr;
	     }
	     else
	     {
		IGNORE sprintf(s,"\tcomiclr%s\t%d,%s,0",j->cc,a,RN(b));
		i=(int)strlen(s);
		j->ins=i_comiclr;
	     }
	     for(;i<63;i++)
		s[i]=' ';
	     s[63]=0;
	     fprintf(outf,"%s\n",s);
	     j->op[2]=0;
	     j->lab=NA;
	     SET_FILE_POSN(outf,pos);
	 }
      }
      else
      if (j->ins==i_ub && line>1 && ((pCode[line-2]->ins==i_cij ||
				        pCode[line-2]->ins==i_cj) &&
				       pCode[line-2]->lab==lab))
      {
	 pCode[line-2]->lab=j->lab;
	 pCode[line-2]->cc=opp(pCode[line-2]->cc);
	 SET_FILE_POSN(outf,(j->fpos));
	 free(j);
	 line--;
      }
   }

   {
      pIn pI;
      pI = (pIn) xmalloc( sizeof(psuedoIn) );
      GET_FILE_POSN(outf,(pI->fpos));
      pI->ins=ins;
      pI->cc=cc;
      pI->lab=lab;
      pI->op[0]=ops[0];
      pI->op[1]=ops[1];
      pI->op[2]=ops[2];
      pI->op[3]=ops[3];
      pCode[line]=pI;
      if (ins==i_lab)
      {
	 if ( (lab-firstlab)>(nLabels-16) )
	 {
	    /* Increment number of labels allowed for by INCR */
	    int i;
	    int *temp=labIntro;
	    labIntro = (int*) xmalloc( (nLabels+INCR)*sizeof(int) );
	    for(i=0;i<nLabels;i++)
	       labIntro[i]=temp[i];
	    for(i=nLabels;i<nLabels+INCR;i++)
	       labIntro[i]=-1;
	    free(temp);
	    nLabels+=INCR;
	 }
	 labIntro[lab-firstlab]=line;
      }
      line++;
      fflush(outf);
      return 1;
   }
}


char *
ext_name(long id)
{
  static char *sp;
  static int sizeof_space = 0;

  if (sizeof_space == 0)
  {
    /* init sp */
    sizeof_space = 64;		/* generous first guess */
    sp = (char *) xmalloc(sizeof_space);
  }

  if (id < 0)
  {
    char *ext = main_globals[(-id) - 1]->dec_u.dec_val.dec_id;

    int len_needed = 1 + strlen(ext) + 1;	/* _NAME\0 */

    if (len_needed > sizeof_space)
    {
      sizeof_space = len_needed;
      sp = (char *) xrealloc(sp, sizeof_space);
    }

    sprintf(sp, "%s", ext);

    return sp;
  }
  else
  {
    assert(id > R_LAST);	/* not a confused register */

    sprintf(sp, "LD$%ld", id);
    return sp;
  }
}

/*
 * 3 register instructions
 */
void
rrr_ins(ins_p ins, ins_p cond, int a, int b, int c)
{
  int p;
  int ops[4];
  clear_reg(c);

   if (ins==i_add && a==b)
   {
      ops[0]=a;
      ops[1]=0;
      ops[2]=c;
      p=outp(i_sh1add,cond,ops,NA);
      if (p)
	 fprintf(outf,"\tsh1add%s\t%s,0,%s\n",cond,RN(a),RN(c));
   }
   else
   {
      ops[0]=a;
      ops[1]=b;
      ops[2]=c;
      p=outp(ins,cond,ops,NA);
      if (p)
	 fprintf(outf,"\t%s%s\t%s,%s,%s\n",ins,cond,RN(a),RN(b),RN(c));
   }
}

/*
 * 1 register pseudo instructions
 */
void
r_ins(ins_p ins, int a)
{
   outp(ins,NOCOND,zops,NA);
   fprintf(outf,"\t%s\t%s\n",ins,RN(a));
}

/*
 * non-store register, immediate, destination register instructions
 */
void
rir_ins(ins_p ins, ins_p cc, int a, long imm, int d)
{
   clear_reg(d);
   outp(ins,cc,zops,NA);
   fprintf(outf,"\t%s%s\t%s,%ld,%s\n",ins,cc,RN(a),imm,RN(d));
}

/*
 * register to register pseudo instructions
 */
void
rr_ins(ins_p ins, int s, int d)
{
  clear_reg(d);
  outp(ins,NOCOND,zops,NA);
  fprintf(outf,"\t%s\t%s,%s\n",ins,RN(s),RN(d));
}

/*
 * non-load immediate, register, register instructions
 */
void
irr_ins(ins_p ins, ins_p cc, ins_p fs, long i, int a, int d)
{
   clear_reg(d);
   outp(ins,cc,zops,NA);
   fprintf(outf,"\t%s%s\t%s%ld,%s,%s\n",ins,cc,fs,i,RN(a),RN(d));
}

/*
 * immediate, immediate, register instructions
 */
void
iir_ins(ins_p ins, ins_p cc, int a, int b, int d)
{
   clear_reg(d);
   outp(ins,cc,zops,NA);
   fprintf(outf,"\t%s%s\t%d,%d,%s\n",ins,cc,a,b,RN(d));
}

/*
 * immediate, immediate, immediate, register instructions
 */
void
iiir_ins(ins_p ins, ins_p cond, int a, int b, int c, int d)
{
   clear_reg(d);
   outp(ins,cond,zops,NA);
   fprintf(outf,"\t%s%s\t%d,%d,%d,%s\n",ins,cond,a,b,c,RN(d));
}

/*
 * immediate (i.e. field selector literal+long) to register instructions
 */
void
ir_ins(ins_p ins, ins_p fs, const char *ltrl, long l, int d)
{
    char I[128];

    /* build immediate, i.e. field selector applied to literal+long */
    if (!(*ltrl))
       sprintf(I,"%s%ld",fs,l);
    else
    if (l>0)
       sprintf(I,"%s%s+%ld",fs,ltrl,l);
    else
    if (l<0)
       sprintf(I,"%s%s-%ld",fs,ltrl,-l);
    else
       sprintf(I,"%s%s",fs,ltrl);

    clear_reg(d);

    outp(ins,NOCOND,zops,NA);
    fprintf(outf,"\t%s\t%s,%s\n",ins,I,RN(d));

}

/*
 * register, register, immediate, register instructions
 */
void
rrir_ins(ins_p ins, ins_p cc, int a, int b, long i, int d)
{
   int ops[4];
   if (ins==i_shd && b==0 && i>28)
   {
      ins_p ins=(i==29 ? i_sh3add : (i==30 ? i_sh2add : i_sh1add));
      rrr_ins(ins,c_,a,0,d);
      return;
   }
   clear_reg(d);
   ops[0]=a;
   ops[1]=b;
   ops[2]=i;
   ops[3]=d;
   outp(ins,cc,ops,NA);
   fprintf(outf,"\t%s%s\t%s,%s,%ld,%s\n",ins,cc,RN(a),RN(b),i,RN(d));
}

/*
 * zeroadic pseudo instruction, not a branch
 */
void
z_ins(ins_p ins)
{
   int b;
   b=outp(ins,NOCOND,zops,NA);
   if (b)
      fprintf(outf, "\t%s\n", ins);
}

/*
 * register, immediate, immediate, register instructions
 */
void
riir_ins(ins_p ins, ins_p cc, int s, long a, long b, int d)
{
   clear_reg(d);
   outp(ins,cc,zops,NA);
   fprintf(outf,"\t%s%s\t%s,%ld,%ld,%s\n",ins,cc,RN(s),a,b,RN(d));
}

/*
 * fixed point load instructions
 */
void
ld_ir_ins(ins_p ins, ins_p cmplt, ins_p fs, const char *ltrl, long l, int b, int d)
{
    char O[128];
    if (d==GR0)
       return;
    /* build offset, i.e. field selector applied to literal+long */
    if (!(*ltrl))
       sprintf(O,"%s%ld",fs,l);
    else
    if (l>0)
       sprintf(O,"%s%s+%ld",fs,ltrl,l);
    else
    if (l<0)
       sprintf(O,"%s%s-%ld",fs,ltrl,-l);
    else
       sprintf(O,"%s%s",fs,ltrl);
   clear_reg(d);
   outp(ins,NOCOND,zops,NA);
   fprintf(outf,"\t%s%s\t%s(%s),%s\n",ins,cmplt,O,RN(b),RN(d));
}

/*
 * loads a long, l, into a register, d, in at most two instructions
 */
void
imm_to_r(long l, int d)
{
   if (d==GR0)
      return;
   if (SIMM14(l))
      ir_ins(i_ldi,fs_,empty_ltrl,l,d);
   else
   {
      int p=0,n,j;
      while ( (l & (1<<p))==0 ) p++;
      n=p;
      while ( l & (1<<n) ) n++;
      j=n;
      while ( j<32 && (l & (1<<j))==0 ) j++;
      if (j==32)
	 iiir_ins(i_zdepi,c_,-1,31-p,n-p,d);
      else
      {
	 long sll;
	 sll=l>>p;
	 if (sll>0 && SIMM5(sll))
	    iiir_ins(i_zdepi,c_,sll,31-p,5,d);
	 else
	 {
	    ir_ins(i_ldil,fs_L,empty_ltrl,l,d);
	    ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,l,d,d);
	 }
      }
   }
}

void
set_ins(char *e, baseoff a, int d)
{
   char *extname;
   long o;
   int p = 0;
   if (d==GR0)
      return;
   clear_reg(d);
   if (e[0])
      extname = e;
   else
      extname = ext_name(a.base);
   o = a.offset;

   if (a.base<0 )
   {
      p = plabel(a.base);
   }
   if (p)
   {
      if (PIC_code)
      {
	 ir_ins(i_ldil,fs_LP,extname,o,d);
	 ld_ir_ins(i_ldo,cmplt_,fs_RP,extname,o,d,d);
      }
      else
      {
	 ir_ins(i_ldil,fs_LP,extname,o,d);
	 ld_ir_ins(i_ldo,cmplt_,fs_RP,extname,o,d,d);
	 riir_ins(i_extru,c_eq,d,31,1,GR1);
	 ld_ir_ins(i_ldw,cmplt_,fs_,empty_ltrl,-4,GR27,GR1);
	 rrr_ins(i_add,c_,GR1,d,d);
      }
   }
   else
   {
      if (PIC_code)
      {
	 if (plusZ)
	 {
	    ir_ins(i_addil,fs_LT,extname,0,GR19);
	    ld_ir_ins(i_ldw,cmplt_,fs_RT,extname,0,GR1,o==0 ? d : GR1);
	 }
	 else
	 {
	    ld_ir_ins(i_ldw,cmplt_,fs_T,extname,0,GR19,o==0 ? d : GR1);
	 }
	 if (o)
	 {
	    if (SIMM14(o))
	       ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,o,GR1,d);
	    else
	    {
	       ir_ins(i_addil,fs_L,empty_ltrl,o,GR1);
	       ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,o,GR1,d);
	    }
	 }
      }
      else
      {
	 char s[128];
	 sprintf(s,"%s-$global$",extname);
	 ir_ins(i_addil,fs_LR,s,o,GR27);
	 ld_ir_ins(i_ldo,cmplt_,fs_RR,s,o,GR1,d);
      }
   }
}

void
ld_rr_ins(ins_p ins, ins_p cmplt, int a, int b, int d)
{
   if (d==GR0)
      return;
   clear_reg(d);
   outp(ins,NOCOND,zops,NA);
   fprintf(outf,"\t%s%s\t%s(0,%s),%s\n",ins,cmplt,RN(a),RN(b),RN(d));
}

void
ld_ins(ins_p ins, int sgnd, baseoff a, int d)
{
   /* ins must be one of i_lb, i_lh, i_lo, i_lwm or i_lw */
   long o=a.offset;
   const char *i_ld;
   if (d==GR0)
      return;
   clear_reg(d);
   if (IS_FIXREG(a.base))
   {
      int b=a.base;
      i_ld=( ins==i_lb ? i_ldb : ( ins==i_lh ? i_ldh : ( ins==i_lo ? i_ldo : ( ins==i_lwm ? i_ldwm : i_ldw ) ) ) ) ;
      if (SIMM14(o))
	 ld_ir_ins(i_ld,cmplt_,fs_,empty_ltrl,o,b,d);
      else
      {
	 ir_ins(i_addil,fs_L,empty_ltrl,o,b);
	 ld_ir_ins(i_ld,cmplt_,fs_R,empty_ltrl,o,GR1,d);
      }
   }
   else
   {
      char *symb = ext_name(a.base);
      i_ld=( ins==i_lb ? i_ldb : ( ins==i_lh ? i_ldh : ( ins==i_lo ? i_ldo :  i_ldw ) ) ) ;
      if (globaldata((long)a.base))
      {
	 if (PIC_code)
	 {
	    if (plusZ)
	    {
	       ir_ins(i_addil,fs_LT,symb,0,GR19);
	       ld_ir_ins(i_ldw,cmplt_,fs_RT,symb,0,GR1,GR1);
	    }
	    else
	    {
	       ld_ir_ins(i_ldw,cmplt_,fs_T,symb,0,GR19,GR1);
	    }
	    if (SIMM14(o))
	       ld_ir_ins(i_ld,cmplt_,fs_,empty_ltrl,o,GR1,d);
	    else
	    {
	       ir_ins(i_addil,fs_L,empty_ltrl,o,GR1);
	       ld_ir_ins(i_ld,cmplt_,fs_R,empty_ltrl,o,GR1,d);
	    }
	 }
	 else
	 {
	    char s[128];
	    sprintf(s,"%s-$global$",symb);
	    ir_ins(i_addil,fs_LR,s,o,GR27);
	    ld_ir_ins(i_ld,cmplt_,fs_RR,s,o,GR1,d);
	    last_line=line;
	    strcpy(last_symb,symb);
	    last_o=o;
	 }
      }
      else
      {
	 ir_ins(i_ldil,fs_L,symb,o,GR1);
	 ld_ir_ins(i_ld,cmplt_,fs_R,symb,o,GR1,d);
      }
   }
   if (sgnd)
   {
      if (ins==i_lb)
	 riir_ins(i_extrs,c_,d,31,8,d);
      else if (ins==i_lh) /* would have to be, but just checking */
	 riir_ins(i_extrs,c_,d,31,16,d);
   }
}

/*
 * fixed point store instructions
 */
void
st_ir_ins(ins_p ins, ins_p cmplt, int s, ins_p fs, const char *ltrl, long l, int b)
{
    char O[128];

    /* build offset, i.e. field selector applied to literal+long */
    if (!(*ltrl))
       sprintf(O,"%s%ld",fs,l);
    else
    if (l>0)
       sprintf(O,"%s%s+%ld",fs,ltrl,l);
    else
    if (l<0)
       sprintf(O,"%s%s-%ld",fs,ltrl,-l);
    else
       sprintf(O,"%s%s",fs,ltrl);

    outp(ins,NOCOND,zops,NA);
    fprintf(outf,"\t%s%s\t%s,%s(%s)\n",ins,cmplt,RN(s),O,RN(b));
}

void
st_ins(ins_p ins, int s, baseoff a)
{
   /* ins must be one of i_sb, i_sh or i_sw */
   long o=a.offset;
   const char *i_st;

   if (IS_FIXREG(a.base))
   {
      int b=a.base;
      i_st = ( ins == i_sb ? i_stb : ( ins == i_sh ? i_sth : i_stw ) );
      if (SIMM14(o))
	 st_ir_ins(i_st,cmplt_,s,fs_,empty_ltrl,o,b);
      else
      {
	 ir_ins(i_addil,fs_L,empty_ltrl,o,b);
	 st_ir_ins(i_st,cmplt_,s,fs_R,empty_ltrl,o,GR1);
      }
   }
   else
   {
      char *symb = ext_name(a.base);
      i_st = ( ins == i_sb ? i_stb : ( ins == i_sh ? i_sth : i_stw ) );
      if (globaldata((long)a.base))
      {
	 if (PIC_code)
	 {
	    if (plusZ)
	    {
	       ir_ins(i_addil,fs_LT,symb,0,GR19);
	       ld_ir_ins(i_ldw,cmplt_,fs_RT,symb,0,GR1,GR1);
	    }
	    else
	    {
	       ld_ir_ins(i_ldw,cmplt_,fs_T,symb,0,GR19,GR1);
	    }
	    if (SIMM14(o))
	       st_ir_ins(i_st,cmplt_,s,fs_,empty_ltrl,o,GR1);
	    else
	    {
	       ir_ins(i_addil,fs_L,empty_ltrl,o,GR1);
	       st_ir_ins(i_st,cmplt_,s,fs_R,empty_ltrl,o,GR1);
	    }
	 }
	 else
	 {
	    char litrl[128];
	    sprintf(litrl,"%s-$global$",symb);
	    if (last_line==line-1 && pCode[line-1]->ins==i_ldo && !strcmp(symb,last_symb) && last_o==o)
	    {
	       st_ir_ins(i_st,cmplt_,s,fs_R,litrl,o,GR1);
	    }
	    else
	    {
	       ir_ins(i_addil,fs_L,litrl,o,GR27);
	       st_ir_ins(i_st,cmplt_,s,fs_R,litrl,o,GR1);
	    }
	 }
      }
      else
      {
	 ir_ins(i_ldil,fs_L,symb,o,1);
	 st_ir_ins(i_st,cmplt_,s,fs_R,symb,o,GR1);
      }
   }
}

void
ldsid_in(int s, int b, int t)
{
   clear_reg(t);
   outp(i_ldsid,NOCOND,zops,NA);
   fprintf(outf,"\tldsid\t(%s,%s),%s\n",SN(s),RN(b),RN(t));
}

void
mtsp_in(int r, int sr)
{
   outp(i_mtsp,NOCOND,zops,NA);
   fprintf(outf,"\tmtsp\t%s,%s\n",RN(r),SN(sr));
}

/*
 * Branch instructions. These have labels as destination.
 */

/*
 * Unconditional branch.
 */
void
ub_ins(const char *cmplt, int lab)
{
    if (optim & OPTIM_PEEPHOLE)
    {
       int b;
       b=outp(i_ub,NOCOND,zops,lab);
       if (b)
	  fprintf(outf,"%s",GAP);
    }
    else
    {
       fprintf(outf,"\tb%s\tL$$%d\n",cmplt,lab);
       z_ins(i_nop);
    }
}

/*
 * Call instructions
 */
void
bl_in(ins_p n, char *target, int t)
{
   outp(i_bl,NOCOND,zops,NA);
   fprintf(outf,"\tbl%s\t%s,%s\n",n,target,(t==RP ? "%rp" : RN(t)) );
}

void
ble_in(ins_p n, char* wd, int sr, int b)
{
   outp(i_ble,NOCOND,zops,NA);
   fprintf(outf,"\tble%s\t%s(%s,%s)\n",n,wd,SN(sr),RN(b));
}

void
call_ins(ins_p n, char *target, int t, char stub[128])
{
   if (nexps<40872 /*62327*/)
   {
      out_directive(".CALL",stub);
      bl_in(n,target,t);
      z_ins(i_nop);
   }
   else
   {
      /*
       * Module so large that bl is not guarenteed to reach start of
       * subspace - must generate a long call sequence.
       */
      if (PIC_code)
      {
	 int n = next_PIC_pcrel_lab();
	 char s[16];
	 bl_in(cmplt_,".+",RP);
	 sprintf(s,"%s-$PIC_pcrel$%d",target,n);
	 ir_ins(i_addil,fs_L,s,4,RP);
	 sprintf(s,"%s-$PIC_pcrel$%d",target,n+1);
	 ld_ir_ins(i_ldo,cmplt_,fs_R,s,8,GR1,GR1);
	 outlab("$PIC_pcrel$",n);
	 ldsid_in(SR0,GR1,GR31);
	 outlab("$PIC_pcrel$",n+1);
	 mtsp_in(GR31,SR0);
	 out_directive(".CALL",stub);
	 ble_in(cmplt_,"0",SR0,GR1);
	 rr_ins(i_copy,GR31,t);
	 next_PIC_pcrel_lab();
      }
      else
      {
	 char wd[128];
	 sprintf(wd,"%s%s",fs_R,target);
	 ir_ins(i_ldil,fs_L,target,0,GR31);
	 out_directive(".CALL",stub);
	 ble_in(cmplt_,wd,SR4,GR31);
	 rr_ins(i_copy,GR31,t);
      }
   }
   if (PIC_code)
      rr_ins(i_copy,GR5,GR19);
}

/*
 * jump/call to compiler generated external identifier, eg .mulI
 */
void
extj_special_ins(const char *nm, int r, char stub[128], int import)
{
   if (import)
   {
      char s[128];
      sprintf(s,"%s,MILLICODE",nm);
      out_directive(".IMPORT",s);
   }
   out_directive(".CALL",stub);
   bl_in(cmplt_,(char*)nm,MRP);
   rr_ins(i_copy,MRP,r);
}

/*
 * jump/call to value of reg
 */
void
extj_reg_ins(ins_p ins, int reg)
{
   outp(i_bv,NOCOND,zops,NA);
   fprintf(outf,"\tbv\t%%r0(%s)\n",RN(reg));
}

/*
 * Conditional pseudo instructions.
 */
void
addb_in(char *cond, int l, int d, int lab)
{
   int ops[4];
   ops[0]=l;
   ops[1]=d;
   outp(i_addb,cond,ops,lab);
   fprintf(outf,"\taddb%s,N\t%s,%s,L$$%d\n",cond,RN(l),RN(d),lab);
   z_ins(i_nop);
}

void
addib_in(char *cond, int i, int d, int lab)
{
   int ops[4];
   ops[0]=i;
   ops[1]=d;
   outp(i_addib,cond,ops,lab);
   fprintf(outf,"\taddib%s,N\t%d,%s,L$$%d\n",cond,i,RN(d),lab);
   z_ins(i_nop);
}

/*
 * register comparisons
 */
void
comb_ins(const char *cond, int l, int r, int lab)
{
   int ops[4];
   ops[0]=l;
   ops[1]=r;
   outp(i_comb,cond,ops,lab);
   if (lab<0)
      fprintf(outf,"\tcomb%s\t%s,%s,.+%d\n",cond,RN(l),RN(r),-lab);
   else
      fprintf(outf,"\tcomb%s\t%s,%s,L$$%d\n",cond,RN(l),RN(r),lab);
}

/*
 * constant/register comparison
 */
void
comib_ins(ins_p cond, int l, int r, int lab)
{
   int ops[4];
   ops[0]=l;
   ops[1]=r;
   outp(i_comib,cond,ops,lab);
   if (lab<0)
      fprintf(outf,"\tcomib%s\t%d,%s,.+%d\n",cond,l,RN(r),-lab);
   else
      fprintf(outf,"\tcomib%s\t%d,%s,L$$%d\n",cond,l,RN(r),lab);
}

void
cj_ins(const char *cond, int l, int r, int lab)
{
   int ops[4];
   ops[0]=l;
   ops[1]=r;
   if (optim & OPTIM_PEEPHOLE)
   {
      outp(i_cj,cond,ops,lab);
      fprintf(outf,"%s",GAP);
   }
   else
   {
      rrr_ins(i_comclr,opp(cond),l,r,0);
      ub_ins(cmplt_,lab);
   }
}

/*
 * register, immediate comparison
 */
void
cij_ins(const char *cond, long l, int r, int lab)
{
   int ops[4];
   ops[0]=l;
   ops[1]=r;
   if (SIMM5(l))
   {
      if (optim & OPTIM_PEEPHOLE)
      {
	 outp(i_cij,cond,ops,lab);
	 fprintf(outf,"%s",GAP);
      }
      else
      {
	 irr_ins(i_comiclr,opp(cond),fs_,l,r,0);
	 ub_ins(cmplt_,lab);
      }
   }
   else
   {
      /* use temp reg for large constant */
      if (r == GR1)
	 /* should not happen */
	 fail("ins: temp reg in use when needed for large constant");
      else
      {
	 imm_to_r(l,GR1);
	 if (optim & OPTIM_PEEPHOLE)
	 {
	    cj_ins(cond,GR1,r,lab);
	 }
	 else
	 {
	    rrr_ins(i_comclr,opp(cond),GR1,r,0);
	    ub_ins(cmplt_,lab);
	 }
      }
   }
}

/*
 * Branch on bit.
 */
void
bb_in(ins_p cond, int r, int b, int lab)
{
   int ops[4];
   ops[0]=r;
   ops[1]=b;
   outp(i_bb,cond,ops,lab);
   fprintf(outf,"%s",GAP);
}

/*
 * Floating point instructions.
 */
void
ldf_ir_ins(ins_p ins, int o, int b, int d)
{
   clear_freg(d);
   outp(ins,NOCOND,zops,NA);
   fprintf(outf,"\t%s\t%d(%s),%s\n",ins,o,RN(b),FN(d));
}

void
ldf_rr_ins(ins_p ins, ins_p cmplt, int a, int b, int d)
{
   clear_freg(d);
   outp(ins,NOCOND,zops,NA);
   fprintf(outf,"\t%s%s\t%s(%s),%s\n",ins,cmplt,RN(a),RN(b),FN(d));
}

void
ldf_ins(ins_p ins, baseoff a, int d)
{
   /* ins must be either i_fldw or i_fldd */
   const char *i_fld = ( ins==i_fldw ? i_fldws : i_fldds );
   if (IS_FIXREG(a.base))
   {
      if (SIMM5(a.offset))
	 ldf_ir_ins(i_fld, a.offset, a.base, d);
      else
      {
	 /* offset too big, put in temp reg and use ldf_ir_ins */
	 /* +++ arrange stack variable to minimise this */
	 assert(a.base != GR1);	/* otherwise we corrupt it */
	 if (SIMM14(a.offset))
	    ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,a.offset,a.base,GR1);
	 else
	 {
	    ir_ins(i_addil,fs_L,empty_ltrl,a.offset,a.base);
	    ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,a.offset,GR1,GR1);
	 }
	 ldf_ir_ins(i_fld, 0, GR1, d);
      }
   }
   else
   {
      /* global */
      set_ins("",a,GR1);
      ldf_ir_ins(i_fld, 0, GR1, d);
   }
}

void
stf_ir_ins(ins_p ins, int s, int o, int b)
{
   outp(ins,NOCOND,zops,NA);
   fprintf(outf,"\t%s\t%s,%d(%s)\n",ins,FN(s),o,RN(b));
}

void
stf_rr_ins(ins_p ins, int s, int a, int b)
{
   outp(ins,NOCOND,zops,NA);
   fprintf(outf,"\t%s\t%s,%s(%s)\n",ins,FN(s),RN(a),RN(b));
}

void
stf_ins(ins_p ins, int s, baseoff a)
{
   /* ins must be either i_fstw or i_fstd */


   const char *i_fst = ( ins==i_fstw ? i_fstws : i_fstds );
   if (IS_FIXREG(a.base))
   {
      if (SIMM5(a.offset))
	 stf_ir_ins(i_fst, s, a.offset, a.base);
      else
      {
	 /* offset too big, put in temp reg and use stf_ir_ins */
	 /* +++ arrange stack variable to minimise this */
	 assert(a.base != GR1);	/* otherwise we corrupt it */
	 if (SIMM14(a.offset))
	    ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,a.offset,a.base,GR1);
	 else
	 {
	    ir_ins(i_addil,fs_L,empty_ltrl,a.offset,a.base);
	    ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,a.offset,GR1,GR1);
	 }
	 stf_ir_ins(i_fst, s, 0, GR1);
      }
   }
   else
   {
      /* global */
      set_ins("",a,GR1);
      stf_ir_ins(i_fst, s, 0, GR1);
   }
}

void
cmp_rrf_ins(ins_p ins, ins_p fmt, ins_p cond, int a, int b)
{
   outp(ins,NOCOND,zops,NA);
   fprintf(outf,"\t%s%s%s\t%s,%s\n",ins,fmt,cond,FN(a),FN(b));
}

void
rrf_ins(ins_p ins, ins_p from_fmt, ins_p to_fmt, int a, int b)
{
   outp(ins,NOCOND,zops,NA);
   fprintf(outf,"\t%s%s%s\t%s,%s\n",ins,from_fmt,to_fmt,FN(a),FN(b));
}

void
rrrf_ins(ins_p ins, ins_p fmt, int a, int b, int dest)
{
   clear_freg(dest);
   fprintf(outf, "\t%s%s\t%s,%s,%s\n",ins,fmt,FN(a),FN(b),FN(dest));
   outp(ins,NOCOND,zops,NA);
}

/*
 * Directives
 */
void
out_directive(const char *d, const char *params)
{
  /* directive, parameters */
   outp(directive,NOCOND,zops,NA);
   fprintf(outf,"\t%s\t%s\n",d,params);
}

/*
 * Print a label
 */
void
outlab(char *prefix, int n)
{
    if (prefix[0]=='L' && prefix[1]=='$')
       outp(i_lab,NOCOND,zops,n);
    else
       outp(i_,NOCOND,zops,NA);
    fprintf(outf,"%s%d\n",prefix,n);
}

