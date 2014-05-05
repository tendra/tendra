# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid3", "sys/types.h.ts" ;
+IMPLEMENT "xpg3", "termios.h.ts" ;
+IMPLEMENT "posix", "unistd.h.ts", "tcpgrp" (!?) ;

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
