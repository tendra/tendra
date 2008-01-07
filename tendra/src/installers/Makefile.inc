# $TenDRA$

# these are relative to installers/
SRCDIRS+=	common/construct common/diag common/linkinfo common/reader \
		common/templ

CFLAGS+= 	-I. -I${.CURDIR} ${SRCDIRS:S|^|-I${SRC_DIR}/src/installers/|} \
		-I${SRC_DIR}/src/include
.PATH :		${.CURDIR} ${SRCDIRS:S|^|${.CURDIR}/../../|}

USE_LIBTEN=	yes

CAT_EXTRA+=	${.CURDIR}/../../common/construct/messages.cat

# installers/common/construct
SRCS+=	aldefs.c case_opt.c check.c check_id.c complex_eq.c const.c exp.c \
	f64.c flags.c flpt.c flpt_fns.c foralls.c global_opt.c inl_norm.c \
	inline.c install_fns.c installglob.c label_ops.c me_fns.c misc_c.c \
	unroll.c

# installers/common/diag
SRCS+=	dg_aux.c dg_fns.c diag_fns.c diag_info.c mark_scope.c

# installers/common/linkinfo
SRCS+=	li_fns.c

# installers/common/reader
SRCS+=	basicread.c decoder.c read_fns.c read_sort.c readglob.c table_fns.c

DEPEND_SRC=	decoder.c ecodes.h externs.h inits.h \
		main_reads.h temp_fns.c

CLEANFILES=	${SRCS} ${DEPEND_SRC}
