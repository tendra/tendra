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
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/sparcins.h,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: sparcins.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/07/14  16:33:58  john
 * New type
 *
 * Revision 1.1.1.1  1995/03/13  10:18:57  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:41  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:59:25  14:59:25  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef SPARCINS_INCLUDED
#define SPARCINS_INCLUDED


/*
    TYPES REPRESENTING INSTRUCTIONS
*/

typedef CONST char ins_t [] ;
typedef CONST char *ins_p ;
typedef char * instruction;

/*
    THE NIL INSTRUCTION
*/

#define I_NIL		null


/*
    INSTRUCTION SPECIFICATION

    If INS_DEFINE is defined then the instructions i_add etc are defined.
    Otherwise they are declared.
*/

#ifdef INS_DEFINE
#define INS( I, S )	ins_t I = S
#else
#define INS( I, S )	extern ins_t I
#endif


/* BASIC INSTRUCTIONS */
INS ( i_add, "add" ) ;
INS ( i_addcc, "addcc" ) ;
INS ( i_addx, "addx" ) ;
INS ( i_addxcc, "addxcc" ) ;
INS ( i_and, "and" ) ;
INS ( i_andcc, "andcc" ) ;
INS ( i_andn, "andn" ) ;
INS ( i_andncc, "andncc" ) ;
INS ( i_b, "b" ) ;
INS ( i_ba, "ba" ) ;
INS ( i_bcc, "bcc" ) ;
INS ( i_bclr, "bclr" ) ;
INS ( i_bcs, "bcs" ) ;
INS ( i_be, "be" ) ;
INS ( i_bg, "bg" ) ;
INS ( i_bge, "bge" ) ;
INS ( i_bgeu, "bgeu" ) ;
INS ( i_bgt, "bgt" ) ;
INS ( i_bgtu, "bgtu" ) ;
INS ( i_bgu, "bgu" ) ;
INS ( i_bl, "bl" ) ;
INS ( i_ble, "ble" ) ;
INS ( i_bleu, "bleu" ) ;
INS ( i_blt, "blt" ) ;
INS ( i_bltu, "bltu" ) ;
INS ( i_blu, "blu" ) ;
INS ( i_bn, "bn" ) ;
INS ( i_bne, "bne" ) ;
INS ( i_bneg, "bneg" ) ;
INS ( i_bnz, "bnz" ) ;
INS ( i_bpos, "bpos" ) ;
INS ( i_bset, "bset" ) ;
INS ( i_btog, "btog" ) ;
INS ( i_btst, "btst" ) ;
INS ( i_bvc, "bvc" ) ;
INS ( i_bvs, "bvs" ) ;
INS ( i_bz, "bz" ) ;
INS ( i_call, "call" ) ;
INS ( i_clr, "clr" ) ;
INS ( i_clrb, "clrb" ) ;
INS ( i_clrh, "clrh" ) ;
INS ( i_cmp, "cmp" ) ;
INS ( i_dec, "dec" ) ;
INS ( i_deccc, "deccc" ) ;
INS ( i_fabsd, "fabsd" ) ;
INS ( i_fabsq, "fabsq" ) ;
INS ( i_fabss, "fabss" ) ;
INS ( i_faddd, "faddd" ) ;
INS ( i_faddq, "faddq" ) ;
INS ( i_fadds, "fadds" ) ;
INS ( i_faddx, "faddx" ) ;
INS ( i_fasbx, "fasbx" ) ;
INS ( i_fba, "fba" ) ;
INS ( i_fbe, "fbe" ) ;
INS ( i_fbg, "fbg" ) ;
INS ( i_fbge, "fbge" ) ;
INS ( i_fbl, "fbl" ) ;
INS ( i_fble, "fble" ) ;
INS ( i_fblg, "fblg" ) ;
INS ( i_fbn, "fbn" ) ;
INS ( i_fbne, "fbne" ) ;
INS ( i_fbnz, "fbnz" ) ;
INS ( i_fbo, "fbo" ) ;
INS ( i_fbu, "fbu" ) ;
INS ( i_fbue, "fbue" ) ;
INS ( i_fbug, "fbug" ) ;
INS ( i_fbuge, "fbuge" ) ;
INS ( i_fbul, "fbul" ) ;
INS ( i_fbule, "fbule" ) ;
INS ( i_fbz, "fbz" ) ;
INS ( i_fcmpd, "fcmpd" ) ;
INS ( i_fcmped, "fcmped" ) ;
INS ( i_fcmpeq, "fcmpeq" ) ;
INS ( i_fcmpes, "fcmpes" ) ;
INS ( i_fcmpex, "fcmpex" ) ;
INS ( i_fcmpq, "fcmpq" ) ;
INS ( i_fcmps, "fcmps" ) ;
INS ( i_fcmpx, "fcmpx" ) ;
INS ( i_fdivd, "fdivd" ) ;
INS ( i_fdivq, "fdivq" ) ;
INS ( i_fdivs, "fdivs" ) ;
INS ( i_fdivx, "fdivx" ) ;
INS ( i_fdmulq, "fdmulq" ) ;
INS ( i_fdmulx, "fdmulx" ) ;
INS ( i_fdtoi, "fdtoi" ) ;
INS ( i_fdtoq, "fdtoq" ) ;
INS ( i_fdtos, "fdtos" ) ;
INS ( i_fdtox, "fdtox" ) ;
INS ( i_fitod, "fitod" ) ;
INS ( i_fitoq, "fitoq" ) ;
INS ( i_fitos, "fitos" ) ;
INS ( i_fitox, "fitox" ) ;
INS ( i_fmovd, "fmovd" ) ;
INS ( i_fmovq, "fmovq" ) ;
INS ( i_fmovs, "fmovs" ) ;
INS ( i_fmovx, "fmovx" ) ;
INS ( i_fmuld, "fmuld" ) ;
INS ( i_fmulq, "fmulq" ) ;
INS ( i_fmuls, "fmuls" ) ;
INS ( i_fmulx, "fmulx" ) ;
INS ( i_fnegd, "fnegd" ) ;
INS ( i_fnegq, "fnegq" ) ;
INS ( i_fnegs, "fnegs" ) ;
INS ( i_fnegx, "fnegx" ) ;
INS ( i_fqtod, "fqtod" ) ;
INS ( i_fqtoi, "fqtoi" ) ;
INS ( i_fqtos, "fqtos" ) ;
INS ( i_fsmuld, "fsmuld" ) ;
INS ( i_fsqrtd, "fsqrtd" ) ;
INS ( i_fsqrtq, "fsqrtq" ) ;
INS ( i_fsqrts, "fsqrts" ) ;
INS ( i_fsqrtx, "fsqrtx" ) ;
INS ( i_fstod, "fstod" ) ;
INS ( i_fstoi, "fstoi" ) ;
INS ( i_fstoq, "fstoq" ) ;
INS ( i_fstox, "fstox" ) ;
INS ( i_fsubd, "fsubd" ) ;
INS ( i_fsubq, "fsubq" ) ;
INS ( i_fsubs, "fsubs" ) ;
INS ( i_fsubx, "fsubx" ) ;
INS ( i_fxtod, "fxtod" ) ;
INS ( i_fxtoi, "fxtoi" ) ;
INS ( i_fxtos, "fxtos" ) ;
INS ( i_inc, "inc" ) ;
INS ( i_inccc, "inccc" ) ;
INS ( i_jmp, "jmp" ) ;
INS ( i_jmpl, "jmpl" ) ;
INS ( i_ld, "ld" ) ;
INS ( i_ld2, "ld2" ) ;
INS ( i_ldc, "ldc" ) ;
INS ( i_ldcsr, "ldcsr" ) ;
INS ( i_ldd, "ldd" ) ;
INS ( i_lddc, "lddc" ) ;
INS ( i_lddf, "lddf" ) ;
INS ( i_ldf, "ldf" ) ;
INS ( i_ldfsr, "ldfsr" ) ;
INS ( i_ldsb, "ldsb" ) ;
INS ( i_ldsh, "ldsh" ) ;
INS ( i_ldst, "ldst" ) ;
INS ( i_ldub, "ldub" ) ;
INS ( i_lduh, "lduh" ) ;
INS ( i_mov, "mov" ) ;
INS ( i_mulscc, "mulscc" ) ;
INS ( i_neg, "neg" ) ;
INS ( i_nop, "nop" ) ;
INS ( i_not, "not" ) ;
INS ( i_or, "or" ) ;
INS ( i_orcc, "orcc" ) ;
INS ( i_orn, "orn" ) ;
INS ( i_orncc, "orncc" ) ;
INS ( i_rdy, "rdy" ) ;
INS ( i_restore, "restore" ) ;
INS ( i_ret, "ret" ) ;
INS ( i_retl, "retl" ) ;
INS ( i_rett, "rett" ) ;
INS ( i_save, "save" ) ;
INS ( i_sdiv, "sdiv" ) ;
INS ( i_sdivcc, "sdivcc" ) ;
INS ( i_set, "set" ) ;
INS ( i_sethi, "sethi" ) ;
INS ( i_sll, "sll" ) ;
INS ( i_smul, "smul" ) ;
INS ( i_smulcc, "smulcc" ) ;
INS ( i_sra, "sra" ) ;
INS ( i_srl, "srl" ) ;
INS ( i_st, "st" ) ;
INS ( i_st2, "st2" ) ;
INS ( i_stb, "stb" ) ;
INS ( i_stc, "stc" ) ;
INS ( i_stcsr, "stcsr" ) ;
INS ( i_std, "std" ) ;
INS ( i_stdc, "stdc" ) ;
INS ( i_stdcq, "stdcq" ) ;
INS ( i_stdf, "stdf" ) ;
INS ( i_stdfq, "stdfq" ) ;
INS ( i_stf, "stf" ) ;
INS ( i_stfsr, "stfsr" ) ;
INS ( i_sth, "sth" ) ;
INS ( i_sub, "sub" ) ;
INS ( i_subcc, "subcc" ) ;
INS ( i_subx, "subx" ) ;
INS ( i_subxcc, "subxcc" ) ;
INS ( i_t, "t" ) ;
INS ( i_ta, "ta" ) ;
INS ( i_taddcc, "taddcc" ) ;
INS ( i_taddcctv, "taddcctv" ) ;
INS ( i_tcc, "tcc" ) ;
INS ( i_tcs, "tcs" ) ;
INS ( i_te, "te" ) ;
INS ( i_teq, "teq" ) ;
INS ( i_tg, "tg" ) ;
INS ( i_tge, "tge" ) ;
INS ( i_tgeu, "tgeu" ) ;
INS ( i_tgt, "tgt" ) ;
INS ( i_tgtu, "tgtu" ) ;
INS ( i_tgu, "tgu" ) ;
INS ( i_tl, "tl" ) ;
INS ( i_tle, "tle" ) ;
INS ( i_tleu, "tleu" ) ;
INS ( i_tlt, "tlt" ) ;
INS ( i_tltu, "tltu" ) ;
INS ( i_tlu, "tlu" ) ;
INS ( i_tn, "tn" ) ;
INS ( i_tne, "tne" ) ;
INS ( i_tneg, "tneg" ) ;
INS ( i_tnz, "tnz" ) ;
INS ( i_tpos, "tpos" ) ;
INS ( i_tst, "tst" ) ;
INS ( i_tsubcc, "tsubcc" ) ;
INS ( i_tsubcctv, "tsubcctv" ) ;
INS ( i_tvc, "tvc" ) ;
INS ( i_tvs, "tvs" ) ;
INS ( i_tz, "tz" ) ;
INS ( i_udiv, "udiv" ) ;
INS ( i_udivcc, "udivcc" ) ;
INS ( i_umul, "umul" ) ;
INS ( i_umulcc, "umulcc" ) ;
INS ( i_wry, "wry" ) ;
INS ( i_xnor, "xnor" ) ;
INS ( i_xnorcc, "xnorcc" ) ;
INS ( i_xor, "xor" ) ;
INS ( i_xorcc, "xorcc" ) ;

/* ATOMIC LOAD-STORE INSTRUCTIONS */
#if 0
INS ( i_ldstub, "ldstub" ) ;
INS ( i_swap, "swap" ) ;
INS ( i_swapa, "swapa" ) ;
#endif

/* PRIVILEGED INSTRUCTIONS */
#if 1
INS ( i_iflush, "iflush" ) ;
INS ( i_rd, "rd" ) ;
INS ( i_rdpsr, "rdpsr" ) ;
INS ( i_rdtbr, "rdtbr" ) ;
INS ( i_rdwim, "rdwim" ) ;
INS ( i_wr, "wr" ) ;
INS ( i_wrpsr, "wrpsr" ) ;
INS ( i_wrtbr, "wrtbr" ) ;
INS ( i_wrwim, "wrwim" ) ;
#endif

/* ALTERNATIVE SPACE INSTRUCTIONS */
#if 0
INS ( i_lda, "lda" ) ;
INS ( i_ldda, "ldda" ) ;
INS ( i_lddfa, "lddfa" ) ;
INS ( i_ldfa, "ldfa" ) ;
INS ( i_ldfsra, "ldfsra" ) ;
INS ( i_ldsba, "ldsba" ) ;
INS ( i_ldsha, "ldsha" ) ;
INS ( i_ldsta, "ldsta" ) ;
INS ( i_ldstuba, "ldstuba" ) ;
INS ( i_lduba, "lduba" ) ;
INS ( i_lduha, "lduha" ) ;
INS ( i_sta, "sta" ) ;
INS ( i_stba, "stba" ) ;
INS ( i_stda, "stda" ) ;
INS ( i_stdfa, "stdfa" ) ;
INS ( i_stdfqa, "stdfqa" ) ;
INS ( i_stfa, "stfa" ) ;
INS ( i_stfsra, "stfsra" ) ;
INS ( i_stha, "stha" ) ;
#endif

/* MISCELLANEOUS INSTRUCTIONS */
INS ( i_unimp, "unimp" ) ;

/* COPROCESSOR INSTRUCTIONS */
#if 0
INS ( i_cb0, "cb0" ) ;
INS ( i_cb01, "cb01" ) ;
INS ( i_cb012, "cb012" ) ;
INS ( i_cb013, "cb013" ) ;
INS ( i_cb02, "cb02" ) ;
INS ( i_cb023, "cb023" ) ;
INS ( i_cb03, "cb03" ) ;
INS ( i_cb1, "cb1" ) ;
INS ( i_cb12, "cb12" ) ;
INS ( i_cb123, "cb123" ) ;
INS ( i_cb13, "cb13" ) ;
INS ( i_cb2, "cb2" ) ;
INS ( i_cb23, "cb23" ) ;
INS ( i_cb3, "cb3" ) ;
INS ( i_cba, "cba" ) ;
INS ( i_cbn, "cbn" ) ;
INS ( i_cpop1, "cpop1" ) ;
INS ( i_cpop2, "cpop2" ) ;
#endif


/*
    IS A CONSTANT SMALL ENOUGH FOR AN IMMEDIATE OPERAND?
*/

#define	SIMM13_SIZE( N )	( ( long ) ( N ) >= -4096 &&\
				  ( long ) ( N ) <= 4095 )


#endif /* SPARCINS_INCLUDED */
