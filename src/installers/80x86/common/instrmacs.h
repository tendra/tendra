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
#define adcl "adcl"
#define adcw "adcw"
#define addb "addb"
#define addl "addl"
#define addw "addw"
#define andb "andb"
#define andl "andl"
#define andw "andw"
#define call "call"
#define cltd "cltd"
#define cmpb "cmpb"
#define cmpl "cmpl"
#define cmpsb "cmpsb"
#define cmpw "cmpw"
#define decb "decb"
#define decl "decl"
#define decw "decw"
#define divb "divb"
#define divl "divl"
#define divw "divw"
#define fabs "fabs"
#define fadd "fadd"
#define faddp "faddp"
#define faddl "faddl"
#define fadds "fadds"
#define fchs "fchs"
#define fclex "fclex"
#define fcoml "fcoml"
#define fcomp "fcomp"
#define fcompp "fcompp"
#define fdiv "fdiv"
#define fdivp "fdivp"
#define fdivl "fdivl"
#define fdivrl "fdivrl"
#define fdivr "fdivr"
#define fdivrp "fdivrp"
#define fdivrs "fdivrs"
#define fdivs "fdivs"
#define fild "fild"
#define fildl "fildl"
#define fildll "fildll"
#define finit "finit"
#define fistp "fistp"
#define fistpl "fistpl"
#define fistpll "fistpll"
#define fld "fld"
#define fld1 "fld1"
#define fldl "fldl"
#define fldcw "fldcw"
#define flds "flds"
#define fldt "fldt"
#define fldz "fldz"
#define fmul "fmul"
#define fmulp "fmulp"
#define fmull "fmull"
#define fmuls "fmuls"
#define fnstsw "fnstsw"
#define frndint "frndint"
#define fst "fst"
#define fstcw "fstcw"
#define fstsw "fstsw"
#define fstl "fstl"
#define fstp "fstp"
#define fstpl "fstpl"
#define fstps "fstps"
#define fstpt "fstpt"
#define fsts "fsts"
#define fstt "fstt"
#define fsub "fsub"
#define fsubp "fsubp"
#define fsubl "fsubl"
#define fsubrl "fsubrl"
#define fsubr "fsubr"
#define fsubrp "fsubrp"
#define fsubrs "fsubrs"
#define fsubs "fsubs"
#define ftst "ftst"
#define fwait "fwait"
#define idivb "idivb"
#define idivl "idivl"
#define idivw "idivw"
#define imulb "imulb"
#define imull "imull"
#define imulw "imulw"
#define incb "incb"
#define incl "incl"
#define incw "incw"
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
#define leal "leal"
#define leave "leave"
#define movb "movb"
#define movl "movl"
#define movsbl "movsbl"
#define movsbw "movsbw"
#define movsb "movsb"
#define movsl "movsl"
#define movsw "movsw"
#define movswl "movswl"
#define movw "movw"
#define movzbl "movzbl"
#define movzbw "movzbw"
#define movzwl "movzwl"
#define mulb "mulb"
#define mull "mull"
#define mulw "mulw"
#define negb "negb"
#define negl "negl"
#define negw "negw"
#define nop "nop"
#define notb "notb"
#define notl "notl"
#define notw "notw"
#define orb "orb"
#define orl "orl"
#define orw "orw"
#define popeax "pop %eax"
#define popedx "pop %edx"
#define popebx "pop %ebx"
#define popecx "pop %ecx"
#define popedi "pop %edi"
#define popesi "pop %esi"
#define popebp "pop %ebp"
#define popl "popl"
#define pusheax "push %eax"
#define pushedx "push %edx"
#define pushecx "push %ecx"
#define pushesi "push %esi"
#define pushedi "push %edi"
#define pushl "pushl"
#define rdtsc "rdtsc"
#define rep "rep"
#define ret "ret"
#define rorb "rorb"
#define rolb "rolb"
#define rorw "rorw"
#define rolw "rolw"
#define rorl "rorl"
#define roll "roll"
#define sahf "sahf"
#define salb "salb"
#define sall "sall"
#define salw "salw"
#define sarb "sarb"
#define sarl "sarl"
#define sarw "sarw"
#define sbbb "sbbb"
#define sbbw "sbbw"
#define sbbl "sbbl"
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
#define shll "shll"
#define shlw "shlw"
#define shldl "shldl"
#define shrb "shrb"
#define shrl "shrl"
#define shrw "shrw"
#define shrdl "shrdl"
#define stc "stc"
#define subb "subb"
#define subw "subw"
#define subl "subl"
#define subbl "subbl"
#define testb "testb"
#define testl "testl"
#define testw "testw"
#define xchg "xchg"
#define xorb "xorb"
#define xorl "xorl"
#define xorw "xorw"

#endif
