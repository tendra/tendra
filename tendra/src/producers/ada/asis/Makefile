# $TenDRA:  $
.SUFFIXES       : .adb .ads

ADA_LIB = libasis.a
ADA_SRC = ${.CURDIR}/asis-[^g]*.adb

ADA_DIR = ${.CURDIR:C/(.*)\/asis.*/\1/}
XML   = ${ADA_DIR}/xml
AFLEX = ${XML}/aflex
AYACC = ${XML}/ayacc
ASIS  = ${XML}/asis

CFLAGS+= -m
CFLAGS+= -I.
CFLAGS+= -I${ADA_DIR}/libgela
CFLAGS+= -I${ADA_DIR}/xasis

.PATH.ads	: ${.CURDIR} ${ADA_DIR}/libgela ${ADA_DIR}/xasis
.PATH.adb	: ${.CURDIR} ${ADA_DIR}/libgela ${ADA_DIR}/xasis

#  Lexer part

LEXER_TMP = lexer.adb lexer-dfa.adb lexer-io.adb lexer-dfa.ads \
            lexer.ads lexer-io.ads

LEXER_SRC = ${LEXER_TMP:S/lexer/asis-gela-lexer/g}

${LEXER_SRC}: ${XML}/tokens.xml    ${AFLEX}/lexic.l     \
              ${AFLEX}/to_l.sed    ${AFLEX}/ident.sed   \
              ${AFLEX}/delim.xsl   ${AFLEX}/delim.sed   \
              ${AFLEX}/keyword.xsl ${AFLEX}/keyword.sed \
              ${AFLEX}/deep.sed                         \

	$(BIN_XSLTPROC) -o delim.tmp ${AFLEX}/delim.xsl ${XML}/tokens.xml
	$(BIN_SED) -f ${AFLEX}/delim.sed delim.tmp > delim.l
	$(BIN_XSLTPROC) -o keyword.tmp ${AFLEX}/keyword.xsl ${XML}/tokens.xml
	$(BIN_SED) -f ${AFLEX}/keyword.sed keyword.tmp > keyword.l
	$(BIN_SED) -e '/^%%/,$$d' ${AFLEX}/lexic.l            > lexer.l
	$(BIN_ECHO) %%                                       >> lexer.l
	$(BIN_SED) -f ${AFLEX}/to_l.sed keyword.l delim.l    >> lexer.l
	$(BIN_SED) -f ${AFLEX}/ident.sed ${AFLEX}/lexic.l    >> lexer.l
	$(BIN_AFLEX) lexer.l
	$(BIN_SED) -f ${AFLEX}/deep.sed ${LEXER_TMP}          > lexer.all
	$(BIN_RM) ${LEXER_TMP}
	$(BIN_GNATCHOP) -w lexer.all

#  Parser part

PARSER_TMP = parser.ads parser.adb parser-goto_table.ads \
             parser-shift_reduce.ads parser-tokens.ads

PARSER_SRC = ${PARSER_TMP:S/parser/asis-gela-parser/g}

${PARSER_SRC}: ${XML}/fixed.xsl      ${XML}/syntax.xml                   \
               ${XML}/asis_hier.xml  ${XML}/tokens.xml   ${XML}/code.xml \
               ${AYACC}/deep.sed     ${AYACC}/asis-gela-parser.adt       \

	$(BIN_XSLTPROC) -o fixed.xml ${XML}/fixed.xsl ${XML}/syntax.xml
	../../../utilities/xml2ayacc/xml_to_y \
           ${XML}/asis_hier.xml ${XML}/tokens.xml fixed.xml ${XML}/code.xml \
           > parser.y
	$(BIN_CAT) ${AYACC}/asis-gela-parser.adt >> parser.y
	$(BIN_AYACC) parser.y
	$(BIN_SED) -f ${AYACC}/deep.sed ${PARSER_TMP} > parser.all
	$(BIN_RM) ${PARSER_TMP}
	$(BIN_GNATCHOP) -w parser.all

#  Asis part

ASIS_SRC = asis.adb asis.ads

${ASIS_SRC}: ${XML}/asis_hier.xml ${ASIS}/asis-gela-elements.xsl \
             ${ASIS}/asis.spec    ${ASIS}/asis-ads.xsl           \
             ${ASIS}/asis.body    ${ASIS}/asis-adb.xsl           \

	$(BIN_CP)       ${ASIS}/asis.spec                            asis.ads
	$(BIN_XSLTPROC) ${ASIS}/asis-ads.xsl ${XML}/asis_hier.xml >> asis.ads
	$(BIN_CP)       ${ASIS}/asis.body                            asis.adb
	$(BIN_XSLTPROC) ${ASIS}/asis-adb.xsl ${XML}/asis_hier.xml >> asis.adb
	$(BIN_XSLTPROC) -o elems.all ${ASIS}/asis-gela-elements.xsl \
           ${XML}/asis_hier.xml
	$(BIN_GNATCHOP) -w elems.all

ADA_LIB_DIR=		lib/${LIB_GNAT}/gela_asis
ADA_INCLUDE_DIR=	include/ada/gela_asis

INSTALL_TARGETS=gela-asis-install
INSTALL_SUB= 	${ADA_LIB_DIR} ${ADA_INCLUDE_DIR}

gela-asis-install: libasis.a *.ali
	$(BIN_CP) -f libasis.a *.ali   ${INSTALL_PREFIX}/${ADA_LIB_DIR}
	${BIN_CHMOD} 0444              ${INSTALL_PREFIX}/${ADA_LIB_DIR}/*.ali
	$(BIN_CP) *.ad[sb]             ${INSTALL_PREFIX}/${ADA_INCLUDE_DIR}
	$(BIN_CP) ${.CURDIR}/*.ad[sb]  ${INSTALL_PREFIX}/${ADA_INCLUDE_DIR}
	$(BIN_CP) ${ADA_DIR}/libgela/* ${INSTALL_PREFIX}/${ADA_INCLUDE_DIR}
	$(BIN_CP) ${ADA_DIR}/xasis/*   ${INSTALL_PREFIX}/${ADA_INCLUDE_DIR}

DEPEND_SRC = ${LEXER_SRC} ${PARSER_SRC} *.ads *.adb ${ASIS_SRC}

CLEANFILES=*

.include "${.CURDIR}/../../../../mk/base/tendra.prog.mk"
