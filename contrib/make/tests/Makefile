# $TenDRA$

PATH=	${.CURDIR}
ENV=	/usr/bin/env
MAKE=	${.CURDIR}/../bmake

LOGFILE=${.CURDIR}/test.log
OUTPUT=	| tee -a ${LOGFILE}

TEST_TARGETS=test1 test2 test3

all: .SILENT
.for T in ${TEST_TARGETS}
	-if ${MAKE} ${T}; then \
		echo "${T}: SUCCESS " ${OUTPUT} ; \
	else \
		echo "${T}: FAIL " ${OUTPUT} ; \
	fi
.endfor

# These are the make test targets.
# Note we completely reset the environment with env -i on each invocation.

# PASS
test1:
	@${ENV} -i PATH=${PATH} TEST=testing ${MAKE} -e -r -f make1 | \
	diff - make1.out

# PASS
test2:
	@${ENV} -i PATH=${PATH} TEST=testing ${MAKE} -r -f make2 | \
	diff - make2.out

# FAIL
test3:
	@${ENV} -i PATH=${PATH} TEST=testing ${MAKE} -r -f make3 | \
	diff - make3.out
