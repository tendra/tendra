# $TenDRA$

# common directory
DATA+=	16bit 32bit Goption K-PIC K-ieee K-noieee K-prom \
	Versions Xa Xc Xp Xs Xt Xw aes alloca ansi bsd_extn \
	building c c++ common compact cose default default.extra \
	gcc iso longlong makelib motif_1_1 motif_1_2 motif_private \
	mse pl_tdf posix posix1 posix2 status strict_mot_1_2 \
	strict_posix strict_svid3 strict_xpg3 svid3 system \
	system+ target_tok tcc_diag tcc_pp tcc_prof tcc_time tdf_ext \
	tdp tnc tsimp unix95 wsl x5_aw x5_ext x5_lib x5_mit x5_mu \
	x5_private x5_proto x5_t xpg3 xpg4

DEPEND_SRC=	${DATA}

${DATA}:
	@echo cp $i ${.TARGET}

.include "${.CURDIR}/../../../../mk/base/tendra.prog.mk"
