/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
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


#ifndef SUFFIX_H
#define SUFFIX_H


/*
 * SINGLE CHARACTER KEYS FOR FILE TYPES - Table 2
 *
 * Each file type has an associated identifying letter. In most cases this
 * corresponds to the file suffix. This table needs to be kept in step with
 * Table 1.
 */

#define C_SOURCE_KEY			'c'
#define PREPROC_C_KEY			'i'
#define CPP_SOURCE_KEY			'C'
#define PREPROC_CPP_KEY			'I'
#define INDEP_TDF_KEY			'j'
#define DEP_TDF_KEY			't'
#define AS_SOURCE_KEY			's'
#define BINARY_OBJ_KEY			'o'
#define BINARY_OBJ_AUX_KEY		'b'
#define PRETTY_TDF_KEY			'p'
#define PL_TDF_KEY			'P'
#define TDF_ARCHIVE_KEY			'A'
#define MIPS_G_FILE_KEY			'G'
#define MIPS_T_FILE_KEY			'T'
#define C_SPEC_KEY			'k'
#define CPP_SPEC_KEY			'K'
#define STARTUP_FILE_KEY		'h'
#define ALL_KEY				'a'
#define EXTRA_KEY			'+'


/*
 * OTHER FILE TYPE INFORMATION - Table 3
 *
 * Most of the file suffixes can be deduced from the table above. This table
 * gives a few other suffixes plus the default names for various output files.
 */

#define CPP_1_SUFFIX			"cc"
#define CPP_2_SUFFIX			"cpp"
#define PREPROC_CPP_1_SUFFIX		"ii"
#define PREPROC_CPP_2_SUFFIX		"ipp"
#define AS_2_SUFFIX			"asm"
#define CPP_SPEC_1_SUFFIX		"kk"
#define PL_TDF_SUFFIX			"tpl"
#define TDF_ARCHIVE_SUFFIX		"ta"
#define TDF_COMPLEX_NAME		"a.j"
#define TDF_ARCHIVE_NAME		"a.ta"
#define C_SPEC_COMPLEX_NAME		"a.k"
#define API_ANAL_NAME			"a.api"

#if FS_DOS
#define EXECUTABLE_NAME			"a.exe"
#define EXECUTABLE_SUFFIX		".exe"
#define CPP_SPEC_COMPLEX_NAME		"a.kk"
#else
#define EXECUTABLE_NAME			"a.out"
#define CPP_SPEC_COMPLEX_NAME		"a.K"
#endif

#define STARTUP_NAME			"tcc_startup.h"
#define ENDUP_NAME			"tcc_endup.h"
#define TOKDEF_NAME			"tcc_tokdef.p"
#define MADE_UP_NAME			"_tcc%04d"
#define TEMP_NAME			"_tcc"


/*
 * SINGLE CHARACTER KEYS FOR EXECUTABLES - Table 4
 *
 * Each executable has an associated identifying letter.
 */

#define PRODUCE_ID			'c'
#define PREPROC_ID			'p'
#define CPP_PRODUCE_ID			'x'
#define CPP_PREPROC_ID			'g'
#define TDF_LINK_ID			'L'
#define TRANSLATE_ID			't'
#define ASSEMBLE_ID			'a'
#define LINK_ID				'l'
#define ARCHIVER_ID			'J'
#define SPEC_LINK_ID			's'
#define CPP_SPEC_LINK_ID		'S'
#define PRETTY_ID			'd'
#define NOTATION_ID			'n'
#define PL_TDF_ID			'P'
#define ASSEMBLE_MIPS_ID		'A'
#define INSTALL_ID			'I'
#define CC_ID				'C'
#define DYNLINK_ID			'D'
#define DUMP_ANAL_ID			'e'
#define DUMP_LINK_ID			'u'


/*
 * OTHER MISCELLANEOUS INFORMATION
 *
 * This table contains miscellaneous configuration items.
 */

#define PROGNAME_TCC			"tcc"
#define PROGNAME_TCHK			"tchk"
#define TCCENV_VAR			"TCCENV"
#define TCCOPT_VAR			"TCCOPTS"
#define DIAG_ENV			"tcc_diag"
#define PREPROC_ENV			"tcc_pp"
#define PROF_ENV			"tcc_prof"
#define TIME_ENV			"tcc_time"
#define TNC_ENV				"tnc"


#endif /* SUFFIX_H */
