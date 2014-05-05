# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "posix", "sys/types.h.ts", "pid_t" ;

+TYPE ( unsigned ) cc_t, ( unsigned ) speed_t, ( unsigned ) tcflag_t ;

+TYPE struct termios ;
+CONST int NCCS | NCCS_EXP ;
+NAT ~NCCS | NCCS ;
+FIELD struct termios {
    tcflag_t c_iflag ;
    tcflag_t c_oflag ;
    tcflag_t c_cflag ;
    tcflag_t c_lflag ;
    cc_t c_cc [ ~NCCS ] ;
} ;

+CONST int VEOF, VEOL, VERASE, VINTR, VKILL, VMIN, VQUIT ;
+CONST int VSTART, VSTOP, VSUSP, VTIME ;

+CONST tcflag_t BRKINT, ICRNL, IGNBRK, IGNCR, IGNPAR, INLCR ;
+CONST tcflag_t INPCK, ISTRIP, IUCLC, IXANY, IXOFF, IXON, PARMRK ;

+CONST tcflag_t OPOST, OLCUC, ONLCR, OCRNL, ONOCR, ONLRET ;
+CONST tcflag_t OFILL, NLDLY, CRDLY, TABDLY, BSDLY, VTDLY, FFDLY ;

+CONST int NL0, NL1, CR0, CR1, CR2, CR3, TAB0, TAB1, TAB2, TAB3 ;
+CONST int BS0, BS1, VT0, VT1, FF0, FF1 ;

+CONST speed_t B0, B50, B75, B110, B134, B150, B200, B300, B600 ;
+CONST speed_t B1200, B1800, B2400, B4800, B9600, B19200, B38400 ;

+CONST tcflag_t CSIZE, CSTOPB, CREAD, PARENB ;
+CONST tcflag_t PARODD, HUPCL, CLOCAL ;

+CONST int CS5, CS6, CS7, CS8 ;

+CONST tcflag_t ECHO, ECHOE, ECHOK, ECHONL, ICANON ;
+CONST tcflag_t IEXTEN, ISIG, NOFLSH, TOSTOP, XCASE ;

+CONST int TCSANOW, TCSADRAIN, TCSAFLUSH ;
+CONST int TCIFLUSH, TCOFLUSH, TCIOFLUSH ;
+CONST int TCIOFF, TCION, TCOOFF, TCOON ;

+FUNC speed_t cfgetispeed ( const struct termios * ) ;
+FUNC speed_t cfgetospeed ( const struct termios * ) ;
+FUNC int cfsetispeed ( struct termios *, speed_t ) ;
+FUNC int cfsetospeed ( struct termios *, speed_t ) ;
+FUNC int tcdrain ( int ) ;
+FUNC int tcflow ( int, int ) ;
+FUNC int tcflush ( int, int ) ;
+FUNC int tcgetattr ( int, struct termios * ) ;
+FUNC pid_t tcgetsid ( int ) ;
+FUNC int tcsendbreak ( int, int ) ;

# tcsetattr() and <termios.h> pages disagree on 'const', we align with POSIX
+FUNC int tcsetattr ( int, int, const struct termios * ) ;
