# $Id$

# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

$UNIQUE = 1;
$VERSION = "2.8";

+IMPLEMENT "cae/xns5-socket", "sys/socket.h.ts";
+IMPLEMENT "cae/xns5-socket", "sys/stat.h.ts";
+IMPLEMENT "cae/xns5-socket", "sys/uio.h.ts";
+IMPLEMENT "cae/xns5-socket", "sys/un.h.ts";

+IMPLEMENT "cae/xns5-socket", "fcntl.h.ts";

