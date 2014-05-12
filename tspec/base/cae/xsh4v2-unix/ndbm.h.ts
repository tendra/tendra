# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "c/c89", "stddef.h.ts", "size_t" ;

# Corrigenda U013 1170/02: define mode_t
+IMPLEMENT "posix/posix", "sys/types.h.ts", "mode_t" ;

+FIELD ( struct ) datum {
	void *dptr ;
	size_t dsize ;
} ;

+TYPE ( struct ) DBM ;

+CONST int DBM_INSERT, DBM_REPLACE ;

+FUNC DBM *dbm_open ( const char *, int, mode_t ) ;
+FUNC void dbm_close ( DBM * ) ;
+FUNC datum dbm_fetch ( DBM *, datum ) ;
+FUNC int dbm_store ( DBM *, datum, datum, int ) ;
+FUNC int dbm_delete ( DBM *, datum ) ;
+FUNC datum dbm_firstkey ( DBM * ) ;
+FUNC datum dbm_nextkey ( DBM * ) ;
+FUNC int dbm_error ( DBM * ) ;
+FUNC int dbm_clearerr ( DBM * ) ;
