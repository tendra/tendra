# OS-Dependent support

The osdep directory contains machine-dependent support.
See <http://www.tendra.org/> for details.

libtsl - TDF Support Library

    libtdf              containing a support library certain aspects of
                        TDF (such as 64 bits integers);

Libtdf provides basic arithmetic functions for types that the
target cpu doesn't have straight-forward assembly instructions for.


provides software implementations of TDF functions for things which target CPUs do not provide natively
e.g. 64-bit arithmetic

similar concepts: libgcc, crt0

historically known as libtdf, but renamed

depends on:
    tpl
    tcc (for -Fj), and therefore machine-specific envs
    C producer
    installers, for .j -> .o
    ar(1), for tendra.lib.mk
    so .: everything needed for normal compilation - just not running - of TDF
    so i think this is the last step to build and install


