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
+USE "svid3", "eti.h" ;

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
