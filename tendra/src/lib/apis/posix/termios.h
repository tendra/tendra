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
