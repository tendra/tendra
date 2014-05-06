# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "termios.h.ts" ;
+CONST int NCC | NCC_EXP ;
+NAT ~NCC | NCC ;
+FIELD struct termio {
    unsigned short c_iflag ;
    unsigned short c_oflag ;
    unsigned short c_cflag ;
    unsigned short c_lflag ;
    char c_line ;
    unsigned char c_cc [ ~NCC ] ;
} ;
