#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#


header $[
#include "istream.h"
]$;

fatal "errf null char in builtin" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: null character in builtin",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "errf null character in name" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: null character in name",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "errf null character in string" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: null character in string",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "errf newline in builtin" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: unescaped newline in builtin",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "errf newline in name" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: unescaped newline in name",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "errf newline in string" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: unescaped newline in string",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "errf eof in builtin" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: unexpected end of file in builtin",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "errf eof in name" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: unexpected end of file in name",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "errf eof in string" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: unexpected end of file in string",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "errf illegal esc in builtin" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: illegal escape sequence in builtin",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "errf illegal escape in name" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: illegal escape sequence in name",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "errf illegal escape in string" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: illegal escape sequence in string",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "errf unknown builtin" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: unknown builtin '%${builtin name}%'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }, {
	"builtin name" : "CStringP" $[
	    write_cstring (ostream, closure->builtin_name);
	]$
    }
};

fatal "errf illegal character" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: illegal character '${character}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }, {
	"character" : "char" $[
	    write_escaped_char (ostream, closure->character);
	]$
    }
};

fatal "errf expected string" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: expected string",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "errf expected section" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: expected name or section header (one of '%strings%', '%prefix%' or '%errors%')",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }
};

fatal "errf unknown string" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: unknown string name '${string name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }, {
	"string name" : "CStringP" $[
	    write_cstring (ostream, closure->string_name);
	]$
    }
};

fatal "errf unknown error" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: unknown error name '${error name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }, {
	"error name" : "CStringP" $[
	    write_cstring (ostream, closure->error_name);
	]$
    }
};

fatal "errf illegal message" ( "istream" : "IStreamP" ) {
    "${file name}: ${line number}: malformed or unterminated tag in message '${message}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = istream_name (istream);
	]$
    }, {
	"line number" : "unsigned" $[
	    write_unsigned (ostream, closure->line_number);
	]$ $[
	    closure.line_number = istream_line (istream);
	]$
    }, {
	"message" : "CStringP" $[
	    write_cstring (ostream, closure->message);
	]$
    }
};

fatal "errf cannot open" {
    "cannot open error file '${file name}': ${system error}",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"system error" : "int" $[
	    write_system_error (ostream);
	]$ $[
	]$
    }
};
