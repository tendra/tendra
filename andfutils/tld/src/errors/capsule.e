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
#include "capsule.h"
#include "istream.h"
#include "name-key.h"
]$;

header(c) $[
#include "solve-cycles.h"
]$;

fatal "cannot open unit set file" {
    "cannot open unit set file '${file name}': ${system error}",
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

fatal "unit set expected quote" ("istream" : "IStreamP") {
    "${file name}: ${line number}: expected double quote to begin unit set name",
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

fatal "unit set illegal escape" ("istream" : "IStreamP") {
    "${file name}: ${line number}: illegal escape sequence in unit set name",
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

fatal "unit set eof in name" ("istream" : "IStreamP") {
    "${file name}: ${line number}: end of file in unit set name",
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

fatal "unit set duplicate name" {
    "${file name}: unit set name '${unit set name}' occurs more than once",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }, {
	"unit set name" : "NStringP" $[
	    write_nstring (ostream, closure->unit_set_name);
	]$
    }
};

fatal "unit set no tld name" {
    "${file name}: linker information unit set name 'tld' does not occur",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }
};

error "capsule bad magic" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: bad magic number '${magic name}' should be '${proper magic name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"magic name" : "NStringP" $[
	    write_nstring (ostream, closure->magic_name);
	]$
    }, {
	"proper magic name" : "NStringP" $[
	    write_nstring (ostream, closure->proper_magic_name);
	]$
    }
};

error "capsule bad version" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: illegal major version number ${major version}",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"major version" : "unsigned" $[
	    write_unsigned (ostream, closure->major_version);
	]$
    }
};

error "capsule version mismatch" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: major version number mismatch (${major version} should be ${proper major version})",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"major version" : "unsigned" $[
	    write_unsigned (ostream, closure->major_version);
	]$
    }, {
	"proper major version" : "unsigned" $[
	    write_unsigned (ostream, closure->proper_major_version);
	]$
    }
};

error "duplicate unit set name" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: unit set '${unit set name}' occurs more than once",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"unit set name" : "NStringP" $[
	    write_nstring (ostream, closure->unit_set_name);
	]$
    }
};

error "out of order unit set name" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: unit set '${unit set name}' occurs in wrong order",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"unit set name" : "NStringP" $[
	    write_nstring (ostream, closure->unit_set_name);
	]$
    }
};

error "unknown unit set name" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: unit set '${unit set name}' is unknown",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"unit set name" : "NStringP" $[
	    write_nstring (ostream, closure->unit_set_name);
	]$
    }
};

error "duplicate shape name" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: shape '${shape name}' occurs more than once",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"shape name" : "NStringP" $[
	    write_nstring (ostream, closure->shape_name);
	]$
    }
};

error "shape and name count mismatch" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: external name count ${name count} does not equal shape count ${shape count}",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"shape count" : "unsigned" $[
	    write_unsigned (ostream, closure->shape_count);
	]$
    }, {
	"name count" : "unsigned" $[
	    write_unsigned (ostream, closure->name_count);
	]$
    }
};

error "name id out of range" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: external ${shape name} name '${name}' has out of range identifier ${identifier} (greater than ${identifier limit})",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"shape name" : "NStringP" $[
	    write_nstring (ostream, closure->shape_name);
	]$
    }, {
	"name" : "NameKeyP" $[
	    write_name_key (ostream, closure->name);
	]$
    }, {
	"identifier" : "unsigned" $[
	    write_unsigned (ostream, closure->identifier);
	]$
    }, {
	"identifier limit" : "unsigned" $[
	    write_unsigned (ostream, closure->identifier_limit);
	]$
    }
};

error "name id used multiple times" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: external ${shape name} name '${name}' is bound to previously used identifier ${identifier}",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"shape name" : "NStringP" $[
	    write_nstring (ostream, closure->shape_name);
	]$
    }, {
	"name" : "NameKeyP" $[
	    write_name_key (ostream, closure->name);
	]$
    }, {
	"identifier" : "unsigned" $[
	    write_unsigned (ostream, closure->identifier);
	]$
    }
};

error "too many tld units" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: capsule contains wrong number of units in linker information unit set (should be one)",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }
};

warning "tld2 unit set type obsolete" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: capsule contains 'tld2' unit set type which is no longer supported",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }
};

error "too many tld unit counts" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: capsule contains wrong number of counts in linker information unit (should be zero)",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }
};

error "too many tld unit mappings" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: capsule contains wrong number of mappings in linker information unit (should be zero)",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }
};

error "tld unit wrong size" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: linker information unit contents is the wrong size (final offset is ${offset} but should be ${correct offset})",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"correct offset" : "unsigned" $[
	    write_unsigned (ostream, closure->correct_offset);
	]$
    }, {
	"offset" : "unsigned" $[
	    write_unsigned (ostream, closure->offset);
	]$
    }
};

error "unknown tld unit type" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: linker information unit version number ${version number} is not supported in this implementation",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"version number" : "unsigned" $[
	    write_unsigned (ostream, closure->version_number);
	]$
    }
};

error "unit set count mismatch" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: unit count ${unit count} does not equal unit set count ${unit set count}",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"unit set count" : "unsigned" $[
	    write_unsigned (ostream, closure->unit_set_count);
	]$
    }, {
	"unit count" : "unsigned" $[
	    write_unsigned (ostream, closure->unit_count);
	]$
    }
};

warning "missing tld unit set" {
    "capsule '${file name}' has no linker information unit set",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }
};

error "extra tld unit set" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: capsule contains both a 'tld' and a 'tld2' unit set",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }
};

error "defined but not declared" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: external ${shape name} '${name}' is defined but not declared",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"shape name" : "NStringP" $[
	    write_nstring (ostream, closure->shape_name);
	]$
    }, {
	"name" : "NameKeyP" $[
	    write_name_key (ostream, closure->name);
	]$
    }
};

error "illegally multiply defined" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: external ${shape name} '${name}' has the multiply defined bit set illegally",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"shape name" : "NStringP" $[
	    write_nstring (ostream, closure->shape_name);
	]$
    }, {
	"name" : "NameKeyP" $[
	    write_name_key (ostream, closure->name);
	]$
    }
};

error "bad usage" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: external ${shape name} '${name}' has usage ${usage} which has no meaning in this implementation",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"shape name" : "NStringP" $[
	    write_nstring (ostream, closure->shape_name);
	]$
    }, {
	"name" : "NameKeyP" $[
	    write_name_key (ostream, closure->name);
	]$
    }, {
	"usage" : "unsigned" $[
	    write_unsigned (ostream, closure->usage);
	]$
    }
};

error "multiply defined" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: external ${shape name} '${name}' is defined more than once (previous definition in '${previous file name}')",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"shape name" : "NStringP" $[
	    write_nstring (ostream, closure->shape_name);
	]$
    }, {
	"name" : "NameKeyP" $[
	    write_name_key (ostream, closure->name);
	]$
    }, {
	"previous file name" : "CStringP" $[
	    write_cstring (ostream, closure->previous_file_name);
	]$
    }
};

error "unit count num mismatch" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: illegal count number ${count number} in ${unit set name} unit ${unit number} (should be 0 or ${shape number})",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"count number" : "unsigned" $[
	    write_unsigned (ostream, closure->count_number);
	]$
    }, {
	"shape number" : "unsigned" $[
	    write_unsigned (ostream, closure->shape_number);
	]$
    }, {
	"unit number" : "unsigned" $[
	    write_unsigned (ostream, closure->unit_number);
	]$
    }, {
	"unit set name" : "NStringP" $[
	    write_nstring (ostream, closure->unit_set_name);
	]$
    }
};

error "unit mapping num mismatch" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: illegal mapping number ${mapping number} in ${unit set name} unit ${unit number} (should be ${count number})",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"mapping number" : "unsigned" $[
	    write_unsigned (ostream, closure->mapping_number);
	]$
    }, {
	"count number" : "unsigned" $[
	    write_unsigned (ostream, closure->count_number);
	]$
    }, {
	"unit number" : "unsigned" $[
	    write_unsigned (ostream, closure->unit_number);
	]$
    }, {
	"unit set name" : "NStringP" $[
	    write_nstring (ostream, closure->unit_set_name);
	]$
    }
};

error "id out of range" ("capsule" : "CapsuleP") {
    "${file name}: byte ${byte number}: ${shape name} identifier ${identifier} is out of range in mapping table of ${unit set name} unit ${unit number} (should be less than ${identifier limit})",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = capsule_name (capsule);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = capsule_byte (capsule);
	]$
    }, {
	"identifier" : "unsigned" $[
	    write_unsigned (ostream, closure->identifier);
	]$
    }, {
	"identifier limit" : "unsigned" $[
	    write_unsigned (ostream, closure->identifier_limit);
	]$
    }, {
	"shape name" : "NStringP" $[
	    write_nstring (ostream, closure->shape_name);
	]$
    }, {
	"unit number" : "unsigned" $[
	    write_unsigned (ostream, closure->unit_number);
	]$
    }, {
	"unit set name" : "NStringP" $[
	    write_nstring (ostream, closure->unit_set_name);
	]$
    }
};
