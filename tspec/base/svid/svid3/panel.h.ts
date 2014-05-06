# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;
+IF %% __SYSV_TERMINAL_INTERFACE %%
+USE "svid/svid3", "curses.h.ts" ;

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
