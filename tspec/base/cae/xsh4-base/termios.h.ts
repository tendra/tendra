# $Id$

# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "cae/xpg3", "termios.h.ts" ;

/*
 * TODO: unsure of the type for these. posix/termios.h.ts has them as int:
 *
 * +CONST tcflag_t BRKINT, ICRNL, IGNBRK, IGNCR, IGNPAR, INLCR ;
 * +CONST tcflag_t INPCK, ISTRIP, IUCLC, IXANY, IXOFF, IXON, PARMRK ;
 *
 * +CONST tcflag_t OPOST, OLCUC, ONLCR, OCRNL, ONOCR, ONLRET ;
 * +CONST tcflag_t OFILL, NLDLY, CRDLY, TABDLY, BSDLY, VTDLY, FFDLY ;
 */

/*
 * XXX: tcsetattr() and <termios.h> pages disagree on 'const', we align with POSIX
 * +FUNC int tcsetattr ( int, int, struct termios * ) ;
 */

