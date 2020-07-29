# Lexi

Lexi is a lexical analyser generator.
See <http://www.tendra.org/> for details.


## Building

Lexi itself has no dependencies. To compile, simply "make" should suffice.

To build the documentation manpages depends on:

 * xsltproc from xmlsoft.org
 * The docbook XSLT stylesheets for XHTML and troff manpages
 * Dia for rendering images

It's worth having XML catalogues set up to use docbook-xslt stylesheets,
to save it from fetching everything across the internet.

To build PDF documentation depends on:

 * TeXML from getfo.org/texml
 * ConTeXt e.g. from teTeX

The PDF documentation is not built by default: to build it, "make pdf" from
the doc directory.


At runtime, Lexi has no dependencies other than libc and POSIX.


## Installation

The "install" target honours the following variables:

	${PREFIX}		- The prefix under which all installation takes place
	${SHAREDIR}		- Shared resources (documentation and examples)
	${DOCDIR}		- Documentation
	${EXAMPLEDIR}		- Examples
	${_MANDIR}		- Manpages

Each of these may be overridden individually. The default value for ${PREFIX}
is /usr/local. See the Makefiles for details of how these are used.


## Historical Changes

 - In 1.* versions, a .lct file was not required

