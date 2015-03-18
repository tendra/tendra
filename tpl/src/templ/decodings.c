/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include "enc_nos.h"
#include "errors.h"
#include "readstreams.h"
#include "decodings.h"
@use all
@loop sort
@if sort.basic


/* DECODE %ST */

unsigned int
d_%SN(int n)
{
	unsigned int enc = get_basic_int(%SB, %SE);
	switch (enc) {
@loop sort.cons
	case e_%CN:
		consname("%CN", n);
@loop cons.param
@if param.sort.eq.bitstream
		    IGNORE d_bitstream("%CN", n + 1);
@else
		    IGNORE d_%PSN(n + 1);
@endif
@end
		    break;
@end
	default:
		fail("Bad %SN value, %u", enc);
		break;
	}
	return enc;
}
@else
@if sort.dummy


/* DECODE %ST */

unsigned int
d_%SN(int n)
{
@loop sort.cons
	    consname("%CN", n);
@loop cons.param
@if param.sort.eq.bitstream
	    IGNORE d_bitstream("%CN", n + 1);
@else
	    IGNORE d_%PSN(n + 1);
@endif
@end
	    return %CE;
@end
}
@else
@if sort.option


/* DECODE OPTIONAL %SST */

unsigned int
d_%SN(int n)
{
	unsigned int nl = get_basic_int(1, 0);
	if (nl) {
		IGNORE d_%SSN(n);
	}
	return nl;
}
@else
@if sort.slist


/* DECODE SIMPLE %SST LIST */

unsigned int
d_%SN(int n)
{
	unsigned int nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_%SSN(n + 1);
	}
	return nl;
}
@else
@if sort.list


/* DECODE %SST LIST */

unsigned int
d_%SN(int n)
{
	unsigned int nl;
	IGNORE get_basic_int(1, 0);
	nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_%SSN(n + 1);
	}
	return nl;
}
@endif
@endif
@endif
@endif
@endif
@end
