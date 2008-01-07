# $TenDRA$
#
# This include is only for building the libraries.

TLD_FLAGS+=	-mc

TCC_OPTS+=      -yTENDRA_BASEDIR=${OBJ_PREFIX}

TCC_OPTS+=	-Fj \
		-Y${DEFAULT_BUILD} \
		-Ybuilding \
		-Y32bit

TCCFLAGS+=	-I${OBJ_PREFIX}/lib/machines/${SRC_MACHINES}/include \
		-I/usr/include

# Point to the tspec-generated directory from lib/${API} and lib/${API}/diag
API_GEN=	${OBJ_DIR:S/apis\/lib/apis/:C/\/diag$//}.api

.include "../../../../mk/base/tendra.var.mk"
