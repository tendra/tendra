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
+IMPLEMENT "posix", "termios.h" ;

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
