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
#include "util.h"
#include "readstreams.h"
#include "enc_nos.h"
#include "errors.h"
#include "decodings.h"
#include "defs.h"


Instream *curin;

unsigned int
get_bit(void)
{
	unsigned int x;
	Chunk *ch = curin->ch;
	if (ch == (Chunk *)0) {
		return 2; /* end of stream */
	}
	while (ch->usage == 0 && ch->offst == 0) {
		Assert(curin->bit_pos == 0 && curin->byte_pos == 0);
		ch = curin->ch = ch->next;
		if (ch == (Chunk *)0) {
			return 2; /* end of stream */
		}
	}
	x = UI(ch->data[curin->byte_pos]) >> (7 - curin->bit_pos);
	if (++curin->bit_pos >= 8) {
		curin->bit_pos = 0;
		curin->byte_pos++;
	}
	if (curin->byte_pos == ch->usage && curin->bit_pos == ch->offst) {
		curin->ch = ch->next;
		curin->byte_pos = 0;
		curin->bit_pos = 0;
	}
	return(x & 1);
}


unsigned int
get_basic_int(int bts, Bool e)
{
	int i;
	unsigned int ans = get_bit();
	for (i = 1; i < bts; i++) {
		ans = (ans << 1) + get_bit();
	}
	if (e && ans==0) {
		return(get_basic_int(bts,e) + (UI(1) <<bts) - 1);
	}
	return ans;
}


unsigned int
get_tdfint(void)
{
	unsigned int x;
	unsigned int ans = 0;
	while ((x = get_basic_int(4, 0)) <= 7) {
		ans = (ans << 3) + x;
	}
	return ((ans << 3) + (x - 8));
}


static void
indent(int n)
{
	int i;
	for (i = 0; i < n; i++) {
		IGNORE printf(((i & 3) == 2) ? " |" : "  ");
	}
}


unsigned int
d_tdfint(int n)
{
	unsigned int x = get_tdfint();
	indent(n);
	IGNORE printf("%u\n", x);
	return x;
}


unsigned int
d_tdfstring(int n)
{
	unsigned int i;
	int k = (int)get_tdfint();
	unsigned int l = get_tdfint();
	char *s = CALLOC(char,l);
	for (i = 0; i < l; i++) {
		s[i] = (char)get_basic_int(k, 0);
	}
	indent(n);
	for (i = 0; i < l; i++) {
		IGNORE printf("%c", s[i]);
	}
	IGNORE printf("\n");
	return l;
}


void
consname(char *s, int n)
{
	indent(n);
	IGNORE printf("%s\n", s);
}


unsigned int
d_tdfbool(int n)
{
	unsigned int x = get_bit();
	indent(n);
	IGNORE printf((x) ? "true\n" : "false\n");
	return x;
}


unsigned int
d_bytestream(int n)
{
	unsigned int i = get_tdfint();
	while (curin->bit_pos != 0) {
		IGNORE get_bit();
	}
	for (; i != 0; i--) {
		IGNORE get_basic_int(8, 0);
	}
	indent(n);
	IGNORE printf("BYTESTREAM\n");
	return i;
}


unsigned int
d_tdfident(int n)
{
	return d_tdfstring(n);
}


static unsigned int
d_X(unsigned int rsort, int n)
{
	switch (rsort) {
	case e_access:
		IGNORE d_access(n);
		break;
	case e_alignment_sort:
		IGNORE d_alignment(n);
		break;
	case e_al_tag:
		IGNORE d_al_tag(n);
		break;
	case e_bitfield_variety:
		IGNORE d_bitfield_variety(n);
		break;
	case e_bool:
		IGNORE d_bool(n);
		break;
	case e_error_treatment:
		IGNORE d_error_treatment(n);
		break;
	case e_exp:
		IGNORE d_exp(n);
		break;
	case e_floating_variety:
		IGNORE d_floating_variety(n);
		break;
	case e_label:
		IGNORE d_label(n);
		break;
	case e_nat:
		IGNORE d_nat(n);
		break;
	case e_ntest:
		IGNORE d_ntest(n);
		break;
	case e_rounding_mode:
		IGNORE d_rounding_mode(n);
		break;
	case e_shape:
		IGNORE d_shape(n);
		break;
	case e_signed_nat:
		IGNORE d_signed_nat(n);
		break;
	case e_tag:
		IGNORE d_tag(n);
		break;
	case e_token:
		IGNORE d_token(n);
		break;
	case e_transfer_mode:
		IGNORE d_transfer_mode(n);
		break;
	case e_variety:
		IGNORE d_variety(n);
		break;
	default:
		fail("Not a 1st class SORT\n");
	}
	return rsort;
}


static unsigned int
d_token_definition(int n)
{
	unsigned int srt;
	unsigned int nl;
	IGNORE get_basic_int(1, 0);
	srt = d_sortname(n);
	IGNORE get_basic_int(1, 0);
	nl = get_tdfint();
	for (; nl != 0; nl--) {
		IGNORE d_tokformals(n);
	}
	IGNORE d_X(srt, n + 1);
	return srt;
}


unsigned int
d_bitstream(char *s, int n)
{
	unsigned int i = get_tdfint();
	int l = (int)strlen(s);
	indent(n);
	IGNORE printf("BITSTREAM/%s\n", s);
	if (strcmp(s + l - 5, "_cond") == 0) {
		int j = 0;
		for (; i != 0; i--) {
			if (((j++) & 31) == 0) {
				IGNORE printf("\n");
				indent(n);
			}
			IGNORE printf("%u", get_bit());
		}
		IGNORE printf("\n");
	} else if (strcmp(s + l - 12, "_apply_token") == 0) {
		int j = 0;
		for (; i != 0; i--) {
			if (((j++) & 31) == 0) {
				IGNORE printf("\n");
				indent(n);
			}
			IGNORE printf("%u", get_bit());
		}
		IGNORE printf("\n");
	} else if (strcmp(s, "make_tokdef") == 0) {
		IGNORE d_token_definition(n + 1);
	} else if (strcmp(s, "use_tokdef") == 0) {
		IGNORE d_token_definition(n + 1);
	} else {
		IGNORE fprintf(stderr, "Don't understand bitstream.\n");
		exit(EXIT_FAILURE);
	}
	return i;
}


void
read_cur(unsigned int(*f)(int))
{
	curin = MALLOC(Instream);
	curin->ch = current_TDF->first;
	curin->byte_pos = 0;
	curin->bit_pos = 0;
	IGNORE f(0);
}


void
print_res(void)
{
	unsigned int i;
	TDF *hold = current_TDF;
	SELECT_UNIT(tokdec_unit);
	for (i = 0; i < current_TDF->no; i++) {
		if (i == 0) {
			read_cur(d_tokdec);
		}
		else {
			IGNORE d_tokdec(0);
		}
	}
	SELECT_UNIT(tokdef_unit);
	for (i = 0; i < current_TDF->no; i++) {
		if (i == 0) {
			read_cur(d_tokdef);
		}
		else {
			IGNORE d_tokdef(0);
		}
	}
	SELECT_UNIT(tagdec_unit);
	for (i = 0; i < current_TDF->no; i++) {
		if (i == 0) {
			read_cur(d_tagdec);
		}
		else {
			IGNORE d_tagdec(0);
		}
	}
	SELECT_UNIT(tagdef_unit);
	for (i = 0; i < current_TDF->no; i++) {
		if (i == 0) {
			read_cur(d_tagdef);
		}
		else {
			IGNORE d_tagdef(0);
		}
	}
	current_TDF = hold;
}
