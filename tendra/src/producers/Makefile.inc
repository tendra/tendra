# $TenDRA$

CFLAGS+= -I${.CURDIR} -I. ${SRCDIRS:S|^|-I${.CURDIR}/../|}
.PATH : ${.CURDIR} ${SRCDIRS:S|^|${.CURDIR}/../|}
SID_OPTS=	-l ansi-c -s numeric -s split -s no-lines

# common/construct
SRCS+=	access.c allocate.c assign.c basetype.c cast.c check.c \
	chktype.c class.c construct.c convert.c copy.c declare.c \
	derive.c destroy.c exception.c expression.c function.c \
	identifier.c initialise.c instance.c inttype.c label.c \
	member.c merge.c namespace.c operator.c overload.c printf.c \
	quality.c redeclare.c rewrite.c statement.c template.c tokdef.c \
	token.c typeid.c variable.c virtual.c

# common/
SRCS+=	main.c

# common/obj_c
SRCS+=	c_class.c

# common/output
SRCS+=	capsule.c compile.c decode.c diag.c diag2.c dump.c encode.c \
	exp.c init.c load.c mangle.c save.c shape.c stmt.c struct.c \
	throw.c tok.c unmangle.c	

# common/parse
SRCS+=	char.c constant.c file.c hash.c lex.c literal.c macro.c parse.c \
	pragma.c predict.c preproc.c psyntax1.c psyntax2.c psyntax3.c table.c

# common/utility
SRCS+=	buffer.c catalog.c debug.c error.c option.c print.c system.c \
	xalloc.c

DEPEND_SRC=	syntax.h psyntax.h c_class.h errors1.h errors2.h errors3.h \
		opts.h tdf1.h

syntax.h:: syntax.sid syntax.act
	${SID} ${SID_OPTS} ${.CURDIR}/syntax/syntax.sid ${.CURDIR}/syntax/syntax.act \
	${OBJ_DIR}/syntax@.c ${OBJ_DIR}/syntax.h

psyntax.h:: psyntax.sid psyntax.act
	${SID} ${SID_OPTS} ${.CURDIR}/../common/parse/psyntax.sid ${.CURDIR}/../common/parse/psyntax.act \
	${OBJ_DIR}/psyntax@.c ${OBJ_DIR}/psyntax.h

c_class.h:: c_class.alg
	${CALCULUS} -a -x ${.CURDIR}/../common/c_class.alg ${.OBJDIR}
	${CALCULUS} ${.CURDIR}/../common/c_class.alg -T${.CURDIR}/../common/obj_templ/bits.h ${.OBJDIR}/bits.h
	${CALCULUS} ${.CURDIR}/../common/c_class.alg -T${.CURDIR}/../common/obj_templ/err_ext.h ${.OBJDIR}/err_ext.h
	${CALCULUS} ${.CURDIR}/../common/c_class.alg -T${.CURDIR}/../common/obj_templ/loc_ext.h ${.OBJDIR}/loc_ext.h

errors1.h:: catalog.err
	${MAKE_ERR} ${.CURDIR}/../common/utility/catalog.err ${.OBJDIR}/errors1.h

errors2.h:: catalog.err extra.err
	${BIN_CAT} ${.CURDIR}/../common/utility/catalog.err ${.CURDIR}/../common/utility/extra.err |\
	${MAKE_ERR} > ${.OBJDIR}/errors2.h

errors3.h:: catalog.err extra.err
	${BIN_CAT} ${.CURDIR}/../common/utility/catalog.err ${.CURDIR}/../common/utility/extra.err |\
	${MAKE_ERR} -d > ${.OBJDIR}/errors3.h

opts.h:: catalog.err
	${MAKE_ERR} -u ${.CURDIR}/../common/utility/catalog.err ${.OBJDIR}/opts.h

tdf1.h:: tdf1.h-tdf
	${MAKE_TDF} ${.CURDIR}/../../lib/tdf/def_4_1.db ${.CURDIR}/../common/output/tdf1.h-tdf \
	${.OBJDIR}/tdf1.h

#calculus generated files
CLEANFILES+=	assert_def.h c_class.h ctype_ops.h err_ops.h etype_ops.h \
		exp_ops.h flt_ops.h ftype_ops.h graph_ops.h hashid_ops.h \
		id_ops.h inst_ops.h itype_ops.h member_ops.h nat_ops.h \
		nspace_ops.h off_ops.h str_ops.h tok_ops.h type_ops.h virt_ops.h

CLEANFILES+=	c_class.h errors1.h errors2.h errors3.h opts.h tdf1.h

CLEANFILES+=	psyntax.h psyntax1.c psyntax2.c psyntax3.c syntax.h syntax1.c \
		syntax2.c syntax3.c syntax4.c syntax5.c syntax6.c syntax7.c
