# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


$PROTECT = "__TDF_BSD_STRINGS" ;
$FILENAME = "string.h.ts" ;
+USE ( "c/c89" ), "string.h.ts" ;

+FUNC char *index ( char *, int ) ;
+FUNC char *rindex ( char *, int ) ;

+FUNC void bcopy ( char *, char *, int ) ;
+FUNC int bcmp ( char *, char *, int ) ;
+FUNC void bzero ( char *, int ) ;

%%%
/* These are the default definitions */
#ifdef __ANSI_STRINGS__
#define index( a, b )		strchr ( a, b )
#define rindex( a, b )		strrchr ( a, b )
#define bcopy( a, b, c )	( ( void ) memcpy ( a, b, c ) )
#define bcmp( a, b, c )		memcmp ( a, b, c )
#define bzero( a, b )		( ( void ) memset ( a, 0, b ) )
#endif
%%%
