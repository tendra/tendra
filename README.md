
# The TenDRA Project

http://www.tendra.org/

The source tree is organised into several independent programs. These are
intended to be packaged separately, and may be built independently of
each other. See the Orientation Guide [1] for details of how this all
fits together.

The top-level Makefile provided here is a convenience to build everything.
If you just want to try TenDRA out, this is what you're looking for.


## Build Dependencies

 - A BSD compatible make(1)

   This can be any BSD's native make(1). An ancient version of NetBSD's
   make is sometimes packaged as "pmake". There's also sjg's portable
   bmake, which you can get here: http://www.crufty.net/help/sjg/bmake.html

   GNU's gmake uses a completely different syntax, and is not supported.

 - A C compiler

   See shared/mk/tendra.compiler.mk for supported compilers.

 - A supported toolchain

   This should be no problem for any of the supported OSes; their provided
   toolchains will do fine. For Linux and BSDs this is GNU's ld, as, etc.

 - A supported OS, libc and architecture combination

   This is trickier than it sounds. I've been working to make it easier,
   and it's certainly easier than it was, but there's still some way to
   go before you can expect a build to work on an arbitrary platform.

   Architecture:

     In particular there is currently no code generation for
     64-bit platforms (other than Alpha) - so no x86_64, mips64,
     UltraSPARC, 64-bit PA-RISC etc.

     You can see the supported architectures under /trans/src.

   OS:

     TenDRA needs to know not only what the OS is, but also what
     version.

     You can see supported OSes under /osdep/machines.

   libc:

     This where it gets more difficult. The particular version of your
     libc matters due to the version-specific workarounds for various
     non-standard or incorrect things in your system headers.

     You can see the supported libc implementations under /api/libc.

     If your particular libc is not supported, it's straightforward to
     add. However this is something of a dark art, involving figuring
     out where system headers deviate from the various standards TenDRA
     enforces (ANSI, POSIX and so on), and what to do about it which is
     decided case-by-case.

     I've started writing a guide on how to do this. [2]


## I don't care about any of that

I'd suggest using either OpenBSD, FreeBSD or Linux. If you're using Linux,
install pmake.

Look at /shared/mk/tendra.makedefs.mk for some idea of supported
versions, pick one, and try it. Talk to me if it doesn't work. [3]


## Building

Build with:

    % bmake -r

If all goes well, this should give you a working compiler in ./obj.$host-bootstrap/bin

### Building with docker

The Dockerfile defines a base system that can compile the compiler.  You will need
to build the docker image first, but thereafter you can just run it (without the --build
parameter).

To build and run the docker image:
    % ./run-docker.sh --build


## Notes on x86_64

There is currently no code generation for x86_64 assembly. So you can't
produce native x86_64 executables. However, for systems with multilib
support (FreeBSD, Linux), you can build TenDRA such that it will
generate x86_32 executables on an x86_64 system:

    % make TARGETARCH=x32_64
    % ./obj.iona-bootstrap/bin/tcc hello.c

which gives you this:

    % ./a.out
       hello, world
    % uname -sm
       Linux x86_64
    % file a.out
       a.out: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV),
       dynamically linked (uses shared libs), ...
    %

When building for x32_64, you'll need x86_32-compatible libc headers.
For Debian, that's packaged as libc6-dev-i386.

Good luck,

--  
Kate  
kate@tendra.org


[1] Orientation Guide: /doc/doc/developer/guides/orientation  
[2] Porting TenDRA to Different Operating Systems: /osdep/doc/porting  
[3] IRC: #tendra on irc.libera.chat

