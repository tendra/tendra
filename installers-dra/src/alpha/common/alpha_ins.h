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


/* 	$Id: alpha_ins.h,v 1.1.1.1 1998/01/17 15:56:01 release Exp $	 */

/*
  alpha_insdecs.h
  This file provides definitions for the components of the alpha 
  instruction set.  The first field of each instruction is its
  symbolic representation, the second is its binasm representation.
*/

/*
$Log: alpha_ins.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:01  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/08/21  08:42:47  john
 * Changed include file
 *
 * Revision 1.3  1995/06/21  14:24:35  john
 * Added declarations for exception-raising operations
 *
 * Revision 1.2  1995/04/07  11:00:34  john
 * Added some special floating point ops
 *
 * Revision 1.1.1.1  1995/03/23  10:39:01  john
 * Entered into CVS
 *
 * Revision 1.6  1995/03/23  09:58:03  john
 * Instruction now include class information (added for scheduling
 * support)
 *
 * Revision 1.5  1995/01/26  13:33:55  john
 * Added some instructions
 *
*/


#ifndef ALPHA_INSTR_DECS
#define ALPHA_INSTR_DECS
#include "ibinasm.h"
#include "instypes.h"
#define PASTE(a,b) a##b

#ifdef INS_DEFINE

#if DO_SCHEDULE
#define instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_null}
#define load_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_load}
#define fload_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_fload}
#define store_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_store_data}
#define fstore_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_fstore_data}
#define ibranch_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_ibranch}
#define fbranch_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_fbranch}
#define subroutine_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_subroutine}
#define iarith_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_iarithmetic}
#define imultl_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_imultiplyl}
#define imultq_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_imultiplyq}
#define ilogical_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_ilogical}
#define ishift_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_ishift}
#define icondmove_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_icondmove}
#define icompare_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_icompare}
#define fpop_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_fpop}
#define fdivs_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_fdivs}
#define fdivd_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_fdivd}
#define null_instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst),class_null}
#else
#define instr(inst) instruction PASTE(i_,inst) = {#inst,PASTE(z,inst)}
#define load_instr instr
#define fload_instr instr
#define store_instr instr
#define fstore_instr instr
#define ibranch_instr instr
#define fbranch_instr instr
#define subroutine_instr instr
#define iarith_instr instr
#define imultl_instr instr
#define imultq_instr instr
#define ilogical_instr instr
#define ishift_instr instr
#define icondmove_instr instr
#define icompare_instr instr
#define fpop_instr instr
#define fdivs_instr instr
#define fdivd_instr instr
#define null_instr instr
#endif

#else	/* INS_DEFINE */
#define instr(inst) extern instruction PASTE(i_,inst)
#define load_instr instr
#define fload_instr instr
#define store_instr instr
#define fstore_instr instr
#define ibranch_instr instr
#define fbranch_instr instr
#define subroutine_instr instr
#define iarith_instr instr
#define imultl_instr instr
#define imultq_instr instr
#define ilogical_instr instr
#define ishift_instr instr
#define icondmove_instr instr
#define icompare_instr instr
#define fpop_instr instr
#define fdivs_instr instr
#define fdivd_instr instr
#define null_instr instr
#endif

/* integer load and store */
iarith_instr(lda);
iarith_instr(ldil);
iarith_instr(ldiq);
iarith_instr(ldah);
load_instr(ldl);
load_instr(ldl_l);
load_instr(ldq);
load_instr(ldq_l);
load_instr(ldq_u);
iarith_instr(ldgp);
store_instr(stl);
store_instr(stl_c);
store_instr(stq);
store_instr(stq_c);
store_instr(stq_u);

/* integer control */
ibranch_instr(beq);
ibranch_instr(bge);
ibranch_instr(bgt);
ibranch_instr(blbc);
ibranch_instr(blbs);
ibranch_instr(ble);
ibranch_instr(blt);
ibranch_instr(bne);
ibranch_instr(br);
subroutine_instr(bsr);
subroutine_instr(jmp);
subroutine_instr(jsr);
subroutine_instr(ret);
subroutine_instr(jsr_coroutine);

/* integer arithmetic */
iarith_instr(addl);
iarith_instr(addq);
iarith_instr(addlv);
iarith_instr(addqv);
iarith_instr(s4addl);
iarith_instr(s8addl);
iarith_instr(s4addq);
iarith_instr(s8addq);
icompare_instr(cmpeq);
icompare_instr(cmplt);
icompare_instr(cmple);
icompare_instr(cmpult);
icompare_instr(cmpule);
imultl_instr(mull);
imultq_instr(mulq);
imultl_instr(mullv);
imultq_instr(mulqv);
imultq_instr(umulh);
iarith_instr(subl);
iarith_instr(sublv);
iarith_instr(subq);
iarith_instr(subqv);
iarith_instr(s4subl);
iarith_instr(s8subl);
iarith_instr(s4subq);
iarith_instr(s8subq);

/* assembler macros */
subroutine_instr(divl);
subroutine_instr(divlu);
subroutine_instr(divq);
subroutine_instr(divqu);
subroutine_instr(reml);
subroutine_instr(remlu);
subroutine_instr(remq);
subroutine_instr(remqu);


/* logic and shift */
ilogical_instr(and);
ilogical_instr(bic);
ilogical_instr(bis);
ilogical_instr(eqv);
ilogical_instr(ornot);
ilogical_instr(xor);
icondmove_instr(cmoveq);
icondmove_instr(cmovge);
icondmove_instr(cmovgt);
icondmove_instr(cmovlbc);
icondmove_instr(cmovlbs);
icondmove_instr(cmovle);
icondmove_instr(cmovlt);
icondmove_instr(cmovne);
ishift_instr(sll);
ishift_instr(sra);
ishift_instr(srl);

/* byte manipulation */
icompare_instr(cmpbge);
ishift_instr(extbl);
ishift_instr(extwl);
ishift_instr(extll);
ishift_instr(extql);
ishift_instr(extwh);
ishift_instr(extlh);
ishift_instr(extqh);
ishift_instr(insbl);
ishift_instr(inswl);
ishift_instr(insll);
ishift_instr(insql);
ishift_instr(inswh);
ishift_instr(inslh);
ishift_instr(insqh);
ishift_instr(mskbl);
ishift_instr(mskwl);
ishift_instr(mskll);
ishift_instr(mskql);
ishift_instr(mskwh);
ishift_instr(msklh);
ishift_instr(mskqh);
ishift_instr(zap);
ishift_instr(zapnot);

/* memory format floating point */
fload_instr(ldf);
fload_instr(ldg);
fload_instr(lds);
fload_instr(ldis);
fload_instr(ldit);
fload_instr(ldt);
fstore_instr(stf);
fstore_instr(stg);
fstore_instr(sts);
fstore_instr(stt);

/* branch format floating point */
fbranch_instr(fbeq);
fbranch_instr(fbge);
fbranch_instr(fbgt);
fbranch_instr(fble);
fbranch_instr(fblt);
fbranch_instr(fbne);

/* floating point operate */
fpop_instr(cpys);
fpop_instr(cpyse);
fpop_instr(cpysn);
fpop_instr(cvtlq);
fpop_instr(cvtql);
fpop_instr(fcmoveq);
fpop_instr(fcmovge);
fpop_instr(fcmovgt);
fpop_instr(fcmovle);
fpop_instr(fcmovlt);
fpop_instr(fcmovne);
fpop_instr(mf_fpcr);
fpop_instr(mt_fpcr);
fpop_instr(addf);
fpop_instr(addg);
fpop_instr(adds);
fpop_instr(addssu);
fpop_instr(addt);
fpop_instr(addtsu);
fpop_instr(cmpgeq);
fpop_instr(cmpgle);
fpop_instr(cmpglt);
fpop_instr(cmpteq);
fpop_instr(cmptle);
fpop_instr(cmptlt);
fpop_instr(cmptun);
fpop_instr(cvtdg);
fpop_instr(cvtgd);
fpop_instr(cvtgf);
fpop_instr(cvtgq);
fpop_instr(cvtqf);
fpop_instr(cvtqg);
fpop_instr(cvtqs);
fpop_instr(cvtqt);
fpop_instr(cvttq);
fpop_instr(cvttqc);
fpop_instr(cvttqd);
fpop_instr(cvttqm);
fpop_instr(cvtts);
instr(divf);
instr(divg);
fdivs_instr(divs);
fdivd_instr(divt);
fdivs_instr(divssu);
fdivd_instr(divtsu);
fpop_instr(mulf);
fpop_instr(mulg);
fpop_instr(muls);
fpop_instr(mulssu);
fpop_instr(mult);
fpop_instr(multsu);
fpop_instr(subf);
fpop_instr(subg);
fpop_instr(subs);
fpop_instr(subssu);
fpop_instr(subt);
fpop_instr(subtsu);
/* miscellaneous */
instr(fetch);
instr(fetch_m);
instr(mb);
instr(rpcc);
instr(trapb);

/* VAX compatibility (!!) */
instr(rc);
instr(rs);

/* 
   The following generate multiple machine instructions 
   (assembler macros) 
*/
instr(ldb);
instr(ldbu);
instr(ldw);
instr(ldwu);
instr(uldw);
instr(uldwu);
instr(uldl);
instr(uldq);
instr(stb);
instr(stw);
instr(ustw);
instr(ustl);
instr(ustq);


/* PalCode */
#if 0
#include "palcode.h"
#endif

#endif
