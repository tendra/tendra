# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;

+IF %% __SYSV_TERMINAL_INTERFACE %%

+USE "svid/svid3", "curses.h.ts" ;
+USE "svid/svid3", "eti.h.ts" ;

+TYPE MENU, ITEM ;

+CONST int REQ_LEFT_ITEM, REQ_RIGHT_ITEM, REQ_UP_ITEM, REQ_DOWN_ITEM ;
+CONST int REQ_SCR_ULINE, REQ_SCR_DLINE, REQ_SCR_DPAGE, REQ_SCR_UPAGE ;
+CONST int REQ_FIRST_ITEM, REQ_LAST_ITEM, REQ_NEXT_ITEM, REQ_PREV_ITEM ;
+CONST int REQ_TOGGLE_ITEM, REQ_CLEAR_PATTERN, REQ_BACK_PATTERN ;
+CONST int REQ_NEXT_MATCH, REQ_PREV_MATCH ;

+CONST OPTIONS O_SELECTABLE ;
+CONST OPTIONS O_ONEVALUE, O_SHOWDESC, O_ROWMAJOR, O_IGNORECASE ;
+CONST OPTIONS O_SHOWMATCH, O_NONCYCLIC ;

+FUNC int set_menu_fore ( MENU *, chtype ) ;
+FUNC chtype menu_fore ( MENU * ) ;
+FUNC int set_menu_back ( MENU *, chtype ) ;
+FUNC chtype menu_back ( MENU * ) ;
+FUNC int set_menu_grey ( MENU *, chtype ) ;
+FUNC chtype menu_grey ( MENU * ) ;
+FUNC int set_menu_pad ( MENU *, int ) ;
+FUNC int menu_pad ( MENU * ) ;

+FUNC int pos_menu_cursor ( MENU * ) ;

+FUNC int menu_driver ( MENU *, int ) ;

+FUNC int set_menu_format ( MENU *, int, int ) ;
+FUNC void menu_format ( MENU *, int *, int * ) ;

+FUNC int set_item_init ( MENU *, void (*) () ) ;
+FUNC int set_item_term ( MENU *, void (*) () ) ;
+FUNC int set_menu_init ( MENU *, void (*) () ) ;
+FUNC int set_menu_term ( MENU *, void (*) () ) ;
+TYPEDEF void ( *~menu_fn ) () ;
+FUNC ~menu_fn item_init ( MENU * ) ;
+FUNC ~menu_fn item_term ( MENU * ) ;
+FUNC ~menu_fn menu_init ( MENU * ) ;
+FUNC ~menu_fn menu_term ( MENU * ) ;

+FUNC int set_current_item ( MENU *, ITEM * ) ;
+FUNC ITEM *current_item ( MENU * ) ;
+FUNC int set_top_row ( MENU *, int ) ;
+FUNC int top_row ( MENU * ) ;
+FUNC int item_index ( ITEM * ) ;
+FUNC char *item_name ( ITEM * ) ;
+FUNC char *item_description ( ITEM * ) ;

+FUNC ITEM *new_item ( char *, char * ) ;
+FUNC int free_item ( ITEM * ) ;

+FUNC int set_item_opts ( ITEM *, OPTIONS ) ;
+FUNC int item_opts_on ( ITEM *, OPTIONS ) ;
+FUNC int item_opts_off ( ITEM *, OPTIONS ) ;
+FUNC OPTIONS item_opts ( ITEM * ) ;

+FUNC int set_item_userptr ( ITEM *, char * ) ;
+FUNC char *item_userptr ( ITEM * ) ;

+FUNC int set_item_value ( ITEM *, int ) ;
+FUNC int item_value ( ITEM * ) ;

+FUNC int item_visible ( ITEM * ) ;

+FUNC int set_menu_items ( MENU *, ITEM ** ) ;
+FUNC ITEM **menu_items ( MENU * ) ;
+FUNC int item_count ( MENU * ) ;

+FUNC int set_menu_mark ( MENU *, char * ) ;
+FUNC char *menu_mark ( MENU * ) ;

+FUNC MENU *new_menu ( ITEM ** ) ;
+FUNC int free_menu ( MENU * ) ;

+FUNC int set_menu_opts ( MENU *, OPTIONS ) ;
+FUNC int item_menu_on ( MENU *, OPTIONS ) ;
+FUNC int item_menu_off ( MENU *, OPTIONS ) ;
+FUNC OPTIONS menu_opts ( MENU * ) ;

+FUNC int set_menu_pattern ( MENU *, char * ) ;
+FUNC char *menu_pattern ( MENU * ) ;

+FUNC int post_menu ( MENU * ) ;
+FUNC int unpost_menu ( MENU * ) ;

+FUNC int set_menu_useptr ( MENU *, char * ) ;
+FUNC char *menu_useptr ( MENU * ) ;

+FUNC int set_menu_win ( MENU *, WINDOW * ) ;
+FUNC WINDOW *menu_win ( MENU * ) ;
+FUNC int set_menu_sub ( MENU *, WINDOW * ) ;
+FUNC WINDOW *menu_sub ( MENU * ) ;
+FUNC int scale_window ( MENU *, int *, int * ) ;

+ENDIF
