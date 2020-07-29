/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stdio.h>

#include "defs.h"
#include "streams.h"
#include "enc_nos.h"
#include "errors.h"

#include <shared/xalloc.h>


TDF *current_TDF; /* all output will be written to this */

static Chunk *free_chunks = (Chunk *)0;


Chunk *
create_chunk(void)
{
	Chunk *ans;
	if (free_chunks != (Chunk *)0) {
		ans = free_chunks;
		free_chunks = free_chunks->next;
	} else {
		ans = xmalloc(sizeof *ans);
	}
	ans->next = (Chunk *)0;
	ans->usage = 0;
	ans->offst = 0;
	ans->aligned = 0;
	ans->data[0] = 0;
	return ans;
}


static void
free_chunk(Chunk *x)
{
	x->next = free_chunks;
	free_chunks = x;
}




/*
 * In append_TDF, free_it says whether the Chunks of tdf can be freed and
 * reused. For example, append_tdf( &new_stream, 1) will append new_stream
 * onto current_TDF, allowing the Chunks of new_stream to be resused (see
 * create_chunk and free_chunk above). The variable new_stream can then only
 * be used as another output stream using NEW_STREAM (streams.h). If one
 * wished to copy new_stream onto the end of the current stream leaving its
 * Chunks intact, use free_it = 0.
 */

void
append_TDF(TDF *tdf, Bool free_it)
    /* appends the stream tdf onto current stream;
       if free_it, chunks in tdf will be reused */
{
	Chunk *t_ch = current_TDF->last;
	Chunk *a_ch = tdf->first;

	if (t_ch->usage < DATA_SIZE - 1 - a_ch->usage) {
		/* room to put it in current chunk */
		int i;
		int offst = a_ch->offst;
		Chunk *nextch = a_ch->next;
		for (i = 0; i < a_ch->usage; i++) {
			out_basic_int(UL(a_ch->data[i]), UI(8));
		}
		if (a_ch->offst != 0) {
			out_basic_int(UL(a_ch->data[i]) >> (8-offst),
				      UI(offst));
		}
		if (free_it) {
			free_chunk(a_ch);
		}
		a_ch = nextch;
	}
	if (a_ch != (Chunk *)0) {
		if (free_it) {	/* use existing chunks */
			t_ch->next = a_ch;
			current_TDF->last = tdf->last;
		} else {  /* copy chunks */
			while (a_ch != (Chunk *)0) {
				Chunk *nch = create_chunk();
				t_ch->next = nch;
				t_ch = current_TDF->last = nch;
				*nch = *a_ch;
				a_ch = a_ch->next;
			}
		}
	}
	SET_RSORT(tdf->sort);
	if (free_it) {
		tdf->first = tdf->last = (Chunk *)0; /* Don't use it again! */
	}
	return;
}

/*
 * Similar to append_TDF, but more specialised, is append_bytestream below,
 * which makes tdf into a BYTESTREAM and appends it onto current_TDF. This
 * would only be used for encoding a UNIT.
 */

void
append_bytestream(TDF *tdf, Bool free_it)
{
	unsigned long len = bits_in_TDF(tdf);
	unsigned long lenb = (len + 7) >> 3;
	out_tdfint32(lenb);
	byte_align();
	append_TDF(tdf, free_it);
	if ((lenb << 3) != len) {
		out_basic_int(UL(0), UI((lenb << 3) - len));
	}
	SET_RSORT(s_bytestream);
}


unsigned long
bits_in_TDF(TDF * tdf)
{
	Chunk *t_ch = tdf->first;
	unsigned long ans = 0;
	while (t_ch != (Chunk *)0) {
		Assert(!t_ch->aligned);
		ans+= (UL(t_ch->usage) << 3) + UL(t_ch->offst);
		t_ch = t_ch->next;
	}
	return ans;
}


/*
  num is output to current_TDF in bts bits. This is the most primitive
  output routine and all the others use it, eg out_tdfint32 does the
  appropriate number of out_basic_int(oct_digit, 4).
*/
void
out_basic_int(unsigned long num, unsigned int bts)
    /* outputs num onto current stream in bts bits */
{
	Chunk *t_ch = current_TDF->last;
	unsigned disp = t_ch->offst;
	unsigned space = 8 - disp;
	for (;bts >= space; bts -= space, space = 8, disp = 0) {
		(t_ch->data)[t_ch->usage] |= UC((num >> (bts-space)) & 255);
		t_ch->usage += 1;
		t_ch->offst = 0;
		if (t_ch->usage == DATA_SIZE) {
			Chunk *nch = create_chunk();
			t_ch->next = nch;
			current_TDF->last = nch;
			t_ch = nch;
		} else {
			(t_ch->data)[t_ch->usage] = 0;
		}
	}
	if (bts) {
		unsigned garbage=8-bts;
		(t_ch->data)[t_ch->usage] |=
		    UC(((num << garbage) & 255) >> disp);
		t_ch->offst+=UC(bts);
	}
}


/* outputs num as extentable encoding in bts bits (see spec 7.3.3) */
void
out_extendable_int(unsigned long num, unsigned int bts)
{
	if (num < (UL(1) << bts)) {
		out_basic_int(num,bts);
	} else {
		out_basic_int(UL(0), bts);
		out_extendable_int(num- (UL(1) << bts) + 1, bts);
	}
}


void
out_tdfint32(unsigned long n)
    /* output 32 bit int as tdfint */
{
	int sh;
	Bool sig = 0;
	for (sh = 30; sh > 0; sh -= 3) {
		unsigned long i = (n >> sh) & 7;
		if (sig || i != 0) {
			out_basic_int(i, UI(4));
			sig = 1;
		}
	}
	out_basic_int((n & 7) + 8, 4);
	SET_RSORT(s_tdfint);
}


void
out_tdfbool(Bool b)
{
	out_basic_int(UL(b), UI(1));
	SET_RSORT(s_tdfbool);
}


/* outputs s as a TDFSTRING with k elements of size k bits. */

void
out_tdfstring_bytes(char *s, unsigned int k, unsigned int n)
{
	unsigned int i;
	out_tdfint32(UL(k));
	out_tdfint32(UL(n));
	for (i = 0; i < n; i++) {
		out_basic_int(UL(s[i]), k);
	}
	SET_RSORT(s_tdfstring);
}


void
byte_align(void)
{
	Chunk *ch = current_TDF->last;
	if (ch->aligned != 0) {
		if (ch->offst != 0) {
			out_basic_int(UL(0), UI(8-ch->offst));
		}
		Assert(ch->offst == 0);
	} else {
		Chunk *nch = create_chunk();
		nch->aligned = 1;
		ch->next = nch;
		current_TDF->last = nch;
	}
}

/* outputs s as a TDFIDENT, putting in the appropriate alignments necessary. */
void
out_tdfident_bytes(char *s)
{
	unsigned long i;
	unsigned long n = (unsigned long)strlen(s);
	byte_align();
	out_tdfint32(UL(8));
	out_tdfint32(n);
	byte_align();
	for (i = 0; i < n; i++) {
		out_basic_int(UL(s[i]), UI(8));
	}
	SET_RSORT(s_tdfident);
}


