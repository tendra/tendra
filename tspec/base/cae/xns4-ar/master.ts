# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

$UNIQUE  = 1 ;
$VERSION = "2.7" ;

# This is Chapter 11, "IP Address Resolution Headers"
# of the CAE Networking Services (XNS) Issue 4,
# Specified by The Open Group. Document number C438,
# ISBN: 1-85912-049-0 published August 1994.

$INFO = "X/Open CAE XNS Issue 4 - IP Address Resolution Headers";

+IMPLEMENT "cae/xns4-ar", "arpa/inet.h.ts" ;

+IMPLEMENT "cae/xns4-ar", "netinet/in.h.ts" ;

+IMPLEMENT "cae/xns4-ar", "netdb.h.ts" ;
+IMPLEMENT "cae/xns4-ar", "unistd.h.ts" ;

