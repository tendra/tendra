# $Id$

TARGETS=alt.o rule-check.o rule-firsts.o rule-mutate.o rule-simp.o \
	rule.o item.o rule-factor.o rule-lre.o rule-names.o rule-tail.o

REMOVE=rm -f

all: rules.a ${TARGETS}

clean:
	${REMOVE} rules.a ${TARGETS}

rules.a: ${TARGETS}
	ar r $@ ${TARGETS}
	ranlib $@

