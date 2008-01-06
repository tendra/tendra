/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
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


#ifndef HIGH_H
#define HIGH_H


/*
    TYPE REPRESENTING HIGH LEVEL SORTS

    A high level sort consists of a name and a dummy sort number, id.
    These are associated with a sort number, giving the result sort,
    and an array of sort numbers, giving the argument sorts.
*/

typedef struct {
	char *name;
	sortname id;
	sortname res;
	int no_args;
	sortname *args;
} high_sort;


/*
    STARTING POINT FOR HIGH LEVEL SORTS

    To distinguish them from the normal TDF sorts, high level sorts
    are assigned sort numbers starting at high_start.  The macro
    is_high is used to test whether a sort number corresponds to a
    high level sort, and high_no is used to transform a high level
    sort number into an offset in the table high_sorts.
*/

#define high_start	100
#define is_high(s)	((s) >= high_start)
#define high_no(n)	((int)((n) - high_start))


/*
    ROUTINES FOR MANIPULATING HIGH LEVEL SORTS
*/

extern high_sort *high_sorts;
extern int crt_high_sort;

high_sort *new_high_sort(high_sort *);
void set_high_sort(char *, tok_info *);
high_sort *unique_high_sort(high_sort *);
sortname find_high_sort(char *);
char *find_decode_string(high_sort *);
char *find_sortname(char *, sortname *);

#define sprint_high_sort(p, s)\
	(void)sprintf(p, "T%d#", high_no(s))


#endif /* HIGH_H */
