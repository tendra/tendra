/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


#include "config.h"
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
	return(enc);
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
	    return(%CE);
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
	return(nl);
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
	return(nl);
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
	return(nl);
}
@endif
@endif
@endif
@endif
@endif
@end
