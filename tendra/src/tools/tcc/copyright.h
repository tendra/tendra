/*
    		 Crown Copyright (c) 1997, 1998

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
    COPYRIGHT NOTICE

    This array gives the copyright notice for the release.
*/

static char *copyright_message [] = {
    "\t\tCrown Copyright (c) 1997, 1998",
    "",
    "    This TenDRA(r) Computer Program is subject to Copyright",
    "    owned by the United Kingdom Secretary of State for Defence",
    "    acting through the Defence Evaluation and Research Agency",
    "    (DERA).  It is made available to Recipients with a",
    "    royalty-free licence for its use, reproduction, transfer",
    "    to other parties and amendment for any purpose not excluding",
    "    product development provided that any such use et cetera",
    "    shall be deemed to be acceptance of the following conditions:",
    "",
    "\t(1) Its Recipients shall ensure that this Notice is",
    "\treproduced upon any copies or amended versions of it;",
    "",
    "\t(2) Any amended version of it shall be clearly marked to",
    "\tshow both the nature of and the organisation responsible",
    "\tfor the relevant amendment or amendments;",
    "",
    "\t(3) Its onward transfer from a recipient to another",
    "\tparty shall be deemed to be that party's acceptance of",
    "\tthese conditions;",
    "",
    "\t(4) DERA gives no warranty or assurance as to its",
    "\tquality or suitability for any purpose and DERA accepts",
    "\tno liability whatsoever in relation to any use to which",
    "\tit may be put.",
    "",
    NULL
} ;


/*
    PRINT THE COPYRIGHT NOTICE

    This routine prints the copyright message to the standard error.
*/

static void print_copyright
    PROTO_Z ()
{
    char *s ;
    FILE *f = stderr ;
    char **p = copyright_message ;
    while ( s = *( p++ ), s != NULL ) {
	IGNORE fprintf ( f, "%s\n", s ) ;
    }
    return ;
}
