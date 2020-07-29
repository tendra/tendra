/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This file defines the MIPS instruction set as C strings for use
 * by assembler producing routines such as make_code.
 *
 * Each MIPS instruction is a unique string starting with i_
 * using MIPS names  with . replaced by _
 *
 * The first character of each string is (binasm coding + 1)
 * for the instruction.
 */

#include "mips_ins.h"

char *i_la = "\45la";
char *i_lb = "\46lb";
char *i_lbu = "\47lbu";
char *i_lh = "\50lh";
char *i_lhu = "\51lhu";
char *i_lw = "\53lw";
char *i_lwc1 = "\55lwc1";
char *i_lwl = "\134lwl";
char *i_sb = "\107sb";
char *i_sh = "\115sh";
char *i_sw = "\130sw";
char *i_swc1 = "\64swc1";
char *i_swl = "\136swl";
char *i_swr = "\137swr";
char *i_ulh = "\320ulh";
char *i_ulhu = "\321ulhu";
char *i_ulw = "\317ulw";
char *i_ush = "\323ush";
char *i_usw = "\322usw";
char *i_rfe = "\104rfe";
char *i_syscall = "\131syscall";
char *i_break = "\34break";
char *i_nop = "\77nop";
char *i_li = "\52li";
char *i_lui = "\316lui";
char *i_abs = "\1abs";
char *i_neg = "\76neg";
char *i_negu = "\334negu";
char *i_not = "\133not";
char *i_add = "\2add";
char *i_addu = "\3addu";
char *i_and = "\4and";
char *i_div = "\41div";
char *i_divu = "\42divu";
char *i_xor = "\132xor";
char *i_mul = "\71mul";
char *i_mulo = "\72mulo";
char *i_mulou = "\73mulou";
char *i_nor = "\100nor";
char *i_or = "\101or";
char *i_rem = "\102rem";
char *i_remu = "\103remu";
char *i_rol = "\105rol";
char *i_ror = "\106ror";
char *i_seq = "\110seq";
char *i_slt = "\121slt";
char *i_sltu = "\122sltu";
char *i_sle = "\116sle";
char *i_sleu = "\117sleu";
char *i_sgt = "\113sgt";
char *i_sgtu = "\114sgtu";
char *i_sge = "\111sge";
char *i_sgeu = "\112sgeu";
char *i_sne = "\123sne";
char *i_sll = "\120sll";
char *i_sra = "\124sra";
char *i_srl = "\125srl";
char *i_sub = "\126sub";
char *i_subu = "\127subu";
char *i_mult = "\74mult";
char *i_multu = "\75multu";
char *i_b = "\5b";
char *i_bc1t = "\11bc1t";
char *i_bc1f = "\10bc1f";
char *i_beq = "\16beq";
char *i_bgt = "\22bgt";
char *i_bge = "\17bge";
char *i_bgeu = "\20bgeu";
char *i_bgtu = "\23bgtu";
char *i_blt = "\30blt";
char *i_bltu = "\31bltu";
char *i_ble = "\25ble";
char *i_bleu = "\26bleu";
char *i_bne = "\33bne";
char *i_bal = "\344bal";
char *i_beqz = "\335beqz";
char *i_bgez = "\21bgez";
char *i_bgezal = "\345bgezal";
char *i_bgtz = "\24bgtz";
char *i_blez = "\27blez";
char *i_bltz = "\32bltz";
char *i_bltzal = "\346bltzal";
char *i_bnez = "\336bnez";
char *i_j = "\43j";
char *i_jal = "\44jal";
char *i_move = "\62move";
char *i_mfhi = "\60mfhi";
char *i_mthi = "\67mthi";
char *i_mflo = "\61mflo";
char *i_mfc1 = "\142mfc1";
char *i_mtc1 = "\146mtc1";
char *i_cfc1 = "\342cfc1";
char *i_ctc1 = "\343ctc1";
char *i_l_d = "\170l.d";
char *i_l_s = "\167l.s";
char *i_s_d = "\173s.d";
char *i_s_s = "\172s.s";
char *i_mov_s = "\214mov.s";
char *i_mov_d = "\215mov.d";
char *i_abs_d = "\220abs.d";
char *i_abs_s = "\217abs.s";
char *i_add_d = "\176add.d";
char *i_add_s = "\175add.s";
char *i_div_s = "\206div.s";
char *i_div_d = "\207div.d";
char *i_mul_d = "\204mul.d";
char *i_mul_s = "\203mul.s";
char *i_sub_d = "\201sub.d";
char *i_sub_s = "\200sub.s";
char *i_cvt_s_d = "\222cvt.s.d";
char *i_cvt_d_s = "\225cvt.d.s";
char *i_cvt_s_w = "\224cvt.s.w";
char *i_cvt_d_w = "\227cvt.d.w";
char *i_cvt_w_d = "\234cvt.w.d";
char *i_cvt_w_s = "\233cvt.w.s";
char *i_neg_d = "\340neg.d";
char *i_neg_s = "\337neg.s";
char *i_c_eq_s = "\244c.eq.s";
char *i_c_eq_d = "\245c.eq.d";
char *i_c_lt_s = "\302c.lt.s";
char *i_c_lt_d = "\303c.lt.d";
char *i_c_le_s = "\310c.le.s";
char *i_c_le_d = "\311c.le.d";

char *i_trunc_w_s = "\351trunc.w.s";
char *i_trunc_w_d = "\352trunc.w.d";
char *i_round_w_s = "\354round.w.s";
char *i_round_w_d = "\355round.w.d";
