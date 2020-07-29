# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+SUBSET "in_t" := {
	+USE "cae/xsh5", "inttypes.h.ts";

	# XNS4 had these as in_addr_t and in_port_t which were defined to be
	# "an unsigned integral type of exactly 32 [and 16] bits". So really
	# there's no difference here.
	#
	# I'm specifying these as uint32_t and uint16_t instead, because that's
	# what XNS5 says, despite that it isn't mentioned in the change history.

	+TYPEDEF uint16_t in_port_t ;
	+TYPEDEF uint32_t in_addr_t ;
} ;

+IMPLEMENT "cae/xns4-ar", "netinet/in.h.ts", "in_generic";

