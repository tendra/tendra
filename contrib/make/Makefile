#	$OpenPackages: Makefile,v 1.21 2001/07/16 14:01:14 espie Exp $
#	$OpenBSD: Makefile,v 1.10 1999/10/05 21:50:34 espie Exp $
# $TenDRA$

OPSYS!=uname -s

LIBOBJS= ohash_create_entry.o ohash_delete.o ohash_do.o ohash_entries.o \
    ohash_enum.o ohash_init.o ohash_interval.o \
    ohash_lookup_interval.o ohash_lookup_memory.o \
    ohash_qlookup.o ohash_qlookupi.o

# ohash wedge for non-OpenBSD
.if ${OPSYS} != "OpenBSD"
.PATH:  ${.CURDIR}/ohash

LIBOHASH=	libohash.a
libohash.a: ${LIBOBJS}
	rm -f $@
	ar cq $@ `lorder ${LIBOBJS}|tsort`
	ranlib $@

CFLAGS+=-I${.CURDIR}/ohash
LDADD=-L${.OBJDIR} -lohash
.endif
CLEANFILES+=${LIBOBJS} libohash.a

# FreeBSD, Darwin, and GNU systems do not have high resolution dates yet
.if ${OPSYS} != "FreeBSD" && ${OPSYS} != "Darwin" \
	&& ${OPSYS} != "GNU" && ${OPSYS} != "Linux"
CFLAGS+=-DUSE_TIMESPEC
.endif

CFLAGS+=-DHAS_EXTENDED_GETCWD
CFLAGS+=-DHAS_BOOL_H
CFLAGS+=-DHAS_PATHS_H
CFLAGS+=-DHAVE_REGEX_H
CFLAGS+=-DHAVE_SYS_UTSNAME_H

PROG=	make
BINDIR?=	/usr/bin
CFLAGS+= -I${.OBJDIR} -I${.CURDIR} ${CDIAGFLAGS}

CDIAGFLAGS=-Wall -W -Wno-char-subscripts -Wstrict-prototypes -pedantic -Wmissing-prototypes
CFLAGS+=-I${.CURDIR}/ohash

#CFLAGS+=-DCLEANUP #-DDEBUG_SRC
#CFLAGS+=-DSTATS_HASH
#CFLAGS+= -DSTATS_VAR_LOOKUP #-DSTATS_GN_CREATION -DSTATS_BUF
#CFLAGS+=-DHAS_STATS

.if (${MACHINE_ARCH} == "m88k")
CFLAGS+=-O0
.endif

SRCS=	arch.c buf.c cmd_exec.c compat.c cond.c dir.c error.c for.c \
	init.c job.c lowparse.c main.c make.c memory.c parse.c \
	parsevar.c str.c stats.c suff.c targ.c timestamp.c \
	var.c varmodifiers.c varname.c
SRCS+=	lstAddNew.c lstAppend.c lstConcat.c lstConcatDestroy.c \
	lstDeQueue.c lstDestroy.c lstDupl.c lstFindFrom.c lstForEachFrom.c \
	lstInsert.c lstMember.c lstRemove.c lstReplace.c lstSucc.c

# Systems with a working stdint.h
.if ${OPSYS} == "Darwin"
CFLAGS+=-DHAVE_STDINT_H
.endif
# GNU systems do not have fgetln()
.if ${OPSYS} == "GNU" || ${OPSYS} == "Linux"
CFLAGS+=-DNEED_FGETLN
SRCS+= util.c
.endif
# NetBSD needs <inttypes.h>
.if ${OPSYS} == "NetBSD"
CFLAGS+=-DNEED_INTTYPES_H
.endif

.PATH:	${.CURDIR}/lst.lib

beforedepend: varhashconsts.h

varhashconsts.h: generate
	${.OBJDIR}/generate 1 >${.TARGET}

generate: generate.o stats.o memory.o ${LIBOHASH}
	${CC} -o ${.TARGET} ${CFLAGS} ${.ALLSRC} ${LDADD}

check: regress.o str.o error.o buf.o ${LIBOHASH}
	${CC} -o ${.TARGET} ${CFLAGS} ${.ALLSRC} ${LDADD}

make: ${LIBOHASH}

regress: check
	${.OBJDIR}/check

CLEANFILES+=generate varhashconsts.h generate.o

# kludge for people who forget to make depend
var.o: varhashconsts.h

#.if ${OPSYS} == "Darwin"
#NO_PSD=		true
#.endif
#
#.if make(install) && !defined(NO_PSD)
#SUBDIR+= PSD.doc
#.endif


.PHONY:	regress

.include <bsd.prog.mk>
