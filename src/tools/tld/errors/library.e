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
#include "library.h"
]$;

header(c) $[
#include "solve-cycles.h"
]$;

error "library bad magic" ("library" : "LibraryP") {
    "${file name}: byte ${byte number}: bad magic number '${magic name}' should be '${proper magic name}'",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = library_name (library);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = library_byte (library);
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

error "library bad version" ("library" : "LibraryP") {
    "${file name}: byte ${byte number}: illegal major version number ${major version}",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = library_name (library);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = library_byte (library);
	]$
    }, {
	"major version" : "unsigned" $[
	    write_unsigned (ostream, closure->major_version);
	]$
    }
};

error "library version mismatch" ("library" : "LibraryP") {
    "${file name}: byte ${byte number}: major version number mismatch (${major version} should be ${proper major version})",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = library_name (library);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = library_byte (library);
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

error "null in file name" ("library" : "LibraryP") {
    "${file name}: byte ${byte number}: capsule name '${cap name}' contains null character",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = library_name (library);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = library_byte (library);
	]$
    }, {
	"cap name" : "NStringP" $[
	    write_nstring (ostream, closure->cap_name);
	]$
    }
};

error "capsule not found" {
    "capsule '${cap name}' is not contained in library '${lib name}'",
    {
	"cap name" : "CStringP" $[
	    write_cstring (ostream, closure->cap_name);
	]$
    }, {
	"lib name" : "CStringP" $[
	    write_cstring (ostream, closure->lib_name);
	]$
    }
};

info "extracting capsule" {
    "extracted capsule '${cap name}' into '${file name}'",
    {
	"cap name" : "CStringP" $[
	    write_cstring (ostream, closure->cap_name);
	]$
    }, {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$
    }
};

error "lib unknown type" ("library" : "LibraryP") {
    "${file name}: byte ${byte number}: library version number ${version number} is not supported in this implementation",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = library_name (library);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = library_byte (library);
	]$
    }, {
	"version number" : "unsigned" $[
	    write_unsigned (ostream, closure->version_number);
	]$
    }
};

error "lib defined but not declared" ("library" : "LibraryP") {
    "${file name}: byte ${byte number}: external ${shape name} '${name}' is defined but not declared",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = library_name (library);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = library_byte (library);
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

error "lib illegally mult defined" ("library" : "LibraryP") {
    "${file name}: byte ${byte number}: external ${shape name} '${name}' has the multiply defined bit set illegally",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = library_name (library);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = library_byte (library);
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

error "lib bad usage" ("library" : "LibraryP") {
    "${file name}: byte ${byte number}: external ${shape name} '${name}' has usage ${usage} which has no meaning in this implementation",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = library_name (library);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = library_byte (library);
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

error "lib multiply defined" ("library" : "LibraryP") {
    "${file name}: byte ${byte number}: external ${shape name} '${name}' is defined more than once in libraries (previous definition in '${previous file name}')",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = library_name (library);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = library_byte (library);
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
	"previous file name" : "LibCapsuleP" $[
	    write_lib_capsule_full_name (ostream, closure->previous_file_name);
	]$
    }
};

error "capsule index too big" ("library" : "LibraryP") {
    "${file name}: byte ${byte number}: external ${shape name} '${name}' has capsule index ${capsule index} (should be less than ${num capsules})",
    {
	"file name" : "CStringP" $[
	    write_cstring (ostream, closure->file_name);
	]$ $[
	    closure.file_name = library_name (library);
	]$
    }, {
	"byte number" : "unsigned" $[
	    write_unsigned (ostream, closure->byte_number);
	]$ $[
	    closure.byte_number = library_byte (library);
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
	"capsule index" : "unsigned" $[
	    write_unsigned (ostream, closure->capsule_index);
	]$
    }, {
	"num capsules" : "unsigned" $[
	    write_unsigned (ostream, closure->num_capsules);
	]$
    }
};
