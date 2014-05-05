# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IFNDEF C_IRUSR
+DEFINE C_IRUSR		%% 0000400 %% ;
+DEFINE C_IWUSR		%% 0000200 %% ;
+DEFINE C_IXUSR		%% 0000100 %% ;
+DEFINE C_IRGRP		%% 0000040 %% ;
+DEFINE C_IWGRP		%% 0000020 %% ;
+DEFINE C_IXGRP		%% 0000010 %% ;
+DEFINE C_IROTH		%% 0000004 %% ;
+DEFINE C_IWOTH		%% 0000002 %% ;
+DEFINE C_IXOTH		%% 0000001 %% ;
+DEFINE C_ISUID		%% 0004000 %% ;
+DEFINE C_ISGID		%% 0002000 %% ;
+DEFINE C_ISVTX		%% 0001000 %% ;
+DEFINE C_ISDIR		%% 0040000 %% ;
+DEFINE C_ISFIFO	%% 0010000 %% ;
+DEFINE C_ISREG		%% 0100000 %% ;
+DEFINE C_ISBLK		%% 0060000 %% ;
+DEFINE C_ISCHR		%% 0020000 %% ;
+DEFINE C_ISCTG		%% 0110000 %% ;
+DEFINE C_ISLNK		%% 0120000 %% ;
+DEFINE C_ISSOCK	%% 0140000 %% ;
+DEFINE MAGIC		%% "070707" %% ;
+ENDIF
