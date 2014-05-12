# $Id$

# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

$UNIQUE  = 1 ;
$VERSION = "2.7" ;

$INFO = "X/Open CAE Networking Services Issue 4";

+IMPLEMENT "cae/xns4-ar", "arpa/inet.h.ts" ;

+IMPLEMENT "cae/xns4-ar", "netinet/in.h.ts" ;

+IMPLEMENT "cae/xns4-ar", "netdb.h.ts" ;
+IMPLEMENT "cae/xns4-ar", "unistd.h.ts" ;

