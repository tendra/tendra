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


/* 80x86/instrmacs.h */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: instrmacs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.12  1996/06/25  09:46:41  pwe
 * correct round toward zero unsigned
 *
 * Revision 1.11  1996/05/20  14:30:39  pwe
 * improved 64-bit handling
 *
 * Revision 1.10  1996/05/13  12:52:04  pwe
 * undo premature commit
 *
 * Revision 1.8  1995/09/26  16:47:03  pwe
 * compare with zero to ignore previous overflow
 *
 * Revision 1.7  1995/09/19  15:42:54  pwe
 * round, fp overflow etc
 *
 * Revision 1.6  1995/09/15  17:39:26  pwe
 * tidy and correct fistp
 *
 * Revision 1.5  1995/09/05  16:25:05  pwe
 * specials and exception changes
 *
 * Revision 1.4  1995/08/14  13:53:57  pwe
 * several corrections, tail calls and error jumps
 *
 * Revision 1.3  1995/02/16  18:47:17  pwe
 * transformed subtract inverts, sets and adds carry in case of error_jump
 *
 * Revision 1.2  1995/01/30  12:56:28  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:35:21  jmf
 * Initial revision
 *
**********************************************************************/

#ifndef instrmackey
#define instrmackey 1


#define push_fl temp_push_fl()
#define pop_fl temp_pop_fl()


#define adcb "adcb"
#define adcl "adc"
#define adcw "o16 adc"
#define addb "addb"
#define addl "add"
#define addw "o16 add"
#define andb "andb"
#define andl "and"
#define andw "o16 and"
#define call "call"
#define cltd "cltd"
#define cmpb "cmpb"
#define cmpl "cmp"
#define cmpsb "cmpsb"
#define cmpw "o16 cmp"
#define decb "decb"
#define decl "dec"
#define decw "o16 dec"
#define divb "divb"
#define divl "div"
#define divw "o16 div"
#define fabs "fabs"
#define fadd "fadd"
#define faddp "faddp"
#define faddl "faddd"
#define fadds "fadds"
#define fchs "fchs"
#define fclex "fclex"
#define fcoml "fcomd"
#define fcomp "fcomp"
#define fcompp "fcompp"
#define fdiv "fdiv"
#define fdivp "fdivp"
#define fdivl "fdivd"
#define fdivrl "fdivrd"
#define fdivr "fdivr"
#define fdivrp "fdivrp"
#define fdivrs "fdivrs"
#define fdivs "fdivs"
#define fild "filds"
#define fildl "fildl"
#define fildll "fildq"
#define finit "finit"
#define fistp "fistps"
#define fistpl "fistpl"
#define fistpll "fistpq"
#define fld "fld"
#define fld1 "fld1"
#define fldl "fldd"
#define fldcw "fldcw"
#define flds "flds"
#define fldt "fldx"
#define fldz "fldz"
#define fmul "fmul"
#define fmulp "fmulp"
#define fmull "fmuld"
#define fmuls "fmuls"
#define fnstsw "fstsw"
#define frndint "frndint"
#define fst "fst"
#define fstcw "fstcw"
#define fstsw "fstsw"
#define fstl "fstd"
#define fstp "fstp"
#define fstpl "fstpd"
#define fstps "fstps"
#define fstpt "fstpx"
#define fsts "fsts"
#define fstt "fstt"
#define fsub "fsub"
#define fsubp "fsubp"
#define fsubl "fsubd"
#define fsubrl "fsubrd"
#define fsubr "fsubr"
#define fsubrp "fsubrp"
#define fsubrs "fsubrs"
#define fsubs "fsubs"
#define ftst "ftst"
#define fwait "wait"
#define idivb "idivb"
#define idivl "idiv"
#define idivw "o16 idiv"
#define imulb "imulb"
#define imull "imul"
#define imulw "o16 imul"
#define incb "incb"
#define incl "inc"
#define incw "o16 inc"
#define into "into"
#define ja "ja"
#define jae "jae"
#define jb "jb"
#define jbe "jbe"
#define je "je"
#define jg "jg"
#define jge "jge"
#define jl "jl"
#define jle "jle"
#define jmp "jmp"
#define jne "jne"
#define jno "jno"
#define jns "jns"
#define jo "jo"
#define jpe "jpe"
#define jpo "jpo"
#define js "js"
#define leal "lea"
#define leave "leave"
#define movb "movb"
#define movl "mov"
#define movw "o16 mov"
#define movsb "movsb"
#define movsl "movs"
#define movsw "o16 movs"
#define movsbl "movsxb"
#define movswl "movsx"
#define movsbw "o16 movsxb"
#define movzbl "movzxb"
#define movzwl "movzx"
#define movzbw "o16 movzxb"
#define mulb "mulb"
#define mull "mul"
#define mulw "o16 mul"
#define negb "negb"
#define negl "neg"
#define negw "o16 neg"
#define nop "nop"
#define notb "notb"
#define notl "not"
#define notw "o16 not"
#define orb "orb"
#define orl "or"
#define orw "o16 or"
#define popeax "pop eax"
#define popedx "pop edx"
#define popebx "pop ebx"
#define popecx "pop ecx"
#define popedi "pop edi"
#define popesi "pop esi"
#define popebp "pop ebp"
#define popl "pop"
#define pusheax "push eax"
#define pushedx "push edx"
#define pushecx "push ecx"
#define pushesi "push esi"
#define pushedi "push edi"
#define pushl "push"
#define rdtsc "rdtsc"
#define rep "rep"
#define ret "ret"
#define rolb "rolb"
#define roll "rol"
#define rolw "o16 rol"
#define rorb "rorb"
#define rorl "ror"
#define rorw "o16 ror"
#define sahf "sahf"
#define salb "salb"
#define sall "sal"
#define salw "o16 sal"
#define sarb "sarb"
#define sarl "sar"
#define sarw "o16 sar"
#define sbbb "sbbb"
#define sbbl "sbb"
#define sbbw "o16 sbb"
#define seta "seta"
#define setae "setae"
#define setb "setb"
#define setbe "setbe"
#define sete "sete"
#define setg "setg"
#define setge "setge"
#define setl "setl"
#define setle "setle"
#define setmp "setmp"
#define setne "setne"
#define shlb "shlb"
#define shll "shl"
#define shlw "o16 shl"
#define shldl "shld"
#define shldw "o16 shld"
#define shrb "shrb"
#define shrl "shr"
#define shrw "o16 shr"
#define shrdl "shrd"
#define shrdw "o16 shrd"
#define stc "stc"
#define subb "subb"
#define subl "sub"
#define subw "o16 sub"
#define subbl "subbl"
#define testb "testb"
#define testl "test"
#define testw "o16 test"
#define xchg "xchg"
#define xorb "xorb"
#define xorl "xor"
#define xorw "o16 xor"

#endif
