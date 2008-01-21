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

#ifndef OPTIONS_INCLUDED
#define OPTIONS_INCLUDED

#include <stdbool.h>
#include <stdio.h>


/*
 * A file to which output is written. The exact purpose of each file
 * is specific to the output language (passed by -l) being employed.
 */
typedef struct options_outputfile {
	const char *name;
	FILE *file;
} options_outputfile;

typedef struct cmd_line_options_tag {
	FILE* copyright_file;

	/*
	 * The selected output language. See main.c for the various
	 * possibilities here.
	 */
	const char *language;

	/*
	 * TODO These are language-specific options; they should be elsewhere
	 */
	bool generate_asserts;
	const char* lexi_prefix;

	/*
	 * An array of files to which output is written. The number (and
	 * purposes) of files is specific to each output language. This
	 * array must be large enough to hold the maximum number of files
	 * specified by outputs[] in main().
	 *
	 * Elements beyond that of the selected output language's number
	 * are undefined. The order of files is defined by each output language.
	 *
	 * Since this is known at compile-time and is relatively small,
	 * a linked list was considered cumbersome.
	 *
	 */
	options_outputfile outputfile[2];
} cmd_line_options ;

extern void cmd_line_options_init(cmd_line_options*);

#endif

