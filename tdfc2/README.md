# DRA TDF Producers

tdfc2 contains the compiler front-ends, which translate C and C++
to the compiler intermediate form, TDF.
In TDF's terminology this process is known as "producing" TDF.

dependencies for the C++ LPI token building:

 - tnc(1)
 - tspec (specifically, the C++ API)
 - tld(1)
 - tcc(1) (specifically, able to call tnc(1), provide the -Yc++ environment, and include the C++ API)

## Structure

The producers subdirectory is divided into a common directory, containing
code shared by both the C and C++ producers, plus directories c and cpp,
containing the language specific components.  The differences between
the languages are driven from the parser, which is found in the syntax
subdirectory of c and cpp.  C merely uses a subset of the routines
available for the C++ producer, with a number of run-time or compile-time
flags to control the differences between the languages.

The common producer directory is divided, for convenience into a number
of subdirectories:

    construct   which contains the main routines for building up
                and checking the internal representation;

    obj_c       which contains macros describing the internal
                representation;

    obj_templ   which contains various template files used in
                automatic code generation;

    obj_tok     which contains TenDRA tokens describing the
                internal representation;

    output      which contains the routines of writing the
                internal representation to disk as TDF;

    parse       which contains routines for lexical analysis
                and preprocessing;

    utility     which contains routines for error reporting,
                memory allocation etc.

