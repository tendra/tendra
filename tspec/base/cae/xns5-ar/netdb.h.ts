# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+USE "cae/xsh5", "inttypes.h.ts";

+TYPEDEF uint32_t ~ne_addr_t;

+IMPLEMENT "cae/xns5-ar", "netinet/in.h.ts", "in_t" (!?);
+IMPLEMENT "cae/xns4-ar", "netdb.h.ts", "ndb_generic";

