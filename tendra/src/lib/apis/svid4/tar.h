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
+DEFINE TMAGIC		%% "ustar" %% ;
+DEFINE TMAGLEN		%% 6 %% ;
+DEFINE TVERSION	%% "00" %% ;
+DEFINE TVERSLEN	%% 2 %% ;

+DEFINE REGTYPE		%% '0' %% ;
+DEFINE AREGTYPE	%% '\0' %% ;
+DEFINE LNKTYPE		%% '1' %% ;
+DEFINE SYMTYPE		%% '2' %% ;
+DEFINE CHRTYPE		%% '3' %% ;
+DEFINE BLKTYPE		%% '4' %% ;
+DEFINE DIRTYPE		%% '5' %% ;
+DEFINE FIFOTYPE	%% '6' %% ;
+DEFINE CONTTYPE	%% '7' %% ;

+DEFINE TSUID		%% 04000 %% ;
+DEFINE TSGID		%% 02000 %% ;
+DEFINE TSVTX		%% 01000 %% ;
+DEFINE TUREAD		%% 00400 %% ;
+DEFINE TUWRITE		%% 00200 %% ;
+DEFINE TUEXEC		%% 00100 %% ;
+DEFINE TGREAD		%% 00040 %% ;
+DEFINE TGWRITE		%% 00020 %% ;
+DEFINE TGEXEC		%% 00010 %% ;
+DEFINE TOREAD		%% 00004 %% ;
+DEFINE TOWRITE		%% 00002 %% ;
+DEFINE TOEXEC		%% 00001 %% ;
