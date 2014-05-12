# $Id$

# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

$UNIQUE  = 1 ;
$VERSION = "2.7" ;

$INFO = "X/Open CAE Networking Services Issue 4";

+IMPLEMENT "cae/xns4-socket", "sys/socket.h.ts" ;
+IMPLEMENT "cae/xns4-socket", "sys/stat.h.ts" ;
+IMPLEMENT "cae/xns4-socket", "sys/un.h.ts" ;

+IMPLEMENT "cae/xns4-socket", "fcntl.h.ts" ;

