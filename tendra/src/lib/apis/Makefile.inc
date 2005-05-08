# $Id$

building/${API}.api/sys.j: c_toks.j dep_toks.j map_toks.j
	@${ECHO} "# Building sys.j"
	${TLD} -o ${OBJ_DIR}/${APIS}/${.TARGET:H}/sys_toks.j c_toks.j dep_toks.j map_toks.j
	${TNC} -t -d -L'.~' ${OBJ_DIR}/${APIS}/${.TARGET:H}/sys_toks.j ${.TARGET}

.include "../Makefile.inc"

.PATH: ${BASE_DIR}/${TOKENS_COMMON} ${BASE_DIR}/${TOKENS_MACH}
