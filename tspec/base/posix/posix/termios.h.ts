# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


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

+CONST int VEOF, VEOL, VERASE, VINTR, VKILL, VMIN, VQUIT, VSTART, VSTOP ;
+CONST int VSUSP, VTIME ;

+CONST int BRKINT, ICRNL, IGNBRK, IGNCR, IGNPAR, INLCR, INPCK, ISTRIP ;
+CONST int IXOFF, IXON, PARMRK, OPOST ;

+CONST int B0, B50, B75, B110, B134, B150, B200, B300, B600, B1200, B1800 ;
+CONST int B2400, B4800, B9600, B19200, B38400 ;

+CONST int CSIZE, CS5, CS6, CS7, CS8, CSTOPB, CREAD, PARENB, PARODD ;
+CONST int HUPCL, CLOCAL ;

+CONST int ECHO, ECHOE, ECHOK, ECHONL, ICANON, IEXTEN, ISIG, NOFLSH, TOSTOP ;

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
+FUNC int tcsendbreak ( int, int ) ;
+FUNC int tcsetattr ( int, int, const struct termios * ) ;
