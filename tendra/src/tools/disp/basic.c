/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#include "config.h"
#include "fmm.h"
#include "msgcat.h"
#include "tdf_types.h"
#include "tdf_stream.h"

#include "ascii.h"
#include "types.h"
#include "basic.h"
#include "capsule.h"
#include "file.h"
#include "sort.h"
#include "tdf.h"
#include "tree.h"


TDFINTL
tdf_int(void)
{
	return tdf_de_tdfintl(tdfr);
}


int tdf_int_digits;


/*
 *    READ A TDF INTEGER AS A STRING OF OCTAL DIGITS
 *
 *    A TDF integer is read into the buffer, with its length being
 *    recorded in tdf_int_digits.
 */

char *
tdf_int_str(void)
{
	ByteT *bp;

	bp = tdf_de_tdfintstr (tdfr);
	tdf_int_digits = tdfr->ts_tdfintlen;
	return (char*)bp;
}


/*
 * Format TDFSTRING
 *
 * Only strings consisting of 8-bit characters are actually dealt with
 * at the moment.  This routine decodes such a string,
 * translating any unprintable characters into escape sequences.
 */

char *
tdf_string_format(TDFSTRING *sp)
{
	TDFINTL i, n;
	int c;
	char *s, *p;

	n = 0;
	for (i = 0 ; i < sp->number ; i++) {
		c = sp->ints.chars[i];
		if (printable (c)) {
			if (c == SLASH || c == QUOTE)
				n++;
			n++;
		} else {
			n++;
			if (c == NEWLINE || c == TAB) {
				n++;
			} else {
				n += 3;
			}
		}
	}
	p = s = xmalloc (n + 1);
	for (i = 0 ; i < sp->number ; i++) {
		c = sp->ints.chars[i];
		if (printable (c)) {
			if (c == SLASH || c == QUOTE) *p++ = SLASH;
			*p++ = (char) c;
		} else {
			*p++ = SLASH;
			if (c == NEWLINE) {
				*p++ = 'n';
			} else if (c == TAB) {
				*p++ = 't';
			} else {
				*p++ = charact (c / 64);
				*p++ = charact ((c % 64) / 8);
				*p++ = charact (c % 8);
			}
		}
    }
    *p++ = 0;
    return (s);
}


/*
 *    DECODE A TDF STRING
 *
 *    A TDF string is read and returned.  This consists of the number
 *    of bits per character and the string length followed by the
 *    appropriate number of characters.  If the character size is not 8
 *    or the string is too long, it is deemed to be unprintable.
 */

char *
de_tdfstring(void)
{
	TDFSTRING ts;
	char *s;

	tdf_de_tdfstring(tdfr, &ts);
    if (ts.size == 8 && ts.number < 1000) {
		s = tdf_string_format (&ts);
    } else {
		s = "<UNPRINTABLE>";
    }
	if (ts.number)
		xfree (ts.ints.chars);
    return (s);
}


/*
 *    DECODE AN ALIGNED TDF STRING
 *
 *    This routine is identical to that above except that there are a
 *    couple of alignments.  This is used by de_extern_name.
 */

char *
de_tdfstring_align(void)
{
	TDFIDENT ti;
	char *s;

	tdf_de_tdfident(tdfr, &ti);
    if (ti.size == 8 && ti.number < 1000) {
		s = tdf_string_format (&ti);
    } else {
		s = "<UNPRINTABLE>";
    }
	if (ti.number)
		xfree (ti.ints.chars);
    return (s);
}


/*
 *    DECODE A UNIQUE IDENTIFIER
 *
 *    A unique consists of an array of strings.  The end of the array is marked
 *    by a null string.
 */

unique
de_unique()
{
    long i, n;
    unique u;
    n = tdf_int ();
    u = xmalloc_nof (string, n + 1);
    for (i = 0 ; i < n ; i++) u [i] = de_tdfstring_align ();
    u [n] = null;
    return (u);
}


/*
 *    DECODE AN EXTERNAL NAME
 *
 *    A number of bits are read and, according to their value, either a
 *    string or a unique is decoded.
 */

external
de_extern_name()
{
    external e;
    long n = de_external ();
	tdf_de_align (tdfr);
    switch (n) {
	case external_string_extern : {
	    e.simple = 1;
	    e.val.str = de_tdfstring_align ();
	    break;
	}
	case external_unique_extern : {
	    e.simple = 0;
	    e.val.uniq = de_unique ();
	    break;
	}
	case external_chain_extern : {
	    e.simple = 1;
	    e.val.str = de_tdfstring_align ();
	    IGNORE tdf_int ();
	    break;
	}
	default : {
	    e.simple = 1;
	    e.val.str = "<ERROR>";
	    break;
	}
    }
    return (e);
}


/*
 *    ARRAY OF FOREIGN SORTS
 *
 *    Foreign sorts are identified by means of strings.  This array gives all
 *    the foreign sorts known to the program.
 */

int do_foreign_sorts = 0;
long no_foreign_sorts = 0;
sortid *foreign_sorts = null;
static long fs_size = 0;


/*
 *    ADD A FOREIGN SORT
 *
 *    The foreign sort with name nm, foreign name fnm and decode letter c is
 *    added to the array of foreign sorts.
 */

void
add_foreign_sort(char *nm, char *fnm, int c)
{
    long n = no_foreign_sorts++;
    if (n >= fs_size) {
		fs_size += 20;
		foreign_sorts = xrealloc (foreign_sorts, sizeof(sortid) * fs_size);
    }
    foreign_sorts [n].name = nm;
    foreign_sorts [n].fname = fnm;
    foreign_sorts [n].decode = (char) c;
    foreign_sorts [n].res = (sortname) (extra_sorts + n);
    foreign_sorts [n].args = null;
    return;
}


/*
 *    DECODE A COMPLEX SORT AS A STRING
 */

static sortid
de_complex_sort(sortname sn)
{
    sortid cs;
    if (sn == sort_token) {
		long i, n;
		sortid cp, cr;
		char buff [1000];
		char *p = buff;

		/* Decode result of token sort */
		cr = de_sort_name (0);
		cs.res = cr.res;
		cr = de_complex_sort (cs.res);

		/* Start decoding token sort */
		cs.decode = 'T';
		check_list ();
		n = tdf_int ();
		cs.args = xmalloc_nof (char, n + 1);
		IGNORE strcpy (p, "TOKEN(");
		p = p + strlen (p);

		/* Decode arguments of token sort */
		for (i = 0 ; i < n ; i++) {
			cp = de_sort_name (0);
			cp = de_complex_sort (cp.res);
			if (i) *(p++) = ',';
			IGNORE strcpy (p, cp.name);
			p = p + strlen (p);
			cs.args [i] = cp.decode;
		}
		cs.args [n] = 0;
		IGNORE strcpy (p, ")->");
		p = p + strlen (p);

		/* Copy token sort */
		IGNORE strcpy (p, cr.name);
		p = xmalloc_nof (char, (int) strlen (buff) + 1);
		IGNORE strcpy (p, buff);
		cs.name = p;
    } else {
		/* Non-token sorts are simple */
		cs = find_sort (sn);
    }
    return (cs);
}


/*
 *    DECODE A SORTNAME
 *
 *    A value representing a sort is read and returned.  If expand is true
 *    then the parameters and result of any high-level sort are read but
 *    discarded.
 */

sortid
de_sort_name(int expand)
{
    sortname sn = (sortname) de_sortname ();
    if (sn == sort_token && expand) {
		return (de_complex_sort (sn));
    }
    if (sn == sort_foreign) {
		long i;
		string nm;
#if string_ext
		long n = tdf_de_tdfextint (tdfr, string_bits);
#else
		long n = tdf_de_bits(tdfr, string_bits);
#endif
		if (n != string_make_string) {
			MSG_unknown_foreign_sort ();
		}
		nm = de_tdfstring ();
		for (i = 0 ; i < no_foreign_sorts ; i++) {
			if (streq (nm, foreign_sorts [i].fname)) {
				return (foreign_sorts [i]);
			}
		}
		add_foreign_sort (nm, nm, 'F');
		return (foreign_sorts [i]);
    }
    return (find_sort (sn));
}
