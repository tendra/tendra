BASE=/u/g/release/Source
SRC=${BASE}/src/lib/machines/minix/80x86/tokens
SRC2=${BASE}/src/lib/machines/common/tokens

TCC=tcc
PL=pl
TLD=tld
TNC=tnc

REMOVE=rm -f
ECHO=echo
SHELL=/bin/sh

LIB=target_tok.tl
LIB_FILES=dep_toks.j map_toks.j except_toks.t var_toks.t
SYS_FILES=c_toks.j dep_toks.j map_toks.j

all : ${LIB}
	@${ECHO} all done

basic : sys.j
	@${ECHO} all done

${LIB} : ${LIB_FILES}
	@${REMOVE} ${LIB}
	${TLD} -mc -o ${LIB} ${LIB_FILES}

c_toks.j : ${SRC2}/c_toks.pl
	${PL} ${SRC2}/c_toks.pl c_toks.j

dep_toks.j : ${SRC}/dep_toks.pl
	${PL} ${SRC}/dep_toks.pl dep_toks.j

except_toks.j : ${SRC}/except_toks.pl
	${PL} ${SRC}/except_toks.pl except_toks.j

except_toks.t : except_toks.j ${SRC2}/except_toks
	${TCC} -Y${SRC2}/except_toks -Ft -o except_toks.t except_toks.j

map_toks.j : ${SRC}/map_toks.pl
	${PL} ${SRC}/map_toks.pl map_toks.j

var_toks.j : ${SRC2}/var_toks.pl
	${PL} ${SRC2}/var_toks.pl var_toks.j

var_toks.t : var_toks.j ${SRC2}/var_toks
	${TCC} -Y${SRC2}/var_toks -Ft -o var_toks.t var_toks.j

sys_toks.j : ${SYS_FILES}
	${TLD} -o sys_toks.j ${SYS_FILES}

sys.j : sys_toks.j
	${TNC} -t -d -L'.~' sys_toks.j sys.j

clean :
	${REMOVE} core

clobber : clean
	${REMOVE} ${LIB}
	${REMOVE} ${LIB_FILES}
	${REMOVE} c_toks.j sys_toks.j sys.j
	${REMOVE} except_toks.j var_toks.j
