# $Id$

# Copyright 2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_CALCULUS_MK_)
_TENDRA_CALCULUS_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(ALGEBRA_C) && !defined(ALGEBRA_TOK) && !defined(ALGEBRA_DISK) && !defined(ALGEBRA_PRINT)
.BEGIN:
	@${ECHO} 'At least one of $${ALGEBRA_C,TOK,DISK,PRINT} must be set'
	@${EXIT} 1;
.endif


CALCFLAGS+=	-a
CALCFLAGS+=	-x


# Output directories
CALC_OUT_C?=     obj_c
CALC_OUT_TOK?=   obj_tok
CALC_OUT_DISK?=  .
CALC_OUT_PRINT?= .
CALC_IN_TEMPL?=  obj_templ


# Generated implementation
.if !empty(CALCFLAGS:M-a)
CALC_GEN_C+=    ${CALC_OUT_C}/assert_def.h
.endif
CALC_GEN_C+=    ${CALC_OUT_C}/${ALGEBRA_C:R}.h
#CALC_GEN_C+=    ${CALC_OUT_C}/type_ops.h
#CALC_GEN_C+=    ${CALC_OUT_C}/cmd_ops.h

# Generated pragma token declarations
.if !empty(CALCFLAGS:M-a)
CALC_GEN_TOK+=   ${CALC_OUT_TOK}/assert_def.h
.endif
CALC_GEN_TOK+=   ${CALC_OUT_TOK}/${ALGEBRA_TOK:R}.h
#CALC_GEN_TOK+=   ${CALC_OUT_TOK}/type_ops.h
#CALC_GEN_TOK+=   ${CALC_OUT_TOK}/cmd_ops.h

# Generated disk I/O routined
CALC_GEN_DISK+=  ${CALC_OUT_DISK}/read_def.h
CALC_GEN_DISK+=  ${CALC_OUT_DISK}/write_def.h

# Generated pretty-printing routines
CALC_GEN_PRINT+= ${CALC_OUT_PRINT}/print_def.h


.if defined(ALGEBRA_C)
${CALC_GEN_C}: ${ALGEBRA_C} ${TEMPLATES:S,^,${CALC_IN_TEMPL}/,}
	@${ECHO} "==> Translating ${ALGEBRA_C:S,^,${WRKDIR}/,g} implementations"
	${CALCULUS} ${CALCFLAGS} ${ALGEBRA_C} ${CALC_OUT_C} \
		|| ( ${RMFILE} ${CALC_GEN_C}; ${EXIT} 1 )
. for templ in ${TEMPLATES}
	${CALCULUS} ${ALGEBRA_C} -T${CALC_IN_TEMPL}/${templ} ${CALC_OUT_C}/${templ}
. endfor
.endif

.if defined(ALGEBRA_TOK)
${CALC_GEN_TOK}: ${ALGEBRA_TOK} ${TEMPLATES:S,^,${CALC_IN_TEMPL}/,}
	@${ECHO} "==> Translating ${ALGEBRA_TOK:S,^,${WRKDIR}/,g} token definitions"
	${CALCULUS} ${CALCFLAGS} -t ${ALGEBRA_TOK} ${CALC_OUT_TOK} \
		|| ( ${RMFILE} ${CALC_GEN_TOK}; ${EXIT} 1 )
. for templ in ${TEMPLATES}
	${CALCULUS} -t ${ALGEBRA_TOK} -T${CALC_IN_TEMPL}/${templ} ${CALC_OUT_TOK}/${templ}
. endfor
.endif

.if defined(ALGEBRA_DISK)
${CALC_GEN_DISK}: ${ALGEBRA_DISK}
	@${ECHO} "==> Translating ${ALGEBRA_DISK:S,^,${WRKDIR}/,g} disk I/O"
	${CALCULUS} ${CALCFLAGS} -d ${ALGEBRA_DISK} ${CALC_OUT_DISK} \
		|| ( ${RMFILE} ${CALC_GEN_DISK}; ${EXIT} 1 )
.endif

.if defined(ALGEBRA_PRINT)
${CALC_GEN_PRINT}: ${ALGEBRA_PRINT}
	@${ECHO} "==> Translating ${ALGEBRA_PRINT:S,^,${WRKDIR}/,g} pretty printer"
	${CALCULUS} ${CALCFLAGS} -p ${ALGEBRA_PRINT} ${CALC_OUT_PRINT} \
		|| ( ${RMFILE} ${CALC_GEN_PRINT}; ${EXIT} 1 )
.endif




#
# User-facing targets
#

.if defined(ALGEBRA_C)
regen:: ${CALC_GEN_C:M*/${ALGEBRA_C:R}.h}
.endif
.if defined(ALGEBRA_TOK)
regen:: ${CALC_GEN_TOK:M*/${ALGEBRA_TOK:R}.h}
.endif
.if defined(ALGEBRA_DISK)
regen:: ${CALC_GEN_DISK:M*/read_def.h}
.endif
.if defined(ALGEBRA_PRINT)
regen:: ${CALC_GEN_PRINT:M*/print_def.h}
.endif


regen-clean::
.if defined(ALGEBRA_C)
	${RMFILE} ${CALC_OUT_C}/*.h
.endif
.if defined(ALGEBRA_TOK)
	${RMFILE} ${CALC_OUT_TOK}/*.h
.endif
.if defined(ALGEBRA_DISK)
	${RMFILE} ${CALC_OUT_DISK}/read_def.h ${CALC_OUT_DISK}/write_def.h
.endif
.if defined(ALGEBRA_PRINT)
	${RMFILE} ${CALC_OUT_PRINT}/print_def.h
.endif


install::



.endif
