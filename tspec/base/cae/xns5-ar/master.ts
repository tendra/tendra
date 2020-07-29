# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

# This is Chapter 11, "IP Address Resolution Headers"
# of the CAE Networking Services (XNS) Issue 5,
# Specified by The Open Group. Document number C523,
# ISBN: 1-85912-165-9 published Feburary 1997.

$UNIQUE  = 1;
$VERSION = "2.8";

$INFO = "X/Open CAE XNS Issue 5 - IP Address Resolution Headers";

+IMPLEMENT "cae/xns5-ar", "dummy.ts";

+IMPLEMENT "cae/xns5-ar", "arpa/inet.h.ts";
+IMPLEMENT "cae/xns5-ar", "netdb.h.ts";
+IMPLEMENT "cae/xns5-ar", "netinet/in.h.ts";
+IMPLEMENT "cae/xns5-ar", "unistd.h.ts";

