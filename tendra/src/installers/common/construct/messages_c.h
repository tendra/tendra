/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#ifndef mess_c_key
#define mess_c_key



#define ILLEGAL_FLADD "illegal floating add constants"
#define ILLEGAL_FLMULT "illegal floating mult constants"
#define ADD_OUT_OF_BOUNDS "constant addition out of bounds, consider using -nepc"
#define MULT_OUT_OF_BOUNDS "constant mult out of bounds, consider using -nepc"
#define BAD_SHAPE "impossible shape found"
#define CONSTC_ERROR "unanticipated component"
#define CASE_OVERLAP "case tags overlap"
#define BIG_FLPT "floating point number too big"
#define FLPT_TO_INT_ERROR "flpt too big to round to int"
#define TOO_MANY_BITS "too many bits in bitfield"
#define NO_EXP_EXTENSION "no exp extension"
#define CHSH_ABS "check_shape: abs"
#define CHSH_ADDPTR "check_shape: add_to_ptr"
#define CHSH_AND "check_shape: and"
#define CHSH_APPLY "check_shape: apply_proc"
#define CHSH_ASSIGN "check_shape: assign"
#define CHSH_ASSIGN_VOL "check_shape: assign to volatile"
#define CHSH_BFASS "check_shape: bitfield_assign"
#define CHSH_BFCONT "check_shape: bitfield_contents"
#define CHSH_CASE "check_shape: case"
#define CHSH_CHBITFIELD "check_shape: change_bitfield_to_int"
#define CHSH_CHFL "check_shape: change_floating_variety"
#define CHSH_CHINTBF "check_shape:  change_int_to_bitfield"
#define CHSH_CHVAR "check_shape: change_variety" 
#define CHSH_COMPONENT "check_shape: component" 
#define CHSH_CONCATNOF "check_shape: concat_nof" 
#define CHSH_CONJUGATE "check_shape: complex_conjugate"
#define CHSH_CONTENTS "check_shape: contents" 
#define CHSH_CONTENTS_VOL "check_shape: contents of volatile" 
#define CHSH_DIV0 "check_shape: div0" 
#define CHSH_DIV1 "check_shape: div1" 
#define CHSH_DIV2 "check_shape: div2" 
#define CHSH_FLINT "check_shape: float_int"
#define CHSH_FLABS "check_shape: floating_abs"
#define CHSH_FLDIV "check_shape: floating_div"
#define CHSH_FLMINUS "check_shape: floating_minus"
#define CHSH_FLMAX "check_shape: floating_maximum"
#define CHSH_FLMIN "check_shape: floating_minimum"
#define CHSH_FLMULT "check_shape: floating_mult"
#define CHSH_FLNEGATE "check_shape: floating_negate"
#define CHSH_FLPLUS "check_shape: floating_plus"
#define CHSH_FLPOWER "check_shape: floating_power"
#define CHSH_FLTEST "check_shape: floating_test"
#define CHSH_GOLOCALLV "check_shape: goto_local_lv"
#define CHSH_IMAG "check_shape: imaginary part"
#define CHSH_INTTEST "check_shape: integer_test"
#define CHSH_LOCALLOC "check_shape: local_alloc"
#define CHSH_LOCFREE "check_shape: local_free"
#define CHSH_LVTEST "check_shape: local_lv_test"
#define CHSH_LONGJUMP "check_shape: long_jump"
#define CHSH_MAKECPD "check_shape: make_compound"
#define BAD_BASE "flpt base not 2,4,8,10,16"
#define BIG_32 "integer too big"
#define CHSH_MAKE_PROC "check_shape: make_proc, result shape must be bottom"
#define CHSH_MAKENOF "check_shape: make_nof"
#define CHSH_MAKE_COMPLEX "check_shape: make_complex"
#define CHSH_MINUS "check_shape: minus"
#define CHSH_MAX "check_shape: max"
#define CHSH_MIN "check_shape: min"
#define CHSH_MOVESOME "check_shape: move_some"
#define CHSH_MULT "check_shape: mult"
#define CHSH_NEGATE "check_shape: negate"
#define CHSH_NOT "check_shape: not"
#define UNDEF_TAG "using undefined tag"
#define CHSH_OFFSETADD "check_shape: offset_add"
#define CHSH_OFFSETDIV "check_shape: offset_div"
#define CHSH_OFFSETDIVINT "check_shape: offset_div_by_int"
#define CHSH_OFFSETMAX "check_shape: offset_max"
#define CHSH_OFFSETMULT "check_shape: offset_mult"
#define CHSH_OFFSETNEG "check_shape: offset_negate"
#define CHSH_OFFSETPAD "check_shape: offset_pad"
#define CHSH_OFFSETPADEXP "check_shape: offset_pad_exp"
#define CHSH_OFFSETTEST "check_shape: offset_test"
#define CHSH_OR "check_shape: or"
#define CHSH_PLUS "check_shape: plus"
#define CHSH_POWER "check_shape: power"
#define CHSH_PTRTEST "check_shape: pointer_test"
#define CHSH_PROCTEST "check_shape: proc_test"
#define CHSH_REAL "check_shape: real part"
#define CHSH_REM0 "check_shape: rem0"
#define CHSH_REM1 "check_shape: rem1"
#define CHSH_REM2 "check_shape: rem2"
#define CHSH_ROTL "check_shape: rotate_left"
#define CHSH_ROTR "check_shape: rotate_right"
#define CHSH_ROUND "check_shape: round_with_mode"
#define CHSH_SHL "check_shape: shift_left"
#define CHSH_SHR "check_shape: shift_right"
#define CHSH_XOR "check_shape: xor"
#define ILLCOMPNAT "illegal computed nat"
#define ILLNAT "constant out of range"
#define ILLCPDOFFSET "non constant offset param for compound"
#define ILLOFF2 "illegal offset second arg"
#define ILLOFF1 "illegal offset first arg"
#define ILLALIGN "illegal alignment"
#define ILLCOMPSNAT "illegal computed signed nat"
#define ILL_OFFSETPAD "unknown alignment in offset_pad"
#define BASE_NOT_10 "flpt base not 10"
#define WRONG_VERSION "Wrong TDF version for this installer"
#define TOO_BIG_A_VECTOR "too big a vector"
#define TOO_BIG_A_VARIETY "too big a variety"
#define TOO_BIG_A_CASE_ELEMENT "too big a case element"
#define BAD_FLOATING_VAR "unimplemented floating variety"
#define WIDTH_ERROR "bad 64 bit number"
#define WRONG_64 "bad variety width"

#endif
