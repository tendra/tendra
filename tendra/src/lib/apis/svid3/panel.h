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
+USE "svid3", "", "config" ;
+IF %% __SYSV_TERMINAL_INTERFACE %%
+USE "svid3", "curses.h" ;

+TYPE PANEL ;

+FUNC PANEL *panel_above ( PANEL * ) ;
+FUNC PANEL *panel_below ( PANEL * ) ;
+FUNC int move_panel ( PANEL *, int, int ) ;
+FUNC PANEL *new_panel ( WINDOW * ) ;
+FUNC int del_panel ( PANEL * ) ;
+FUNC int show_panel ( PANEL * ) ;
+FUNC int hide_panel ( PANEL * ) ;
+FUNC int panel_hidden ( PANEL * ) ;
+FUNC void update_panels ( void ) ;
+FUNC int set_panel_useptr ( PANEL *, char * ) ;
+FUNC char *panel_useptr ( PANEL * ) ;
+FUNC WINDOW *panel_window ( PANEL * ) ;
+FUNC int replace_panel ( PANEL *, WINDOW * ) ;

+ENDIF
