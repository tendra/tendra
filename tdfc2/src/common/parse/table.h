/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED


/*
    TYPE REPRESENTING A PORTABILITY TABLE ENTRY

    The portability table consists of an array of type PORT_ENTRY.  The
    PORT_* macros identify the various elements of this array.
*/

typedef struct {
	const char *name;
	int set;
	unsigned value;
	BASE_TYPE type;
} PORT_ENTRY;

enum {
	PORT_char_bits,
	PORT_short_bits,
	PORT_int_bits,
	PORT_long_bits,
	PORT_llong_bits,
	PORT_max_bits,
	PORT_signed_range,
	PORT_char_type,
	PORT_exact_range,
	PORT_ptr_int,
	PORT_ptr_fn,
	PORT_non_proto,
	PORT_multibyte,
	PORT_size
};


/*
    PORTABILITY TABLE DECLARATIONS

    The routines in this module are concerned with reading the portability
    table.
*/

extern void read_table(string);
extern PORT_ENTRY port_entry[];


#endif
