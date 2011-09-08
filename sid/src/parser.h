/*
 * Automatically generated from the files:
 *	parser.sid
 * and
 *	parser.act
 * by:
 *	/Users/kate/svn/tendra1/obj-regen/bin/sid
 */

/* BEGINNING OF HEADER */

#line 277 "parser.act"


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

	/*
	 * parser.h - SID parser.
	 *
	 * This file specifies the interface to the SID file parser that is produced
	 * from the file "parser.sid".
	 */

	#include "grammar.h"
	#include "lexer.h"

	LexerStreamT *  sid_current_stream;

#line 57 "parser.h"

/* BEGINNING OF FUNCTION DECLARATIONS */

extern void sid_parse_grammar(GrammarP);
/* BEGINNING OF TRAILER */

#line 2211 "parser.act"


#line 67 "parser.h"

/* END OF FILE */
