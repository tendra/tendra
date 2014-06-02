/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include <shared/xalloc.h>

#include "config.h"
#include "ascii.h"
#include "types.h"
#include "basic.h"
#include "capsule.h"
#include "file.h"
#include "sort.h"
#include "tdf.h"
#include "tree.h"
#include "utility.h"


/*
 * READ AN EXTENDED NUMBER FROM THE INPUT FILE
 *
 * This routine reads n bits.  If these are nonzero they give the result.
 * Otherwise the result is ( 2^n - 1 ) plus the next extended number.
 */
long
fetch_extn(int n)
{
    long r = 0, s;
    while (s = fetch(n), s == 0)r += ((1 << n) - 1);
    return r + s;
}


/*
 * READ A TDF INTEGER FROM THE INPUT FILE
 *
 * This routine reads a TDF integer from the input file, returning
 * the result as a long.  Any overflow is ignored.  A TDF integer
 * is encoded as a series of 4 bit chunks, the least significant
 * three of which represent an octal digit, and the most significant
 * of which is a flag which is set to mark the last digit.
 */
long
tdf_int(void)
{
    long dig;
    long num = 0;
    if (read_error) return 0;
    do {
	dig = fetch(4);
	num = 8 * num + (dig & 7);
    } while (!(dig & 8));
    return num;
}


/*
 * BUFFER FOR LARGE TDF INTEGERS
 *
 * Larger TDF integers are stored as strings of octal digits.  This
 * buffer is used to hold them temporarily.  tdf_int_digits gives
 * the number of octal digits read.
 */
int tdf_int_digits;
static char tdf_int_buff[1000];


/*
 * READ A TDF INTEGER AS A STRING OF OCTAL DIGITS

 * A TDF integer is read into the buffer tdf_int_buff, with its length being
 * recorded in tdf_int_digits.
 */
char *
tdf_int_str(void)
{
    long dig;
    int i = 0;
    int reported = 0;
    if (read_error) {
	/* allow for recovery */
	tdf_int_digits = 1;
	return "0";
    }
    do {
	dig = fetch(4);
	if (i < 1000) {
	    tdf_int_buff[i] = charact(dig & 7);
	    i++;
	} else {
	    if (!reported)input_error("Numeric overflow");
	    reported = 1;
	}
    } while (!(dig & 8));
    tdf_int_buff[i] = 0;
    tdf_int_digits = i;
    return tdf_int_buff;
}


/*
 * READ AN 8-BIT STRING
 *
 * Only strings consisting of 8-bit characters are actually dealt with
 * at the moment.  This routine decodes such a string of length n,
 * translating any unprintable characters into escape sequences.
 */
string
get_string(long n, long sz)
{
    long i;
    string s;
    char buff[5000];
    char *p = buff;
    for (i = 0; i < n; i++) {
	int c = (int)fetch((int)sz);
	if (printable(c)) {
	    if (c == SLASH || c == QUOTE)*(p++) = SLASH;
	    *(p++) = (char)c;
	} else {
	    *(p++) = SLASH;
	    if (c == NEWLINE) {
		*(p++) = 'n';
	    } else if (c == TAB) {
		*(p++) = 't';
	    } else {
		*(p++) = charact(c / 64);
		*(p++) = charact((c % 64) / 8);
		*(p++) = charact(c % 8);
	    }
	}
    }
    *(p++) = 0;
    n = (int)(p - buff);
    s = xmalloc_nof(char, n);
    IGNORE memcpy(s, buff,(size_t)n);
    return s;
}


/*
 * DECODE A TDF STRING
 *
 * A TDF string is read and returned.  This consists of the number
 * of bits per character and the string length followed by the
 * appropriate number of characters.  If the character size is not 8
 * or the string is too long, it is deemed to be unprintable.
 */
string
de_tdfstring(void)
{
    string s;
    long sz = tdf_int();
    long n = tdf_int();
    if (sz == 8 && n < 1000) {
	s = get_string(n, sz);
    } else {
	skip_bits((long)(n * sz));
	s = "<UNPRINTABLE>";
    }
    return s;
}


/*
 * DECODE AN ALIGNED TDF STRING
 *
 * This routine is identical to that above except that there are a
 * couple of alignments.  This is used by de_extern_name.
 */
string
de_tdfstring_align(void)
{
    string s;
    long sz = tdf_int();
    long n = tdf_int();
    byte_align();
    if (sz == 8 && n < 1000) {
	s = get_string(n, sz);
    } else {
	skip_bits((long)(n * sz));
	s = "<UNPRINTABLE>";
    }
    byte_align();
    return s;
}


/*
 * DECODE A UNIQUE IDENTIFIER
 *
 * A unique consists of an array of strings.  The end of the array is marked
 * by a null string.
 */
unique
de_unique(void)
{
    long i, n;
    unique u;
    n = tdf_int();
    u = xmalloc_nof(string, n + 1);
    for (i = 0; i < n; i++)u[i] = de_tdfstring_align();
    u[n] = null;
    return u;
}


/*
 * DECODE AN EXTERNAL NAME
 *
 * A number of bits are read and, according to their value, either a
 * string or a unique is decoded.
 */
external
de_extern_name(void)
{
    external e;
    long n = de_external();
    byte_align();
    switch (n) {
	case external_string_extern: {
	    e.simple = 1;
	    e.val.str = de_tdfstring_align();
	    break;
	}
	case external_unique_extern: {
	    e.simple = 0;
	    e.val.uniq = de_unique();
	    break;
	}
	case external_chain_extern: {
	    e.simple = 1;
	    e.val.str = de_tdfstring_align();
	    IGNORE tdf_int();
	    break;
	}
	default : {
	    e.simple = 1;
	    e.val.str = "<ERROR>";
	    break;
	}
    }
    return e;
}


/*
 * ARRAY OF FOREIGN SORTS
 *
 * Foreign sorts are identified by means of strings.  This array gives all
 * the foreign sorts known to the program.
 */
int do_foreign_sorts = 0;
long no_foreign_sorts = 0;
sortid *foreign_sorts = null;
static long fs_size = 0;


/*
 * ADD A FOREIGN SORT
 *
 * The foreign sort with name nm, foreign name fnm and decode letter c is
 * added to the array of foreign sorts.
 */
void
add_foreign_sort(char *nm, char *fnm, int c)
{
    long n = no_foreign_sorts++;
    if (n >= fs_size) {
	fs_size += 20;
	foreign_sorts = xrealloc_nof(foreign_sorts, sortid, fs_size);
    }
    foreign_sorts[n].name = nm;
    foreign_sorts[n].fname = fnm;
    foreign_sorts[n].decode = (char)c;
    foreign_sorts[n].res = (sortname)(extra_sorts + n);
    foreign_sorts[n].args = null;
    return;
}


/*
 * DECODE A COMPLEX SORT AS A STRING
 */
static
sortid de_complex_sort(sortname sn)
{
    sortid cs;
    if (sn == sort_token) {
	long i, n;
	sortid cp, cr;
	char buff[1000];
	char *p = buff;

	/* Decode result of token sort */
	cr = de_sort_name(0);
	cs.res = cr.res;
	cr = de_complex_sort(cs.res);

	/* Start decoding token sort */
	cs.decode = 'T';
	check_list();
	n = tdf_int();
	cs.args = xmalloc_nof(char, n + 1);
	IGNORE strcpy(p, "TOKEN(");
	p = p + strlen(p);

	/* Decode arguments of token sort */
	for (i = 0; i < n; i++) {
	    cp = de_sort_name(0);
	    cp = de_complex_sort(cp.res);
	    if (i)*(p++) = ',';
	    IGNORE strcpy(p, cp.name);
	    p = p + strlen(p);
	    cs.args[i] = cp.decode;
	}
	cs.args[n] = 0;
	IGNORE strcpy(p, ")->");
	p = p + strlen(p);

	/* Copy token sort */
	IGNORE strcpy(p, cr.name);
	p = xmalloc_nof(char,(int)strlen(buff) + 1);
	IGNORE strcpy(p, buff);
	cs.name = p;
    } else {
	/* Non-token sorts are simple */
	cs = find_sort(sn);
    }
    return cs;
}


/*
 * DECODE A SORTNAME
 *
 * A value representing a sort is read and returned.  If expand is true
 * then the parameters and result of any high-level sort are read but
 * discarded.
 */
sortid
de_sort_name(int expand)
{
    sortname sn = (sortname)de_sortname();
    if (sn == sort_token && expand) {
	return de_complex_sort(sn);
    }
    if (sn == sort_foreign) {
	long i;
	string nm;
#if string_ext
	long n = fetch_extn(string_bits);
#else
	long n = fetch(string_bits);
#endif
	if (n != string_make_string) {
	    input_error("Unknown foreign sort");
	}
	nm = de_tdfstring();
	for (i = 0; i < no_foreign_sorts; i++) {
	    if (streq(nm, foreign_sorts[i].fname)) {
		return foreign_sorts[i];
	    }
	}
	add_foreign_sort(nm, nm, 'F');
	return foreign_sorts[i];
    }
    return find_sort(sn);
}
