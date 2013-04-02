/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CONVERT_INCLUDED
#define CONVERT_INCLUDED


/*
    TYPE REPRESENTING AN IMPLICIT CONVERSION SEQUENCE

    This type is used to represent an implicit conversion sequence.  The
    main components are the two types being converted from and to, and
    the overall rank of the conversion (see below).  For user-defined
    conversions, the conversion function used and the rank of the following
    standard conversion are recorded.  For base class and qualification
    conversions the associated data is also recorded.
*/

typedef struct {
	TYPE from, to;
	unsigned rank;
	unsigned std;
	IDENTIFIER usr;
	GRAPH base;
	CV_SPEC qual;
} CONVERSION;


/*
    TYPE CONVERSION DECLARATIONS

    The routines in this module are concerned with the standard C and C++
    type conversions.
*/

extern TYPE arith_type(TYPE, TYPE, EXP, EXP);
extern TYPE promote_type(TYPE);
extern TYPE unpromote_type(TYPE);
extern TYPE arg_promote_type(TYPE, ERROR *);
extern TYPE ptr_common_type(TYPE, TYPE, int, int *);
extern TYPE ptr_mem_common_type(TYPE, TYPE, int *);
extern TYPE common_type(TYPE, TYPE, int *);
extern unsigned check_qualifier(TYPE, TYPE, int);
extern int is_arg_promote(TYPE);
extern int qualifier_depth;

extern EXP convert_arith(TYPE, EXP, int, int);
extern EXP convert_bitfield(EXP);
extern EXP convert_boolean(EXP, unsigned, ERROR *);
extern EXP convert_array(EXP, int, ERROR *);
extern EXP convert_lvalue(EXP);
extern EXP convert_none(EXP);
extern EXP convert_const(EXP);
extern EXP convert_promote(TYPE, EXP);
extern EXP convert_ptr_common(TYPE, EXP, int, int);
extern EXP convert_ptr_mem_common(TYPE, EXP, int, int);
extern EXP convert_reference(EXP, int);
extern TYPE convert_qual_type(TYPE);

extern unsigned convert_seq(CONVERSION *, EXP, int, int);
extern unsigned std_convert_seq(CONVERSION *, EXP, int, int);
extern int compare_seq(CONVERSION *, CONVERSION *);
extern int is_ambiguous_func(IDENTIFIER);


/*
    QUALIFICATION CONVERSION RULES

    These values comprise the bitpattern returned by check_qualifier.  They
    indicate which of the conditions required by the qualifaction conversions
    are satisfied by a particular pair of types.  They are also used to
    indicate whether the types are equal or equal functions.
*/

#define QUAL_SIMILAR		((unsigned)0x01)
#define QUAL_CONST		((unsigned)0x02)
#define QUAL_VOLATILE		((unsigned)0x04)
#define QUAL_ALL_CONST		((unsigned)0x08)
#define QUAL_EXACT		((unsigned)0x10)
#define QUAL_FUNC		((unsigned)0x20)
#define QUAL_TEMPL		((unsigned)0x40)

#define QUAL_CV			((unsigned)0x0e)
#define QUAL_OK			((unsigned)0x0f)
#define QUAL_EQUAL		((unsigned)0x1f)
#define QUAL_EQ_FUNC		((unsigned)0x3f)


/*
    CONVERSION SEQUENCE RANKS

    These values are used to indicate the various ranks of implicit
    conversion sequences used within overload resolution.  The upper byte
    gives the conversion rank (the higher the value, the better the
    conversion), while the lower byte gives further information on the
    dominant conversion.
*/

#define CONV_EXACT		((unsigned)0x60)

#define CONV_QUAL		((unsigned)0x50)
#define CONV_STRING		((unsigned)0x51)

#define CONV_INT_PROM		((unsigned)0x40)
#define CONV_FLT_PROM		((unsigned)0x41)
#define CONV_BITFIELD		((unsigned)0x42)

#define CONV_INT_INT		((unsigned)0x30)
#define CONV_FLT_FLT		((unsigned)0x31)
#define CONV_INT_FLT		((unsigned)0x32)
#define CONV_FLT_INT		((unsigned)0x33)
#define CONV_PTR_BASE		((unsigned)0x34)
#define CONV_PTR_VOID		((unsigned)0x35)
#define CONV_PTR_BOTTOM		((unsigned)0x36)
#define CONV_PTR_NULL		((unsigned)0x37)
#define CONV_PTR_MEM_BASE	((unsigned)0x38)
#define CONV_PTR_MEM_NULL	((unsigned)0x39)
#define CONV_BASE		((unsigned)0x3a)
#define CONV_BOOL		((unsigned)0x3b)

#define CONV_USER		((unsigned)0x20)
#define CONV_USER_MULTI		((unsigned)0x21)

#define CONV_ELLIPSIS		((unsigned)0x10)

#define CONV_NONE		((unsigned)0x00)
#define CONV_NULL		((unsigned)0x01)
#define CONV_PTR_PTR		((unsigned)0x02)
#define CONV_PTR_PTR_ALIGN	((unsigned)0x03)
#define CONV_INT_PTR		((unsigned)0x04)
#define CONV_PTR_INT		((unsigned)0x05)
#define CONV_PTR_MEM_PTR_MEM	((unsigned)0x06)
#define CONV_PTR_MEM_FUNC	((unsigned)0x07)
#define CONV_FUNC		((unsigned)0x08)
#define CONV_ENUM		((unsigned)0x09)

#define CONV_REVERSE		((unsigned)0x80)

#define CONV_RANK(A)		((A) & 0x70)


/*
    REFERENCE CONVERSION CONTEXTS

    These values are used in convert_reference to indicate the various
    contexts for reference conversion.
*/

#define REF_NORMAL		0
#define REF_FUNCTION		1
#define REF_ASSIGN		2
#define REF_ADDRESS		3


#endif
