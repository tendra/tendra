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
+USE "svid3", "sys/types.h" ;
+IMPLEMENT "xpg3", "termios.h" ;
+IMPLEMENT "posix", "unistd.h", "tcpgrp" (!?) ;

+FUNC pid_t tcgetsid ( int ) ;

+CONST int VEOL2, VSWTCH, VDSUSP, VREPRINT, VDISCARD, VWERASE, VLNEXT ;
+CONST int IMAXBEL ;
+CONST int CBAUD, CIBAUD, PAREXT ;
+CONST int ECHOCTL, ECHOPRT, ECHOKE, FLUSHO, PENDIN ;

+FIELD struct winsize {
    unsigned short ws_row ;
    unsigned short ws_col ;
    unsigned short ws_xpixel ;
    unsigned short ws_ypixel ;
} ;

+CONST int TIOCM_LE, TIOCM_DTR, TIOCM_RTS, TIOCM_ST, TIOCM_SR ;
+CONST int TIOCM_CTS, TIOCM_CAR, TIOCM_RNG, TIOCM_DSR ;
+DEFINE TIOCM_CD %% TIOCM_CAR %% ;
+DEFINE TIOCM_RI %% TIOCM_RNG %% ;
+CONST int TCGETS, TCSETS, TCSETSW, TCSETSF, TCGETA, TCSETA, TCSETAW ;
+CONST int TCSETAF, TCSBRK, TCXONC, TCFLSH, TIOCGPGRP, TIOCSPGRP, TIOCGSID ;
+CONST int TIOCGWINSZ, TIOCSWINSZ, TIOCMBIS, TIOCMBIC, TIOCMGET, TIOCMSET ;
