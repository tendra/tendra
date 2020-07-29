/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */
    
#ifndef MACH_INCLUDED
#define MACH_INCLUDED

#include <construct/installtypes.h>

#include <flpt/flpt.h>


/*
    STRUCTURE REPRESENTING MACHINE OPERANDS

    A machine operand consists of a type, the meaning of which is explained
    below, a value, which can be a number, a string or a floating-point
    number, and two pointers to further machine operands, plus and of.
*/

typedef struct tag_mach_op {
    char type ;
    union {
	long num ;
	char *str ;
	flt *fp ;
    } def ;
    struct tag_mach_op *plus ;
    struct tag_mach_op *of ;
#ifndef tdf3
#ifndef NDEBUG
    int id ;
#endif
#endif
} mach_op ;


/*
    STRUCTURE REPRESENTING MACHINE INSTRUCTIONS

    A machine instruction consists of an instruction number, which can
    take the values given in instrs.h, two machine operands, giving
    the operands of this instruction, a register mask, giving all the
    registers changed by this instruction, and a pointer to the next
    instruction.
*/

typedef struct tag_mach_ins {
    short ins_no ;
    mach_op *op1 ;
    mach_op *op2 ;
    bitpattern changed ;
    struct tag_mach_ins *next ;
#ifndef tdf3
#ifndef NDEBUG
    int id ;
#endif
#endif
} mach_ins ;


/*
    OPERAND TYPES

    These are the possible values for the type of a machine operand.
    The meanings are given below.
*/

#define  MACH_BF	0
#define  MACH_CONT	1
#define  MACH_DEC	2
#define  MACH_EXT	3
#define  MACH_EXTQ	4
#define  MACH_FLOATQ	5
#define  MACH_HEX	6
#define  MACH_HEXQ	7
#define  MACH_INC	8
#define  MACH_LAB	9
#define  MACH_LABQ	10
#define  MACH_NEG	11
#define  MACH_REG	12
#define  MACH_RPAIR	13
#define  MACH_SCALE	14
#define  MACH_SPEC	15
#define  MACH_SPECQ	16
#define  MACH_VAL	17
#define  MACH_VALQ	18

#ifndef tdf3
#ifndef NDEBUG
#define  MACH_COMMENT   19
#endif
#endif

/*
    REGISTER NUMBERS

    Each register is identified by a register number.
*/

#define  REG_D0		0
#define  REG_D1		1
#define  REG_D2		2
#define  REG_D3		3
#define  REG_D4		4
#define  REG_D5		5
#define  REG_D6		6
#define  REG_D7		7
#define  REG_A0		8
#define  REG_A1		9
#define  REG_A2		10
#define  REG_A3		11
#define  REG_A4		12
#define  REG_A5		13
#define  REG_AP		14
#define  REG_SP		15
#define  REG_FP0	16
#define  REG_FP1	17
#define  REG_FP2	18
#define  REG_FP3	19
#define  REG_FP4	20
#define  REG_FP5	21
#define  REG_FP6	22
#define  REG_FP7	23
#define  REG_PC		24
#define  REG_CCR	25
#define  REG_FPCR	26
#define  REG_FPSR	27
#define  REG_FPIAR	28
#define  REG_ZA0	29


/*
    TESTS ON REGISTER NUMBERS

    These test whether a given register number represents a D-register
    or an A-register.
*/

#define  is_dreg(X)	((X) < REG_A0)
#define  is_areg(X)	((X) >= REG_A0 && (X) < REG_FP0)


/*
    CONVERSION FROM REGISTER NUMBERS TO MASKS

    Given a register mask, reg returns the smallest register number
    involved in that mask.  Given a register number, regmsk gives the
    corresponding register mask.
*/

#define  reg(X)	bit_one(X)
#define  regmsk(X)	(((bitpattern) 1) << (X))


/*
    USEFUL MASKS ETC.

    dreg_msk gives all D-registers, areg_msk gives all A-registers,
    save_msk gives all registers preserved across procedure calls.
    regs extracts all the D- and A-registers from a mask.  fregs
    extracts all the F-registers.
*/

#define  dreg_msk	((bitpattern) 0x000000ff)
#define  areg_msk	((bitpattern) 0x0000ff00)
#define  save_msk	((bitpattern) 0xfffc3cfc)
#define  regs(X)	((X) & ((bitpattern) 0xffff))
#define  fregs(X)	((X) & ((bitpattern) 0xff0000))


/*
    MEANINGS OF OPERAND TYPES

    MACH_BF is used to represent bitfield operands.  Its of field is
    the basic operand, the def field is a number, giving the bitfield
    offset, the plus field is a dummy operand whose def field is a
    number, giving the bitfield size.

    MACH_CONT is used to represent contents operands.  The of field
    gives the operand the contents of which are meant.  The plus field
    may give another operand to be added.  The def field is a number
    giving all the registers used in this operand and all its sub-operands.

    MACH_DEC is used to represent pre-decremented registers.  Its def
    field is the register number involved.

    MACH_EXT and MACH_EXTQ are used to represent external names.  Their
    def field is a string giving the external name.

    MACH_FLOATQ is used to represent floating-point numbers.  Its def
    field is a pointer to the internal representation of the number.

    MACH_HEX, MACH_HEXQ, MACH_VAL and MACH_VALQ are used to represent
    integer constants.  Their def field gives the value.  The different
    types allow different numbers to be expressed in decimal or hex.

    MACH_INC is used to represent post-incremented registers.  Its def
    field is the register number involved.

    MACH_LAB and MACH_LABQ are used to represent labels.  Their def
    field is the label number.

    MACH_NEG is used to indicate that an operand should be negated.
    The operand to be negated is given by the plus field.

    MACH_REG is used to represent registers.  Its def field gives the
    register number.

    MACH_RPAIR is used to represent register pairs.  Its def field
    gives the first register number, the plus field is a dummy operand
    whose def field gives the second register number.

    MACH_SCALE is used to represent scaled operands.  Its def field
    is a number, giving the scaling factor, and its of field gives
    the operand being scaled.

    MACH_SPEC and MACH_SPECQ are used to represent special labels.
    Their def field is a string giving the special identifier.

    Most m68k operands and constants can be expressed by using the
    plus and of fields to connect the basic operands.  A special use
    of the of field is to string together a list of constants
    (which do not otherwise use it - see evaluate.c and output.c).

    For example, the register indirect operand 4(%a0) is represented
    by the machine operand a given by :

	    a = { MACH_CONT, regmsk (REG_A0), NULL, &b }
	    b = { MACH_REG, REG_A0, &c, NULL }
	    c = { MACH_VAL, 4, NULL, NULL }
*/

#endif
