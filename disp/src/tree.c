/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>
#include <shared/xalloc.h>

#include "config.h"
#include "types.h"
#include "ascii.h"
#include "basic.h"
#include "file.h"
#include "pretty.h"
#include "tdf.h"
#include "tree.h"
#include "utility.h"


/*
 * INTERNAL MEMORY STORAGE AREA
 *
 * Some strings are output directly.  Others are built up gradually
 * in this buffer.  length gives the length of the current string.
 * page_length gives the size of the buffer.
 */
int length;
static int page_length;
static char *page = null;


/*
 * TOP LEVEL WORD AND CURRENT WORD POINTER
 *
 * The top of the TDF tree is given by word1.  The current position in
 * the tree is given by word_ptr.
 */
word word1 = { SIMPLE, 0, null, null, null };
word *word_ptr;


/*
 * SET UP INITIAL PAGE AND WORDS
 *
 * The page buffer is initialized and the current word pointer is set
 * to the top-level word.
 */
void
initialize_tree(void)
{
    if (page == null) {
	page = xmalloc_nof(char, 10000);
	page_length = 10000;
    }
    word_ptr = &word1;
    length = 0;
    return;
}


/*
 * START A NEW WORD
 *
 * A new word of layout type c is created.
 */
word *
new_word(int c)
{
#define BLOCK 100
    static word *wblock;
    static int block_count = BLOCK;

    word *new_ptr;
    if (printflag) {

	if (block_count == BLOCK) {
	    /* Allocate space if required */
	    wblock = xmalloc_nof(word, BLOCK);
	    block_count = 0;
	}

	/* set up fields of new word */
	new_ptr = wblock + (block_count++);
	if (word_ptr->type != SIMPLE && word_ptr->son == null) {
	    word_ptr->son = new_ptr;
	} else {
	    word_ptr->bro = new_ptr;
	}
	word_ptr = new_ptr;
	word_ptr->type = (char)c;
	if (length) {
	    word_ptr->text = page;
	    word_ptr->length = length;
	    page += (length + 1);
	    page_length -= (length + 1);
	    if (page_length < 100) {
		page = xmalloc_nof(char, 10000);
		page_length = 10000;
	    }
	    length = 0;
	} else {
	    word_ptr->text = "";
	    word_ptr->length = 0;
	}
	word_ptr->son = null;
	word_ptr->bro = null;
    }
    return word_ptr;
}


/*
 * OUTPUT A SINGLE CHARACTER INTO INTERNAL MEMORY
 *
 * The character c is appended to the internal memory buffer.
 */
void
out_char(int c)
{
    if (printflag) {
	page[length] = (char)c;
	length++;
	page[length] = 0;
    }
    return;
}


/*
 * OUTPUT A STRING INTO INTERNAL MEMORY
 *
 * The string str is appended to the internal memory buffer.
 */
void
out_string(char *str)
{
    if (printflag) {
	IGNORE strcpy(page + length, str);
	length += (int)strlen(str);
    }
    return;
}


/*
 * MAKE A STRING INTO A WORD
 *
 * This routine creates a simple word from the string str, appending it
 * to any text in the internal memory buffer.
 */
void
out(char *str)
{
    if (printflag) {
	if (length) {
	    out_string(str);
	    IGNORE new_word(SIMPLE);
	} else {
	    word *ptr = new_word(SIMPLE);
	    ptr->text = str;
	    ptr->length = (int)strlen(str);
	}
    }
    return;
}


/*
 * MAKE AN INTEGER INTO A WORD
 *
 * This routine creates a simple word from an integer.
 */
void
out_int(long n)
{
    if (printflag) {
	/* Note that the input is cast to an unsigned int */
	unsigned long m = (unsigned long)n, dig, power = 1;

	/* Get the highest power of 10 dividing m */
	while ((m / power) >= 10)power *= 10;

	/* Now output digits of m */
	while (power != 0) {
	    dig = (m / power);
	    m -= dig * power;
	    power = (power / 10);
	    out_char(charact(dig));
	}
	/* Make this into a simple word */
	IGNORE new_word(SIMPLE);
    }
    return;
}


/*
 * MAKE A STRING OF OCTAL DIGITS INTO A WORD
 *
 * This routine creates a simple word from a string of octal digits
 * and a sign.  If the string of octal digits corresponds to a
 * number of at most 32 bits, out_int is used, otherwise the string
 * is output directly.
 */
void
out_signed(char *n, int sn)
{
    if (printflag) {
	/* Calculate the number of binary digits in n */
	int a = digit(*n), d;
	if (a & 4) {
	    d = 3 * tdf_int_digits;
	} else {
	    if (a & 2) {
		d = 3 * tdf_int_digits - 1;
	    } else {
		d = 3 * tdf_int_digits - 2;
	    }
	}
	if (d <= BYTESIZE *(int)sizeof(long)) {
	    /* If n will fit into a long work out its value */
	    char *s;
	    long t = 0;
	    for (s = n; *s; s++)t = 8 * t + digit(*s);
	    if (sn && t)out_char('-');
	    out_int(t);
	} else {
	    /* Otherwise output n as a string of octal digits */
	    word *w;
	    out_string("octal");
	    w = new_word(HORIZ_BRACKETS);
	    out_string(sn ? "-0" : "0");
	    out(n);
	    end_word(w);
	}
    }
    return;
}


/*
 * MAKE A UNIQUE INTO A WORD
 *
 * The unique u is output.
 */
void
out_unique(unique u)
{
    word *w;
    out_string("unique");
    w = new_word(HORIZ_BRACKETS);
    while (*u) {
	out(*u);
	u++;
    }
    end_word(w);
    return;
}


/*
 * UTILITY FORMATTING ROUTINE
 *
 * This routine is used to format a function and its arguments.  The
 * function name is given by func, the layout type by c, and the
 * arguments by the decode string args.
 */
void
format(int c, char *func, char *args)
{
    if (printflag) {
	word *ptr;
	if (length) {
	    out_string(func);
	    ptr = new_word(c);
	} else {
	    ptr = new_word(c);
	    ptr->text = func;
	    ptr->length = (int)strlen(func);
	}
	decode(args);
	end_word(ptr);
    } else {
	decode(args);
    }
    return;
}
