# Machine Dependent Source

This directory contains the source for the machine dependent libraries
and support programs for the various supported platforms.  It is
organised into subdirectories:

	common/tokens
	<os>/<cpu>/include
	<os>/<cpu>/src
	<os>/<cpu>/startup
	<os>/<cpu>/tokens

for each operating system <os> and processor type <cpu>.  The common
directory contains those components which are used by all machines,
and the machine directories contain the machine dependent components.

The src directory, if present, contains the source for any machine
dependent system libraries or object files which are required to be
linked with the compiled object files.  Certain platforms also require
a program, dyninit, which patches together any dynamic initialisation
routines (i.e. those arising from the TDF initial_value construct).
The source for this program is also included in the src directory.

The tokens directory contains the source (as tpl or tnc source files) for
the basic TDF tokens which are used to configure the system for a particular
platform.  The simplest information, such as 'char is signed' or 'int
contains 32 bits', is contained in the files:

	<os>/<cpu>/tokens/map_toks.tpl
	<os>/<cpu>/tokens/dep_toks.tpl

The program:

	common/tokens/gen_tokens.c

can be used to help generate these files on a new platform.

The system interface with the C and C++ producers is slightly more complex;
for example, it says 'int is represented by the variety token ~signed_int'.
These tokens are defined in terms of the more primitive tokens in the
file:

	common/tokens/c_toks.tpl

This file is linked with the primitive token definitions from map_toks.tpl
and dep_toks.tpl and 'preprocessed' by expanding all the token definitions
and evaluating any constant expressions.  This gives a capsule sys.j which
defines the producer interface.  This capsule is linked into the C producer
TDF library, c.tl.

The directory also contains the source for the target_tok.tl TDF library.
This consists of the basic tokens from:

	<os>/<cpu>/tokens/map_toks.tpl
	<os>/<cpu>/tokens/dep_toks.tpl

as described above, plus other machine dependent tokens defined in:

	common/tokens/var_toks.tpl
	<os>/<cpu>/tokens/var_toks.tpl
	<os>/<cpu>/tokens/except_toks.tpl

which describe how the target machine handles variable parameter lists
and overflow exceptions.  These tokens require to be linked with the
POSIX API library, however to make the resultant library self-contained
the necessary POSIX tokens are linked into the library and hidden
using the TDF linker options given by the tcc environments:

	common/tokens/var_toks
	common/tokens/except_toks
