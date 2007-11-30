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


#include "config.h"
#include "types.h"
#include "fetch.h"
#include "file.h"
#include "read_types.h"
#include "analyser.h"
#include "utility.h"


/*
    LIST OF DIRECTORIES

    This is the list of all directories to be searched for included files.
*/

static directory *search_path = null;


/*
    INPUT FILE

    The current input file, together with its name.
*/

FILE *input;
char *input_file = null;


/*
    OPEN INPUT FILE

    This routine opens the file nm.  If search is true it will search
    for it along search_path.
*/

void
open_input(char *nm, int search)
{
    input = fopen(nm,(text_input ? "r" : "rb"));
    if (search && input == null) {
	directory *d = search_path;
	while (input == null && d) {
	    char buff[1000];
	    IGNORE sprintf(buff, "%s/%s", d->dirname, nm);
	    input = fopen(buff,(text_input ? "r" : "rb"));
	    d = d->next;
	}
    }
    if (input == null)fatal_error("Can't open input file, %s", nm);
    input_file = nm;
    bits_in_buff = 0;
    bytes_read = 0;
    crt_line_no = 1;
    line_no = 1;
    looked_ahead = 0;
    return;
}


/*
    ADD A DIRECTORY TO THE SEARCH PATH

    The directory nm is added to search_path.
*/

void
add_directory(char *nm)
{
    directory *d = alloc_nof(directory, 1);
    d->dirname = nm;
    d->next = null;
    if (search_path == null) {
	search_path = d;
    } else {
	directory *p = search_path;
	while (p->next)p = p->next;
	p->next = d;
    }
    return;
}


/*
    OUTPUT FILE

    The current output file.
*/

FILE *output /* = stdout */ ;


/*
    OPEN OUTPUT FILE

    The output file nm is opened.
*/

void
open_output(char *nm)
{
    static char *opened = null;
    if (opened) {
	warning("Multiple output files given, using %s", opened);
	return;
    }
    output = fopen(nm,(text_output ? "w" : "wb"));
    if (output == null)fatal_error("Can't open output file, %s", nm);
    opened = nm;
    return;
}
