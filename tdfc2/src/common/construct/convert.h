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

enum {
	QUAL_SIMILAR         = 0x01U,
	QUAL_CONST           = 0x02U,
	QUAL_VOLATILE        = 0x04U,
	QUAL_ALL_CONST       = 0x08U,
	QUAL_EXACT           = 0x10U,
	QUAL_FUNC            = 0x20U,
	QUAL_TEMPL           = 0x40U,

	QUAL_CV              = 0x0eU,
	QUAL_OK              = 0x0fU,
	QUAL_EQUAL           = 0x1fU,
	QUAL_EQ_FUNC         = 0x3fU
};


/*
	CONVERSION SEQUENCE RANKS

	These values are used to indicate the various ranks of implicit
	conversion sequences used within overload resolution.  The upper byte
	gives the conversion rank (the higher the value, the better the
	conversion), while the lower byte gives further information on the
	dominant conversion.
*/

enum {
	CONV_EXACT           = 0x60U,

	CONV_QUAL            = 0x50U,
	CONV_STRING          = 0x51U,

	CONV_INT_PROM        = 0x40U,
	CONV_FLT_PROM        = 0x41U,
	CONV_BITFIELD        = 0x42U,

	CONV_INT_INT         = 0x30U,
	CONV_FLT_FLT         = 0x31U,
	CONV_INT_FLT         = 0x32U,
	CONV_FLT_INT         = 0x33U,
	CONV_PTR_BASE        = 0x34U,
	CONV_PTR_VOID        = 0x35U,
	CONV_PTR_BOTTOM      = 0x36U,
	CONV_PTR_NULL        = 0x37U,
	CONV_PTR_MEM_BASE    = 0x38U,
	CONV_PTR_MEM_NULL    = 0x39U,
	CONV_BASE            = 0x3aU,
	CONV_BOOL            = 0x3bU,

	CONV_USER            = 0x20U,
	CONV_USER_MULTI      = 0x21U,

	CONV_ELLIPSIS        = 0x10U,

	CONV_NONE            = 0x00U,
	CONV_NULL            = 0x01U,
	CONV_PTR_PTR         = 0x02U,
	CONV_PTR_PTR_ALIGN   = 0x03U,
	CONV_INT_PTR         = 0x04U,
	CONV_PTR_INT         = 0x05U,
	CONV_PTR_MEM_PTR_MEM = 0x06U,
	CONV_PTR_MEM_FUNC    = 0x07U,
	CONV_FUNC            = 0x08U,
	CONV_ENUM            = 0x09U,

	CONV_REVERSE         = 0x80U
};

#define CONV_RANK(A)		((A) & 0x70)


/*
	REFERENCE CONVERSION CONTEXTS

	These values are used in convert_reference to indicate the various
	contexts for reference conversion.
*/

enum {
	REF_NORMAL,
	REF_FUNCTION,
	REF_ASSIGN,
	REF_ADDRESS
};


#endif
