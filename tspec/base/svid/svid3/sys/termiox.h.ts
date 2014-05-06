# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+CONST int NFF | NFF_EXP ;
+NAT ~NFF | NFF ;
+TYPE struct termiox ;
+FIELD struct termiox {
    unsigned short x_hflag ;
    unsigned short x_cflag ;
    unsigned short x_rflag [ ~NFF ] ;
    unsigned short x_sflag ;
} ;

+DEFINE RTSXOFF		%% 0000001 %% ;
+DEFINE CTSXON		%% 0000002 %% ;
+DEFINE DTRXOFF		%% 0000004 %% ;
+DEFINE CDXON		%% 0000010 %% ;
+DEFINE ISXOFF		%% 0000010 %% ;
+DEFINE XMTCLK		%% 0000007 %% ;
+DEFINE XCIBRG		%% 0000000 %% ;
+DEFINE XCTSET		%% 0000001 %% ;
+DEFINE XCRSET		%% 0000002 %% ;
+DEFINE RCVCLK		%% 0000070 %% ;
+DEFINE RCIBRG		%% 0000000 %% ;
+DEFINE RCTSET		%% 0000010 %% ;
+DEFINE RCRSET		%% 0000010 %% ;
+DEFINE TSETCLK		%% 0000700 %% ;
+DEFINE TSETCOFF	%% 0000000 %% ;
+DEFINE TSETCRBRG	%% 0000100 %% ;
+DEFINE TSETCTBRG	%% 0000200 %% ;
+DEFINE TSETCTSET	%% 0000300 %% ;
+DEFINE TSETCRSET	%% 0000400 %% ;
+DEFINE RSETCLK		%% 0007000 %% ;
+DEFINE RSETCOFF	%% 0000000 %% ;
+DEFINE RSETCRBRG	%% 0001000 %% ;
+DEFINE RSETCTBRG	%% 0002000 %% ;
+DEFINE RSETCTSET	%% 0003000 %% ;
+DEFINE RSETCRSET	%% 0004000 %% ;

+CONST int TCGETX, TCSETX, TCSETXW, TCSETXF ;
