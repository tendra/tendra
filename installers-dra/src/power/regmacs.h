/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef REGMACS_H
#define REGMACS_H


/* fixed point regs */
#define R_0	0
#define R_SP	1
#define R_TOC	2
#define R_3	3
#define R_4	4
#define R_5	5
#define R_6	6
#define R_7	7
#define R_8	8
#define R_9	9
#define R_10	10
#define R_11	11
#define R_12	12
#define R_13	13
#define R_14	14
#define R_15	15
#define R_16	16
#define R_17	17
#define R_18	18
#define R_19	19
#define R_20	20
#define R_21	21
#define R_22	22
#define R_23	23
#define R_24	24
#define R_25	25
#define R_26	26
#define R_27	27
#define R_28	28
#define R_29	29
#define R_30	30
#define R_31	31



/* float point regs */
#define FR_0	0
#define FR_1	1
#define FR_2	2
#define FR_3	3
#define FR_4	4
#define FR_5	5
#define FR_6	6
#define FR_7	7
#define FR_8	8
#define FR_9	9
#define FR_10	10
#define FR_11	11
#define FR_12	12
#define FR_13	13
#define FR_14	14
#define FR_15	15
#define FR_16	16
#define FR_17	17
#define FR_18	18
#define FR_19	19
#define FR_20	20
#define FR_21	21
#define FR_22	22
#define FR_23	23
#define FR_24	24
#define FR_25	25
#define FR_26	26
#define FR_27	27
#define FR_28	28
#define FR_29	29
#define FR_30	30
#define FR_31	31

/* frame pointer */
#define R_FP    R_31
/* top of frame pointer */
#define R_TP    R_30

/* temp scratch register than can be used without allocation */
#define R_TMP0		R_0		/* reg 0, which is not totally general */

#define IS_R_TMP(r)	((r) == R_TMP0)


/* registers used for proc paramaters */
#define R_FIRST_PARAM		R_3
#define R_LAST_PARAM		R_10
#define FR_FIRST_PARAM		FR_1
#define FR_LAST_PARAM		FR_13

#define IS_PARAM_REG(r)    ((r) >= R_FIRST_PARAM && (r)<= R_LAST_PARAM)
#define IS_FLT_PARAM_REG(r)    ((r) >= FR_FIRST_PARAM && (r)<= FR_LAST_PARAM)

/* registers used for proc results */
#define R_RESULT		R_3
#define FR_RESULT		FR_1


/* range R_FIRST..R_LAST to loop over fixed regs */
#define R_FIRST			R_0
#define R_LAST			R_31

/* range FR_FIRST..FR_LAST to loop over float regs */
#define FR_FIRST		FR_0
#define FR_LAST			FR_31



/*
 * POWER floating point registers
 *
 * Two representations are used in sparctrans,
 * 0..15 to represent 16 reg-pairs for doubles at the higher (eg fregalloc)
 * levels,
 * and 0..31 at the lower (assembler) levels.
 * This is somewhat confusing, conversion is one way using a 'frg<<1' like
 * expression, often in the parameter position of a XXX_ins() function call.
 */

/* range R_FLT_FIRST..R_FLT_LAST to loop over float regs */
#define R_FLT_FIRST	0
#define R_FLT_LAST	31



/* Codes, which can be used where register number is usual */
#define R_NO_REG	100	/* code for no reg allocated */
#define R_USE_RES_REG	101	/* code to indicate result reg to be used */

#define FR_NO_REG	R_NO_REG /* code for no reg allocated */
#define FR_DEFER_RESULT	34	/* code to indicate FR_RESULT to be used */


#define IS_R_NO_REG(r)		((r) == R_NO_REG || (r) == R_0)		/* +++ R_0 historical */
#define IS_FR_NO_REG(r)		((r) == FR_NO_REG)


/*
 * Register masks, a bit per reg, as used in 'space' etc.
 * A set bit indicates reg is not available for allocation.
 */

#define	RMASK(r)	(((unsigned long)1)<<(r))


/*
 * Register sets.
 */


#define IS_FIXREG(r)	((r) >= R_FIRST && (r) <= R_LAST  )


/* s reg, for local variables, preserved over calls: R_13..R_31  */
#define IS_SREG(r)	((r) >= R_13 && (r) <= R_31)

/* t reg, for temp use, not preserved over calls: R_3..R_12 */
#define IS_TREG(r)	((r) >= R_3 && (r) <= R_12)	/* R_0-2 special */

#define MAXFIX_SREGS	(R_31-R_13+1)
/* maxfix_tregs calculated in translat.c to permit differing reg conventions */


/* output parameter t fixed regs: R_3..R_10 */
#define PARAM_TREGS \
			(RMASK(R_3)|RMASK(R_4)|RMASK(R_5)|RMASK(R_6)| \
			RMASK(R_7)|RMASK(R_8)|RMASK(R_9)|RMASK(R_10))


/* output parameter t float regs: FR_1..FR_13 */
#define PARAM_FLT_TREGS \
			(RMASK(FR_1)|RMASK(FR_2)|RMASK(FR_3)|RMASK(FR_4)| \
			RMASK(FR_5)|RMASK(FR_6)|RMASK(FR_7)|RMASK(FR_8)| \
			RMASK(FR_9)|RMASK(FR_10)|RMASK(FR_11)|RMASK(FR_12)| \
			RMASK(FR_13))

/*
 * t regs mask available in proc
 *
 *	PROC_TREGS	fixed point regs: R_3..R_12
 *	PROC_FLT_TREGS	float point regs: FR_0..FR_13
 *
 * Note this mask sets a bit for those registers that are NOT a t reg.
 */
#define PROC_TREGS	(~0 - (PARAM_TREGS|RMASK(R_11)|RMASK(R_12)))

#define PROC_FLT_TREGS	(~0 - (RMASK(FR_0)|PARAM_FLT_TREGS))


/* float s reg, for local variables, preserved over calls: FR_14..FR_31  */
#define IS_FLT_SREG(r)	((r) >= FR_14 && (r) <= FR_LAST)

/* float t reg, for temp use, not preserved over calls: FR_0..FR_13 */
#define IS_FLT_TREG(r)	((r) >= FR_0 && (r) <= FR_13)

#define MAXFLT_SREGS	(FR_LAST-FR_14+1)
#define MAXFLT_TREGS	(FR_13-FR_0+1)



/* map fixreg s number 1..n onto real s-reg R_13..R_31 */
#define SREG_TO_REALREG(n)	((n) - 1 + R_13)

/* map floatreg s number 1..n onto real s-reg FR_14..FR_31 */
#define SFREG_TO_REALFREG(n)	((n) - 1 + FR_14)



/* Needed to restore s-regs in tail_call */

#define R_TEMP_FP    R_11
#define R_TEMP_TP    R_12
#endif /* regmacs.h */
