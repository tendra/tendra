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

+TYPE FORM, FIELD, FIELDTYPE ;

+CONST int REQ_NEXT_PAGE, REQ_PREV_PAGE, REQ_FIRST_PAGE, REQ_LAST_PAGE ;
+CONST int REQ_NEXT_FIELD, REQ_PREV_FIELD, REQ_FIRST_FIELD, REQ_LAST_FIELD ;
+CONST int REQ_SNEXT_FIELD, REQ_SPREV_FIELD, REQ_SFIRST_FIELD ;
+CONST int REQ_SLAST_FIELD, REQ_LEFT_FIELD, REQ_RIGHT_FIELD, REQ_UP_FIELD ;
+CONST int REQ_DOWN_FIELD, REQ_NEXT_CHAR, REQ_PREV_CHAR, REQ_NEXT_LINE ;
+CONST int REQ_PREV_LINE, REQ_NEXT_WORD, REQ_PREV_WORD, REQ_BEG_FIELD ;
+CONST int REQ_END_FIELD, REQ_BEG_LINE, REQ_END_LINE, REQ_LEFT_CHAR ;
+CONST int REQ_RIGHT_CHAR, REQ_UP_CHAR, REQ_DOWN_CHAR, REQ_NEW_LINE ;
+CONST int REQ_INS_CHAR, REQ_INS_LINE, REQ_DEL_CHAR, REQ_DEL_PREV ;
+CONST int REQ_DEL_LINE, REQ_DEL_WORD, REQ_CLR_EOL, REQ_CLR_EOF ;
+CONST int REQ_CLR_FIELD, REQ_OVL_MODE, REQ_INS_MODE, REQ_SCR_FLINE ;
+CONST int REQ_SCR_BLINE, REQ_SCR_FPAGE, REQ_SCR_BPAGE, REQ_SCR_FHPAGE ;
+CONST int REQ_SCR_BHPAGE, REQ_SCR_FCHAR, REQ_SCR_BCHAR, REQ_SCR_HFLINE ;
+CONST int REQ_SCR_HBLINE, REQ_SCR_HFHALF, REQ_SCR_HBHALF, REQ_VALIDATION ;
+CONST int REQ_NEXT_CHOICE, REQ_PREV_CHOICE ;

+CONST int NO_JUSTIFICATION, JUSTIFY_RIGHT, JUSTIFY_LEFT, JUSTIFY_CENTER ;

+CONST OPTIONS O_VISIBLE, O_ACTIVE, O_PUBLIC, O_EDIT, O_WRAP, O_BLANK ;
+CONST OPTIONS O_AUTOSKIP, O_NULLOK, O_STATIC, O_PASSOK ;
+CONST OPTIONS O_NL_OVERLOAD, O_BS_OVERLOAD ;

+CONST FIELDTYPE *TYPE_ALNUM, *TYPE_ALPHA, *TYPE_ENUM, *TYPE_INTEGER ;
+CONST FIELDTYPE *TYPE_NUMERIC, *TYPE_REGEXP ;

+FUNC int pos_form_cursor ( FORM * ) ;
+FUNC int data_ahead ( FORM * ) ;
+FUNC int data_behind ( FORM * ) ;
+FUNC int form_driver ( FORM *, int ) ;
+FUNC int set_form_fields ( FORM *, FIELD ** ) ;
+FUNC FIELD **form_fields ( FORM * ) ;
+FUNC int field_count ( FORM * ) ;
+FUNC int move_field ( FIELD *, int, int ) ;
+FUNC int set_field_fore ( FIELD *, chtype ) ;
+FUNC chtype field_fore ( FIELD * ) ;
+FUNC int set_field_back ( FIELD *, chtype ) ;
+FUNC chtype field_back ( FIELD * ) ;
+FUNC int set_field_pad ( FIELD *, int ) ;
+FUNC int field_pad ( FIELD * ) ;
+FUNC int set_field_buffer ( FIELD *, int, char * ) ;
+FUNC char *field_buffer ( FIELD *, int ) ;
+FUNC int set_field_status ( FIELD *, int ) ;
+FUNC int field_status ( FIELD * ) ;
+FUNC int set_max_field ( FIELD *, int ) ;
+FUNC int field_info ( FIELD *, int *, int *, int *, int *, int *, int * ) ;
+FUNC int dynamic_field_info ( FIELD *, int *, int *, int * ) ;
+FUNC int set_field_just ( FIELD *, int ) ;
+FUNC int field_just ( FIELD * ) ;
+FUNC FIELD *new_field ( int, int, int, int, int, int ) ;
+FUNC FIELD *dup_field ( FIELD *, int, int ) ;
+FUNC FIELD *link_field ( FIELD *, int, int ) ;
+FUNC int free_field ( FIELD * ) ;
+FUNC int set_field_opts ( FIELD *, OPTIONS ) ;
+FUNC int field_opts_on ( FIELD *, OPTIONS ) ;
+FUNC int field_opts_off ( FIELD *, OPTIONS ) ;
+FUNC OPTIONS field_opts ( FIELD * ) ;
+FUNC int set_field_userptr ( FIELD *, char * ) ;
+FUNC char *field_userptr ( FIELD * ) ;
+FUNC int set_field_type ( FIELD *, FIELDTYPE *, ... ) ;
+FUNC FIELDTYPE *field_type ( FIELD * ) ;
+FUNC char *field_arg ( FIELD * ) ;
+FUNC FIELDTYPE *new_fieldtype ( int (*) (), int (*) () ) ;
+FUNC int free_fieldtype ( FIELDTYPE * ) ;
+FUNC int set_fieldtype_arg ( FIELDTYPE *, char * (*) (), char * (*) (),
			      void (*) () ) ;
+FUNC FIELDTYPE *link_fieldtype ( FIELDTYPE *, FIELDTYPE * ) ;
+FUNC int set_form_init ( FORM *, void (*) () ) ;
+FUNC int set_form_term ( FORM *, void (*) () ) ;
+FUNC int set_field_init ( FORM *, void (*) () ) ;
+FUNC int set_field_term ( FORM *, void (*) () ) ;
+TYPEDEF void ( *~form_fn ) () ;
+FUNC ~form_fn form_init ( FORM * ) ;
+FUNC ~form_fn form_term ( FORM * ) ;
+FUNC ~form_fn field_init ( FORM * ) ;
+FUNC ~form_fn field_term ( FORM * ) ;
+FUNC FORM *new_form ( FIELD ** ) ;
+FUNC int free_form ( FORM * ) ;
+FUNC int set_new_page ( FIELD *, int ) ;
+FUNC int new_page ( FIELD * ) ;
+FUNC int set_form_opts ( FORM *, OPTIONS ) ;
+FUNC int form_opts_on ( FORM *, OPTIONS ) ;
+FUNC int form_opts_off ( FORM *, OPTIONS ) ;
+FUNC OPTIONS form_opts ( FORM * ) ;
+FUNC int set_form_page ( FORM *, int ) ;
+FUNC int form_page ( FORM * ) ;
+FUNC int set_current_field ( FORM *, FIELD * ) ;
+FUNC FIELD *current_field ( FORM * ) ;
+FUNC int field_index ( FIELD * ) ;
+FUNC int post_form ( FORM * ) ;
+FUNC int unpost_form ( FORM * ) ;
+FUNC int set_form_usrptr ( FORM *, char * ) ;
+FUNC char *form_usrptr ( FORM * ) ;
+FUNC int set_form_win ( FORM *, WINDOW * ) ;
+FUNC WINDOW *form_win ( FORM * ) ;
+FUNC int set_form_sub ( FORM *, WINDOW * ) ;
+FUNC WINDOW *form_sub ( FORM * ) ;
+FUNC int scale_form ( FORM *, int *, int * ) ;

+ENDIF
