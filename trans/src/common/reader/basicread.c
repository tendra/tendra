/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <stdlib.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <tdf/nat.h>

#include <reader/messages_r.h>
#include <reader/readglob.h>
#include <reader/basicread.h>
#include <reader/reader.h>

#include <construct/flpt.h>
#include <construct/installglob.h>

#include <utility/bits.h>

#include <main/flags.h>

#define bpby 8 /* bits per byte */

#define cppkt 256 /* bytes per packet */

#define bppkt (bpby*cppkt) /* the number of bits per packet (from the file). */

/* All variables are initialised, jmf */

static char *crt_ptr;	/* initialised by init_reader */
static char *end_ptr;	/* initialised by init_reader */

static int getcode_bitposn;
static union pun_u
  { unsigned int intc;
    struct pun_s {char a; char b; char c; char d;} chars;
  } crt_bits;		/* set before use */

int crt_lno;			/* initialised to -1 by init_reader */
int crt_charno;			/* only used if crt_lno != -1. No init needed */
char *crt_flnm;			/* only used if crt_lno != -1. No init needed */
static int pkt_index;		/* initialised by init_reader */
				/* the index of the current packet in the
				   file */
static int table_flag;		/* initialised by init_reader */
				/* 1 if reading from memory, 0 if reading
				   from file buffer */
static char *crt_line;		/* set before use */
				/* current line of encoding */
static int file_pkt;		/* initialised by init_reader */
				/* holds the index of the packet in the file */
static FILE *fpin;		/* initialised by init_reader */
				/* file pointer for input */
static int buff[64];		/* set by read_line */
				/* file buffer for input */
static place current_place;	/* set before use */
static place bytestream_pickup;	/* set before use */
				/* records the end of a bytestream */

/*
 * read_line reads the next line from the file and updates pkt_index,
 * file_pkt and crt_line.
 */
static void
read_line(int complain)
{

  size_t test = fread((char *)buff, sizeof(char), cppkt, fpin);

  if (test == (size_t)0 && complain) {
    error(ERR_INTERNAL, READ_PAST_END);
    exit(EXIT_FAILURE);
  }
  pkt_index++;
  file_pkt++;
  crt_line = (char *)buff;
}

static void check_magic_no(void);

/*
 * initreader opens the file called n and sets initial values into variables.
 */
void
initreader(FILE *f, const char *n)
{
  crt_lno = -1;

  fpin = f;

  pkt_index = -1;
  file_pkt = -1;
  table_flag = 0;
  getcode_bitposn = 0;
  read_line(1);

  crt_line = (char *)buff;
  crt_ptr = crt_line;
  end_ptr = crt_line + cppkt;
  check_magic_no();
}

int
getcode(int np)
{
  /* np = no of bits to read, np is >= 1 */
  {
    unsigned int m;
    int p;
    {
      int n = np;
      p = getcode_bitposn - n;
      m = lsmask[n];
    }
    if (p >= 0) {
      getcode_bitposn = p;
      return (int)((crt_bits.intc >> p) & m);
    }
  }

  {
    int p = getcode_bitposn;
    int q;
    unsigned int m;
    {
      int n = np - p;
      m = lsmask[n];
      q = (int)((crt_bits.intc & lsmask[p]) << n);
      p = 32 - n;
    }

    if (crt_ptr == end_ptr) {
      read_line(1);
      crt_ptr = crt_line;
    }

    crt_bits.chars.a = (* (unsigned int *) crt_ptr) >> 24 & 0xff;
    crt_bits.chars.b = (* (unsigned int *) crt_ptr) >> 16 & 0xff;
    crt_bits.chars.c = (* (unsigned int *) crt_ptr) >>  8 & 0xff;
    crt_bits.chars.d = (* (unsigned int *) crt_ptr) >>  0 & 0xff;

    crt_ptr += 4;
    getcode_bitposn = p;
    return q + (int)((crt_bits.intc >> p) & m);
  }
}

int
get_big_code(int n)
{
  int t;
  int res = 0;

  while (1) {
     t = getcode(n);
     if (t == 0) {
       res += (int) lsmask[n];
     } else {
       return res + t;
     }
  }
}

/*
 * keep_place records the present state of the getcode variables in a place.
 * It condenses the position variables into the bits_on field, measured
 * from the start of the recorded line.
 */
place
keep_place(void)
{
  place new_pl;
  new_pl.flag = table_flag;
  if (table_flag) {
    new_pl.pl_mem = crt_line;
  }
  new_pl.bits_on = (int)(crt_ptr - crt_line) * 8 - getcode_bitposn;
  if (!table_flag) {
    new_pl.bits_on += pkt_index * bppkt;
  }
  return new_pl;
}

/*
 * set_place resets the getcode variables from the place pl, which was
 * produced by keep_place or add_place. If necessary it reads more lines
 * from the file.
 */
void
set_place(place pl)
{
  int new_pi;
  table_flag = pl.flag;
  if (!table_flag) {
    new_pi = pl.bits_on / bppkt;
    crt_line = (char *)buff;
    crt_ptr = crt_line + (pl.bits_on / 32) * 4 - new_pi * cppkt;
    getcode_bitposn = 32 - pl.bits_on % 32;
    pkt_index = file_pkt;
    while (pkt_index < new_pi)
      read_line(0);
  } else {
    crt_line = pl.pl_mem;
    crt_ptr = crt_line + (pl.bits_on/32) * 4;
    getcode_bitposn = 32 - pl.bits_on % 32;
    current_place = pl;
  }
  if (getcode_bitposn == 32)
    getcode_bitposn = 0;

  if (getcode_bitposn > 0) {
    crt_bits.chars.a = (* (unsigned int *) crt_ptr) >> 24 & 0xff;
    crt_bits.chars.b = (* (unsigned int *) crt_ptr) >> 16 & 0xff;
    crt_bits.chars.c = (* (unsigned int *) crt_ptr) >>  8 & 0xff;
    crt_bits.chars.d = (* (unsigned int *) crt_ptr) >>  0 & 0xff;

    crt_ptr += 4;
  }
}

/*
 * add_place produces a place n bits on from the place pl.
 */
static place
add_place(place pl, int n)
{
  place new_pl;
  new_pl.bits_on = pl.bits_on + n;
  new_pl.pl_mem = pl.pl_mem;
  new_pl.flag = pl.flag;
  return new_pl;
}

/*
 * new_place memorises a line starting from the current position and going on
 * for bn bits. This may cause more lines to be read from the file.
 * The input stream is stepped on over these bits.
 */
static void
add_capsule_frees(void *vp)
{
  capsule_frees *cf;
  cf = (capsule_frees*)xmalloc(sizeof(capsule_frees));
  cf->next = capsule_freelist;
  cf->ptr = vp;
  capsule_freelist = cf;
}

static place
new_place(int bn)
{
  place pl;
  int   no_chars, i;
  char *mem;
  char  c;
  pl.flag = 1;

  if (!table_flag) {
    pl.bits_on = 32 - getcode_bitposn;
    if (getcode_bitposn == 0)
      pl.bits_on = 0;
    no_chars = ((pl.bits_on + bn + 31) / 32) * 4;
    if (getcode_bitposn > 0) {
      crt_ptr -= 4;
    }
    if (no_chars == 0) {
        mem = NULL;
    } else {
        mem = (char *)xcalloc(no_chars, sizeof(char));
    }
    for (i = 0; i < no_chars; ++i) {
      if (crt_ptr == end_ptr) {
        read_line(1);
        crt_ptr = crt_line;
      }
      c = *crt_ptr++;
      mem[i] = c;
    }
    pl.pl_mem = mem;
    add_capsule_frees((void*)mem);
    return pl;
  }

  pl.bits_on = (int)(crt_ptr - crt_line)* 8 - getcode_bitposn;
  pl.pl_mem = current_place.pl_mem;
  return pl;
}

/*
 * small_dtdfint reads one TDF integer using getcode. TDF integers are encoded
 * as a number of octal digits, most significant first. These octal digits are
 * encoded in 4-bit chunks with 8 added on to the last digit only.
 */
int
small_dtdfint(void)
{
  int digit;
  int total = 0;
  while (digit = getcode(4), digit < 8) {
    total = 8 * total + digit;
  }
  return 8 * total + (digit - 8);
}

/*
 * step the input stream on to the next byte boundary
 */
void
to_boundary(void)
{
  getcode_bitposn = getcode_bitposn - getcode_bitposn % 8;
}

/*
 * delivers a new place for the bitstream in the input stream and steps over it
 */
bitstream
d_bitstream(void)
{
  bitstream crt_bitstream;
  place here;
  int length;
  length = small_dtdfint();
  here = keep_place();
  crt_bitstream = new_place(length);
  set_place(add_place(here, length));
  return crt_bitstream;
}

bytestream
d_bytestream(void)
{
  return bytestream_pickup;
}

void
ignore_bytestream(void)
{
  /* steps over a bytestream */
  int length;
  place here;
  length = small_dtdfint();
  to_boundary();
  here = keep_place();
  set_place(add_place(here,(length * 8)));
}

/*
 * records in bytestream_pickup the end of a bytestream
 */
void
start_bytestream(void)
{
  int length;
  place here;
  length = small_dtdfint();
  to_boundary();
  here = keep_place();
  bytestream_pickup = add_place(here,(length * 8));
}

/*
 * resets the input stream from bytestream_pickup
 */
void
end_bytestream(void)
{
  set_place(bytestream_pickup);
}

tdfstring
d_tdfstring(void)
{
  /* reads a tdfstring from the input stream */
  int bits = small_dtdfint();
  int n = small_dtdfint();
  tdfstring tdb;
  int i;
  tdb.number = n;
  if (bits <= 8) {
    tdb.ints.chars = (char *)xcalloc(n + 1, sizeof(char));
    for (i = 0; i < n; ++i) {
      tdb.ints.chars[i] = (char)getcode(bits);
    }
    tdb.ints.chars[n] = 0;
    tdb.size = 8;
    return tdb;
  }
  if (bits <= 16) {
    tdb.ints.shorts = (short *)xcalloc(n + 1, sizeof(short));
    for (i = 0; i < n; ++i) {
      tdb.ints.shorts[i] = (short)getcode(bits);
    }
    tdb.ints.shorts[n] = 0;
    tdb.size = 16;
    return tdb;
  }
  if (bits <= 32) {
    tdb.ints.longs = (int *)xcalloc(n + 1, sizeof(int));
    for (i = 0; i < n; ++i) {
      tdb.ints.longs[i] = getcode(bits);
    }
    tdb.ints.longs[n] = 0;
    tdb.size = 32;
    return tdb;
  }
  if (bits <= 64) {
    tdb.ints.longs = (int *)xcalloc(n + 1, sizeof(int));
    for (i = 0; i < n; ++i) {
      flt64 x;
      flpt f;
      x.big = getcode(bits - 32);
      x.small = (unsigned int)getcode(32);
      f = f64_to_flt(x, 0);
      tdb.ints.longs[i] = f;
    }
    tdb.ints.longs[n] = 0;
    tdb.size = 64;
    return tdb;
  }
  error(ERR_INTERNAL, NO_BIG_STRINGS);
  return tdb;
}

tdfstring
d_tdfident(void)
{
  /* reads a tdfident from the input stream */
  int bits = small_dtdfint();
  int n = small_dtdfint();
  tdfstring tdb;
  int i;
  tdb.size = bits;
  tdb.number = n;
  if (bits <= 8) {
    tdb.ints.chars = (char *)xcalloc(n + 1, sizeof(char));
    to_boundary();
    for (i = 0; i < n; ++i) {
      tdb.ints.chars[i] = (char)getcode(bits);
    }
    tdb.ints.chars[n] = 0;
    to_boundary();
    return tdb;
  }
  if (bits <= 16) {
    tdb.ints.shorts = (short *)xcalloc(n + 1, sizeof(short));
    to_boundary();
    for (i = 0; i < n; ++i) {
      tdb.ints.shorts[i] = (short)getcode(bits);
    }
    tdb.ints.shorts[n] = 0;
    to_boundary();
    return tdb;
  }
  tdb.ints.longs = (int *)xcalloc(n + 1, sizeof(int));
  to_boundary();
  for (i = 0; i < n; ++i) {
    tdb.ints.longs[i] = getcode(bits);
  }
  tdb.ints.longs[n] = 0;
  to_boundary();
  return tdb;
}

tdfbool
d_tdfbool(void)
{
  /* reads a tdfbool from the input stream */
  return (tdfbool) getcode(1);
}

tdfint
d_tdfint(void)
{
  /* reads a tdfint from the input stream */
  nat n;
  unsigned int  digit;
  unsigned int total = 0;
  int small = 1;
  int goon = 1;
  flpt f;

  while (goon)
   {
     digit = (unsigned int)getcode(4);
     if (digit >= 8) {
	 goon = 0;
	 digit -= 8;
     }
     if (small) {
	 if (total > 0x1fffffff) {
	   small = 0;
	   f = floatrep_unsigned(total);
	   flpt_newdig(digit, &flptnos[f], 8);
	 } else {
	   total = (total << 3) + digit;
	 }
     } else {
       SET(f);
       flpt_newdig(digit, &flptnos[f], 8);
     }
   }
  nat_issmall(n) = (bool)small;
  if (small) {
    natint(n) = (int)total;
  } else {
    SET(f);
    nat_issmall(n) = 0;
    natbig(n) = f;
   }
  return n;
}

static void
check_magic_no(void)
{
	tdfint maj;
	tdfint min;

	if (getcode(8) != 'T' || getcode(8) != 'D' || getcode(8) != 'F' ||
	    getcode(8) != 'C') {
		error(ERR_FATAL, "This is not a TDF Version >= 4 capsule");
	}
	maj = d_tdfint();
	if (natint(maj) > MAJOR_VERSION) {
		error(ERR_FATAL, "TDF version of capsule is later than version dealt with by translator - update the translator");
	}
	else
	if (natint(maj) < MAJOR_VERSION) {
		error(ERR_FATAL, "TDF version dealt with by translator is later than version of capsule - recompile capsule with later compiler");
	}
	min = d_tdfint();
	if (natint(min) > MINOR_VERSION) {
	    error(ERR_WARN, "capsule may contain constructions not dealt with in this minor version of the translator");
	}
	to_boundary();
}
