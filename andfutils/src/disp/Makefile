# $Id$

# Standard directories and files

#TEMPL=templ

REMOVE=rm -f

TARGETS=basic.o binding.o capsule.o file.o main.o pretty.o sort.o tdf.o \
		tree.o unit.o utility.o

all: disp

disp: $(TARGETS)
	$(CC) -o disp $(TARGETS)

clean:
	$(REMOVE) disp $(TARGETS)

#MAKE_TDF=make_tdf
#SED=sed
#
#auto : ${SRC}/tdf.c ${SRC}/tdf.h
#
#${SRC}/tdf.c : ${SPEC} ${SRC1}/tdf.c ${SRC1}/tdf.sed
#	@${REMOVE} ${SRC}/tdf.c
#	${MAKE_TDF} ${SPEC} ${SRC1}/tdf.c | ${SED} -f ${SRC1}/tdf.sed > ${SRC}/tdf.c
#
#${SRC}/tdf.h : ${SPEC} ${SRC1}/tdf.h
#	@${REMOVE} ${SRC}/tdf.h
#	${MAKE_TDF} ${SPEC} ${SRC1}/tdf.h ${SRC}/tdf.h
#
#auto_clobber :
#	${REMOVE} ${SRC}/tdf.c ${SRC}/tdf.h

