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


/**********************************************************************
$Author: release $
$Date: 1998/02/04 10:43:38 $
$Revision: 1.2 $
$Log: dwarf_out.c,v $
 * Revision 1.2  1998/02/04  10:43:38  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1997/03/24  12:44:29  pwe
 * outn int->long
 *
 * Revision 1.4  1997/02/19  12:53:47  pwe
 * NEWDIAGS for debugging optimised code
 *
 * Revision 1.3  1995/09/28  12:39:48  pwe
 * dwarf.h via import, and type changes for tcc checks
 *
 * Revision 1.2  1995/09/13  14:25:38  pwe
 * tidy for gcc
 *
 * Revision 1.1.1.1  1995/08/14  14:30:23  pwe
 * transferred from DJCH
 *
**********************************************************************/

/* extra fns for writing DWARF info */
/* LOG 6/9/93 changes for sparc/ICL port of SVR4.2 djch
   */
/* LOG 7/9/93 this will only compile with -Ycommon, assuming 32 bit int
   makes life a lot easier djch. several changes of long to int to
   get weak prototypes to work */
/* LOG 25/11/93 removed redundant labbufe djch */

#include "config.h"
#include "common_types.h"
#include "installtypes.h"
#include "machine.h"

/* machine dependant */
#include "out.h"

#include "diagglob.h"
#include "diagtypes.h"
#include "basicread.h"

/* machine dependant */
#include "expmacs.h"

#include "shapemacs.h"

#include "xalloc.h"
#include "dwarf_types.h"
#include "dwarf_loc.h"
#include "dwarf_mc.h"
#include "dwarf_out.h"
#include "cross_config.h"
#ifdef NEWDIAGS
#include "tags.h"
#endif

#ifndef CROSS_INCLUDE
#include <dwarf.h>
#else
#include CROSS_INCLUDE/dwarf.h>
#endif

#define WHOLE_LINE ( 0xffff)	/* this should be in dwarf.h */
#define WHOLE_SECT ( 0)		/* this should be in dwarf.h */

#if issparc
#define DWARF_NAME "D"
#else
#define DWARF_NAME "dwf"
#endif

#if (is80x86)
static char * nl80x86 = "\n";
#define outnl()	outs(nl80x86)	/* avoid side effects of 80x86 outnl */
#endif

void out_dwarf_lab
    PROTO_N ( (l) )
    PROTO_T ( H_dwarf_lab *l )
{
  if (OUT_FLAG(*l) !=0)
  {
    failer("attempt to re_output dwarf label");
    exit(EXIT_FAILURE);
  }
  OUT_FLAG(*l) = (char)1;
  outs(LAB2CHAR(*l));
  outc(':');
  outnl();
}

static void mk_dwarf_label
    PROTO_N ( (p,x) )
    PROTO_T ( dwarf_label *p X CONST char *x )
{
  sprintf(LAB2CHAR(p->beg),"%s%s%s",local_prefix,DWARF_NAME,x);
  OUT_FLAG(p->beg) = 0;
  sprintf(LAB2CHAR(p->end),"%s%s%s.e",local_prefix,DWARF_NAME,x);
  OUT_FLAG(p->end) = 0;
}

void next_dwarf_lab
    PROTO_N ( (p) )
    PROTO_T ( dwarf_label *p )
{
  static unsigned long next_dwarf_lab_no = 0;
  char num_buf[DWARF_LAB_LEN];

  sprintf(num_buf,"%ld",next_dwarf_lab_no++);
  mk_dwarf_label(p,num_buf);
}

dwarf_type_label * next_dwarf_type_lab
    PROTO_Z ()
{
  dwarf_type_label * ptr = (dwarf_type_label *)
    xcalloc(1,sizeof (dwarf_type_label));

  static unsigned long next_dwarf_type_lab_no = 0;

  sprintf(LAB2CHAR(*ptr),"%s%sT%ld",local_prefix,DWARF_NAME,
	  next_dwarf_type_lab_no++);
  return ptr;
}

#if (is80x86)
#define GO_DWARF	outs("\t.section\t.debug");outnl()
#define GO_LINE		outs("\t.section\t.line");outnl()
#define LEAVE_DWARF	outs("\t.previous");outnl()
#define LEAVE_LINE	LEAVE_DWARF
#define BYTE4S		".4byte"
#define BYTE2S		".2byte"
#define BYTE		".byte"
#define STRING		".string"
#define TEXT_SEG 	".text"
#define END_UNIT_ALIGN  ".align 4"
#define SUB3_F		"[ %s - %s] - %s\t"
#else
#if (issparc)

#define GO_DWARF	outs("\t.pushsection\t\".debug\"");outnl()
#define GO_LINE		outs("\t.pushsection\t\".line\"");outnl()
#define LEAVE_DWARF	outs("\t.popsection");outnl()
#define LEAVE_LINE	LEAVE_DWARF
#define BYTE4S		".uaword"
#define BYTE2S		".uahalf"
#define BYTE		".byte"
#define STRING		".asciz"
#define TEXT_SEG 	".section \".text\""
#define END_UNIT_ALIGN  ".align 4"
#define SUB3_F		"(%s - %s) - %s\t"

#else
error need elf section swapping code
#endif
#endif

#if FS_CONCAT_STRING

#define BYTE4_F "\t"BYTE4S"\t%s"
#define BYTE2_CMT_F "\t"BYTE2S COMMENT_2("\t%#x\t","%s")
#define BYTE2_F "\t"BYTE2S"\t%s"
#define BYTE_CMT_F "\t"BYTE COMMENT_2("\t%#x\t","%s")
#define STRING_M "\t"STRING"\t"
#define STRING_F STRING_M"\"%s\""
#define END_UNIT "\t"END_UNIT_ALIGN

#else
#if (issparc)
/* KEEP these in step.......... */
#define BYTE4_F "\t.uaword\t%s"
#define BYTE2_CMT_F "\t.uahalf\t%#x\t!%s"
#define BYTE2_F "\t.uahalf\t%s"
#define BYTE_CMT_F "\t.byte\t%#x\t!%s"
#define STRING_M "\t.asciz\t"
#define STRING_F "\t.asciz\t\"%s\""
#define END_UNIT "\t.align 4"
#else
#if (is80x86)
#define BYTE4_F "\t.4byte\t%s"
#define BYTE2_CMT_F "\t.2byte\t%#x\t!%s"
#define BYTE2_F "\t.2byte\t%s"
#define BYTE_CMT_F "\t.byte\t%#x\t!%s"
#define STRING_M "\t.string\t"
#define STRING_F "\t.string\t\"%s\""
#define END_UNIT "\t.align 4"
#else
error not yet written
#endif
#endif
#endif

void dwarf4
    PROTO_N ( (t) )
    PROTO_T ( CONST char *t )
{
  char outbuf[100];

  sprintf(outbuf,BYTE4_F,t);

  outs(outbuf);
  outnl();
}

void dwarf4n
    PROTO_N ( (x) )
    PROTO_T ( int x )
{
  char outbuf[100];

  sprintf(outbuf,"%#x",x);
  dwarf4(outbuf);
}

void out_dwarf_thing
    PROTO_N ( (t,cmt) )
    PROTO_T ( int t X char *cmt )
{
  char outbuf[100];

  if (t > 0xffff)
    failer("value too big for .2byte constant in out_dwarf_thing");

  sprintf(outbuf,BYTE2_CMT_F,t,cmt);
  outs(outbuf);
  outnl();
}

void out_dwarf_string
    PROTO_N ( (s) )
    PROTO_T ( CONST char * CONST s )
{
  /* s = null term'ed in core and to be in asm file */
  char outbuf[100];

  sprintf(outbuf,STRING_F,s);
  outs(outbuf);
  outnl();
}

void dwarf2
    PROTO_N ( (c) )
    PROTO_T ( char *c )
{
  char outbuf[100];

  sprintf(outbuf,BYTE2_F,c);
  outs(outbuf);
  outnl();
}

void out_dwarfone
    PROTO_N ( (t,cmt) )
    PROTO_T ( int t X char *cmt )
{
  char outbuf[100];

  sprintf(outbuf,BYTE_CMT_F,t,cmt);
  outs(outbuf);
  outnl();
}

static dwarf_label 	dwarf_blk_stk[100];
static unsigned int 	dwarf_blk_stk_ptr=0;

void enter_dwarf_blk
    PROTO_N ( (four,exclusive,lb) )
    PROTO_T ( int four X int exclusive X dwarf_label *lb )
{
				/* switch to debug section, put out begin
				 label and length expr */
  char exprbuf[100];

  dwarf_blk_stk[dwarf_blk_stk_ptr++] = *lb;
				/* the block stack is used for nested
				 dwarf blocks, not for sibling structure */

  if (four)			/* two byte block are already in debug */
    GO_DWARF;

  OUT_DWARF_BEG(lb);
  if (exclusive)
    sprintf(exprbuf,COMMENT_2(SUB3_F," excl. entry len")
	    ,lb->end,lb->beg,
	    four ? "4":"2");
  else
    sprintf(exprbuf,COMMENT_2("%s-%s\t"," entry len"),lb->end,lb->beg);
  if (four)
    dwarf4(exprbuf);
  else
    dwarf2(exprbuf);
}

void leave_dwarf_blk1
    PROTO_N ( (leave) )
    PROTO_T ( int leave )
{
  if (dwarf_blk_stk_ptr == 0)
    failer("dwarf stack underflow");
  {
    dwarf_label *lb = &dwarf_blk_stk[--dwarf_blk_stk_ptr];

    OUT_DWARF_END(lb);
    if (leave)
      LEAVE_DWARF;
  }
}

char * current_label_name
    PROTO_Z ()
{
  return LAB2CHAR(dwarf_blk_stk[dwarf_blk_stk_ptr - 1].beg);
}


void new_dwarf_blk2
    PROTO_Z ()
{
  dwarf_label lb;
  next_dwarf_lab(&lb);

  enter_dwarf_blk(0,1,&lb);
}

void new_dwarf_blk4
    PROTO_Z ()
{
  dwarf_label lb;
  next_dwarf_lab(&lb);

  enter_dwarf_blk(1,1,&lb);
}

static dwarf_label text_range;
static dwarf_label line_range;

void out_diagnose_prelude
    PROTO_Z ()
{

  char exprbuf[100];

  mk_dwarf_label(&text_range,"text");
  mk_dwarf_label(&line_range,"line");

  outs(TEXT_SEG);
  outnl();
  OUT_DWARF_BEG(&text_range);
  GO_DWARF;
  LEAVE_DWARF;
  GO_LINE;
  LEAVE_LINE;

  GO_LINE;
  OUT_DWARF_BEG(&line_range);
  sprintf(exprbuf,"%s-%s",line_range.end,line_range.beg);
  dwarf4(exprbuf);
  dwarf4(text_range.beg);
  LEAVE_LINE;
  enter_dwarf_comp_unit();

}

void out_diagnose_postlude
    PROTO_Z ()
{
  char exprbuf[100];

  leave_dwarf_comp_unit();

  outs(TEXT_SEG);
  outnl();
  OUT_DWARF_END(&text_range);
  GO_LINE;
  dwarf4n(WHOLE_SECT);			/* line 0 means whole section */
  dwarf2c(WHOLE_LINE);
  sprintf(exprbuf,"%s-%s",text_range.end,text_range.beg);
  dwarf4(exprbuf);
  OUT_DWARF_END(&line_range);
  LEAVE_LINE;
}

static filename main_filename;

void out_dwarf_sourcemark
    PROTO_N ( (x) )
    PROTO_T ( CONST sourcemark * CONST x )
{
  dwarf_label lb;

  if (x->file != main_filename)
  {
/*    fprintf(stderr,"Sourcemark for file %s cannot be used\n",
	    TDFSTRING2CHAR(x->file->file));*/
    return;
  }

  next_dwarf_lab(&lb);
  OUT_DWARF_BEG(&lb);		/* note this label is in TEXT space */

  GO_LINE;
  dwarf4n((int)x->line_no.nat_val.small_nat);
  if ((x->char_off.nat_val.small_nat) == 0)
    out_dwarf_thing(WHOLE_LINE,"no source pos");
  else
    out_dwarf_thing((int)x->char_off.nat_val.small_nat,"source pos");
  {
    char expr_buf[100];

    sprintf(expr_buf,"%s - %s",LAB2CHAR(lb.beg),LAB2CHAR(text_range.beg));
    dwarf4(expr_buf);
  }
  LEAVE_LINE;
}

static dwarf_label 	dwarf_sib_stk[100];
static int	 	dwarf_sib_stk_ptr= -1;
/* static dwarf_label	underflow_lab = {"underflow","undeflow.e"};*/

#define SIB_TOS	        (dwarf_sib_stk[dwarf_sib_stk_ptr])
#define SIB_PUSH	(dwarf_sib_stk[++dwarf_sib_stk_ptr])
#define SIB_POP		(--dwarf_sib_stk_ptr)

/* ((dwarf_sib_stk_ptr) ==0 ? failer("sib stack underflow"), underflow_lab */

void start_sib_chain1
    PROTO_N ( (d_tag,tag_name) )
    PROTO_T ( int d_tag X char *tag_name )
{
				/* generate new label
				 enter blk for new label
				 gen sib label
				 push sib label
				 gen sib chain */
  dwarf_label chain_head;
  next_dwarf_lab(&chain_head);

  enter_dwarf_entry(&chain_head);
  next_dwarf_lab(&SIB_PUSH);

  OUT_DWARF_TAG_NAMED(d_tag,tag_name);
  outs(COMMENT_2("\t"," new sibling chain level "));
  outn((long)dwarf_sib_stk_ptr);
  outnl();
  OUT_DWARF_ATTR(AT_sibling);
  dwarf4(SIB_TOS.beg);
}

void make_next_new_chain
    PROTO_Z ()
{
  /* simulate entering next level */
  next_dwarf_lab(&SIB_PUSH);
}

void cont_sib_chain1
    PROTO_N ( (d_tag,tag_name) )
    PROTO_T ( int d_tag X char *tag_name )
{
				/* enter blk for TOS
				 gen sib label
				 setq TOS sib label
				 gen sib chain */
  enter_dwarf_entry(&SIB_TOS);
  next_dwarf_lab(&SIB_TOS);
  outs(COMMENT_2("\t"," sibling chain level "));
  outn((long)dwarf_sib_stk_ptr);
  outnl();

  OUT_DWARF_TAG_NAMED(d_tag,tag_name);
  OUT_DWARF_ATTR(AT_sibling);
  dwarf4(SIB_TOS.beg);
}

void end_sib_chain
    PROTO_Z ()
{
				/* enter blk for TOS
				   gen dummy blk
				   pop stack
				   leave blk */
  enter_dwarf_entry(&SIB_TOS);
  outs(COMMENT_2("\t"," end sibling chain level "));
  outn((long)dwarf_sib_stk_ptr);
  outnl();
  leave_dwarf_blk();
  SIB_POP;
}

static void end_toplevel_chain
    PROTO_Z ()
{
				/* just put out the label */
  GO_DWARF;
  OUT_DWARF_BEG(&SIB_TOS);
  outs(COMMENT_2("\t"," end toplevel chain"));
  outnl();
  LEAVE_DWARF;
  SIB_POP;
}

				/* HACK to get a filename */
static long name_space;

static char *first_filename = (char *) 0;

void dwarf_inspect_filename
    PROTO_N ( (f) )
    PROTO_T ( filename f )
{
  if (first_filename)
    return;
  {
    char * str = TDFSTRING2CHAR(f->file);
    char *lastdot = strrchr(str,'.');

    if (!lastdot)
      return;			/* no dot in name */

    if (lastdot[1] != 'h')
    {
      first_filename = (char *) xcalloc(1,strlen(str) + 1);
				/* +1 for null ending */
      strcpy(first_filename,str);

      main_filename = f;	/* note this to validate sourcemarks */

      fflush(fpout);
      {
	long old_tell = ftell(fpout);

	fseek(fpout,name_space,SEEK_SET);
	outc('"'); outs(str); outc('"');
	fseek(fpout,old_tell,SEEK_SET);
      }
    }
  }
}

extern char *crt_filename;

static void maybe_fix_filename
    PROTO_Z ()
{
  char name_buf[100];
  char * last_dot;

  if (first_filename)		/* seen a .c already */
    return;

  if (crt_filename == NULL)
    name_buf[0] = '\0';
  else
    strcpy(name_buf,crt_filename);

  if (strlen(name_buf) > 0)
  {
    last_dot = strrchr(name_buf,'.');

    if (last_dot)
      last_dot[1] = 'c';
    else
      strcpy(name_buf,"UNKNOWN_SUFFIX.c");
  }
  else
    strcpy(name_buf,"UNKNOWN_FILE.c");

  fflush(fpout);
  {
    long old_tell = ftell(fpout);

    fseek(fpout,name_space,SEEK_SET);
    outc('"'); outs(name_buf); outc('"');
    fseek(fpout,old_tell,SEEK_SET);
  }
}

void enter_dwarf_comp_unit
    PROTO_Z ()
{
 start_sib_chain(TAG_compile_unit);
  OUT_DWARF_ATTR(AT_name);
  outs(STRING_M);
  fflush(fpout);
  name_space = ftell(fpout);
  outs("                                                                    ");
  outs("                                                                    ");
  outnl();
  OUT_DWARF_ATTR(AT_language);
  dwarf4n((int)LANG_C89);
  OUT_DWARF_ATTR(AT_low_pc);
  dwarf4(LAB2CHAR(text_range.beg));
  OUT_DWARF_ATTR(AT_high_pc);
  dwarf4(LAB2CHAR(text_range.end));
  OUT_DWARF_ATTR(AT_stmt_list);
  dwarf4(LAB2CHAR(line_range.beg));
  leave_dwarf_blk();

  make_next_new_chain();
}


#include "dwarf_type.h"
#include "dwarf_queue.h"


void leave_dwarf_comp_unit
    PROTO_Z ()
{
  dump_type_q();
  end_sib_chain();		/* end sib chain below comp unit */

  {
    dwarf_label lb;
    next_dwarf_lab(&lb);

    enter_dwarf_blk(1,0,&lb);
    outs(END_UNIT);
    outnl();
    leave_dwarf_blk();
  }

  end_toplevel_chain();		/* sib of comp unit */
  maybe_fix_filename();
}

void out_dwarf_name_attr
    PROTO_N ( (s) )
    PROTO_T ( CONST char * CONST s )
{
  if (*s == 0)
  {
    outs(COMMENT_2("\t"," no source name"));
    outnl();
    return;
  }
  OUT_DWARF_ATTR(AT_name);
  out_dwarf_string(s);
}

void out_dwarf_bytesize_attr
    PROTO_N ( (t) )
    PROTO_T ( shape t )
{
  OUT_DWARF_ATTR(AT_byte_size);
  dwarf4n((int)(shape_size(t)/8));
}


static void dwarf_out_descriptor
    PROTO_N ( (x) )
    PROTO_T ( diag_descriptor *x )
{
  switch(x->key)
  {
   case DIAG_ID_KEY:
    {
      exp acc = x->data.id.access;
      exp t = son(acc);
#ifdef NEWDIAGS
      if (name(acc) != hold_tag) {
	failer("access should be in hold");
	break;
      };
      acc = son(acc);
      if (name(acc) == cont_tag && name(son(acc)) == name_tag && isvar(son(son(acc))))
	acc = son(acc);
      if (name(acc) != name_tag) {
	failer("not name_tag");
	break;
      };
      t = son(acc);
#endif

      if (!isvar(brog(t)->dec_u.dec_val.dec_exp)
	  && (name(brog(t)->dec_u.dec_val.dec_shape) == prokhd))
/*	fprintf(stderr,"%s was a proc\n",TDFSTRING2CHAR(x->data.id.nme));*/
	break;
      else
      {
	if (isparam(t))
	  failer("out descriptor for parameter variable");
	if (!brog(t)->dec_u.dec_val.extnamed)
	  cont_sib_chain(TAG_local_variable);
	else
	  cont_sib_chain(TAG_global_variable);

	out_dwarf_name_attr(TDFSTRING2CHAR(x->data.id.nme));
	out_dwarf_type_attr(x->data.id.new_type);
	out_dwarf_loc_attr(acc,-1);
	/* -1 for proc_no, since outside any proc */
	leave_dwarf_blk();
      }
      break;
    }
   case DIAG_STRUCT_KEY:
    fprintf(stderr,"Not yet doing desc key %d name %s\n",x->key,
	    TDFSTRING2CHAR(x->data.id.nme));
    break;
   case DIAG_TYPEDEF_KEY:
    if ((base_type(x->data.typ.new_type))->key == DIAG_TYPE_INITED)
    {
/*      fprintf(stderr,"No diagtype defn provided for %s... omitting typedef\n",
	      TDFSTRING2CHAR(x->data.typ.nme)); */
      break;
    }
    cont_sib_chain(TAG_typedef);
    out_dwarf_name_attr(TDFSTRING2CHAR(x->data.typ.nme));
    out_dwarf_type_attr(x->data.typ.new_type);
    leave_dwarf_blk();
    break;
   default:
    failer("Unknown descriptor");
  }
}


void out_dwarf_global_list
    PROTO_Z ()
{
  int i;

/*  fprintf(stderr,"diagvartab len %d used %d\n",unit_diagvar_tab.len,
	  unit_diagvar_tab.lastused); */
  outs(COMMENT_2("\t","\tdumping global list"));
  outnl();
  for(i=0;i<unit_diagvar_tab.lastused;i++)
    dwarf_out_descriptor(&(unit_diagvar_tab.array[i]));
  dump_type_q();
}

void out_dwarf_diag_tags
    PROTO_Z ()	/* maybe put out unused ones later */
{
  return;
}


dwarf_global *new_dwarf_global
    PROTO_N ( (d) )
    PROTO_T ( diag_descriptor * d )
{
  dwarf_global * new = (dwarf_global *) xcalloc(1,sizeof(dwarf_global));

  new->desc = d;

  return new;
}
