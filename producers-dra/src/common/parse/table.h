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

#define PORT_char_bits			0
#define PORT_short_bits			1
#define PORT_int_bits			2
#define PORT_long_bits			3
#define PORT_llong_bits			4
#define PORT_max_bits			5
#define PORT_signed_range		6
#define PORT_char_type			7
#define PORT_exact_range		8
#define PORT_ptr_int			9
#define PORT_ptr_fn			10
#define PORT_non_proto			11
#define PORT_multibyte			12
#define PORT_size			13


/*
    PORTABILITY TABLE DECLARATIONS

    The routines in this module are concerned with reading the portability
    table.
*/

extern void read_table(string);
extern PORT_ENTRY port_entry[];


#endif
