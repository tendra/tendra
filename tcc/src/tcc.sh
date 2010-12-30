#!/bin/sh

exec -PREFIX_LIBEXEC-/tcc             \
	-yPREFIX=-PREFIX-                 \
	-yPREFIX_BIN=-PREFIX_BIN-         \
	-yPREFIX_LIB=-PREFIX_LIB-         \
	-yPREFIX_LIBEXEC=-PREFIX_LIBEXEC- \
	-yPREFIX_SHARE=-PREFIX_SHARE-     \
	-yPREFIX_INCLUDE=-PREFIX_INCLUDE- \
	-yPREFIX_MAN=-PREFIX_MAN-         \
	-yPREFIX_TSPEC=-PREFIX_TSPEC-     \
	-yPREFIX_STARTUP=-PREFIX_STARTUP- \
	-yPREFIX_ENV=-PREFIX_ENV-         \
	-yPREFIX_API=-PREFIX_API-         \
	-yPREFIX_LPI=-PREFIX_LPI-         \
	-yPREFIX_TMP=-PREFIX_TMP-         \
                                      \
	-yMD_EXECFORMAT=-EXECFORMAT-      \
	-yMD_BLDARCH=-BLDARCH-            \
	-yMD_BLDARCHBITS=-BLDARCHBITS-    \
	-yMD_OSFAM=-OSFAM-                \
	-yMD_OSVER=-OSVER-                \
                                      \
	--SED-PREFIX_ENV- --CFE -Ydefault ${@+"$@"}

