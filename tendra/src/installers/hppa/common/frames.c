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
$Log: frames.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1996/11/14  15:22:13  wfs
 *    Fixed a bug in regexps.c which was common to most of the installers and
 * has only just come to light due to PWE's work on powertrans. (There was
 * previously only a patch.) Cosmetic changes to other files.
 *
 * Revision 1.5  1996/10/24  15:51:14  wfs
 * Added "~alloc_size" special token. Minor change to alloca_tag - only need
 * one word for storage of pointer. Major change to round_tag (rounding to
 * unsigned chars) in the fix of avs bug.
 *
 * Revision 1.4  1996/09/06  10:38:19  wfs
 * bug fixes to "offset.pl" and cosmetic changes to the dynamic initialization
 * code.
 *
 * Revision 1.3  1996/09/05  11:05:08  wfs
 * "dynamic_init" boolean variable removed - must always be considered true.
 *
 * Revision 1.2  1995/12/18  13:11:19  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.5  1995/10/11  15:52:57  wfs
 * "Has_no_vcallers" was defined incorrectly.
 *
 * Revision 5.4  1995/10/09  13:04:27  wfs
 * Cosmetic changes.
 *
 * Revision 5.3  1995/09/15  14:47:07  wfs
 * Removed "#include "extra_expmacs.h"".
 *
 * Revision 5.2  1995/09/15  12:20:09  wfs
 * "extra_expmacs.h" included + minor variable name changes and
 * initializations.
 *
 * Revision 5.1  1995/09/07  15:41:49  wfs
 * Removed "extra_expmacs.h" include.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  09:20:13  wfs
 * All the stuff (formerly in "proc.c") which set up the variables
 * for stack frames has been moved to frames.c. Substantial comments
 * have been added.
 *
 * Revision 3.4  1995/08/25  09:20:13  wfs
 * All the stuff (formerly in "proc.c") which set up the variables
 * for stack frames has been moved to frames.c. Substantial comments
 * have been added.
 *
 * Revision 3.1  95/04/10  16:26:26  16:26:26  wfs (William Simmonds)
 * Apr95 tape version.
 *
 * Revision 3.0  95/03/30  11:17:06  11:17:06  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 *
 * Revision 2.0  95/03/15  15:26:53  15:26:53  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 *
 * Revision 1.1  95/01/11  13:06:47  13:06:47  wfs (William Simmonds)
 * Initial revision
 *
*/


#include "config.h"
#include "bitsmacs.h"
#include "common_types.h"
#include "expmacs.h"
#include "procrec.h"
#include "tags.h"
#include "addrtypes.h"
#include "hppains.h"
#include "regmacs.h"
#include "flags.h"
#include "frames.h"

extern char *proc_name;
extern int bitsin PROTO_S ((long));
extern exp father PROTO_S ((exp));
extern int diagnose;
extern int gdb;

bool Has_fp = 0;
bool Has_vsp = 0;
bool Has_tos = 0;
bool No_S = 0;
bool Has_ll = 0;
bool Has_checkalloc = 0;
bool Has_callees = 0;
bool Has_vcallees = 0;
bool Has_no_vcallers = 0;
bool Uses_crt_env = 0;
bool is_PIC_and_calls = 0;
bool plusZ;
int fixdump = 0;
long callee_sz;
long callees_offset;
long locals_offset;
long max_args;
long params_offset;
long locals_space;
long frame_sz;
long stackerr_lab;
long aritherr_lab;

baseoff MEM_TEMP_BOFF;
baseoff LONG_RESULT_BOFF;
baseoff SP_BOFF;
baseoff FP_BOFF;

/*
	The purpose of this file (the 5th revision) is to collect together
     all the code which maintains the stack frame. Below is an illustration
     of the >>most general<< stack frame.



	|                                       |
	|---------------------------------------|<--SP
	|                                       |
	|                                       |
	|                                       |
	|                                       |
	|                                       |
	|                                       |
	|                                       |
	|         8 word "frame marker"         |
	|                                       |
	|                                       |
	|                                       |
	|                                       |
	|                                       |
	|                                       |
	|                                       |
	|---------------------------------------|
	|                                       |
	|                                       |
	|                                       |
	|        4 word "parameter dump"        |
	|                                       |
	|                                       |
	|                                       |
	|---------------------------------------|
	|                                       |
	:                                       :
	:          remaining arguments          :
	:                                       :
	|                                       |
	|---------------------------------------|
	|                                       |
	:                                       :
	:      dynamically allocated space      :
	:                                       :
	|                                       |
	|---------------------------------------|
	|                                       |
	|       2 words of temporary mem        |
	|                                       |
	|---------------------------------------|
	|                                       |
	|       2 words for long result         |
	|                                       |
	|---------------------------------------|
	|     1 word to keep track of SP        |
	|---------------------------------------|
	|                                       |
	:                                       :
	:                                       :
	:                                       :
	:            locals space               :
	:                                       :
	:                                       :
	:                                       :
	|                                       |
	|---------------------------------------|
	|                                       |
	:                                       :
	:                                       :
	:                                       :
	:            callees space              :
	:                                       :
	:                                       :
	:                                       :
	|                                       |
	|---------------------------------------|
	|        2 words for callee_sz          |
	|---------------------------------------|
	|                                       |
	:                                       :
	:  s reg save space (16 words maximum)  :
	:                                       :
	|                                       |
	|---------------------------------------|<--FP (=OLD SP)
	|                                       |




	   EP ("enviroment" pointer) is a copy of the SP before (if ever) SP
	is incremented to create dynamically allocated space.
	   The locals, the temporary memory, the long result words, and the
	stack copies of SP and FP (both reset at possible long jump
	targets) are all offset relative to EP. If Has_fp==0, then the
	parameters and the callees are also offset relative to EP,
	otherwise they are offset relative to FP. The callee_sz is stored
	on the stack only when Has_vcallees==1, and therefore Has_fp==1,
	and is offset relative to FP.

*/


void setframe_flags
    PROTO_N ( (e,leaf) )
    PROTO_T ( exp e X bool leaf )
{
   /* e is a proc_tag */
   unsigned char ne = name(e);
   Uses_crt_env = proc_uses_crt_env(e);
   No_S = ( !leaf && Uses_crt_env && proc_has_lv(e)
		  && (ne!=general_proc_tag || !proc_has_nolongj(e)) );
   Has_ll = procrecs[no(e)].Has_ll;
   Has_checkalloc = procrecs[no(e)].Has_checkalloc;
   Has_vsp = ( proc_has_alloca(e) || No_S || ne==general_proc_tag  );
   Has_tos = ( No_S && proc_has_alloca(e) );
   Has_callees = ( ne==general_proc_tag );
   Has_vcallees = ( ne==general_proc_tag && proc_has_vcallees(e) );
   Has_no_vcallers = ( ne==proc_tag || !proc_has_vcallers(e) );
   Has_fp = ( Has_vcallees || gdb );
   /*  n.b. gdb, apparently, tracks all locals and parameters via +ve
       offsets relative to a frame pointer = %r3. We comply by putting
       Has_fp=1  */
   is_PIC_and_calls = ( PIC_code && !leaf );

#ifdef Try_No_S
   No_S = 1;
#endif
#ifdef Try_Has_fp
   Has_fp = !leaf;
#endif
#ifdef Try_Has_tos
   Has_tos = 1;
#endif
}


void set_up_frame
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
    procrec * pr = & procrecs[no(e)];
    needs * ndpr = & pr->needsproc;
    spacereq *sppr = & pr->spacereqproc;
    long pprops = (ndpr->propsneeds);
    bool leaf = (pprops & anyproccall) == 0;
    long ma = ndpr->maxargs;   /* maxargs of proc body in bits  */
    long st = sppr->stack;    /*  space for locals in bits     */
    bool simpleans = (pprops & long_result_bit) == 0;
    int cs = pr->callee_sz;

    setframe_flags(e,leaf);

    if (No_S)
    {
       fixdump = -65536; /* dump all sregs */
    }
    else
    {
       fixdump = sppr->fixdump;
    }
    if (Has_fp) /* Has frame pointer */
    {
       /* reserved GR3 for use as frame pointer...     */
       fixdump|=(1<<FP) ; /* ...dump and restore FP  */
    }
    if (Has_vsp) /* Has variable stack pointer */
    {
       /* reserved GR4 for use as "enviroment pointer"...   */
       EP = GR4;
       fixdump|=(1<<EP) ; /* ...dump and restore EP    */
    }
    else
    {
       EP = SP;
    }
    if (is_PIC_and_calls)
    {
       /* reserved GR5 as a copy of GR19...             */
       fixdump|=(1<<GR5) ; /* ...dump and restore GR5  */
    }

    st+=(2<<5);       /* 2 words of temporary memory */
    if (!simpleans)  /*  + 2 words in which to store address of long result */
    {
       st+=(2<<5);
    }
    if (Has_tos)
    {
       st+=(1<<5);  /*  + 1 word in which to store SP (reset at possible  */
    }              /*   long jump targets)                               */

    /*   HP PA reserved stack area. c.f. p 3-13 of HP PA reference manual */
    if (!leaf)
    {
       if (ma<(4<<5))
	  ma = (4<<5);	 /* 4 words for parameter dump */
       ma+=(8<<5);  	/*  + 8 word frame marker     */
    }

    /* keep maxargs a multiple of 2 words to ease possible alloca inlining */
    ma = (ma+63) & ~63;
    /* keep st a multiple of 2 words */
    st = (st + 63) & ~63;

    pr->locals_offset = ma + st;  /* relative to EP */

    /*  Budget for sreg save area  */
    if (Has_callees)
    {
       st+=(18<<5); /* 2 words to keep a record of callee sz (2 words      */
		   /*  are allocated to guarentee the callees are double  */
		  /*   word aligned) + (maximum) 16 word register save   */
		 /*    area (because callers must know where to put     */
		/*     callees).                                       */
    }
    else
    {
       /* Can we be more economical? */
       int nos;
       if (No_S)
       {
	  nos = 16;
       }
       else
       {
	  nos = bitsin(fixdump); /* = number of s regs used in body of proc */
       }
       st+=(nos<<5);
    }

    if (!Has_vcallees)
    {
       /* adjust st so that ma + st + cs is a multiple of 16 words
	* according to convention */
       st = ((ma+st+cs+511) & (~511)) - ma -cs ;
    }

    pr->locals_space = st;
    pr->frame_sz = ma + st + cs;
    if (Has_vcallees)
    {
       /* relative to FP */
       pr->params_offset = (8<<5);
       pr->callees_offset = -(18<<5);
    }
    else
    {
       /* relative to EP */
       pr->params_offset = pr->frame_sz + (8<<5);
       pr->callees_offset = pr->frame_sz - (18<<5);
    }
    pr->leaf = leaf;
    pr->max_args = ma;

    MEM_TEMP_BOFF.base = EP; MEM_TEMP_BOFF.offset = -(ma>>3)-(2<<2);
    LONG_RESULT_BOFF.base = EP; LONG_RESULT_BOFF.offset = -(ma>>3)-(4<<2);
    SP_BOFF.base = EP; SP_BOFF.offset = -(ma>>3)-(simpleans ? (3<<2) : (5<<2));
    FP_BOFF.base = EP; FP_BOFF.offset = -4;

    stackerr_lab=0;
    aritherr_lab=0;
}


long frame_offset
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
   exp p;
   procrec *pr;
   int eo,lo,po,co;
   for (p = father(e); (name(p)!=proc_tag && name(p)!=general_proc_tag);                              p = father(p));
   pr = &procrecs[no(p)];
   lo = pr->locals_offset>>3;
   po = pr->params_offset>>3;
   co = pr->callees_offset>>3;
   if (isparam(e))
   {
      int nse = no(son(e));
      if (name(son(e))==formal_callee_tag)
      {
	 eo = -co+(nse>>3);
      }
      else
      {
	 eo = -po-(nse>>3);
      }
   }
   else
   {
      int  n = no(e);
      int  b = n & 0x3f;
      eo = -lo+((n-b)>>4);
   }
   return eo;
}






