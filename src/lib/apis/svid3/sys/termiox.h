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
