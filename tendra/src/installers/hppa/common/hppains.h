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
$Log: hppains.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1996/11/14  15:22:15  wfs
 *    Fixed a bug in regexps.c which was common to most of the installers and
 * has only just come to light due to PWE's work on powertrans. (There was
 * previously only a patch.) Cosmetic changes to other files.
 *
 * Revision 1.3  1996/08/30  09:02:20  wfs
 * Various fixes of bugs arising from avs and pl_tdf tests.
 *
 * Revision 1.2  1995/12/18  13:11:34  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.2  1995/10/09  13:10:27  wfs
 * Cosmetic changes.
 *
 * Revision 5.1  1995/09/15  14:05:29  wfs
 * Minor changes to stop gcc compiler from complaining.
 *
 * Revision 5.0  1995/08/25  13:56:17  wfs
 * Preperation for August 95 Glue release
 *
 * Revision 4.0  1995/08/25  13:34:00  wfs
 * *** empty log message ***
 *
 * Revision 4.0  1995/08/25  13:34:00  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  11:04:28  wfs
 * Mostly cosmetic changes
 *
 * Revision 3.4  1995/08/25  11:04:28  wfs
 * Mostly cosmetic changes
 *
 * Revision 3.1  95/04/10  16:26:48  16:26:48  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:17:25  11:17:25  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:27:12  15:27:12  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.2  95/01/25  12:18:45  12:18:45  wfs (William Simmonds)
 * Added floating point exception code macros.
 * 
 * Revision 1.1  95/01/17  14:05:57  14:05:57  wfs (William Simmonds)
 * Initial revision
 * 
*/


#ifndef HPPAINS_INCLUDED
#define HPPAINS_INCLUDED


/*    This header file defines all the HPPA RISC instructions, formats,
**  field selectors, conditions and completers which the translator might
**  require. Not all the instruction set is included.  **/


/* Personal preferences */

#define STRCMP(S1,S2) !strcmp((S1),(S2))


/* Types representing instructions */

typedef CONST char ins_t [] ;
typedef CONST char *ins_p ;

#define I_NIL  null  /*  The nil instruction */


/*
*   Instruction specification. If INS_DEFINE is defined then the instructions
*   i_add etc. are defined, otherwise they are declared.
 */

#ifdef INS_DEFINE
#define INS( I, S )	ins_t I = S
#else
#define INS( I, S )	extern ins_t I
#endif


/* Basic instruction set */

INS ( i_add, "add" ) ;
INS ( i_and, "and" ) ;
INS ( i_addb, "addb" ) ;
INS ( i_addi, "addi" ) ;
INS ( i_addib, "addib" ) ;
INS ( i_addil, "addil" ) ;
INS ( i_andcm, "andcm" ) ;
INS ( i_b, "b" ) ;
INS ( i_bl, "bl" ) ;
INS ( i_bv, "bv" ) ;
INS ( i_bb, "bb" ) ;
INS ( i_ble, "ble" ) ;
INS ( i_blr, "blr" ) ;
INS ( i_copy, "copy");
INS ( i_comb, "comb");
INS ( i_comclr, "comclr");
INS ( i_comib, "comib");
INS ( i_comiclr, "comiclr");
INS ( i_ub, "ub");
INS ( i_cj, "cj");
INS ( i_cij, "cij");
INS ( i_dep, "dep");
INS ( i_depi, "depi");
INS ( directive, "" );
INS ( i_extrs, "extrs" );
INS ( i_extru, "extru" );
INS ( i_fabs, "fabs" ) ;
INS ( i_fadd, "fadd" ) ;
INS ( i_fcmp, "fcmp" ) ;   
INS ( i_fcpy, "fcpy" ) ; 
INS ( i_fdiv, "fdiv" ) ;
INS ( i_fmpy, "fmpy" ) ;
INS ( i_frnd, "frnd" ) ;
INS ( i_fsub, "fsub" ) ;
INS ( i_fldds, "fldds" );
INS ( i_flddx, "flddx" );
INS ( i_fldws, "fldws" );
INS ( i_fldwx, "fldwx" );
INS ( i_fstds, "fstds" );
INS ( i_fstdx, "fstdx" );
INS ( i_fstws, "fstws" );
INS ( i_fstwx, "fstwx" );
INS ( i_ftest, "ftest" ) ;
INS ( i_fcnvxf, "fcnvxf" ) ;   
INS ( i_fcnvff, "fcnvff" ) ;   
INS ( i_fcnvfx, "fcnvfx" ) ;   
INS ( i_fcnvfxt, "fcnvfxt" ) ;   
INS ( i_ldb, "ldb" ) ;    
INS ( i_ldbs, "ldbs" ) ;    
INS ( i_ldd, "ldd" ) ;  
INS ( i_ldf, "ldf" ) ;  
INS ( i_ldh, "ldh" ) ;    
INS ( i_ldhs, "ldhs" ) ;    
INS ( i_ldo, "ldo" ) ;    
INS ( i_ldw, "ldw" ) ;    
INS ( i_ldwm, "ldwm" ) ;    
INS ( i_ldws, "ldws" ) ;    
INS ( i_ldbx, "ldbx" );
INS ( i_ldhx, "ldhx" );
INS ( i_ldwx, "ldwx" );
INS ( i_ldi, "ldi" ) ;
INS ( i_ldil, "ldil" ) ;
INS ( i_ldsid, "ldsid" ) ;
INS ( i_mtsp, "mtsp" );
INS ( i_mtsar, "mtsar" );
INS ( i_nop, "nop" ) ;
INS ( i_or, "or" ) ;
INS ( i_shd, "shd" ) ;
INS ( i_sh1add, "sh1add" ) ;
INS ( i_sh2add, "sh2add" ) ;
INS ( i_sh3add, "sh3add" ) ;
INS ( i_stb, "stb" ) ;
INS ( i_sth, "sth" ) ;
INS ( i_stw, "stw" ) ;
INS ( i_stwm, "stwm" ) ;
INS ( i_stbs, "stbs" ) ;
INS ( i_sths, "sths" ) ;
INS ( i_stws, "stws" ) ;
INS ( i_sub, "sub" ) ;
INS ( i_subi, "subi" ) ;
INS ( i_subt, "subt" ) ;
INS ( i_uaddcm, "uaddcm" );
INS ( i_vshd, "vshd" ) ;
INS ( i_vextrs, "vextrs" ) ;
INS ( i_xor, "xor" ) ;
INS ( i_xmpyu, "xmpyu");
INS ( i_zdep, "zdep" ) ;
INS ( i_zdepi, "zdepi" ) ;
INS ( i_zvdep, "zvdep" ) ;
INS ( i_zvdepi, "zvdepi" ) ;

/* 
*   The following are translator internal psuedo "instructions" which 
*   do not appear in the PA RISC instruction set.
 */

INS ( i_lb, "lb" );      /* load byte                     */
INS ( i_lh, "lh" );      /* load halfword                 */
INS ( i_lo, "lo" );      /* load offset                   */
INS ( i_lw, "lw" );      /* load word                     */
INS ( i_lwm, "lwm" );    /* load word and modify          */
INS ( i_fldw, "fldw" );  /* load float single             */
INS ( i_fldd, "fldd" );  /* load float double             */
INS ( i_sb, "sb" );      /* store byte                    */
INS ( i_sh, "sh" );      /* store halfword                */
INS ( i_sw, "sw" );      /* store word                    */
INS ( i_fstw, "fstw" );  /* store float single            */ 
INS ( i_fstd, "fstd" );  /* store float double            */

INS( i_lab, "" );
INS( i_, "" );


/* Millicode - compiler generated routines, not instructions */

INS ( milli_mulU,"$$mulU" );
INS ( milli_mulI, "$$mulI" );
INS ( milli_divU, "$$divU" );
INS ( milli_divI, "$$divI" );
INS ( milli_remU, "$$remU" );
INS ( milli_remI, "$$remI" );
INS ( milli_dyncall, "$$dyncall" );
INS ( milli_mcount, "mcount" );

#define MILLI_MULU 0
#define MILLI_MULI 1
#define MILLI_DIVU 2
#define MILLI_DIVI 3
#define MILLI_REMU 4
#define MILLI_REMI 5
#define MILLI_DYNCALL 6


/* Floating point formats */

INS (  f_,     ""      );
INS (  f_sgl,  ",SGL"  );
INS (  f_dbl,  ",DBL"  );
INS (  f_quad, ",QUAD" );


/* Field selectors */

INS (  fs_,   ""    );
INS (  fs_L,  "L'"  );
INS (  fs_R,  "R'"  );
INS (  fs_LR, "L'"  );
INS (  fs_RR, "R'"  );
INS (  fs_LP, "LP'" );  /* left plabel constructor  */
INS (  fs_RP, "RP'" ); /* right plabel constructor */
INS (  fs_T,  "T'"  );
INS (  fs_LT,  "LT'"  );
INS (  fs_RT,  "RT'"  );


/* Condition codes */

INS (  c_,       "" ); /* the default condition code */
INS (  c_TR,     ",TR" );
INS (  c_g,      ",>" );
INS (  c_l,      ",<" );
INS (  c_eq,     ",=" );
INS (  c_gu,     ",>>" );
INS (  c_lu,     ",<<" );
INS (  c_geq,    ",>=" );
INS (  c_leq,    ",<=" );
INS (  c_neq,    ",<>" );
INS (  c_fneq,    ",!=" );
INS (  c_gequ,   ",>>=" );
INS (  c_lequ,   ",<<=" );
INS (  bit_is_0, ",>=" );
INS (  bit_is_1, ",<" );
INS (  c_OD, ",OD" );
INS (  c_EV, ",EV" );
INS (  c_NSV, ",NSV" );
INS (  c_NUV, ",NUV" );
INS (  c_UV, ",UV" );
INS (  c_SV, ",SV" );


/* Logical opposites of condition codes */

#define opp(C) ( C==c_g ? c_leq : ( C==c_leq ? c_g : ( C==c_l ? c_geq :\
                 ( C==c_geq ? c_l : ( C==c_eq ? c_neq : ( C==c_neq ? c_eq :\
                   ( C==c_gu ? c_lequ : ( C==c_lequ ? c_gu :\
                     ( C==c_lu ? c_gequ : c_lu ) ) ) ) ) ) ) ) )


/* Completers */

INS (  cmplt_, "" );  /* the default completer */
INS (  cmplt_M, ",M" );
INS (  cmplt_S, ",S" );
INS (  cmplt_SM, ",SM" );
INS (  cmplt_MA, ",MA" );
INS (  cmplt_MB, ",MB" );
INS (  cmplt_N, ",N" ); /* the nullify completer */


/* Some macros */

#define	 SIMM5( N )  ( (long)(N)>-17 && (long)(N)<16 )
#define	SIMM11( N )  ( (long)(N)>-1025 && (long)(N)<1024 )
#define	SIMM13( N )  ( (long)(N)>-4097 && (long)(N)<4096 )
#define	SIMM14( N )  ( (long)(N)>-8193 && (long)(N)<8192 )
#define	SIMM19( N )  ( (long)(N)>-262145 && (long)(N)<262144 )
#define IS_POW2(c)	((c) != 0 && ((c) & ((c)-1)) == 0)
#define SIGNED 1
#define UNSIGNED 0


/* Exception Codes for floating point operations */
 
#define NO_EXCEPTION        0
#define INVALID_OPERATION   128
#define DIVISION_BY_ZERO    64
#define OVERFLOW            32
#define UNDERFLOW           16
#define INEXACT             8
#define UNIMPLEMENTED       4


/* Essential exception codes for the floating point operations */

#define EXCEPTION_CODE   ( UNDERFLOW | OVERFLOW | DIVISION_BY_ZERO  )




INS ( empty_ltrl, "" ); /* empty literal */
INS ( label_LB, "LB$" );
INS ( label_LD, "LD$" );

#endif /* HPPAINS_INCLUDED */




















