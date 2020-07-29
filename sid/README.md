# SID: Syntax Improving Device

SID is an LL(1) parser generator.
See <http://www.tendra.org/> for details.


## Building

Compiling SID depends on:

 * An ANSI C compiler (C89)
 * POSIX C library functions
 * POSIX userspace programs, including make(1)
 * perl
 * libexds

And to build the documentation and manpages:

 * xsltproc from xmlsoft.org
 * The docbook XSLT stylesheets for XHTML and troff manpages

It's worth having XML catalogues set up to use docbook-xslt stylesheets,
to save it from fetching everything across the internet.

At runtime, SID has no dependancies other than libc and POSIX.


## Installation

The "install" target honours the following variables:

	${PREFIX}		- The prefix under which all installation takes place
	${SHAREDIR}		- Shared resources (documentation and examples)
	${DOCDIR}		- Documentation
	${EXAMPLEDIR}	- Examples
	${_MANDIR}		- Manpages

Each of these may be overridden individually. The default value for ${PREFIX}
is /usr/local. See the Makefiles for details of how these are used.

