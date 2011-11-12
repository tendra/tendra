/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef INSTRUCTDECS_H
#define INSTRUCTDECS_H

#define CRF0 0
#define CRF1 1
#define CRF2 2
#define CRF3 3
#define CRF4 4
#define CRF5 5
#define CRF6 6
#define CRF7 7

/* is constant small enough for signed immediate operand */
#define	IMM_SIZE(i)	((long)(i) >= - 0x8000 && ((long)(i) <= 0x7fff))

/* is constant small enough for logical immediate lower operand */
#define	IMMLOGL_SIZE(i)	(((unsigned long)(i) >> 16) == 0)

/* is constant small enough for logical immediate upper operand */
#define	IMMLOGU_SIZE(i)	(((unsigned long)(i) << 16) == 0)

/* STRUCTURE FOR INSTRUCTIONS */
typedef struct Instruction
{
  char *com;
  char *ppc;
  char *pwr;
} Instruction_T;

typedef Instruction_T * Instruction_P;

#define SPR_MQ   0
#define SPR_XER  1
#define SPR_RTCU 4
#define SPR_RTCL 5
#define SPR_DEC  6
#define SPR_LR   8
#define SPR_CTR  9

#define OV_BIT_MASK  0x40000000
#define CA_BIT_MASK  0x20000000
#define SO_BIT_MASK  0x80000000

/*
 * INS_DEFINE only set in instruct.c before including this header.
 * This causes definition and initialisation rather than external declaration.
 */
#ifdef INS_DEFINE
/* define */
#define INS(inst,com,ppc,pwr)	 Instruction_T INSTRUCTION_##inst = {com,ppc,pwr};\
                                 Instruction_P inst = &INSTRUCTION_##inst
#else
/* external declaration */
#define INS(inst,com,ppc,pwr)	 extern Instruction_P inst;\
                                 extern Instruction_T INSTRUCTION_##inst
#endif

#if 1
/* some pseudo instruction, mapped onto POWER instructions in inst_format.c */
INS(i_s          ,"s"      ,"s"     ,"s");
/* pseudo instruction: subtract, mapped
   onto sf with regs reversed */
INS(i_not        ,"not"    ,"not"      ,"not");		
/* pseudo instruction: monadic not reg to reg
				   expanded to sfi dest,-1,src */
#endif


/*
 * Instructions PowerPC 601 User's manual Appendix B says
 * is in POWER but not PowerPC.  We avoid them for future advantage.
 * Obviously we do not yet use any of the new PowerPC instructions.
 */
/* All definitions are of common,ppc,pwr */
/*  
 *  Name           Common     Powerpc    POWER    
 */

INS(I_NIL         ,"VOID"    ,"VOID"    ,"VOID");


/*
 * Non PowerPC instruction we must use as we cannot use the replacement
 * instructions yet.
 */
INS(i_mfmq        ,"mfmq"    ,"mfmq"    ,"mfmq");
INS(i_mtmq        ,"mtmq"    ,"mtmq"    ,"mtmq");



#if PowerPC_PRIVILEGED
/* we dont use privileged instructions */
INS(i_mfmsr       ,"mfmsr"   ,"mfmsr"   ,"mfmsr");
INS(i_mfsr        ,"mfsr"    ,"mfsr"    ,"mfsr");
#endif
/* Table B-3 */
/* POWER instructions dropped for PowerPC architecture*/
INS(i_abs         ,"VOID"    ,"VOID"    ,"abs");
INS(i_abs_cr      ,"VOID"    ,"VOID"    ,"abs.");
INS(i_abso        ,"VOID"    ,"VOID"    ,"abso");
INS(i_abso_cr     ,"VOID"    ,"VOID"    ,"abso.");
INS(i_clcs        ,"VOID"    ,"VOID"    ,"clcs");
INS(i_clf         ,"VOID"    ,"VOID"    ,"clf");
INS(i_cli         ,"VOID"    ,"VOID"    ,"cli");
INS(i_dclst       ,"VOID"    ,"VOID"    ,"dclst");
INS(i_div         ,"div"     ,"VOID"    ,"div");/* Seem to work for common */
INS(i_div_cr      ,"VOID"    ,"VOID"    ,"div.");
INS(i_divo        ,"VOID"    ,"VOID"    ,"divo");
INS(i_divo_cr     ,"VOID"    ,"VOID"    ,"divo.");
INS(i_divs        ,"divs"    ,"VOID"    ,"divs"); /* Seem to work for common*/
INS(i_divs_cr     ,"VOID"    ,"VOID"    ,"divs.");
INS(i_divso       ,"VOID"    ,"VOID"    ,"divso");
INS(i_divso_cr    ,"VOID"    ,"VOID"    ,"divso.");
INS(i_doz         ,"VOID"    ,"VOID"    ,"doz");
INS(i_doz_cr      ,"VOID"    ,"VOID"    ,"doz.");
INS(i_dozi        ,"VOID"    ,"VOID"    ,"dozi");
INS(i_dozo        ,"VOID"    ,"VOID"    ,"dozo");
INS(i_dozo_cr     ,"VOID"    ,"VOID"    ,"dozo.");
INS(i_lscbx       ,"VOID"    ,"VOID"    ,"lscbx");
INS(i_lscbx_cr    ,"VOID"    ,"VOID"    ,"lscbx.");
INS(i_maskg       ,"VOID"    ,"VOID"    ,"maskg");
INS(i_maskg_cr    ,"VOID"    ,"VOID"    ,"maskg.");
INS(i_maskir      ,"VOID"    ,"VOID"    ,"maskir");
INS(i_maskir_cr   ,"VOID"    ,"VOID"    ,"maskir.");
INS(i_mfsri       ,"VOID"    ,"VOID"    ,"mfsri");
INS(i_mul         ,"mul"     ,"mulhw"   ,"mul");/* mul appears to work */
INS(i_mul_cr      ,"VOID"    ,"VOID"    ,"mul.");
INS(i_mulo        ,"VOID"    ,"VOID"    ,"mulo");
INS(i_mulo_cr     ,"VOID"    ,"VOID"    ,"mulo.");
INS(i_nabs        ,"VOID"    ,"VOID"    ,"nabs");
INS(i_nabs_cr     ,"VOID"    ,"VOID"    ,"nabs.");
INS(i_nabso       ,"VOID"    ,"VOID"    ,"nabso");
INS(i_nabso_cr    ,"VOID"    ,"VOID"    ,"nabso.");
INS(i_rac         ,"VOID"    ,"VOID"    ,"rac");
INS(i_rac_cr      ,"VOID"    ,"VOID"    ,"rac.");
INS(i_rlmi        ,"VOID"    ,"VOID"    ,"rlmi");
INS(i_rlmi_cr     ,"VOID"    ,"VOID"    ,"rlmi.");
INS(i_rrib        ,"VOID"    ,"VOID"    ,"rrib");
INS(i_rrib_cr     ,"VOID"    ,"VOID"    ,"rrib.");
INS(i_sle         ,"VOID"    ,"VOID"    ,"sle");
INS(i_sle_cr      ,"VOID"    ,"VOID"    ,"sle.");
INS(i_sleq        ,"VOID"    ,"VOID"    ,"sleq");
INS(i_sleq_cr     ,"VOID"    ,"VOID"    ,"sleq.");
INS(i_sliq        ,"VOID"    ,"VOID"    ,"sliq");
INS(i_sliq_cr     ,"VOID"    ,"VOID"    ,"sliq.");
INS(i_slliq       ,"VOID"    ,"VOID"    ,"slliq");
INS(i_slliq_c     ,"VOID"    ,"VOID"    ,"slliq.");
INS(i_sllq        ,"VOID"    ,"VOID"    ,"sllq");
INS(i_sllq_cr     ,"VOID"    ,"VOID"    ,"sllq.");
INS(i_slq         ,"VOID"    ,"VOID"    ,"slq");
INS(i_slq_cr      ,"VOID"    ,"VOID"    ,"slq.");
INS(i_sraiq       ,"VOID"    ,"VOID"    ,"sraiq");
INS(i_sraiq_cr    ,"VOID"    ,"VOID"    ,"sraiq.");
INS(i_sraq        ,"VOID"    ,"VOID"    ,"sraq");
INS(i_sraq_cr     ,"VOID"    ,"VOID"    ,"sraq.");
INS(i_sre         ,"VOID"    ,"VOID"    ,"sre");
INS(i_sre_cr      ,"VOID"    ,"VOID"    ,"sre.");
INS(i_srea        ,"VOID"    ,"VOID"    ,"srea");
INS(i_srea_cr     ,"VOID"    ,"VOID"    ,"srea.");
INS(i_sreq        ,"VOID"    ,"VOID"    ,"sreq");
INS(i_sreq_cr     ,"VOID"    ,"VOID"    ,"sreq.");
INS(i_sriq        ,"VOID"    ,"VOID"    ,"sriq");
INS(i_sriq_cr     ,"VOID"    ,"VOID"    ,"sriq.");
INS(i_srliq       ,"VOID"    ,"VOID"    ,"srliq");
INS(i_srliq_cr    ,"VOID"    ,"VOID"    ,"srliq.");
INS(i_srlq        ,"VOID"    ,"VOID"    ,"srlq");
INS(i_srlq_cr     ,"VOID"    ,"VOID"    ,"srlq.");
INS(i_srq         ,"VOID"    ,"VOID"    ,"srq");
INS(i_srq_cr      ,"VOID"    ,"VOID"    ,"srq.");
INS(i_svc         ,"VOID"    ,"VOID"    ,"svc");
INS(i_svcl        ,"VOID"    ,"VOID"    ,"svcl");
INS(i_svcla       ,"VOID"    ,"VOID"    ,"svcla");


/* Table B-4
 * POWER instructions implemented in the PowerPC architecture
 * Different mnemonics
 */
INS(i_a           ,"a"       ,"addc"    ,"a");
INS(i_a_cr        ,"a."      ,"addc."   ,"a.");
INS(i_ao          ,"ao"      ,"addco"   ,"ao");
INS(i_ao_cr       ,"ao."     ,"addco."  ,"ao.");
INS(i_ae          ,"ae"      ,"adde"    ,"ae");
INS(i_ae_cr       ,"ae."     ,"adde."   ,"ae.");
INS(i_aeo         ,"aeo"     ,"addeo"   ,"aeo");
INS(i_aeo_cr      ,"aeo."    ,"addeo."  ,"aeo.");
INS(i_ai          ,"ai"      ,"addic"   ,"ai");
INS(i_ai_cr       ,"ai."     ,"addic."  ,"ai.");
INS(i_ame         ,"ame"     ,"addme"   ,"ame");
INS(i_ame_cr      ,"ame."    ,"addme."  ,"ame.");
INS(i_ameo        ,"ameo"    ,"addmeo"  ,"ameo");
INS(i_ameo_cr     ,"ameo."   ,"addmeo." ,"ameo.");
INS(i_andil_cr    ,"andil."  ,"andi."   ,"andil.");
INS(i_andiu_cr    ,"andiu."  ,"andis."  ,"andiu.");
INS(i_aze         ,"aze"     ,"addze"   ,"aze");
INS(i_aze_cr      ,"aze."    ,"addze."  ,"aze.");
INS(i_azeo        ,"azeo"    ,"addzeo"  ,"azeo");
INS(i_azeo_cr     ,"azeo."   ,"addzeo." ,"azeo.");
INS(i_bcc         ,"bcc"     ,"bcctr"   ,"bcc");
INS(i_bccl        ,"bccl"    ,"bcctrl"  ,"bccl");
INS(i_bcr         ,"bcr"     ,"bclr"    ,"bcr");
INS(i_bcrl        ,"bcrl"    ,"bclrl"   ,"bcrl");
INS(i_cal         ,"cal"     ,"addi"    ,"cal");
INS(i_cau         ,"cau"     ,"addis"   ,"cau");
INS(i_cax         ,"cax"     ,"add"     ,"cax");
INS(i_cax_cr      ,"cax."    ,"add."    ,"cax.");
INS(i_caxo        ,"caxo"    ,"addo"    ,"caxo");
INS(i_caxo_cr     ,"caxo."   ,"addo."   ,"caxo.");
INS(i_cntlz       ,"cntlz"   ,"cntlzw"  ,"cntlz");
INS(i_cntlz_cr    ,"cntlz."  ,"cntlzw." ,"cntlz.");
INS(i_dclz        ,"dclz"    ,"dcbz"    ,"dclz");
INS(i_dcs         ,"dcs"     ,"sync"     ,"dcs");
INS(i_exts        ,"exts"    ,"extsh"   ,"exts");
INS(i_exts_cr     ,"exts."   ,"extsh."  ,"exts.");
INS(i_fa          ,"fa"      ,"fadd"    ,"fa");
INS(i_fa_cr       ,"fa."     ,"fadd."   ,"fa");
INS(i_fd          ,"fd"      ,"fdiv"    ,"fd");
INS(i_fd_cr       ,"fd."     ,"fdiv."   ,"fd.");
INS(i_fm          ,"fm"      ,"fmul"    ,"fm");
INS(i_fm_cr       ,"fm."     ,"fmul."   ,"fm.");
INS(i_fma         ,"fma"     ,"fmadd"   ,"fma");
INS(i_fma_cr      ,"fma."    ,"fmadd."  ,"fma.");
INS(i_fms         ,"fms"     ,"fmsub"   ,"fms");
INS(i_fms_cr      ,"fms."    ,"fmsub."  ,"fms");
INS(i_fnma        ,"fnma"    ,"fnmadd"  ,"fnma");
INS(i_fnma_cr     ,"fnma."   ,"fnmadd." ,"fnma.");
INS(i_fnms        ,"fnms"    ,"fnmsub"  ,"fnms");
INS(i_fnms_cr     ,"fnms."   ,"fnmsub." ,"fnms.");
INS(i_fs          ,"fs"      ,"fsub"    ,"fs");
INS(i_fs_cr       ,"fs."     ,"fsub."   ,"fs.");
INS(i_l           ,"l"       ,"lwz"     ,"l");
INS(i_lbrx        ,"lbrx"    ,"lwbrx"   ,"lbrx");
INS(i_lm          ,"lm"      ,"lmw"     ,"lm");
INS(i_lsi         ,"lsi"     ,"lswi"    ,"lswi");
INS(i_lsx         ,"lsx"     ,"lswx"    ,"lsx");
INS(i_lu          ,"lu"      ,"lwzu"    ,"lu");
INS(i_lux         ,"lux"     ,"lwzux"   ,"lux");
INS(i_lx          ,"lx"      ,"lwzx"    ,"lx");
INS(i_mtsri       ,"mtsri"   ,"mtsrin"  ,"mtsri");
INS(i_muli        ,"muli"    ,"mulli"   ,"muli");
INS(i_muls        ,"muls"    ,"mullw"   ,"muls");
INS(i_muls_cr     ,"muls."   ,"mullw."  ,"muls.");
INS(i_mulso       ,"mulso"   ,"mullwo"  ,"mulso");
INS(i_mulso_cr    ,"mulso."  ,"mullwo." ,"mulso.");
INS(i_oril        ,"oril"    ,"ori"     ,"oril");
INS(i_oriu        ,"oriu"    ,"oris"    ,"oriu");
INS(i_rlimi       ,"rlimi"   ,"rlwimi"  ,"rlimi");
INS(i_rlimi_cr    ,"rlimi."  ,"rlwimi." ,"rlimi.");
INS(i_rlinm       ,"rlinm"   ,"rlwinm"  ,"rlinm");
INS(i_rlinm_cr    ,"rlinm."  ,"rlwinm." ,"rlinm.");
INS(i_rlnm        ,"rlnm"    ,"rlwnm"   ,"rlnm");
INS(i_rlnm_cr     ,"rlnm."   ,"rlwnm."  ,"rlnm.");
INS(i_sf          ,"sf"      ,"subfc"   ,"sf");
INS(i_sf_cr       ,"sf."     ,"subfc."  ,"sf.");
INS(i_sfo         ,"sfo"     ,"subfco"  ,"sfo");
INS(i_sfo_cr      ,"sfo."    ,"subfco." ,"sfo.");
INS(i_sfe         ,"sfe"     ,"subfe"   ,"sfe");
INS(i_sfe_cr      ,"sfe."    ,"subfe."  ,"sfe.");
INS(i_sfeo        ,"sfeo"    ,"subfeo"  ,"sfeo");
INS(i_sfeo_cr     ,"sfeo."   ,"subfeo." ,"sfeo.");
INS(i_sfi         ,"sfi"     ,"subfic"  ,"sfi");
INS(i_sfme        ,"sfme"    ,"subfme"  ,"sfme");
INS(i_sfme_cr     ,"sfme."   ,"subfme." ,"sfme.");
INS(i_sfmeo       ,"sfmeo"   ,"subfmeo" ,"sfmeo");
INS(i_sfmeo_cr    ,"sfmeo."  ,"subfmeo.","sfmeo.");
INS(i_sfze        ,"sfze"    ,"subfze"  ,"sfze");
INS(i_sfze_cr     ,"sfze."   ,"subfze." ,"sfze.");
INS(i_sfzeo       ,"sfzeo"   ,"subfzeo" ,"sfzeo");
INS(i_sfzeo_cr    ,"sfzeo."  ,"subfzeo.","sfzeo.");
INS(i_sl          ,"sl"      ,"slw"     ,"sl");
INS(i_sl_cr       ,"sl."     ,"slw."    ,"sl.");
INS(i_sr          ,"sr"      ,"srw"     ,"sr");
INS(i_sr_cr       ,"sr."     ,"srw."    ,"sr.");
INS(i_sra         ,"sra"     ,"sraw"    ,"sra");
INS(i_sra_cr      ,"sra."    ,"sraw."   ,"sra.");
INS(i_srai        ,"srai"    ,"srawi"   ,"srai");
INS(i_srai_cr     ,"srai."   ,"srawi."  ,"srai.");
INS(i_st          ,"st"      ,"stw"     ,"st");
INS(i_stbrx       ,"stbrx"   ,"stwbrx"  ,"stbrx");
INS(i_stm         ,"stm"     ,"stmw"    ,"stm");
INS(i_stsi        ,"stsi"    ,"stswi"   ,"stsi");
INS(i_stsx        ,"stsx"    ,"stswx"   ,"stsx");
INS(i_stu         ,"stu"     ,"stwu"    ,"stu");
INS(i_stux        ,"stux"    ,"stwux"   ,"stux");
INS(i_stx         ,"stx"     ,"stwx"    ,"stx");
INS(i_svca        ,"svca"    ,"sc"      ,"svca");
INS(i_t           ,"t"       ,"tw"      ,"t");
INS(i_ti          ,"ti"      ,"twi"     ,"ti");
INS(i_tlbi        ,"tlbi"    ,"tlbie"   ,"tlbi");
INS(i_xoril       ,"xoril"   ,"xori"    ,"xoril");
INS(i_xoriu       ,"xoriu"   ,"xoris"   ,"xoriu");
/* end*/

/* POWER instructions retained on PowerPc with same mnenonic */
INS(i_and         ,"and"     ,"and"     ,"and");
INS(i_and_cr      ,"and."    ,"and."    ,"and.");
INS(i_andc        ,"andc"    ,"andc"    ,"andc");
INS(i_andc_cr     ,"andc."   ,"andc."   ,"andc.");
INS(i_b           ,"b"       ,"b"       ,"b");
INS(i_ba          ,"ba"      ,"ba"      ,"ba");
INS(i_bbf         ,"bbf"     ,"bbf"     ,"bbf");
INS(i_bbfa        ,"bbfa"    ,"bbfa"    ,"bbfa");
INS(i_bbfc        ,"bbfc"    ,"bbfc"    ,"bbfc");
INS(i_bbfcl       ,"bbfcl"   ,"bbfcl"   ,"bbfcl");
INS(i_bbfl        ,"bbfl"    ,"bbfl"    ,"bbfl");
INS(i_bbfla       ,"bbfla"   ,"bbfla"   ,"bbfla");
INS(i_bbfr        ,"bbfr"    ,"bbfr"    ,"bbfr");
INS(i_bbfrl       ,"bbfrl"   ,"bbfrl"   ,"bbfrl");
INS(i_bbt         ,"bbt"     ,"bbt"     ,"bbt");
INS(i_bbta        ,"bbta"    ,"bbta"    ,"bbta");
INS(i_bbtc        ,"bbtc"    ,"bbtc"    ,"bbtc");
INS(i_bbtcl       ,"bbtcl"   ,"bbtcl"   ,"bbtcl");
INS(i_bbtl        ,"bbtl"    ,"bbtl"    ,"bbtl");
INS(i_bbtla       ,"bbtla"   ,"bbtla"   ,"bbtla");
INS(i_bbtr        ,"bbtr"    ,"bbtr"    ,"bbtr");
INS(i_bbtrl       ,"bbtrl"   ,"bbtrl"   ,"bbtrl");
INS(i_bc          ,"bc"      ,"bc"      ,"bc");
INS(i_bca         ,"bca"     ,"bca"     ,"bca");
INS(i_bcl         ,"bcl"     ,"bcl"     ,"bcl");
INS(i_bcla        ,"bcla"    ,"bcla"    ,"bcla");
INS(i_bctr        ,"bctr"    ,"bctr"    ,"bctr");
INS(i_bctrl       ,"bctrl"   ,"bctrl"   ,"bctrl");
INS(i_bdn         ,"bdn"     ,"bdn"     ,"bdn");
INS(i_bdna        ,"bdna"    ,"bdna"    ,"bdna");
INS(i_bdneq       ,"bdneq"   ,"bdneq"   ,"bdneq");
INS(i_bdnge       ,"bdnge"   ,"bdnge"   ,"bdnge");
INS(i_bdngt       ,"bdngt"   ,"bdngt"   ,"bdngt");
INS(i_bdnl        ,"bdnl"    ,"bdnl"    ,"bdnl");
INS(i_bdnla       ,"bdnla"   ,"bdnla"   ,"bdnla");
INS(i_bdnle       ,"bdnle"   ,"bdnle"   ,"bdnle");
INS(i_bdnlt       ,"bdnlt"   ,"bdnlt"   ,"bdnlt");
INS(i_bdnne       ,"bdnne"   ,"bdnne"   ,"bdnne");
INS(i_bdnns       ,"bdnns"   ,"bdnns"   ,"bdnns");
INS(i_bdnr        ,"bdnr"    ,"bdnr"    ,"bdnr");
INS(i_bdnrl       ,"bdnrl"   ,"bdnrl"   ,"bdnrl");
INS(i_bdnso       ,"bdnso"   ,"bdnso"   ,"bdnso");
INS(i_bdz         ,"bdz"     ,"bdz"     ,"bdz");
INS(i_bdza        ,"bdza"    ,"bdza"    ,"bdza");
INS(i_bdzeq       ,"bdzeq"   ,"bdzeq"   ,"bdzeq");
INS(i_bdzge       ,"bdzge"   ,"bdzge"   ,"bdzge");
INS(i_bdzgt       ,"bdzgt"   ,"bdzgt"   ,"bdzgt");
INS(i_bdzl        ,"bdzl"    ,"bdzl"    ,"bdzl");
INS(i_bdzla       ,"bdzla"   ,"bdzla"   ,"bdzla");
INS(i_bdzle       ,"bdzle"   ,"bdzle"   ,"bdzle");
INS(i_bdzlt       ,"bdzlt"   ,"bdzlt"   ,"bdzlt");
INS(i_bdzne       ,"bdzne"   ,"bdzne"   ,"bdzne");
INS(i_bdzns       ,"bdzns"   ,"bdzns"   ,"bdzns");
INS(i_bdzr        ,"bdzr"    ,"bdzr"    ,"bdzr");
INS(i_bdzrl       ,"bdzrl"   ,"bdzrl"   ,"bdzrl");
INS(i_bdzso       ,"bdzso"   ,"bdzso"   ,"bdzso");
INS(i_beq         ,"beq"     ,"beq"     ,"beq");
INS(i_beqa        ,"beqa"    ,"beqa"    ,"beqa");
INS(i_beqc        ,"beqc"    ,"beqc"    ,"beqc");
INS(i_beqcl       ,"beqcl"   ,"beqcl"   ,"beqcl");
INS(i_beql        ,"beql"    ,"beql"    ,"beql");
INS(i_beqla       ,"beqla"   ,"beqla"   ,"beqla");
INS(i_beqr        ,"beqr"    ,"beqr"    ,"beqr");
INS(i_beqrl       ,"beqrl"   ,"beqrl"   ,"beqrl");
INS(i_bge         ,"bge"     ,"bge"     ,"bge");
INS(i_bgea        ,"bgea"    ,"bgea"    ,"bgea");
INS(i_bgec        ,"bgec"    ,"bgec"    ,"bgec");
INS(i_bgecl       ,"bgecl"   ,"bgecl"   ,"bgecl");
INS(i_bgel        ,"bgel"    ,"bgel"    ,"bgel");
INS(i_bgela       ,"bgela"   ,"bgela"   ,"bgela");
INS(i_bger        ,"bger"    ,"bger"    ,"bger");
INS(i_bgerl       ,"bgerl"   ,"bgerl"   ,"bgerl");
INS(i_bgt         ,"bgt"     ,"bgt"     ,"bgt");
INS(i_bgta        ,"bgta"    ,"bgta"    ,"bgta");
INS(i_bgtc        ,"bgtc"    ,"bgtc"    ,"bgtc");
INS(i_bgtcl       ,"bgtcl"   ,"bgtcl"   ,"bgtcl");
INS(i_bgtl        ,"bgtl"    ,"bgtl"    ,"bgtl");
INS(i_bgtla       ,"bgtla"   ,"bgtla"   ,"bgtla");
INS(i_bgtr        ,"bgtr"    ,"bgtr"    ,"bgtr");
INS(i_bgtrl       ,"bgtrl"   ,"bgtrl"   ,"bgtrl");
INS(i_bl          ,"bl"      ,"bl"      ,"bl");
INS(i_bla         ,"bla"     ,"bla"     ,"bla");
INS(i_ble         ,"ble"     ,"ble"     ,"ble");
INS(i_blea        ,"blea"    ,"blea"    ,"blea");
INS(i_blec        ,"blec"    ,"blec"    ,"blec");
INS(i_blecl       ,"blecl"   ,"blecl"   ,"blecl");
INS(i_blel        ,"blel"    ,"blel"    ,"blel");
INS(i_blela       ,"blela"   ,"blela"   ,"blela");
INS(i_bler        ,"bler"    ,"bler"    ,"bler");
INS(i_blerl       ,"blerl"   ,"blerl"   ,"blerl");
INS(i_blt         ,"blt"     ,"blt"     ,"blt");
INS(i_blta        ,"blta"    ,"blta"    ,"blta");
INS(i_bltc        ,"bltc"    ,"bltc"    ,"bltc");
INS(i_bltcl       ,"bltcl"   ,"bltcl"   ,"bltcl");
INS(i_bltl        ,"bltl"    ,"bltl"    ,"bltl");
INS(i_bltla       ,"bltla"   ,"bltla"   ,"bltla");
INS(i_bltr        ,"bltr"    ,"bltr"    ,"bltr");
INS(i_bltrl       ,"bltrl"   ,"bltrl"   ,"bltrl");
INS(i_bne         ,"bne"     ,"bne"     ,"bne");
INS(i_bnea        ,"bnea"    ,"bnea"    ,"bnea");
INS(i_bnec        ,"bnec"    ,"bnec"    ,"bnec");
INS(i_bnecl       ,"bnecl"   ,"bnecl"   ,"bnecl");
INS(i_bnel        ,"bnel"    ,"bnel"    ,"bnel");
INS(i_bnela       ,"bnela"   ,"bnela"   ,"bnela");
INS(i_bner        ,"bner"    ,"bner"    ,"bner");
INS(i_bnerl       ,"bnerl"   ,"bnerl"   ,"bnerl");
INS(i_bng         ,"bng"     ,"bng"     ,"bng");
INS(i_bnga        ,"bnga"    ,"bnga"    ,"bnga");
INS(i_bngc        ,"bngc"    ,"bngc"    ,"bngc");
INS(i_bngcl       ,"bngcl"   ,"bngcl"   ,"bngcl");
INS(i_bngl        ,"bngl"    ,"bngl"    ,"bngl");
INS(i_bngla       ,"bngla"   ,"bngla"   ,"bngla");
INS(i_bngr        ,"bngr"    ,"bngr"    ,"bngr");
INS(i_bngrl       ,"bngrl"   ,"bngrl"   ,"bngrl");
INS(i_bnl         ,"bnl"     ,"bnl"     ,"bnl");
INS(i_bnla        ,"bnla"    ,"bnla"    ,"bnla");
INS(i_bnlc        ,"bnlc"    ,"bnlc"    ,"bnlc");
INS(i_bnlcl       ,"bnlcl"   ,"bnlcl"   ,"bnlcl");
INS(i_bnll        ,"bnll"    ,"bnll"    ,"bnll");
INS(i_bnlla       ,"bnlla"   ,"bnlla"   ,"bnlla");
INS(i_bnlr        ,"bnlr"    ,"bnlr"    ,"bnlr");
INS(i_bnlrl       ,"bnlrl"   ,"bnlrl"   ,"bnlrl");
INS(i_bns         ,"bns"     ,"bns"     ,"bns");
INS(i_bnsa        ,"bnsa"    ,"bnsa"    ,"bnsa");
INS(i_bnsc        ,"bnsc"    ,"bnsc"    ,"bnsc");
INS(i_bnscl       ,"bnscl"   ,"bnscl"   ,"bnscl");
INS(i_bnsl        ,"bnsl"    ,"bnsl"    ,"bnsl");
INS(i_bnsla       ,"bnsla"   ,"bnsla"   ,"bnsla");
INS(i_bnsr        ,"bnsr"    ,"bnsr"    ,"bnsr");
INS(i_bnsrl       ,"bnsrl"   ,"bnsrl"   ,"bnsrl");
INS(i_bnz         ,"bnz"     ,"bnz"     ,"bnz");
INS(i_bnza        ,"bnza"    ,"bnza"    ,"bnza");
INS(i_bnzc        ,"bnzc"    ,"bnzc"    ,"bnzc");
INS(i_bnzcl       ,"bnzcl"   ,"bnzcl"   ,"bnzcl");
INS(i_bnzl        ,"bnzl"    ,"bnzl"    ,"bnzl");
INS(i_bnzla       ,"bnzla"   ,"bnzla"   ,"bnzla");
INS(i_bnzr        ,"bnzr"    ,"bnzr"    ,"bnzr");
INS(i_bnzrl       ,"bnzrl"   ,"bnzrl"   ,"bnzrl");
INS(i_br          ,"br"      ,"br"      ,"br");
INS(i_brl         ,"brl"     ,"brl"     ,"brl");
INS(i_bso         ,"bso"     ,"bso"     ,"bso");
INS(i_bsoa        ,"bsoa"    ,"bsoa"    ,"bsoa");
INS(i_bsoc        ,"bsoc"    ,"bsoc"    ,"bsoc");
INS(i_bsocl       ,"bsocl"   ,"bsocl"   ,"bsocl");
INS(i_bsol        ,"bsol"    ,"bsol"    ,"bsol");
INS(i_bsola       ,"bsola"   ,"bsola"   ,"bsola");
INS(i_bsor        ,"bsor"    ,"bsor"    ,"bsor");
INS(i_bsorl       ,"bsorl"   ,"bsorl"   ,"bsorl");
INS(i_bz          ,"bz"      ,"bz"      ,"bz");
INS(i_bza         ,"bza"     ,"bza"     ,"bza");
INS(i_bzc         ,"bzc"     ,"bzc"     ,"bzc");
INS(i_bzcl        ,"bzcl"    ,"bzcl"    ,"bzcl");
INS(i_bzl         ,"bzl"     ,"bzl"     ,"bzl");
INS(i_bzla        ,"bzla"    ,"bzla"    ,"bzla");
INS(i_bzr         ,"bzr"     ,"bzr"     ,"bzr");
INS(i_bzrl        ,"bzrl"    ,"bzrl"    ,"bzrl");
INS(i_ca          ,"ca"      ,"ca"      ,"ca");
INS(i_cmp         ,"cmp"     ,"cmp"     ,"cmp");
INS(i_cmpi        ,"cmpi"    ,"cmpi"    ,"cmpi");
INS(i_cmpl        ,"cmpl"    ,"cmpl"    ,"cmpl");
INS(i_cmpli       ,"cmpli"   ,"cmpli"   ,"cmpli");
INS(i_crand       ,"crand"   ,"crand"   ,"crand");
INS(i_crandc      ,"crandc"  ,"crandc"  ,"crandc");
INS(i_creqv       ,"creqv"   ,"creqv"   ,"creqv");
INS(i_crnand      ,"crnand"  ,"crnand"  ,"crnand");
INS(i_crnor       ,"crnor"   ,"crnor"   ,"crnor");
INS(i_cror        ,"cror"    ,"cror"    ,"cror");
INS(i_crorc       ,"crorc"   ,"crorc"   ,"crorc");
INS(i_crxor       ,"crxor"   ,"crxor"   ,"crxor");
INS(i_eqv         ,"eqv"     ,"eqv"     ,"eqv");
INS(i_eqv_cr      ,"eqv."    ,"eqv."    ,"eqv.");
INS(i_er          ,"er"      ,"er"      ,"er");


INS(i_fabs        ,"fabs"    ,"fabs"    ,"fabs");
INS(i_fabs_cr     ,"fabs."   ,"fabs."   ,"fabs.");
INS(i_fcmpo       ,"fcmpo"   ,"fcmpo"   ,"fcmpo");
INS(i_fcmpu       ,"fcmpu"   ,"fcmpu"   ,"fcmpu");


INS(i_fmr         ,"fmr"     ,"fmr"     ,"fmr");
INS(i_fmr_cr      ,"fmr."    ,"fmr."    ,"fmr.");

INS(i_fnabs       ,"fnabs"   ,"fnabs"   ,"fnabs");
INS(i_fnabs_cr    ,"fnabs."  ,"fnabs."  ,"fnabs.");
INS(i_fneg        ,"fneg"    ,"fneg"    ,"fneg");
INS(i_fneg_cr     ,"fneg."   ,"fneg."   ,"fneg.");

INS(i_frsp        ,"frsp"    ,"frsp"    ,"frsp");
INS(i_frsp_cr     ,"frsp."   ,"frsp."   ,"frsp.");

INS(i_ics         ,"ics"     ,"isync"   ,"ics");
INS(i_ilop        ,"ilop"    ,"ilop"    ,"ilop");
INS(i_ilopi       ,"ilopi"   ,"ilopi"   ,"ilopi");
INS(i_ilopr       ,"ilopr"   ,"ilopr"   ,"ilopr");

INS(i_lbz         ,"lbz"     ,"lbz"     ,"lbz");
INS(i_lbzu        ,"lbzu"    ,"lbzu"    ,"lbzu");
INS(i_lbzux       ,"lbzux"   ,"lbzux"   ,"lbzux");
INS(i_lbzx        ,"lbzx"    ,"lbzx"    ,"lbzx");
INS(i_lfd         ,"lfd"     ,"lfd"     ,"lfd");
INS(i_lfdu        ,"lfdu"    ,"lfdu"    ,"lfdu");
INS(i_lfdux       ,"lfdux"   ,"lfdux"   ,"lfdux");
INS(i_lfdx        ,"lfdx"    ,"lfdx"    ,"lfdx");
INS(i_lfs         ,"lfs"     ,"lfs"     ,"lfs");
INS(i_lfsu        ,"lfsu"    ,"lfsu"    ,"lfsu");
INS(i_lfsux       ,"lfsux"   ,"lfsux"   ,"lfsux");
INS(i_lfsx        ,"lfsx"    ,"lfsx"    ,"lfsx");
INS(i_lha         ,"lha"     ,"lha"     ,"lha");
INS(i_lhau        ,"lhau"    ,"lhau"    ,"lhau");
INS(i_lhaux       ,"lhaux"   ,"lhaux"   ,"lhaux");
INS(i_lhax        ,"lhax"    ,"lhax"    ,"lhax");
INS(i_lhbrx       ,"lhbrx"   ,"lhbrx"   ,"lhbrx");
INS(i_lhz         ,"lhz"     ,"lhz"     ,"lhz");
INS(i_lhzu        ,"lhzu"    ,"lhzu"    ,"lhzu");
INS(i_lhzux       ,"lhzux"   ,"lhzux"   ,"lhzux");
INS(i_lhzx        ,"lhzx"    ,"lhzx"    ,"lhzx");
INS(i_li          ,"li"      ,"li"      ,"li");
INS(i_lil         ,"lil"     ,"lil"     ,"lil");
INS(i_liu         ,"liu"     ,"liu"     ,"liu");




INS(i_mcrf        ,"mcrf"    ,"mcrf"    ,"mcrf");
INS(i_mcrfs       ,"mcrfs"   ,"mcrfs"   ,"mcrfs");
INS(i_mcrxr       ,"mcrxr"   ,"mcrxr"   ,"mcrxr");
INS(i_mfcr        ,"mfcr"    ,"mfcr"    ,"mfcr");
INS(i_mfctr       ,"mfctr"   ,"mfctr"   ,"mfctr");
INS(i_mfdar       ,"mfdar"   ,"mfdar"   ,"mfdar");
INS(i_mfdec       ,"mfdec"   ,"mfdec"   ,"mfdec");
INS(i_mfdsisr     ,"mfdsisr" ,"mfdsisr" ,"mfdsisr");
INS(i_mffs        ,"mffs"    ,"mffs"    ,"mffs");
INS(i_mffs_cr     ,"mffs."   ,"mffs."   ,"mffs.");
INS(i_mflr        ,"mflr"    ,"mflr"    ,"mflr");
INS(i_mfrtcl      ,"mfrtcl"  ,"mfrtcl"  ,"mfrtcl");
INS(i_mfrtcu      ,"mfrtcu"  ,"mfrtcu"  ,"mfrtcu");
INS(i_mfsdr0      ,"mfsdr0"  ,"mfsdr0"  ,"mfsdr0");
INS(i_mfsdr1      ,"mfsdr1"  ,"mfsdr1"  ,"mfsdr1");
INS(i_mfspr       ,"mfspr"   ,"mfspr"   ,"mfspr");

INS(i_mfsrr0      ,"mfsrr0"  ,"mfsrr0"  ,"mfsrr0");
INS(i_mfsrr1      ,"mfsrr1"  ,"mfsrr1"  ,"mfsrr1");
INS(i_mftid       ,"mftid"   ,"mftid"   ,"mftid");
INS(i_mfxer       ,"mfxer"   ,"mfxer"   ,"mfxer");
INS(i_mr          ,"mr"      ,"mr"      ,"mr");
INS(i_mr_cr       ,"mr."     ,"mr."     ,"mr.");
INS(i_mtcr        ,"mtcr"    ,"mtcr"    ,"mtcr");
INS(i_mtcrf       ,"mtcrf"   ,"mtcrf"   ,"mtcrf");
INS(i_mtctr       ,"mtctr"   ,"mtctr"   ,"mtctr");
INS(i_mtdar       ,"mtdar"   ,"mtdar"   ,"mtdar");
INS(i_mtdec       ,"mtdec"   ,"mtdec"   ,"mtdec");
INS(i_mtdsisr     ,"mtdsisr" ,"mtdsisr" ,"mtdsisr");
INS(i_mtfs        ,"mtfs"    ,"mtfs"    ,"mtfs");
INS(i_mtfs_cr     ,"mtfs."   ,"mtfs."   ,"mtfs.");
INS(i_mtfsb0      ,"mtfsb0"  ,"mtfsb0"  ,"mtfsb0");
INS(i_mtfsb0_cr   ,"mtfsb0." ,"mtfsb0." ,"mtfsb0.");
INS(i_mtfsb1      ,"mtfsb1"  ,"mtfsb1"  ,"mtfsb1");
INS(i_mtfsb1_cr   ,"mtfsb1." ,"mtfsb1." ,"mtfsb1.");
INS(i_mtfsf       ,"mtfsf"   ,"mtfsf"   ,"mtfsf");
INS(i_mtfsf_cr    ,"mtfsf."  ,"mtfsf."  ,"mtfsf.");
INS(i_mtfsfi      ,"mtfsfi"  ,"mtfsfi"  ,"mtfsfi");
INS(i_mtfsfi_cr   ,"mtfsfi." ,"mtfsfi." ,"mtfsfi.");
INS(i_mtlr        ,"mtlr"    ,"mtlr"    ,"mtlr");
INS(i_mtmsr       ,"mtmsr"   ,"mtmsr"   ,"mtmsr");
INS(i_mtrtcl      ,"mtrtcl"  ,"mtrtcl"  ,"mtrtcl");
INS(i_mtrtcu      ,"mtrtcu"  ,"mtrtcu"  ,"mtrtcu");
INS(i_mtsdr0      ,"mtsdr0"  ,"mtsdr0"  ,"mtsdr0");
INS(i_mtsdr1      ,"mtsdr1"  ,"mtsdr1"  ,"mtsdr1");
INS(i_mtspr       ,"mtspr"   ,"mtspr"   ,"mtspr");
INS(i_mtsr        ,"mtsr"    ,"mtsr"    ,"mtsr");
INS(i_mtsrr0      ,"mtsrr0"  ,"mtsrr0"  ,"mtsrr0");
INS(i_mtsrr1      ,"mtsrr1"  ,"mtsrr1"  ,"mtsrr1");
INS(i_mttid       ,"mttid"   ,"mttid"   ,"mttid");
INS(i_mtxer       ,"mtxer"   ,"mtxer"   ,"mtxer");


INS(i_nand        ,"nand"    ,"nand"    ,"nand");
INS(i_nand_cr     ,"nand."   ,"nand."   ,"nand.");
INS(i_neg         ,"neg"     ,"neg"     ,"neg");
INS(i_neg_cr      ,"neg."    ,"neg."    ,"neg.");
INS(i_nego        ,"nego"    ,"nego"    ,"nego");
INS(i_nego_cr     ,"nego."   ,"nego."   ,"nego.");
INS(i_nor         ,"nor"     ,"nor"     ,"nor");
INS(i_nor_cr      ,"nor."    ,"nor."    ,"nor.");
INS(i_or          ,"or"      ,"or"      ,"or");
INS(i_or_cr       ,"or."     ,"or."     ,"or.");
INS(i_orc         ,"orc"     ,"orc"     ,"orc");
INS(i_orc_cr      ,"orc."    ,"orc."    ,"orc.");

INS(i_re          ,"re"      ,"re"      ,"re");
INS(i_rfi         ,"rfi"     ,"rfi"     ,"rfi");
INS(i_rfsvc       ,"rfsvc"   ,"rfsvc"   ,"rfsvc");

INS(i_rtc         ,"rtc"     ,"rtc"     ,"rtc");
INS(i_ru          ,"ru"      ,"ru"      ,"ru");
INS(i_ryo         ,"ryo"     ,"ryo"     ,"ryo");
INS(i_ryod        ,"ryod"    ,"ryod"    ,"ryod");


INS(i_si          ,"si"      ,"si"      ,"si");
INS(i_si_cr       ,"si."     ,"si."     ,"si.");
INS(i_sli         ,"sli"     ,"sli"     ,"sli");
INS(i_sli_cr      ,"sli."    ,"sli."    ,"sli.");
INS(i_sri         ,"sri"     ,"sri"     ,"sri");
INS(i_sri_cr      ,"sri."    ,"sri."    ,"sri.");
INS(i_stb         ,"stb"     ,"stb"     ,"stb");
INS(i_stbu        ,"stbu"    ,"stbu"    ,"stbu");
INS(i_stbux       ,"stbux"   ,"stbux"   ,"stbux");
INS(i_stbx        ,"stbx"    ,"stbx"    ,"stbx");
INS(i_stfd        ,"stfd"    ,"stfd"    ,"stfd");
INS(i_stfdu       ,"stfdu"   ,"stfdu"   ,"stfdu");
INS(i_stfdux      ,"stfdux"  ,"stfdux"  ,"stfdux");
INS(i_stfdx       ,"stfdx"   ,"stfdx"   ,"stfdx");
INS(i_stfs        ,"stfs"    ,"stfs"    ,"stfs");
INS(i_stfsu       ,"stfsu"   ,"stfsu"   ,"stfsu");
INS(i_stfsux      ,"stfsux"  ,"stfsux"  ,"stfsux");
INS(i_stfsx       ,"stfsx"   ,"stfsx"   ,"stfsx");
INS(i_sth         ,"sth"     ,"sth"     ,"sth");
INS(i_sthbrx      ,"sthbrx"  ,"sthbrx"  ,"sthbrx");
INS(i_sthu        ,"sthu"    ,"sthu"    ,"sthu");
INS(i_sthux       ,"sthux"   ,"sthux"   ,"sthux");
INS(i_sthx        ,"sthx"    ,"sthx"    ,"sthx");
INS(i_teq         ,"teq"     ,"teq"     ,"teq");
INS(i_teqi        ,"teqi"    ,"teqi"    ,"teqi");
INS(i_tge         ,"tge"     ,"tge"     ,"tge");
INS(i_tgei        ,"tgei"    ,"tgei"    ,"tgei");
INS(i_tgt         ,"tgt"     ,"tgt"     ,"tgt");
INS(i_tgti        ,"tgti"    ,"tgti"    ,"tgti");
INS(i_tlbp        ,"tlbp"    ,"tlbp"    ,"tlbp");
INS(i_tle         ,"tle"     ,"tle"     ,"tle");
INS(i_tlei        ,"tlei"    ,"tlei"    ,"tlei");
INS(i_tlge        ,"tlge"    ,"tlge"    ,"tlge");
INS(i_tlgei       ,"tlgei"   ,"tlgei"   ,"tlgei");
INS(i_tlgt        ,"tlgt"    ,"tlgt"    ,"tlgt");
INS(i_tlgti       ,"tlgti"   ,"tlgti"   ,"tlgti");
INS(i_tlle        ,"tlle"    ,"tlle"    ,"tlle");
INS(i_tllei       ,"tllei"   ,"tllei"   ,"tllei");
INS(i_tllt        ,"tllt"    ,"tllt"    ,"tllt");
INS(i_tllti       ,"tllti"   ,"tllti"   ,"tllti");
INS(i_tlne        ,"tlne"    ,"tlne"    ,"tlne");
INS(i_tlnei       ,"tlnei"   ,"tlnei"   ,"tlnei");
INS(i_tlt         ,"tlt"     ,"tlt"     ,"tlt");
INS(i_tlti        ,"tlti"    ,"tlti"    ,"tlti");
INS(i_tne         ,"tne"     ,"tne"     ,"tne");
INS(i_tnei        ,"tnei"    ,"tnei"    ,"tnei");
INS(i_tri         ,"tri"     ,"tri"     ,"tri");
INS(i_trr         ,"trr"     ,"trr"     ,"trr");
INS(i_xor         ,"xor"     ,"xor"     ,"xor");
INS(i_xor_cr      ,"xor."    ,"xor."    ,"xor.");





/* PowerPC only instructions */

INS(i_divw        ,"VOID"    ,"divw"    ,"VOID");
INS(i_divw_cr     ,"VOID"    ,"divw."   ,"VOID");
INS(i_divwo       ,"VOID"    ,"divwo"   ,"VOID");
INS(i_divwo_cr    ,"VOID"    ,"divwo."  ,"VOID");
INS(i_divwu       ,"VOID"    ,"divwu"   ,"VOID");
INS(i_divwu_cr    ,"VOID"    ,"divwu."  ,"VOID");
INS(i_divwuo      ,"VOID"    ,"divwuo"  ,"VOID");
INS(i_divwuo_cr   ,"VOID"    ,"divwuo." ,"VOID");
INS(i_extsb       ,"VOID"    ,"extsb"   ,"VOID");
INS(i_extsb_cr    ,"VOID"    ,"extsb."  ,"VOID");
INS(i_fctiw       ,"VOID"    ,"fctiw"   ,"VOID");
INS(i_fctiwz      ,"VOID"    ,"fctiwz"  ,"VOID");
INS(i_mulhw       ,"VOID"    ,"mulhw"   ,"VOID");
INS(i_mulhw_cr    ,"VOID"    ,"mulhw."  ,"VOID");
INS(i_mulhwu      ,"VOID"    ,"mulhwu"  ,"VOID");
INS(i_mulhwu_cr   ,"VOID"    ,"mulhwu." ,"VOID");



#endif			/* INSTRUCTDECS_H */
