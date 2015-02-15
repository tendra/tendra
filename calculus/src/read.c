/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>

#include <shared/error.h>
#include <shared/xalloc.h>
#include <shared/string.h>

#define calculus_IO_ROUTINES
#include "read.h"
#include "calculus.h"
#include "common.h"
#include "output.h"


/*
 * BITMASKS
 *
 * This array gives the masks for each bit value.
 */

unsigned long bitmask[CHAR_BIT];


/*
 * INITIALISE MASKS
 *
 * This routine initialises the array of bitmasks.  This is done
 * dynamically rather than statically in case CHAR_BIT is not 8.
 */

void
init_bitmask(void)
{
    int i;
    for (i = 0; i < CHAR_BIT; i++) {
	    bitmask[i] = MASK(i);
    }
    return;
}


/*
 * INPUT FILE
 *
 * These variables describe the input file.  There is a one byte input
 * buffer.
 */

static FILE *input_file;
static unsigned long input_buff = 0;
static int input_bits = 0;


/*
 * READ A NUMBER OF BITS
 *
 * This routine reads the next n bits from the input file.
 */

static unsigned long
read_bits(int n)
{
    int b = input_bits;
    unsigned long m = input_buff;
    unsigned long r = 0;
    while (n) {
	if (b == 0) {
	    /* Read next byte */
	    int c = getc(input_file);
	    if (c == EOF) {
		error(ERR_FATAL, "Premature end of file");
	    } else {
		m = (((unsigned long)c) & MASK(CHAR_BIT));
	    }
	    b = CHAR_BIT;
	}
	if (n >= b) {
	    r = (r << b) | m;
	    n -= b;
	    b = 0;
	} else {
	    int c = b - n;
	    r = (r << n) | (m >> c);
	    m &= bitmask[c];
	    n = 0;
	    b = c;
	}
    }
    input_bits = b;
    input_buff = m;
    return r;
}


/*
 * READ AN INTEGER
 *
 * This routine reads an integer from the input file.  This is encoded
 * as a sequence of octal digits with a marker bit for the end of the
 * number.
 */

static unsigned long
read_int(void)
{
    unsigned long r = 0, d;
    while (d = read_bits(4), (d & 0x08) == 0) {
	r = (r << 3) | d;
    }
    r = (r << 3) | (d & 0x07);
    return r;
}


/*
 * READ A STRING
 *
 * This routine reads an integer from the input file.  This is encoded
 * as the string length followed by the characters comprising the
 * string (8 bits each).
 */

static char *
read_string(void)
{
    unsigned long i, n = read_int();
    char *s = xmalloc((long)(n + 1));
    for (i = 0; i < n; i++) {
	s[i] = (char)read_bits(8);
    }
    s[n] = 0;
    return s;
}


/*
 * READ A FILENAME
 *
 * File names are just strings, however they are buffered to save
 * space.
 */

static char *
read_filename(void)
{
    char *s;
    static char *last_filename = "????";
    if (read_bits(1)) {
	s = last_filename;
    } else {
	s = read_string();
	last_filename = s;
    }
    return s;
}


/*
 * AUTOMATICALLY GENERATED DISK READING ROUTINES
 *
 * The main disk reading routines are automatically generated.  The
 * various macros are used to customise these routines.
 */

#define READ_BITS(N)		((unsigned)read_bits(N))
#define READ_ALIAS()		((unsigned)read_int())
#define READ_DIM()		((unsigned)read_int())
#define READ_int()		((int)read_int())
#define READ_number()		((number)read_int())
#define READ_string()		read_string()
#define READ_name_string()	read_filename()
#define READ_zero_int()		0

#include "read_def.h"


/*
 * READ AN INPUT FILE
 *
 * This routine reads an algebra from the input file nm.
 */

void
read_file(char *nm)
{
    char *s;

    /* Open file */
    crt_line_no = -1;
    crt_file_name = nm;
    input_file = fopen(nm, "rb");
    if (input_file == NULL) {
	error(ERR_SERIOUS, "Can't open input file, '%s'", nm);
	return;
    }
    init_bitmask();
    input_buff = 0;
    input_bits = 0;

    /* Confirm file header */
    s = READ_string();
    if (!!strcmp(s, calculus_NAME)) {
	error(ERR_FATAL, "Invalid file header identifier");
    }
    s = READ_string();
    if (!!strcmp(s, calculus_VERSION)) {
	error(ERR_FATAL, "Invalid file header version, '%s'", s);
    }

    /* Read the algebra */
    algebra->name = READ_string();
    algebra->major_no = READ_int();
    algebra->minor_no = READ_int();
    algebra->types = READ_list_ptr_type();
    clear_calculus_alias();

    /* Extract lists of primitives etc */
    LOOP_TYPE {
	TYPE_P t = CRT_TYPE;
	TYPE t0 = DEREF_type(t);
	switch (TAG_type(t0)) {
	    case type_primitive_tag: {
		PRIMITIVE_P p = DEREF_ptr(type_primitive_prim(t0));
		CONS_ptr(p, algebra->primitives, algebra->primitives);
		break;
	    }
	    case type_ident_tag: {
		IDENTITY_P p = DEREF_ptr(type_ident_id(t0));
		CONS_ptr(p, algebra->identities, algebra->identities);
		break;
	    }
	    case type_enumeration_tag: {
		ENUM_P p = DEREF_ptr(type_enumeration_en(t0));
		CONS_ptr(p, algebra->enumerations, algebra->enumerations);
		break;
	    }
	    case type_structure_tag: {
		STRUCTURE_P p = DEREF_ptr(type_structure_struc(t0));
		CONS_ptr(p, algebra->structures, algebra->structures);
		break;
	    }
	    case type_onion_tag: {
		UNION_P p = DEREF_ptr(type_onion_un(t0));
		CONS_ptr(p, algebra->unions, algebra->unions);
		break;
	    }
	}
    }

    /* Close file */
    fclose(input_file);
    return;
}
