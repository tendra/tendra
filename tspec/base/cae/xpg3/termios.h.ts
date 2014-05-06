# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix", "termios.h.ts" ;

+CONST int BSDLY, BS0, BS1, CRDLY, CR0, CR1, CR2, CR3, FFDLY, FF0, FF1 ;
+CONST int IUCLC, IXANY, NLDLY, NL0, NL1, OFDEL, OFILL, OLCUC, ONLCR ;
+CONST int ONLRET, ONOCR, TABDLY, TAB0, TAB1, TAB2, TAB3, VTDLY, VT0 ;
+CONST int VT1, XCASE ;

+CONST int OCRNL ;

%%
/*
    These values are optional :

    CBAUD, DEFECHO, ECHOCTL, ECHOKE, ECHOPRT, EXTA, EXTB, FLUSHO,
    LOBLK, PENDIN, SWTCH, VDISCARD, VDSUSP, VLNEXT, VREPRINT,
    VSTATUS, VWERASE
*/
%%
